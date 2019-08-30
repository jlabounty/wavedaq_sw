#ifndef TCBTester_h
#define TCBTester_h

#include <sys/types.h>
#include <stdlib.h>
#include "TCBLib.h"
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <string>

//for memset
#include <cstring>

class TCBMemoryWriter{
   private:
      uint32_t fAddress;
   protected:
      uint32_t fSize;
      uint32_t *fBuffer;

   public:
      TCBMemoryWriter(uint32_t address, uint32_t size);
      virtual ~TCBMemoryWriter() { delete [] fBuffer; }
      uint32_t GetAddress(){ return fAddress; }
      uint32_t GetSize(){ return fSize; }
      void Dump(uint32_t* buffer);
      void Fill(uint32_t* data);
      void WriteTo(TCB* tcb);
      virtual void Compose(){};
};

class TCBMemoryCleaner : public TCBMemoryWriter{
   public:
   TCBMemoryCleaner(uint32_t address, uint32_t size): TCBMemoryWriter(address, size) {}

   void Compose() {memset(fBuffer, 0, sizeof(uint32_t)*fSize); }
};

class TCBMemoryReader{
   private:
      uint32_t fAddress;
   protected:
      uint32_t fSize;
      uint32_t *fBuffer;

   public:
      TCBMemoryReader(uint32_t address, uint32_t size);
      virtual ~TCBMemoryReader() { delete [] fBuffer; }
      uint32_t GetAddress(){ return fAddress; }
      uint32_t GetSize(){ return fSize; }
      void Dump(uint32_t* buffer);
      void Clean();
      void ReadFrom(TCB* tcb);
      virtual void Decompose() {}
};

class TCBTester {
   private:
      std::vector<TCBMemoryWriter*> fMemoryWriters;
      std::vector<TCBMemoryReader*> fMemoryReaders;
      TCB *fTCB;

   public:

      void AddMemoryWriter(TCBMemoryWriter* writer) {
         fMemoryWriters.push_back(writer);
      }
      
      void AddMemoryReader(TCBMemoryReader* reader) {
         fMemoryReaders.push_back(reader);
      }
      
      void ShowMemoryWriters(){
         for(auto writer: fMemoryWriters){
            printf("Writer at address %08x with size %d\n", writer->GetAddress(), writer->GetSize());     
         }
      }

      void ShowMemoryReaders(){
         for(auto reader: fMemoryReaders){
            printf("Reader at address %08x with size %d\n", reader->GetAddress(), reader->GetSize());     
         }
      }

      void DeleteMemoryWriters(){
         for(auto writer: fMemoryWriters)
            delete writer;
         fMemoryWriters.clear(); 
      }
      
      void DeleteMemoryReaders(){
         for(auto reader: fMemoryReaders)
            delete reader;
         fMemoryReaders.clear(); 
      }

      //interface functions with fTCB
      void SetTcbParameter(uint32_t position, uint32_t value){
         fTCB->SetParameter(position, &value);
      }
      uint32_t GetTcbIdCode(){
         return fTCB->GetIDCode();
      }
      uint32_t GetTcbAlgsel(){
         uint32_t algsel;
         fTCB->GetRALGSEL(&algsel);
         return algsel;
      }
      void SetTcbAlgsel(char algsel){
         uint32_t alg=algsel;
         fTCB->SetRALGSEL(&alg);
      }
      
      void DoTest();
      TCBTester(std::string crateId, int slot, char algsel=0);
      ~TCBTester(){ DeleteMemoryWriters(); DeleteMemoryReaders(); delete fTCB; }

};

#endif
