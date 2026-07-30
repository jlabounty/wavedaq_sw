#include "DAQLib.h"

// Explicit rather than relying on <thread> pulling it in: Clean() uses steady_clock.
#include <chrono>
// --- DAQ Alarm --- Thread safe alarm system
// Resize internal vectors
void DAQAlarm::Resize(unsigned int size){
   fAlarmTriggered.reset(new std::atomic<bool>[size]);
   fNAlarms = size;
   fAlarmCallback.resize(size);
   fAlarmDescription.resize(size);
   for(unsigned int i = 0; i<size; i++){
      // std::atomic's default constructor does NOT initialise the value before C++20 and
      // this builds as C++11, so each element must be stored explicitly. Leaving them
      // indeterminate would mean alarms that read as already-triggered at startup and
      // therefore never fire.
      fAlarmTriggered[i].store(false, std::memory_order_relaxed);
      fAlarmCallback[i] = nullptr;
   }
}
// lockless check of alarm state
bool DAQAlarm::Test(unsigned int id) const {
   if( id < fNAlarms )
      return fAlarmTriggered[id].load(std::memory_order_acquire);
   else
      return false;
}

//triggers an alarm
void DAQAlarm::Trigger(unsigned int id){
   if( id < fNAlarms ){
      //locks
      std::unique_lock<std::mutex> lock(fAccessMutex);

      //only set if not previously fired
      if (!fAlarmTriggered[id].load(std::memory_order_relaxed)){
         fAlarmTriggered[id].store(true, std::memory_order_release);
         //release the lock and call the callback
         lock.unlock();
         if(fAlarmCallback[id] != nullptr)
            fAlarmCallback[id](id, "");
      }
   }
}

//resets an alarm
void DAQAlarm::Reset(unsigned int id){
   if( id < fNAlarms ){
      //locks
      std::lock_guard<std::mutex> lock(fAccessMutex);

      fAlarmTriggered[id].store(false, std::memory_order_release);
   }
}

//resets all alarms at once
//
// A note, because this loop is a trap for readers and was misread during review:
//
//   for (auto a : fAlarmTriggered) a = false;     // the previous body
//
// looks like it assigns to a copy and does nothing. With std::vector<bool> it does NOT.
// `*it` yields std::vector<bool>::reference, a proxy, so `auto` deduces the proxy and not
// bool -- and assigning through the copied proxy writes to the underlying bit. Verified:
// the loop cleared the vector correctly. For any non-proxy element type (vector<char>, an
// array) the same loop really would be a no-op, which is what makes it so easy to misjudge.
//
// So alarms did re-arm at each begin_of_run. The rewrite below is for the data race on
// Test(), not to fix a no-op -- see the comment on fAlarmTriggered in DAQLib.h and
// HARDENING.md 2.4.
void DAQAlarm::Clean(){
   //locks
   std::lock_guard<std::mutex> lock(fAccessMutex);

   for (size_t i = 0; i < fNAlarms; i++)
      fAlarmTriggered[i].store(false, std::memory_order_release);
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
   if (id < fNAlarms && !fAlarmTriggered[id].load(std::memory_order_relaxed)){
      fAlarmTriggered[id].store(true, std::memory_order_release);
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

   // Nothing may escape this function.
   //
   // Start() launches ThreadMain in a std::thread, so an exception leaving it calls
   // std::terminate and aborts the whole frontend with no MIDAS message and no clean
   // end-of-run. Several things in the data path throw as a matter of course --
   // "Cannot recvmmsg" on a stray socket error, "Cannot select", the inverted SO_RCVBUF
   // check, std::bad_alloc from pool growth -- and alarm callbacks run on these threads
   // too, so a throw from user code inside one had the same effect.
   //
   // A thread that stops is recoverable and diagnosable; a process that aborts mid-run is
   // neither. Log it, stop this thread, and leave the rest of the system standing.
   // See HARDENING.md 2.4.
   try {
      Setup();

      while(fStop != true){

         bool shouldEnd = false;
         //checks and run begin of run
         if(fRunning && !fRunning_old) Begin();
         //checks end of run
         if(!fRunning && fRunning_old) shouldEnd = true;
         fRunning_old = fRunning;

         //timed loop
         if(fRunning && fRunning_old) Loop();
         else std::this_thread::sleep_for(fIdleLoopDuration);

         //run end of run
         if(shouldEnd) End();

      }

      Close();
   } catch (const std::exception& ex){
      fprintf(stderr, "FATAL: thread %s stopped by an unhandled exception: %s\n",
              fThreadName.c_str(), ex.what());
      AlarmThreadStopped(ex.what());
      fStop = true;
   } catch (...){
      fprintf(stderr, "FATAL: thread %s stopped by an unhandled exception\n",
              fThreadName.c_str());
      AlarmThreadStopped("unknown exception");
      fStop = true;
   }

   //acknowledge thread stop
   fStarted = false;
}

// Raise the library alarm for a thread that has just died, so the containment above is
// visible outside stderr.
//
// Best-effort by construction, and deliberately so: this runs on a thread that is already
// unwinding from an unhandled exception, and a throw from here would escape ThreadMain and
// call std::terminate -- reintroducing exactly the whole-process abort that containment
// exists to prevent. Everything is guarded and nothing propagates.
//
// The system pointer can legitimately be null: Setup() may throw before the thread is
// fully wired up, and DAQThread's default constructor takes parent = nullptr. In that case
// the stderr message above is all there is, which is no worse than before.
void DAQThread::AlarmThreadStopped(const char* what) noexcept {
   try {
      DAQSystem* sys = GetSystem();
      if(sys == nullptr) return;
      DAQAlarm* alarms = sys->GetAlarms();
      if(alarms == nullptr) return;
      alarms->Trigger(DAQLIB_ALARM_THREADSTOPPED,
                      "thread " + fThreadName + " stopped: " + std::string(what));
   } catch (...){
      // Nothing useful left to do, and nothing may leave this function.
   }
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
      fIoVecs[i].iov_base             = fDatagramBuffer[i];
      fIoVecs[i].iov_len              = MAXUDPSIZE;
      fMsgs[i].msg_hdr.msg_name       = &fAddresses[i];
      fMsgs[i].msg_hdr.msg_namelen    = sizeof(sockaddr_in);
      fMsgs[i].msg_hdr.msg_iov        = &fIoVecs[i];
      fMsgs[i].msg_hdr.msg_iovlen     = 1;
      fMsgs[i].msg_hdr.msg_control    = NULL;
      fMsgs[i].msg_hdr.msg_controllen = 0;
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

   //select can generate EINTR "Interrupted function call", it is safe to restart the syscall so we can mimic a timeout
   if(retval == -1 && errno == EINTR){
      retval = 0;
   }

   if (retval == -1)
      throw std::runtime_error(std::string("Cannot select"));
   else if (retval){

      fRecvMsg =  recvmmsg(fDataSocket, fMsgs, MAXMSG, MSG_WAITFORONE, &fTimeout);

      if(fRecvMsg<0){
         throw std::runtime_error(std::string("Cannot recvmmsg"));
      } else if(fRecvMsg>0){
         //produce
         GotData();
      }
   } else {
      //timeout: nothing to read
   }
}

// Discard whatever is sitting in the socket's kernel receive buffer.
//
// Why this exists (was an empty //TODO stub; see HARDENING.md 2.1):
//
// Between runs the collector stops calling Loop() -- ThreadMain only calls it while
// fRunning -- but the board keeps streaming. The kernel buffer therefore fills with
// datagrams belonging to the *previous* run and, once it is full, with truncated ones.
// At begin-of-run the board's event counter is reset to zero, so those leftovers arrive
// at the builder carrying keys far ABOVE the new run's, and nothing can remove them:
//
//   * the reorder purge tests (new_key - old_key) > N, and old_key is much larger;
//   * the map-overflow guard erases the numerically smallest key, which is the
//     brand-new event, not the stale one.
//
// The builder then destroys every new event as it is created, for the rest of the run,
// after emitting a single latching alarm. Draining here removes the trigger entirely.
//
// It cannot simply drain until the socket is empty. A free-running board streams
// continuously at ~10 MB/s, so "empty" may never happen and an unbounded loop would hang
// the run transition. Two bounds, whichever comes first:
//
//   * a wall-clock deadline, since the backlog is what matters and it is finite;
//   * a packet cap, as a second line of defence if the clock misbehaves.
//
// Dropping a few packets of the *new* run along with the backlog is harmless: they form
// at most one incomplete event whose key is adjacent to the ones that follow, which the
// reorder purge removes normally.
//
// Hitting a bound is itself diagnostic -- it means the board is filling the buffer faster
// than we can empty it, so the backlog was not fully cleared -- and is reported.
unsigned long DAQServerThread::Clean(){
   if(fDataSocket < 0) return 0;

   const unsigned long cMaxPackets = 200000;                  // ~2x a full 1 MB buffer
   const auto cDeadline = std::chrono::milliseconds(200);

   unsigned long dropped = 0;
   bool hitBound = false;
   auto start = std::chrono::steady_clock::now();

   while(true){
      int n = recvmmsg(fDataSocket, fMsgs, MAXMSG, MSG_DONTWAIT, nullptr);

      // EAGAIN/EWOULDBLOCK: the buffer is empty, which is the normal exit.
      if(n <= 0) break;

      dropped += n;

      // A short batch means the kernel had nothing more to give us.
      if(n < MAXMSG) break;

      if(dropped >= cMaxPackets ||
         std::chrono::steady_clock::now() - start > cDeadline){
         hitBound = true;
         break;
      }
   }

   // fRecvMsg is used by the GetMessage* helpers to bound their index checks. Leaving it
   // pointing at this drain's batch would let a later caller read datagram buffers that
   // were discarded rather than processed.
   fRecvMsg = 0;

   if(dropped > 0){
      printf("%s: discarded %lu stale datagram(s) from the receive buffer%s\n",
             fThreadName.c_str(), dropped,
             hitBound ? " (hit drain limit -- backlog may remain)" : "");
   }

   return dropped;
}

//return address for given message
char* DAQServerThread::GetMessageSourceAddress(unsigned int id){
   if(id >= fRecvMsg){
      fSrcAddress[0] = '\0';
   } else {
      inet_ntop(AF_INET, &(fAddresses[id].sin_addr), fSrcAddress, INET_ADDRSTRLEN);
   }
   return fSrcAddress;  
}

//return buffer content
unsigned char* DAQServerThread::GetMessageData(unsigned int id){
   if(id >= fRecvMsg){
      // out of range
      return nullptr;
   } else {
      return fDatagramBuffer[id];
   }
}

//return buffer length
unsigned int DAQServerThread::GetMessageSize(unsigned int id){
   if(id >= fRecvMsg){
      // out of range
      return 0;
   } else {
      return fMsgs[id].msg_len;
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
