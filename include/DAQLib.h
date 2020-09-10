#include <string>
#include <string.h>
#include <mutex>
#include <queue>
#include <thread>
#include <condition_variable>
#include <atomic>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

class DAQBufferBase;
template <class T> class DAQBuffer;
class DAQThread;
class DAQServerThread;
class DAQSystem;

#ifndef DAQLIB_H
#define DAQLIB_H

// --- DAQ Buffer Base --- virtual class for buffer interface functions
class DAQBufferBase {
   private:
      std::string fName;
   public:
      std::string  GetName(){ return fName; }

      virtual unsigned int GetSize() = 0;
      virtual void Clean() = 0;
      virtual unsigned int GetMaxSize() = 0;
      virtual float GetOccupancy() = 0;

      DAQBufferBase(DAQSystem* parent, std::string name);
      virtual ~DAQBufferBase(){};
};


// --- DAQ Buffer --- thread safe queue with max size
template <class T> class DAQBuffer : public DAQBufferBase {
   private:
      std::queue<T*> fEvents;
      unsigned int fMaxSize;
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
      float GetOccupancy(){ return fEvents.size() *1./fMaxSize; }//NOTE: only for monitoring

      //Constructor  
      DAQBuffer(unsigned int maxsize = 0, std::string name = "NEWBUFFER", DAQSystem* parent = nullptr): DAQBufferBase(parent, name){ 
         fMaxSize = maxsize;
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
      unsigned int fThreadId;
      static std::atomic<unsigned int> fThreadCount;
   private:
      std::thread fThread;
      volatile bool fStarted;
      volatile bool fStop;
      volatile bool fRunning;
      volatile bool fRunning_old;

      //reserved Methods
      void ThreadMain();

      //to be implemented in derived class to setup functionalities
      virtual void Setup(){;} //called before thread Loop
      virtual void Begin(){;} //called before thread Loop
      virtual void Loop(){;}  //called inside thread Loop
      virtual void End(){;} //called before thread Loop
      virtual void Close(){;}  //called at the end of thread Loop

   public:
      //Methods
      void Start();
      void Stop();

      void GoRun();
      void StopRun();

      bool IsStarted(){
         return fStarted;
      }

      bool IsRunning(){
         return fRunning_old;
      }
      std::chrono::microseconds GetLastLoopDuration(){
         return std::chrono::duration_cast<std::chrono::microseconds>(fLastLoopDuration);
      }

      //setter
      void SetIdleLoopDuration(std::chrono::microseconds d){fIdleLoopDuration = std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(d); }

      //Constructor
      DAQThread(DAQSystem* parent = nullptr);

      //Destructor
      virtual ~DAQThread(){
         Stop();
      }
};

// --- DAQ Network Thread --- thread with socket functionalities
#define MAXUDPSIZE 9000
#define MAXMSG 200
class DAQServerThread : public DAQThread{
   private:

      //define missing stuff for replacing recvmmsg on apple systems
#if __APPLE__
      struct mmsghdr {
         struct msghdr msg_hdr;  /* Message header */
         unsigned int  msg_len;  /* Number of received bytes for header */
      };

#define MSG_WAITFORONE 0
      int recvmmsg(int sockfd, struct mmsghdr *msgvec, unsigned int vlen,
                   unsigned int flags, struct timespec *timeout){
         msgvec[0].msg_len = recvmsg(sockfd, &msgvec[0].msg_hdr, 0);

         return 1;
      }
#endif

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
      void Setup();

      void Loop();


      void Close(){
         close(fDataSocket);
         fServerPort = 0;
      }

      //to be implemented in derived class to setup functionalities
      virtual void GotData(int size, unsigned char *data) { };

   public:
      //Methods
      void Clean(){
         //TODO: clean fDataSocket kernel buffer
      }

      void SetServerPort(int port){
         if(fServerPort==0) fServerPort = port;
      }

      void SetDataWaitDuration(std::chrono::microseconds d){
         fDataWaitDuration = d;
      }

      //Getter
      int GetServerPort(){ return fServerPort; }
      int GetReceivedMessages(){ return fRecvMsg; }

      //Constructor
      DAQServerThread(int buffersize=-1, DAQSystem* parent=nullptr);

      //Destructor
      virtual ~DAQServerThread(){
      }
};

// --- DAQ System --- grouping of threads and buffers
class DAQSystem {
   std::vector<DAQBufferBase*> fBuffers;
   std::vector<DAQThread*> fThreads;

   public:
      //Methods
      void Start();
      void Stop();

      void WaitRunStarted();
      void WaitRunStopped();
      void WaitStopped();

      void GoRun();
      void StopRun();

      void CleanBuffers();

      void AddThread(DAQThread* thread);
      void AddBuffer(DAQBufferBase* buffer);

      //Constructor
      DAQSystem();

      //Destructor
      ~DAQSystem();
      
};

#endif
