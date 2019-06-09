#include "TCBTester.h"
#include "mscb.h"
#include <cstring>
#include <chrono>
#include <thread>

//--------------------------------------------------------------------
//       TCB Memory Writer
//--------------------------------------------------------------------

TCBMemoryWriter::TCBMemoryWriter(uint32_t address, uint32_t size){
   fAddress=address;
   fSize=size;
   fBuffer = new uint32_t[size];
}
void TCBMemoryWriter::Dump(uint32_t *buffer){
   memcpy(buffer, fBuffer, fSize*(sizeof(uint32_t)/sizeof(unsigned char)));
}
void TCBMemoryWriter::Fill(uint32_t *data){
   memcpy(fBuffer, data, fSize*(sizeof(uint32_t)/sizeof(unsigned char)));
}
void TCBMemoryWriter::WriteTo(TCB* tcb){

   Compose();

   for (unsigned int iblt = 0; iblt<fSize;) {
      int size = 0;
      if((fSize-iblt) >= BLTSIZE){
         size = BLTSIZE;
      } else {
         size = (fSize-iblt);
      }

      tcb->WriteBLT(fAddress+iblt, fBuffer+iblt, size);
      
      /*for(int i=0; i<size; i++){
         printf("%2d (address: %08x) : %08x\n", i, fAddress+iblt+i, fBuffer[iblt+i]);
      }*/

      iblt += size;
   }

}
//--------------------------------------------------------------------
//       TCB Memory Reader
//--------------------------------------------------------------------
TCBMemoryReader::TCBMemoryReader(uint32_t address, uint32_t size){
   fAddress=address;
   fSize=size;
   fBuffer = new uint32_t[size];
   Clean();
}
void TCBMemoryReader::Dump(uint32_t *buffer){
   memcpy(buffer, fBuffer, fSize*(sizeof(uint32_t)/sizeof(unsigned char)));
}
void TCBMemoryReader::Clean(){
   memset(fBuffer, 0, (sizeof(uint32_t)/sizeof(unsigned char))*fSize);
}
void TCBMemoryReader::ReadFrom(TCB* tcb){
   for (unsigned int iblt = 0; iblt<fSize;) {
      int size = 0;
      if((fSize-iblt) >= BLTSIZE){
         size = BLTSIZE;
      } else {
         size = (fSize-iblt);
      }

      tcb->ReadBLT(fAddress+iblt, fBuffer+iblt, size);
      
      /*for(int i=0; i<size; i++){
         printf("%2d (address: %08x): %08x\n", i, fAddress+iblt+i, fBuffer[i+iblt]);
      }*/

      iblt += size;
   }

   Decompose();
}


//--------------------------------------------------------------------
//       TCB Tester
//--------------------------------------------------------------------
void TCBTester::DoTest(){

   fTCB->SWStop();

   for(auto writer: fMemoryWriters)
      writer->WriteTo(fTCB);

   fTCB->GoRun();
   std::this_thread::sleep_for(std::chrono::milliseconds(500));
   fTCB->SWStop();

   for(auto reader: fMemoryReaders)
      reader->ReadFrom(fTCB);
}

TCBTester::TCBTester(std::string crateId, int slot, char algsel){
   fTCB = new TCB(crateId.c_str(), 20, slot);
   char temp[128];
   sprintf(temp, "%s", crateId.c_str());
   fTCB->fh = mscb_init(temp, 0, "", 0); 

   u_int32_t rrun_config = 0x0000E010;  //masktrg, masksync, maskbusy, ~fadcmode, ~testtxmode, enable trg_bus
   fTCB->SetRRUN(&rrun_config);
   SetTcbAlgsel(algsel);
}
