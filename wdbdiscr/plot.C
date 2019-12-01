int getNum(TString s){
   return atoi(s(6,3).Data());
}


void plot(string dirname="./"){
   //FILE* f = fopen("out.dat", "r")
   //

   TH1F *hfmeanthr = new TH1F("hfmeanthr", "WD2F Mean discriminator thr", 60, -0.03, 0.03);
   hfmeanthr->GetXaxis()->SetTitle("V");
   TH1F *hfpedwidth = new TH1F("hfpedwidth", "WD2F Pedestal witdh @discriminator", 50, 0, 0.004);
   hfpedwidth->GetXaxis()->SetTitle("V");
   TH1F *hgmeanthr = new TH1F("hgmeanthr", "WD2G Mean discriminator thr", 60, -0.03, 0.03);
   hgmeanthr->GetXaxis()->SetTitle("V");
   TH1F *hgpedwidth = new TH1F("hgpedwidth", "WD2G Pedestal witdh @discriminator", 50, 0, 0.004);
   hgpedwidth->GetXaxis()->SetTitle("V");
   TH1F *hdiffmeanthr = new TH1F("hdiffmeanthr", "WD2ADiff Mean discriminator thr", 60, -0.03, 0.03);
   hdiffmeanthr->GetXaxis()->SetTitle("V");
   TH1F *hdiffpedwidth = new TH1F("hdiffpedwidth", "WD2ADiff Pedestal witdh @discriminator", 50, 0, 0.004);
   hdiffpedwidth->GetXaxis()->SetTitle("V");

   TSystemDirectory dir(dirname.c_str(),dirname.c_str());
   TList *files = dir.GetListOfFiles();

   FILE *outxml = fopen("out.xml","w");

   if (files){
      TSystemFile *file; TString fname; TIter next(files);
      while ((file=(TSystemFile*)next())) {
         fname = file->GetName();
         if (!file->IsDirectory() && fname.EndsWith(".dat") && fname.Index("out-wd")==0) {
            TNtuple *tuple = new TNtuple("tuple", "pippo", "v:s0:s1:s2:s3:s4:s5:s6:s7:s8:s9:s10:s11:s12:s13:s14:s15");

            std::string s = dirname;
            s += fname.Data();
            tuple->ReadFile(s.c_str());

            if(tuple->GetEntries()){

               for(int i=0; i<16; i++){
                  int n = tuple->Draw(Form("v:s%d", i), "",  "goff");
                  TGraph *g = new TGraph(n, tuple->GetV1(), tuple->GetV2());
                  //TH2D* h= (TH2D*)gROOT->Get(Form("s%d", i));
                  g->SetMarkerStyle(20);
                  g->SetMarkerColor(i+30);
                  g->Fit("gaus","Q","Q");
                  if(getNum(fname)>190) {
                     //		    printf("wd%d is ADiff!\n", getNum(fname));
                     hdiffmeanthr->Fill(g->GetFunction("gaus")->GetParameter(1));
                     hdiffpedwidth->Fill(g->GetFunction("gaus")->GetParameter(2));
                  }
                  else if(getNum(fname)>155) {
                     //		    printf("wd%d is G!\n", getNum(fname));
                     hgmeanthr->Fill(g->GetFunction("gaus")->GetParameter(1));
                     hgpedwidth->Fill(g->GetFunction("gaus")->GetParameter(2));
                     //		    if(g->GetFunction("gaus")->GetParameter(2)>0.0009)
                  }
                  else {
                     //		    printf("wd%d is F!\n", getNum(fname));
                     hfmeanthr->Fill(g->GetFunction("gaus")->GetParameter(1));
                     hfpedwidth->Fill(g->GetFunction("gaus")->GetParameter(2));
                  }
                  Double_t truethr = g->GetFunction("gaus")->GetParameter(1)-3*g->GetFunction("gaus")->GetParameter(2);
                  if(i==0) {
                     fprintf(outxml,"%s\n",fname.Data());
                     fprintf(outxml,"<FrontendThreshold>");
                     fprintf(outxml,"%1.3lf,", truethr);
                  }
                  else if(i==15) {
                     fprintf(outxml,"%1.3lf",truethr);
                     fprintf(outxml,"</FrontendThreshold>\n");
                  }
                  else
                     fprintf(outxml,"%1.3lf,",truethr);

                  //g->Draw((i)?"LP SAME":"ALP");
               }//end for 
            }//end if tuple->getEntries
         }//end if IsDirectory
      }//end while
   }//end if(files)
   
   TCanvas *cmean = new TCanvas("cmean");
   cmean->Divide(3,1);
   cmean->cd(1);
   hfmeanthr->Draw();
   cmean->cd(2);
   hgmeanthr->Draw();
   cmean->cd(3);
   hdiffmeanthr->Draw();

   TCanvas *cpedw = new TCanvas("cmpedw");
   cpedw->Divide(3,1);
   cpedw->cd(1);
   hfpedwidth->Draw();
   cpedw->cd(2);
   hgpedwidth->Draw();
   cpedw->cd(3);
   hdiffpedwidth->Draw();
   
}
