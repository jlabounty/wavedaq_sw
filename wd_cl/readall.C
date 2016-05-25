#include <stdio.h>
#include "TH1D.h"
#include "TCanvas.h"
#include "TAxis.h"

void readall(){
	FILE *in = fopen("data.dat", "r");
	
	TH1D *hWFM = new TH1D("hWFM", "waveform", 512, 0, 512);
	TH1D *hInWFM[16];
       	for(int i=0; i<16;i++) hInWFM[i] = new TH1D(Form("hWFM%2d", i), Form("waveform %d", i), 512, 0, 512);
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
		if(data>0x7FFFFFFF){
			data -= 0xFFFFFFFE;
		}
		hWFM->SetBinContent((i-memaddr)%512+1, ((data)));
		hDISC0->SetBinContent((i-memaddr)%512+1, d1*20+150);
		hDISC1->SetBinContent((i-memaddr)%512+1, d2*20+180);
		hDISC2->SetBinContent((i-memaddr)%512+1, d3*20+210);
		//printf("%04x %04x %d\n", datain, 0xFFF & (datain), (datain));
	}
	fclose(in);
	printf("done output!\n");
	
	in = fopen("datamemin.dat", "r");
	fscanf(in, "%08x\n", &memaddr);
	for(int i=0; i<8192;i++){
		unsigned int datain;
		fscanf(in, "%x\n", &datain);
		datain &=0x3FFF;	
		hInWFM[i/512]->SetBinContent((i%512-memaddr)%512+1, datain);
		if (i%512 == 0)printf("doing input %d!\n", i/512);
	}
	fclose(in);

	new TCanvas();
	hWFM->GetXaxis()->SetTitle("address (1bin = 12.5ns)");
	hWFM->Draw();
	hDISC0->Draw("SAME");
	hDISC1->Draw("SAME");
	hDISC2->Draw("SAME");
	TCanvas *c= new TCanvas();
	c->Divide(2,2);
	c->cd(1);
	hInWFM[0]->Draw();
	c->cd(2);
	hInWFM[1]->Draw();
	c->cd(3);
	hInWFM[2]->Draw();
	c->cd(4);
	hInWFM[3]->Draw();
	c= new TCanvas();
	c->Divide(2,2);
	c->cd(1);
	hInWFM[4]->Draw();
	c->cd(2);
	hInWFM[5]->Draw();
	c->cd(3);
	hInWFM[6]->Draw();
	c->cd(4);
	hInWFM[7]->Draw();
	c= new TCanvas();
	c->Divide(2,2);
	c->cd(1);
	hInWFM[8]->Draw();
	c->cd(2);
	hInWFM[9]->Draw();
	c->cd(3);
	hInWFM[10]->Draw();
	c->cd(4);
	hInWFM[11]->Draw();
	c= new TCanvas();
	c->Divide(2,2);
	c->cd(1);
	hInWFM[12]->Draw();
	c->cd(2);
	hInWFM[13]->Draw();
	c->cd(3);
	hInWFM[14]->Draw();
	c->cd(4);
	hInWFM[15]->Draw();
}
