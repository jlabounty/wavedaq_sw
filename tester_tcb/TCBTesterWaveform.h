#include "TCBTester.h"
#include "waveform/MEGFADCWaveform.h"
#include "waveform/MEGDiscrWaveform.h"

//--------------------------------------------------------------------
//       TCB Generic Waveform Writer/Reader
//--------------------------------------------------------------------

class TCBWaveformWriter : public TCBMemoryWriter{
   MEGFADCWaveform* fWf;
   public:
   TCBWaveformWriter(uint32_t address, uint32_t size): TCBMemoryWriter(address, size) {}

   void SetWaveform(MEGFADCWaveform* wf);

   void Compose();
};

class TCBWaveformReader : public TCBMemoryReader{
   MEGFADCWaveform* fWf;
   public:
   TCBWaveformReader(uint32_t address, uint32_t size): TCBMemoryReader(address, size) {}

   void SetWaveform(MEGFADCWaveform* wf);

   void Decompose();
};

//--------------------------------------------------------------------
//       TCB1 XEC-Like WDB Writer
//--------------------------------------------------------------------

class TCB1XECWriter : public TCBMemoryWriter{
   MEGFADCWaveform* fWDBSum;
   MEGFADCWaveform* fWDBMaxId;
   MEGFADCWaveform* fWDBMaxVal;
   MEGFADCWaveform* fWDBTime;
   public:
   TCB1XECWriter(uint32_t address, uint32_t size): TCBMemoryWriter(address, size) {}

   void SetWaveforms(MEGFADCWaveform* sum, MEGFADCWaveform* maxid, MEGFADCWaveform* maxval, MEGFADCWaveform* time) {fWDBSum=sum; fWDBMaxId=maxid; fWDBMaxVal=maxval; fWDBTime=time; }

   void Compose();
};

//--------------------------------------------------------------------
//       TCB1 TC-Like WDB Writer
//--------------------------------------------------------------------

class TCB1TCWriter : public TCBMemoryWriter{
   MEGFADCWaveform* fHitTime[16];
   MEGDiscrWaveform* fHit[16];
   public:
   TCB1TCWriter(uint32_t address, uint32_t size): TCBMemoryWriter(address, size) {}

   void SetWaveforms(MEGFADCWaveform** times, MEGDiscrWaveform**hits) { for(int i=0; i<16; i++){ fHitTime[i]=times[i]; fHit[i]=hits[i];} }

   void Compose();
};

//--------------------------------------------------------------------
//       TCB1 XEC-Like Reader
//--------------------------------------------------------------------

class TCB1XECReader : public TCBMemoryReader{
   MEGFADCWaveform* fWDBSum;
   MEGFADCWaveform* fWDBMaxId;
   MEGFADCWaveform* fWDBMaxVal;
   MEGFADCWaveform* fWDBTime;
   public:
   TCB1XECReader(uint32_t address, uint32_t size): TCBMemoryReader(address, size) {}

   void SetWaveforms(MEGFADCWaveform* sum, MEGFADCWaveform* maxid, MEGFADCWaveform* maxval, MEGFADCWaveform* time) {fWDBSum=sum; fWDBMaxId=maxid; fWDBMaxVal=maxval; fWDBTime=time; }

   void Decompose();
};

//--------------------------------------------------------------------
//       TCB1 TC-Like Reader
//--------------------------------------------------------------------

class TCB1TCReader : public TCBMemoryReader{
   MEGDiscrWaveform* fTCOr;
   MEGDiscrWaveform* fTCHit0;
   MEGFADCWaveform* fTCTileId0;
   MEGFADCWaveform* fTCTileTime0;
   MEGDiscrWaveform* fTCHit1;
   MEGFADCWaveform* fTCTileId1;
   MEGFADCWaveform* fTCTileTime1;
   MEGFADCWaveform* fTCMultiplicity;
   public:
   TCB1TCReader(uint32_t address, uint32_t size): TCBMemoryReader(address, size) {}

   void SetWaveforms(MEGDiscrWaveform* tcor, MEGDiscrWaveform* tchit0, MEGFADCWaveform* tctileid0, MEGFADCWaveform* tctiletime0, MEGDiscrWaveform* tchit1, MEGFADCWaveform* tctileid1,MEGFADCWaveform* tctiletime1, MEGFADCWaveform* tcmultiplicity) { fTCOr=tcor; fTCHit0=tchit0; fTCTileId0=tctileid0; fTCTileTime0=tctiletime0; fTCHit1=tchit1; fTCTileId1=tctileid1; fTCTileTime1=tctiletime1; fTCMultiplicity=tcmultiplicity; }

   void Decompose();
};

//--------------------------------------------------------------------
//       TCB2 XEC-Like WDB Writer
//--------------------------------------------------------------------

class TCB2XECWriter : public TCBMemoryWriter{
   MEGFADCWaveform* fWDBSum;
   MEGFADCWaveform* fWDBMaxId;
   MEGFADCWaveform* fWDBMaxVal;
   MEGFADCWaveform* fWDBTime;
   public:
   TCB2XECWriter(uint32_t address, uint32_t size): TCBMemoryWriter(address, size) {}

   void SetWaveforms(MEGFADCWaveform* sum, MEGFADCWaveform* maxid, MEGFADCWaveform* maxval, MEGFADCWaveform* time) {fWDBSum=sum; fWDBMaxId=maxid; fWDBMaxVal=maxval; fWDBTime=time; }

   void Compose();
};

//--------------------------------------------------------------------
//       TCB2 XEC-Like Reader
//--------------------------------------------------------------------

class TCB2XECReader : public TCBMemoryReader{
   MEGFADCWaveform* fWDBSum;
   MEGFADCWaveform* fWDBMaxId;
   MEGFADCWaveform* fWDBMaxVal;
   MEGFADCWaveform* fWDBTime;
   public:
   TCB2XECReader(uint32_t address, uint32_t size): TCBMemoryReader(address, size) {}

   void SetWaveforms(MEGFADCWaveform* sum, MEGFADCWaveform* maxid, MEGFADCWaveform* maxval, MEGFADCWaveform* time) {fWDBSum=sum; fWDBMaxId=maxid; fWDBMaxVal=maxval; fWDBTime=time; }

   void Decompose();
};

