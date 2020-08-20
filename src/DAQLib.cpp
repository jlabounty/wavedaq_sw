#include "DAQLib.h"

// --- DAQ Thread --- basic thread wrapper
//static variable to assign unique thread id
std::atomic<unsigned int> DAQThread::fThreadCount(0);

// thread loop
void DAQThread::ThreadMain(){
   //if pthread is enabled lock the threads to CPU cores
#ifdef PTHREAD_SCOPE_SYSTEM
   pthread_t thread = pthread_self();
   cpu_set_t cpuset;

   CPU_ZERO(&cpuset);
   CPU_SET(fThreadId % std::thread::hardware_concurrency(), &cpuset);
   pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
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
      std::chrono::high_resolution_clock::time_point loopStart = std::chrono::high_resolution_clock::now();
      if(fRunning && fRunning_old) Loop();
      else std::this_thread::sleep_for(fIdleLoopDuration);
      std::chrono::high_resolution_clock::time_point loopEnd = std::chrono::high_resolution_clock::now();

      //run end of run
      if(shouldEnd) End();

   }

   Close();
}

//thread start
void DAQThread::Start(){ 
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
DAQThread::DAQThread(){
   fStop = false;
   fRunning = false;
   fRunning_old = false;
   fIdleLoopDuration = std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(std::chrono::microseconds(100)); 
   fLastLoopDuration = std::chrono::high_resolution_clock::duration::zero();

   fThreadId = fThreadCount++;
}

// --- DAQ Network Thread --- thread with socket functionalities
// Setup Socket
void DAQServerThread::Setup(){
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

DAQServerThread::DAQServerThread(int buffersize){
   fDataSocket = -1;
   fServerPort = -1;
   fRecvMsg = 0;
   if(buffersize>0) fBufferSize = buffersize;
   else fBufferSize = 4*1024*1024; //default 4MB

   SetDataWaitDuration(std::chrono::microseconds(100));
}
