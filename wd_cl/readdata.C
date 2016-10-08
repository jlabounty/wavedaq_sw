#include <stdio.h>
#include "TH1D.h"
#include "TAxis.h"
#define SWAP(x) (((x&0x000002000) >> 13) | (((x) & 0x000001000) >> 11) | (((x) & 0x000000800) >> 9) | (((x) & 0x000000400) >> 7) | (((x) & 0x000000200) >> 5) | (((x) & 0x000000100) >> 3) | (((x) & 0x000000080) >> 1) | (((x) & 0x000000040)<<1) | (((x) & 0x000000020) << 3) | (((x) & 0x000000010) << 5) | (((x) & 0x0000000008) <<7) | (((x) & 0x000000004) << 9) | (((x) & 0x000000002) << 11) | (((x) & 0x000000001))<<13)
#define SWAPBYTE(x) (((x) & 0x0000FF00) >> 8) |(((x) & 0x000000FF) << 8)

void readdata(string filename="data.dat"){
	FILE *in = fopen(filename.c_str(), "r");
	
	TH1D *hWFM = new TH1D("hWFM", "waveform", 512, 0, 512);
	TH1D *hDISC0 = new TH1D("hDISC0", "disc0", 512, 0, 512);
	TH1D *hDISC1 = new TH1D("hDISC1", "disc1", 512, 0, 512);
	TH1D *hDISC2 = new TH1D("hDISC2", "disc2", 512, 0, 512);
	
	unsigned int memaddr;	
	fscanf(in, "%08x\n", &memaddr);

	for(int i=0; i<512;i++){
		unsigned long int datain;
		fscanf(in, "%lx\n", &datain);
		int d1= (datain >> 45) & 0x1;
		int d2= (datain >> 46) & 0x1;
		int d3= (datain >> 47) & 0x1;
		int data = datain & 0xFFFFFFFF;
		//		printf("%08x ", data);
		if(data>0x7FFFFFFF){
			data -= 0xFFFFFFFE;
		}
		//		printf("%08x\n", data);
		hWFM->SetBinContent((i-memaddr)%512+1, ((data)));
		hDISC0->SetBinContent((i-memaddr)%512+1, d1*20+150);
		hDISC1->SetBinContent((i-memaddr)%512+1, d2*20+180);
		hDISC2->SetBinContent((i-memaddr)%512+1, d3*20+210);
		//printf("%04x %04x %d\n", datain, 0xFFF & (datain), (datain));
	}
	hWFM->GetXaxis()->SetTitle("address (1bin = 12.5ns)");
	hWFM->Draw();
	//	hDISC0->Draw("SAME");
	//	hDISC1->Draw("SAME");
	//	hDISC2->Draw("SAME");
	fclose(in);
}
