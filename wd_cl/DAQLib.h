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
            std::cv_status status = fHasData.wait_for(lock,std::chrono::milliseconds(100));
            if(status == std::cv_status::timeout) {
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

      //Getters
      unsigned int GetMaxSize(){ return fMaxSize; }
      std::string  GetName(){ return fName; }
      float GetOccupancy(){ return fEvents.size() *1./fMaxSize; }//NOTE: only for monitoring

      //Constructor  
      DAQBuffer(unsigned int maxsize = 0, std::string name = "NEWBUFFER"){ 
         fMaxSize = maxsize;
         fName = name;
      }

      //Destructor
      ~DAQBuffer(){
      }

};

// --- DAQ Thread --- basic thread wrapper
class DAQThread{
   private:
      std::thread fThread;
      std::chrono::high_resolution_clock::duration fMinLoopDuration; //allows to avoid polling too much
      std::chrono::high_resolution_clock::duration fLastLoopDuration; //for monitoring
      volatile bool fStop;
      volatile bool fRunning;
      bool fRunning_old;

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
            std::chrono::high_resolution_clock::time_point loopEnd = std::chrono::high_resolution_clock::now();

            //run end of run
            if(shouldEnd) End();

            fLastLoopDuration = loopEnd - loopStart;
            if(fLastLoopDuration<fMinLoopDuration){
               //need to slow down
               std::this_thread::sleep_for(fMinLoopDuration-fLastLoopDuration);
            }
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
         return fRunning;
      }

      std::chrono::microseconds GetLastLoopDuration(){
         return std::chrono::duration_cast<std::chrono::microseconds>(fLastLoopDuration);
      }

      //setter
      void SetMinLoopDuration(std::chrono::microseconds d){fMinLoopDuration = std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(d); }

      //Constructor
      DAQThread(){
         fStop = false;
         fRunning = false;
         fRunning_old = false;
         fMinLoopDuration = std::chrono::high_resolution_clock::duration::zero();
         fLastLoopDuration = std::chrono::high_resolution_clock::duration::zero();
      }

      //Destructor
      virtual ~DAQThread(){
         Stop();
      }
};

// --- DAQ Network Thread --- thread with socket functionalities
#define MAXUDPSIZE 1800
class DAQServerThread : public DAQThread{
   private:
      int fDataSocket;
      volatile int fServerPort;
      unsigned char fDatagramBuffer[MAXUDPSIZE];
      int fDatagramSize;

      //reserved Methods
      void Setup(){
         //create socket
         struct sockaddr_in server_addr;
         fDataSocket = socket(AF_INET, SOCK_DGRAM, 0);
         if(fDataSocket == 0){
            throw std::runtime_error(std::string("Cannot create socket"));
         }
      
	 // increase receive buffer size
	 int rcvBufferSizeSet = 4*1024*1024; // 4 MB
	 int rcvBufferSizeGet;
	 socklen_t sockOptSize = sizeof(rcvBufferSizeGet);
      
	 getsockopt(fDataSocket, SOL_SOCKET, SO_RCVBUF, &rcvBufferSizeGet, &sockOptSize);
	 if (rcvBufferSizeGet < 2*rcvBufferSizeSet) {
	   setsockopt(fDataSocket, SOL_SOCKET, SO_RCVBUF, &rcvBufferSizeSet, sizeof(rcvBufferSizeSet));
	   getsockopt(fDataSocket, SOL_SOCKET, SO_RCVBUF, &rcvBufferSizeGet, &sockOptSize);
	 }
  

         int flags = fcntl(fDataSocket, F_GETFL, 0);
         fcntl(fDataSocket, F_SETFL, flags | O_NONBLOCK);

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

      }

      void Loop(){

         struct sockaddr_in client_addr;
         socklen_t sockaddr_in_len = sizeof(client_addr);
	 
         fDatagramSize = (int) recvfrom(fDataSocket, (char*) fDatagramBuffer, sizeof(fDatagramBuffer), 0, 
					(struct sockaddr *)&client_addr, (socklen_t *)&sockaddr_in_len);

         if(fDatagramSize==-1){
            if(errno != EWOULDBLOCK){
               perror("recvfrom");
               throw std::runtime_error(std::string("Cannot recvfrom"));
            } else {
               //nothing to read
               return ;
            }
         }

         if(fDatagramSize>0){
            //produce
            GotData(fDatagramSize, fDatagramBuffer);
         }
      }


      void Close(){
         close(fDataSocket);
      }

      //to be implemented in derived class to setup functionalities
      virtual void GotData(int size, unsigned char *data) { };

   public:
      //Methods

      //Getter
      int GetServerPort(){ return fServerPort; }

      //Constructor
      DAQServerThread(){
         fDataSocket = -1;
         fServerPort = -1;
         fDatagramSize = 0;
      }

      //Destructor
      virtual ~DAQServerThread(){
      }
};

#endif
