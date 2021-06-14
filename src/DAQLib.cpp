#include "DAQLib.h"
// --- DAQ Alarm --- Thread safe alarm system
// Resize internal vectors
void DAQAlarm::Resize(unsigned int size){
   fAlarmTriggered.resize(size);
   fAlarmCallback.resize(size);
   fAlarmDescription.resize(size);
   for(unsigned int i = 0; i<size; i++)
      fAlarmCallback[i] = nullptr;
}
// lockless check of alarm state
bool DAQAlarm::Test(unsigned int id) const {
   if( id < fAlarmTriggered.size() )
      return fAlarmTriggered[id];
   else
      return false;
}

//triggers an alarm
void DAQAlarm::Trigger(unsigned int id){
   if( id < fAlarmTriggered.size() ){
      //locks
      std::unique_lock<std::mutex> lock(fAccessMutex);

      //only set if not previously fired
      if (!fAlarmTriggered[id]){
         fAlarmTriggered[id] = true;
         //release the lock and call the callback
         lock.unlock();
         if(fAlarmCallback[id] != nullptr)
            fAlarmCallback[id](id, "");
      }
   }
}

//resets an alarm
void DAQAlarm::Reset(unsigned int id){
   if( id < fAlarmTriggered.size() ){
      //locks
      std::lock_guard<std::mutex> lock(fAccessMutex);

      fAlarmTriggered[id] = false;
   }
}

//resets all alarms at once
void DAQAlarm::Clean(){
   //locks
   std::lock_guard<std::mutex> lock(fAccessMutex);

   for (auto a: fAlarmTriggered)
      a = false;
}


//get the alarm description
std::string DAQAlarm::GetDescription(unsigned int id){
   //locks
   std::lock_guard<std::mutex> lock(fAccessMutex);

   //retrieve the description
   if( id < fAlarmDescription.size() )
      return fAlarmDescription[id];
   else
      return "";
   
}

//Trigger alarm including a description
void DAQAlarm::Trigger(unsigned int id, const std::string &description){
   //locks
   std::unique_lock<std::mutex> lock(fAccessMutex);

   //only set if not previously fired
   if (!fAlarmTriggered[id]){
      fAlarmTriggered[id] = true;
      //copy the description
      if( id < fAlarmDescription.size() )
         fAlarmDescription[id] = description;

      //release the lock and call the callback
      lock.unlock();
      if(fAlarmCallback[id] != nullptr)
         fAlarmCallback[id](id, description);
   }
}

void DAQAlarm::SetCallback(unsigned int id, callback_t callback){
   if( id < fAlarmCallback.size() )
      fAlarmCallback[id] = callback;
}

// --- DAQ Buffer Base --- virtual class for buffer interface functions
DAQBufferBase::DAQBufferBase(DAQSystem* parent, std::string name){
   fName = name;
   if(parent != nullptr) parent->AddBuffer(this);
}

// --- DAQ Thread --- basic thread wrapper
//static variable to assign unique thread id
std::atomic<unsigned int> DAQThread::fThreadCount(0);

// thread loop
void DAQThread::ThreadMain(){
   //if pthread is enabled lock the threads to CPU cores
#ifndef __APPLE__
   pthread_t thread = pthread_self();
   cpu_set_t cpuset;

   CPU_ZERO(&cpuset);
   CPU_SET(fThreadId % std::thread::hardware_concurrency(), &cpuset);
   pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
   pthread_setname_np(thread, fThreadName.c_str());
#endif

   Setup();

   while(fStop != true){

      bool shouldEnd = false;
      //checks and run begin of run
      if(fRunning && !fRunning_old) Begin();
      //checks end of run
      if(!fRunning && fRunning_old) shouldEnd = true;
      fRunning_old = fRunning;

      //timed loop
      //std::chrono::high_resolution_clock::time_point loopStart = std::chrono::high_resolution_clock::now();
      if(fRunning && fRunning_old) Loop();
      else std::this_thread::sleep_for(fIdleLoopDuration);
      //std::chrono::high_resolution_clock::time_point loopEnd = std::chrono::high_resolution_clock::now();

      //run end of run
      if(shouldEnd) End();

   }

   Close();

   //acknowledge thread stop
   fStarted = false;
}

//thread start
void DAQThread::Start(){ 
   //TODO: check thread is not already started
   fStarted = true;
   fThread = std::thread([=] { ThreadMain(); });
   fThread.detach();
}

//thread stop
void DAQThread::Stop(){
   fStop = true;
}

//transition to run
void DAQThread::GoRun(){
   fRunning = true;
}

//transition to pause
void DAQThread::StopRun(){
   fRunning = false;
}

//constructor
DAQThread::DAQThread(DAQSystem* parent, std::string name){
   fStarted = false;
   fStop = false;
   fRunning = false;
   fRunning_old = false;
   fIdleLoopDuration = std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(std::chrono::microseconds(100)); 
   fLastLoopDuration = std::chrono::high_resolution_clock::duration::zero();
   fThreadName = name;
   fSystem = nullptr;

   fThreadId = fThreadCount++;
   if(parent != nullptr) parent->AddThread(this);
}

// --- DAQ Network Thread --- thread with socket functionalities
// Setup Socket
void DAQServerThread::Setup(){
   //create socket
   struct sockaddr_in server_addr;
   fDataSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
   if(fDataSocket == 0){
      throw std::runtime_error(std::string("Cannot create socket"));
   }

   //set SO_REUSEADDR
   int ret;
   int one = 1;
#ifdef SO_REUSEADDR
	ret = setsockopt(fDataSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&one, sizeof(one));
   if(ret < 0) {
      throw std::runtime_error(std::string("Cannot set SO_REUSEADDR"));
   }
#endif

   //set SO_REUSEPORT
#ifdef SO_REUSEPORT
   one = 1;
	ret = setsockopt(fDataSocket, SOL_SOCKET, SO_REUSEPORT, (char *)&one, sizeof(one));
   if(ret < 0) {
      throw std::runtime_error(std::string("Cannot set SO_REUSEADDR"));
   }
#endif

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

   //bind
   memset((char*)&server_addr, 0, sizeof(server_addr));
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(fServerPort);
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

//wait for data to produce
void DAQServerThread::Loop(){
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

DAQServerThread::DAQServerThread(int buffersize, DAQSystem* parent, std::string name): DAQThread(parent, name){
   fDataSocket = -1;
   fServerPort = 0; //by default let OS choose server port
   fRecvMsg = 0;
   if(buffersize>0) fBufferSize = buffersize;
   else fBufferSize = 4*1024*1024; //default 4MB

   SetDataWaitDuration(std::chrono::microseconds(100));
}

// --- DAQ System --- grouping of threads and buffers
// starts all threads
void DAQSystem::Start(){
   for(auto t: fThreads) t->Start();
}

// stop all threads
void DAQSystem::Stop(){
   for(auto t: fThreads) t->Stop();
}

// wait all threads acknoowledged start run
void DAQSystem::WaitRunStarted(){
   for(auto t: fThreads){
      while(!t->IsRunning())
         std::this_thread::yield();
   }
}

// wait all threads acknoowledged stop run
void DAQSystem::WaitRunStopped(){
   for(auto t: fThreads){
      while(t->IsRunning())
         std::this_thread::yield();
   }
}

// wait all threads acknoowledged stop
void DAQSystem::WaitStopped(){
   for(auto t: fThreads){
      while(t->IsStarted())
         std::this_thread::yield();
   }
}

// start run
void DAQSystem::GoRun(){
   for(auto t: fThreads) t->GoRun();
}

// stop run
void DAQSystem::StopRun(){
   for(auto t: fThreads) t->StopRun();
}

// clean all buffers
void DAQSystem::CleanBuffers(){
   for(auto b: fBuffers) b->Clean();
}

// add thread to vector
void DAQSystem::AddThread(DAQThread* thread){
   fThreads.push_back(thread);
   thread->fSystem = this;
}

// add buffer to vector
void DAQSystem::AddBuffer(DAQBufferBase* buffer){
   fBuffers.push_back(buffer);
}

DAQSystem::DAQSystem(){
   fBuffers.clear();
   fThreads.clear();

   fAlarms = new DAQAlarm();
}

DAQSystem::~DAQSystem(){
   //make sure threads are stopped
   Stop();
   WaitStopped();

   //delete threads and buffers
   for(auto b: fBuffers) delete b;
   for(auto t: fThreads) delete t;

   delete fAlarms;

   fBuffers.clear();
   fThreads.clear();
}
