#include <sstream>
#include "TH1D.h"
#include "TCanvas.h"

typedef struct {
   std::string boardName = "UNKNOWN";
   std::string boardId = "WDXXX";
   char version = 'G';
   int slot = 0;
   std::string crateName = "CRATE";
   unsigned int chnPolarity;
   float thr[16];
   bool written = false;
   bool bad[16];
} boardData;

//prints a tag fot the WDB in the output file
void printBoard(ofstream &outfile, boardData &b){
   bool badChn = false;
   //cout << "Board "<< b.boardName << "\n";
   outfile << "<WDB Name=\"" << b.boardName << "\" Slot=\""<< b.slot <<"\">"<< std::endl;
   outfile << "<TriggerLevel>" << std::endl;
   for(int i=0; i<16; i++){
      //cout << b.thr[i];
      outfile << b.thr[i];

      if(b.bad[i])
         badChn = true;

      //next board
      if(i!=15){
         //cout << ", ";
         outfile << ", ";
      }
   }
   outfile << std::endl << "</TriggerLevel>" << std::endl;
   outfile << "</WDB>"<< std::endl;
   //cout << "\n";
   if(badChn){
      cout << "Bad Channel on Board "<< b.boardName << "\n";
      for(int i=0; i<16; i++){
         if(b.bad[i]){
            cout << "Channel " << i << " thr " << b.thr[i] << "\n";
         }
      }
   }
}

void makeThr(string dirname="./", double absoluteThr = 0.01 ){
   int noped=0;
   const double fallbackThr = -0.035;//in case no pedestal is found
   //XEC MPPC
   //const double absoluteThr = 0.010;//offset WRT observed threshold
   //RDC LYSO
   //const double absoluteThr = 0.005;//offset WRT observed threshold
   //CDCH
   //const double absoluteThr = 0.005;//offset WRT observed threshold

   //variable threshold option
   //const double nsigma = 10.;

   std::vector<boardData> boards;

   //open output file
   TFile *outroot = new TFile("output.root", "recreate");

   TH1F* hMean = new TH1F("hMean", "Pedestal position", 100, 0, 0);
   hMean->SetCanExtend(TH1::kAllAxes);
   TH1F* hSigma = new TH1F("hSigma", "Pedestal sigma", 100, 0, 0);
   hSigma->SetCanExtend(TH1::kAllAxes);
   TH1F* hThr = new TH1F("hThr", "Threshold", 100, 0, 0);
   hThr->SetCanExtend(TH1::kAllAxes);

   //list directory content
   TSystemDirectory dir(dirname.c_str(),dirname.c_str());
   TList *files = dir.GetListOfFiles();

   if (files){
      TSystemFile *file; TString fname; TIter next(files);
      while ((file=(TSystemFile*)next())) {
         fname = file->GetName();
         if (!file->IsDirectory() && fname.EndsWith(".dat") && fname.Index("out-")==0) {
            std::string s = dirname;
            s += fname.Data();
            ifstream myfile(s.c_str());
            cout << fname << '\n';

            //data for current board
            boardData board;

            //dataset
            std::array<std::vector<int>, 16> scals;
            std::vector<float> thrs;

            string line;
            while ( getline (myfile,line) ){
               if(line.front() == '#'){
                  //comments
                  //erase "# "
                  line.erase(0, 2);
                  //parsing
                  std::istringstream ss(line);
                  std::string parametername;
                  if(std::getline(ss, parametername, ':')){
                     if(parametername == "Name"){
                        //board name
                        ss >> board.boardName;
                        cout << "Board Name: "<< board.boardName << '\n';
                     } else if(parametername == "WDB"){
                        //board id (WDXXX)
                        ss >> board.boardId;
                        cout << "Board Id: "<< board.boardId << '\n';
                     } else if(parametername == "Revision"){
                        //board revision (E, F, G)
                        ss >> board.version;
                        cout << "Board Version: "<< board.version << '\n';
                     } else if(parametername == "Crate"){
                        //crate name in xml
                        ss >> board.crateName;
                        cout << "Crate Name: "<< board.crateName << '\n';
                     } else if(parametername == "Slot"){
                        //slot number 0-15
                        ss >> board.slot;
                        cout << "Slot: "<< board.slot << '\n';
                     } else if(parametername == "Gain"){
                        //gain array
                     } else if(parametername == "PZC"){
                        //pzc enable (0-1)
                     } else if(parametername == "PZC level"){
                        //pzc level (0-6)
                     } else if(parametername == "Channel Polarity"){
                        //channel polarity in hex
                        ss >> hex >> board.chnPolarity;
                        cout << "Channel Polarity: "<< board.chnPolarity << '\n';
                     } else if(parametername == "Down"){
                        //lowest threshold
                     } else if(parametername == "Up"){
                        //highest threshold
                     } else if(parametername == "N"){
                        //number of points
                     } else {
                        cout << "unknown parameter " << parametername << '\n';
                     }
                  }
               }
               else {
                  stringstream myss(line);
                  float thr;
                  myss >> thr;
                  thrs.push_back(thr);
                  for(int i=0; i<16; i++) {
                     int scal;
                     myss >> scal;
                     scals[i].push_back(scal);
                  }
               }
            }
            myfile.close();

            float peds[16] = {-100};

            //TCanvas* c=new TCanvas();
            //c->SetLogy();
            //
            TF1 *fgau= new TF1("fgau", "gaus", thrs.front(), thrs.back());
            for(int i=0; i<16; i++){

               //fit WD2G
               if(board.version == 'G'){
                  TH1F *h = new TH1F(Form("%s-%d", board.boardName.c_str(), i), Form("%s-%d", board.boardName.c_str(), i), thrs.size()-1, thrs.data());
                  for(int j=0; j<scals[i].size(); j++){
                     h->SetBinContent(j+1, scals[i][j]);
                  }

                  h->Fit(fgau, "Q");
                  if(fgau->GetParameter(2) > 0.001){
                     noped++;
                     board.bad[i] = true;
                     printf("!!");
                  } else {
                     board.bad[i] = false;
                  }

                  hMean->Fill(fgau->GetParameter(1));
                  hSigma->Fill(fgau->GetParameter(2));

                  float thr = fgau->GetParameter(1);
                  if(board.chnPolarity & (1<<i)){
                     //negative threshold
                     //thr -= nsigma*fgau->GetParameter(2);
                     thr -= absoluteThr;
                  } else {
                     //positive threshold
                     //thr += nsigma*fgau->GetParameter(2);
                     thr += absoluteThr;
                  }

                  printf("%2d: %lf %lf -> %lf\n", i,  fgau->GetParameter(1), fgau->GetParameter(2), thr);
                  board.thr[i] = thr;
                  hThr->Fill(thr);

                  h->Write(Form("%s-%d", board.boardName.c_str(), i));

                  /*h->Draw();
                  TLine *l=new TLine(fgau->GetParameter(1) +0.0005 + nsigma*fgau->GetParameter(2),c->GetUymin(),fgau->GetParameter(1) +0.0005 + nsigma*fgau->GetParameter(2),c->GetUymax());
                  l->SetLineColor(kRed);
                  l->Draw();
                  
                  c->Update();
                  c->WaitPrimitive();
                  delete h;*/


               //edge for WD2F
               } else if (board.version == 'F' || board.version == 'E'){
                  peds[i] = -100;
                  TH1F *h = new TH1F(Form("%s-%d", board.boardName.c_str(), i), Form("%s-%d", board.boardName.c_str(), i), thrs.size()-1, thrs.data());
                  for(int j=0; j<scals[i].size(); j++){
                     h->SetBinContent(j+1, scals[i][j]);
                  }
                  h->Write(Form("%s-%d", board.boardName.c_str(), i));
                  delete h;

                  for(int j=0; j<scals[i].size(); j++){
                     if (peds[i] == -100 && scals[i][j]>2000){
                        peds[i] = thrs[j];
                     }
                  }

                  if(peds[i] != -100){
                     printf("%2d: %lf\n", i,  peds[i]);
                     board.thr[i] = peds[i] + absoluteThr;
                  }else {
                     printf("%2d: no ped\n", i);
                     board.thr[i] = fallbackThr;
                     noped++;
                  }
               }
               
            }

            boards.push_back(board);
         }
      }
      cout << "\n\n FINAL STATUS:\n";
      cout << noped << " channels without or with bad pedestal\n";

      ofstream outfile("output.xml");
      outfile << "<System>" << std::endl;
      for(auto it= boards.begin(); it<boards.end(); it++){
         if(it->written == false){
            //new board to be written
            outfile << "<Crate Name=\"" << it->crateName << "\">"<< std::endl;
            printBoard(outfile, *it);
            it->written = true;

            //write all other boards in crate
            auto others = it;
            for(auto others = it; others<boards.end(); others++){
               if(others->written == false && others->crateName == it->crateName){
                  printBoard(outfile, *others);
                  others->written = true;
               }
            }
            outfile << "</Crate>" << std::endl;
         }
      }
      outfile << "</System>" << std::endl;
      outfile.close();
   }

   hMean->Write();
   hSigma->Write();
   hThr->Write();
   outroot->Close();

}
