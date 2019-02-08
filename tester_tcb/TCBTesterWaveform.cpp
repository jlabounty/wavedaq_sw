#include "TCBTesterWaveform.h"

void TCBWaveformWriter::SetWaveform(MEGFADCWaveform* wf){
   if ((unsigned)wf->GetNPoints()!= fSize) printf("size mismatch\n");

   fWf = wf;
   
}

void TCBWaveformWriter::Compose(){
   for(unsigned i=0; i< fSize; i++){
      fBuffer[i]= fWf->GetAmplitudeAt(i);
   }
}

void TCBWaveformReader::SetWaveform(MEGFADCWaveform* wf){
   if ((unsigned)wf->GetNPoints()!= fSize) printf("size mismatch\n");

   fWf = wf;
   
}

void TCBWaveformReader::Decompose(){
   for(unsigned i=0; i< fSize; i++){
      fWf->SetAmplitudeAt(i,fBuffer[i]);
   }
}

void TCB1XECWriter::Compose(){
   //lower memeory
   for(unsigned i=0; i< fSize/2; i++){
      unsigned sum = fWDBSum->GetAmplitudeAt(i);
      unsigned max = fWDBMaxId->GetAmplitudeAt(i);

      uint32_t val =0;
      val |= sum & 0x3FFFFF;
      val |= ((sum >>22)&0x1)<<22;
      val |= ((sum >>22)&0x1)<<23;
      val |= ((sum >>22)&0x1)<<24;
      val |= ((sum >>22)&0x1)<<25;
      val |= ((sum >>22)&0x1)<<26;
      val |= ((sum >>22)&0x1)<<27;
      val |= (max&0xF)<<28;
      fBuffer[i]= val;
   }
   //upper memory
   for(unsigned i=fSize/2; i< fSize; i++){
      unsigned maxval = fWDBMaxVal->GetAmplitudeAt(i-fSize/2);
      unsigned time = fWDBTime->GetAmplitudeAt(i-fSize/2); 

      uint32_t val =0;
      val |= (maxval&0x3FFFF)<<2;
      val |= (time&0xFFFF)<<20;
      fBuffer[i]= val;
   }
}

void TCB1TCWriter::Compose(){
   //lower memeory
   for(unsigned i=0; i< fSize/2; i++){

      uint32_t val =0;
      for(int iCh=0; iCh<16; iCh++){
         unsigned isHit= fHit[iCh]->GetAmplitudeAt(i);
         val |= (isHit & 0x1) << iCh;
      }
      for(int iCh=0; iCh<5; iCh++){
         unsigned time = fHitTime[iCh]->GetAmplitudeAt(i);
         val |= (time & 0x7) << (16+(3*iCh));
      }
      unsigned time = fHitTime[5]->GetAmplitudeAt(i);
      val |= (time& 0x1) <<31;
      fBuffer[i]= val;
   }
   //upper memory
   for(unsigned i=fSize/2; i< fSize; i++){
      uint32_t val =0;
      unsigned time = fHitTime[5]->GetAmplitudeAt(i-fSize/2);
      val |= (time& 0x6)>>1;
      for(int iCh=6; iCh<16; iCh++){
         unsigned time = fHitTime[iCh]->GetAmplitudeAt(i-fSize/2);
         val |= (time & 0x7) << (3*(iCh-6)+2);
      }
      fBuffer[i]= val;
   }
}

void TCB1XECReader::Decompose(){
   for(unsigned i=0; i< fSize/2; i++){
      uint32_t lowerval = fBuffer[i];
      uint32_t upperval = fBuffer[i+fSize/2];

      int sum = lowerval&0x1FFFFFF;
      if(sum > 0x1000000){
         sum -= 0x2000000;
      }
      fWDBSum->SetAmplitudeAt(i, sum);
      fWDBMaxId->SetAmplitudeAt(i, (lowerval>>26)&0xF);
      int maxAmpl = ((lowerval>>30)&0x3)|((upperval<<2)&0x3FFFFC);
      if(maxAmpl>0x200000){
         maxAmpl -= 0x400000;
      }
      fWDBMaxVal->SetAmplitudeAt(i, maxAmpl);
      fWDBTime->SetAmplitudeAt(i,upperval>>20);
   }
}

void TCB1TCReader::Decompose(){
   for(unsigned i=0; i< fSize/2; i++){
      uint32_t lowerval = fBuffer[i];
      uint32_t upperval = fBuffer[i+fSize/2];

      fTCOr->SetAmplitudeAt(i, lowerval&0x1);
      fTCHit0->SetAmplitudeAt(i, (lowerval>>1)&0x1);
      fTCTileId0->SetAmplitudeAt(i, (lowerval>>2)&0x7F);
      fTCTileTime0->SetAmplitudeAt(i, (lowerval>>9)&0x1F);
      fTCHit1->SetAmplitudeAt(i, (lowerval>>14)&0x1);
      fTCTileId1->SetAmplitudeAt(i, (lowerval>>15)&0x7F);
      fTCTileTime1->SetAmplitudeAt(i, (lowerval>>22)&0x1F);
      fTCMultiplicity->SetAmplitudeAt(i, (upperval<<5)|((lowerval>>27)&0x1F));
   }
}

void TCB2XECWriter::Compose(){
   //lower memeory
   for(unsigned i=0; i< fSize/2; i++){
      unsigned sum = fWDBSum->GetAmplitudeAt(i);
      unsigned max = fWDBMaxId->GetAmplitudeAt(i);

      uint32_t val =0;
      val |= sum & 0x3FFFFFF;
      val |= (max&0xF)<<26;
      val |= (max&0x3)<<30;
      fBuffer[i]= val;
   }
   //upper memory
   for(unsigned i=fSize/2; i< fSize; i++){
      unsigned maxval = fWDBMaxVal->GetAmplitudeAt(i-fSize/2);
      unsigned time = fWDBTime->GetAmplitudeAt(i-fSize/2); 

      uint32_t val =0;
      val |= (maxval&0x3FFFF)>>2;
      val |= (time&0xFFFF)<<22;
      fBuffer[i]= val;
   }
}

void TCB2XECReader::Decompose(){
   for(unsigned i=0; i< fSize/2; i++){
      uint32_t lowerval = fBuffer[i];
      uint32_t upperval = fBuffer[i+fSize/2];

      int sum = lowerval&0xFFFFFFF;
      if(sum > 0x8000000){
         sum -= 0x10000000;
      }
      fWDBSum->SetAmplitudeAt(i, sum);
      fWDBMaxId->SetAmplitudeAt(i, ((upperval&0x3)<<2)|(lowerval>>28)&0xF);
      int maxAmpl = ((upperval>>2)&0x3FFFFF);
      if(maxAmpl>0x200000){
         maxAmpl -= 0x400000;
      }
      fWDBMaxVal->SetAmplitudeAt(i, maxAmpl);
      fWDBTime->SetAmplitudeAt(i,upperval>>24);
   }
}

