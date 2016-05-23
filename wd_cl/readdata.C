#include <stdio.h>
#include "TH1D.h"
#include "TAxis.h"
#define SWAP(x) (((x&0x000002000) >> 13) | (((x) & 0x000001000) >> 11) | (((x) & 0x000000800) >> 9) | (((x) & 0x000000400) >> 7) | (((x) & 0x000000200) >> 5) | (((x) & 0x000000100) >> 3) | (((x) & 0x000000080) >> 1) | (((x) & 0x000000040)<<1) | (((x) & 0x000000020) << 3) | (((x) & 0x000000010) << 5) | (((x) & 0x0000000008) <<7) | (((x) & 0x000000004) << 9) | (((x) & 0x000000002) << 11) | (((x) & 0x000000001))<<13)
#define SWAPBYTE(x) (((x) & 0x0000FF00) >> 8) |(((x) & 0x000000FF) << 8)

void readdata(string filename="data.dat"){
	FILE *in = fopen(filename.c_str(), "r");
	
	TH1D *hWFM = new TH1D("hWFM", "waveform", 512, 0, 512);
	
	unsigned int memaddr;	
	fscanf(in, "%08x\n", &memaddr);

	for(int i=0; i<512;i++){
		int datain;
		fscanf(in, "%x\n", &datain);
		if(datain>131071){
			datain -= 262143;
		}
		hWFM->SetBinContent((i-memaddr)%512+1, ((datain)));
		//printf("%04x %04x %d\n", datain, 0xFFF & (datain), (datain));
	}
	hWFM->GetXaxis()->SetTitle("address (1bin = 12.5ns)");
	hWFM->Draw();
	fclose(in);
}
