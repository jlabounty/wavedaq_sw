#include <string>
#include <string.h>
#include <mutex>
#include <queue>
#include <thread>
#include <condition_variable>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

template <class T> class DAQBuffer;
class DAQThread;
class DAQServerThread;

#ifndef DAQLIB_H
#define DAQLIB_H

// --- DAQ Buffer --- thread safe queue with max size

template <class T> class DAQBuffer {
   private:
      std::queue<T*> fEvents;
      unsigned int fMaxSize;
      std::string fName;
      std::mutex fAccess;
      std::condition_variable fHasData;
      std::chrono::microseconds fLockWaitDuration;

      //reserved Methods

   public:
      //Methods
      bool Try_push(T* data){
         std::lock_guard<std::mutex> lock(fAccess);
         //check size
         if(fEvents.size() < fMaxSize){
            //not full
            fEvents.push(data);
            fHasData.notify_one();
            return true;
         } else {
            //full
            //TODO: add exception
            //printf("BUFFER OVERSIZE");
            return false;
         }
      };
      // pops outs one event if available
      bool Try_pop(T* &ptr){
         std::unique_lock<std::mutex> lock(fAccess);
         //check size
         if(fEvents.size() == 0){
            //no data, wait
            /*std::cv_status status = fHasData.wait_for(lock,std::chrono::milliseconds(100), GetSize());
            if(status == std::cv_status::timeout) {
               lock.unlock();
               return false;
            }*/

            if(fHasData.wait_for(lock, fLockWaitDuration, [&]{return fEvents.size()!=0; }))
            {
               ptr = fEvents.front();
               fEvents.pop();
               lock.unlock();
               return true;
            } else {
               lock.unlock();
               return false;

            }
         }
         ptr = fEvents.front();
         fEvents.pop();
         lock.unlock();
         return true;
      }

      unsigned int GetSize(){
         std::lock_guard<std::mutex> lock(fAccess);

         return fEvents.size();
      }
      void Clean(){
         std::lock_guard<std::mutex> lock(fAccess);

         while(fEvents.size()){
            delete fEvents.front();
            fEvents.pop();
         }

      }

      //Setters
      void SetLockWaitDuration(std::chrono::microseconds d){ fLockWaitDuration = d; }

      //Getters
      unsigned int GetMaxSize(){ return fMaxSize; }
      std::string  GetName(){ return fName; }
      float GetOccupancy(){ return fEvents.size() *1./fMaxSize; }//NOTE: only for monitoring

      //Constructor  
      DAQBuffer(unsigned int maxsize = 0, std::string name = "NEWBUFFER"){ 
         fMaxSize = maxsize;
         fName = name;
         fLockWaitDuration = std::chrono::microseconds(100);
      }

      //Destructor
      ~DAQBuffer(){
      }

};

// --- DAQ Thread --- basic thread wrapper
class DAQThread{
   protected:
      std::chrono::high_resolution_clock::duration fIdleLoopDuration; //allows to avoid polling too much
      std::chrono::high_resolution_clock::duration fLastLoopDuration; //for monitoring
   private:
      std::thread fThread;
      volatile bool fStop;
      volatile bool fRunning;
      volatile bool fRunning_old;

      //reserved Methods
      void ThreadMain(){
         Setup();

         while(fStop != true){

            bool shouldEnd = false;
            //checks and run begin of run
            if(fRunning && !fRunning_old) Begin();
            //checks end of run
            if(!fRunning && fRunning_old) shouldEnd = true;
            fRunning_old = fRunning;

            //timed loop
            std::chrono::high_resolution_clock::time_point loopStart = std::chrono::high_resolution_clock::now();
            if(fRunning && fRunning_old) Loop();
            else std::this_thread::sleep_for(fIdleLoopDuration);
            std::chrono::high_resolution_clock::time_point loopEnd = std::chrono::high_resolution_clock::now();

            //run end of run
            if(shouldEnd) End();

         }

         Close();
      }

      //to be implemented in derived class to setup functionalities
      virtual void Setup(){;} //called before thread Loop
      virtual void Begin(){;} //called before thread Loop
      virtual void Loop(){;}  //called inside thread Loop
      virtual void End(){;} //called before thread Loop
      virtual void Close(){;}  //called at the end of thread Loop

   public:
      //Methods
      void Start(){ 
         fThread = std::thread([=] { ThreadMain(); });
         fThread.detach();
      }
      void Stop(){
         fStop = true;
      }

      void GoRun(){
         fRunning = true;
      }

      void StopRun(){
         fRunning = false;
      }

      bool IsRunning(){
         //if(fRunning_old==false) printf("thread not running\n");
         //else printf("still running\n");
         
         return fRunning_old;
      }

      std::chrono::microseconds GetLastLoopDuration(){
         return std::chrono::duration_cast<std::chrono::microseconds>(fLastLoopDuration);
      }

      //setter
      void SetIdleLoopDuration(std::chrono::microseconds d){fIdleLoopDuration = std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(d); }

      //Constructor
      DAQThread(){
         fStop = false;
         fRunning = false;
         fRunning_old = false;
         //fMinLoopDuration = std::chrono::high_resolution_clock::duration::zero();
         fIdleLoopDuration = std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(std::chrono::microseconds(100)); 
         fLastLoopDuration = std::chrono::high_resolution_clock::duration::zero();
      }

      //Destructor
      virtual ~DAQThread(){
         Stop();
      }
};

// --- DAQ Network Thread --- thread with socket functionalities
#define MAXUDPSIZE 1800
#define MAXMSG 200
class DAQServerThread : public DAQThread{
   private:
      int fDataSocket;
      volatile int fServerPort;
      unsigned char fDatagramBuffer[MAXMSG][MAXUDPSIZE];
      struct mmsghdr fMsgs[MAXMSG];
      struct iovec fIoVecs[MAXMSG];
      int fRecvMsg;
      struct timespec fTimeout;

      int fBufferSize;
      std::chrono::microseconds fDataWaitDuration;

      //reserved Methods
      void Setup(){
         //create socket
         struct sockaddr_in server_addr;
         fDataSocket = socket(AF_INET, SOCK_DGRAM, 0);
         if(fDataSocket == 0){
            throw std::runtime_error(std::string("Cannot create socket"));
         }
      
         // increase receive buffer size
         int rcvBufferSizeSet = fBufferSize;
         int rcvBufferSizeGet;
         socklen_t sockOptSize = sizeof(rcvBufferSizeGet);

         printf("allocating %d bytes\n", fBufferSize);      

         getsockopt(fDataSocket, SOL_SOCKET, SO_RCVBUF, &rcvBufferSizeGet, &sockOptSize);
         printf("initial %d\n", rcvBufferSizeGet);

         if (rcvBufferSizeGet < 2*rcvBufferSizeSet) {
            setsockopt(fDataSocket, SOL_SOCKET, SO_RCVBUF, &rcvBufferSizeSet, sizeof(rcvBufferSizeSet));
            getsockopt(fDataSocket, SOL_SOCKET, SO_RCVBUF, &rcvBufferSizeGet, &sockOptSize);
            printf("final %d\n", rcvBufferSizeGet);
         } else {
            throw std::runtime_error(std::string("Cannot allocate enough memory for kernel buffer"));
         }
  

         //int flags = fcntl(fDataSocket, F_GETFL, 0);
         //fcntl(fDataSocket, F_SETFL, flags | O_NONBLOCK);

         //bind
         memset((char*)&server_addr, 0, sizeof(server_addr));
         server_addr.sin_family = AF_INET;
         server_addr.sin_port = htons(0); // let OS choose port
         server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
         if (::bind(fDataSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
            perror("bind");
            throw std::runtime_error(std::string("Cannot bind socket"));
         }

         //retrieve port
         auto size = sizeof(server_addr);
         getsockname(fDataSocket, (struct sockaddr *) &server_addr, (socklen_t *) &size);
         fServerPort = ntohs(server_addr.sin_port);

         //setup iovecs
         memset(fMsgs, 0, sizeof(fMsgs));
         for (int i = 0; i < MAXMSG; i++) {
            fIoVecs[i].iov_base         = fDatagramBuffer[i];
            fIoVecs[i].iov_len          = MAXUDPSIZE;
            fMsgs[i].msg_hdr.msg_iov    = &fIoVecs[i];
            fMsgs[i].msg_hdr.msg_iovlen = 1;
         }

      }

      void Loop(){
         fd_set rfds;
         int retval;

         fTimeout.tv_sec = fDataWaitDuration.count() / 1000;
         fTimeout.tv_nsec = (fDataWaitDuration.count() % 1000) * 1000;

         FD_ZERO(&rfds);
         FD_SET(fDataSocket, &rfds);

         retval = pselect(FD_SETSIZE, &rfds, NULL, NULL, &fTimeout, NULL);

         if (retval == -1)
            throw std::runtime_error(std::string("Cannot select"));
         else if (retval){

            fRecvMsg =  recvmmsg(fDataSocket, fMsgs, MAXMSG, MSG_WAITFORONE, &fTimeout);

            if(fRecvMsg<0){
               throw std::runtime_error(std::string("Cannot recvmmsg"));
            } else if(fRecvMsg>0){
               //produce
               for(int i=0; i<fRecvMsg; i++){
                  GotData(fMsgs[i].msg_len, fDatagramBuffer[i]);
               }
            }
         } else {
            //timeout: nothing to read

         }

      }


      void Close(){
         close(fDataSocket);
      }

      //to be implemented in derived class to setup functionalities
      virtual void GotData(int size, unsigned char *data) { };

   public:
      //Methods
      void Clean(){
         //TODO: clean fDataSocket kernel buffer
      }


      //Getter
      int GetServerPort(){ return fServerPort; }
      int GetReceivedMessages(){ return fRecvMsg; }

      //Constructor
      DAQServerThread(int buffersize=-1){
         fDataSocket = -1;
         fServerPort = -1;
         fRecvMsg = 0;
         if(buffersize>0) fBufferSize = buffersize;
         else fBufferSize = 4*1024*1024; //default

         SetDataWaitDuration(std::chrono::microseconds(100));
      }

      void SetDataWaitDuration(std::chrono::microseconds d){
         fDataWaitDuration = d;
      }


      //Destructor
      virtual ~DAQServerThread(){
      }
};

#endif
