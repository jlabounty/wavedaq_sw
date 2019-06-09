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
   //lower memory
   for(unsigned i=0; i< fSize/2; i++){
      unsigned sum = fWDBSum->GetAmplitudeAt(i);

      uint32_t val =0;
      val |= sum & 0x1FFFFFF;
      fBuffer[i]= val;
   }
   //upper memory
   for(unsigned i=fSize/2; i< fSize; i++){
      unsigned tdcnum = fWDBTdcNum->GetAmplitudeAt(i-fSize/2);
      unsigned tdcsum = fWDBTdcSum->GetAmplitudeAt(i-fSize/2); 

      uint32_t val =0;
      val |= (tdcsum&0xFF)<<16;
      val |= (tdcnum&0x1F)<<24;
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

      int sum = lowerval & 0x1FFFFFFF;
      if(sum > 0x10000000){
         sum -= 0x20000000;
      }
      fSum->SetAmplitudeAt(i, sum);
      fMaxId->SetAmplitudeAt(i, ((upperval)&0x1)|((lowerval>>29)&0x7));
      fTdcSum->SetAmplitudeAt(i, (upperval>>16)&0xFF);
      fTdcNum->SetAmplitudeAt(i, (upperval>>24)&0x1F);
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
   //lower memory
   for(unsigned i=0; i< fSize/2; i++){
      unsigned sum = fSum->GetAmplitudeAt(i);
      unsigned maxid = fMaxId->GetAmplitudeAt(i);

      uint32_t val =0;
      val |= sum & 0x1FFFFFFF;
      val |= ((maxid &0x7) << 29);
      fBuffer[i]= val;
   }
   //upper memory
   for(unsigned i=fSize/2; i< fSize; i++){
      unsigned maxid = fMaxId->GetAmplitudeAt(i);
      unsigned tdcnum = fTdcNum->GetAmplitudeAt(i-fSize/2);
      unsigned tdcsum = fTdcSum->GetAmplitudeAt(i-fSize/2); 

      uint32_t val =0;
      val |= (maxid>>3) & 0x1;
      val |= (tdcsum&0xFF)<<16;
      val |= (tdcnum&0x1F)<<24;
      fBuffer[i]= val;
   }
}

void TCB2XECReader::Decompose(){
   for(unsigned i=0; i< fSize/2; i++){
      uint32_t lowerval = fBuffer[i];
      uint32_t upperval = fBuffer[i+fSize/2];

      int sum = lowerval & 0x7FFFFFFF;
      if(sum > 0x70000000){
         sum -= 0x80000000;
      }
      fSum->SetAmplitudeAt(i, sum);
      fMaxId->SetAmplitudeAt(i, ((upperval)&0x5)|((lowerval>>31)&0x1));
      fTdcSum->SetAmplitudeAt(i, (upperval>>16)&0xFF);
      fTdcNum->SetAmplitudeAt(i, (upperval>>24)&0x1F);
   }

}

