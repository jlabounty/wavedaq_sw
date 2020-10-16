#include <sstream>

void makeThr(string dirname="2020-10-12/"){
   int noped=0;
   const double fallbackThr = -0.035;//in case no pedestal is found
   const double absoluteThr = -0.010;//offset WRT observed threshold

   TSystemDirectory dir(dirname.c_str(),dirname.c_str());
   TList *files = dir.GetListOfFiles();
   ofstream outfile("output.xml");
   if (files){
      TSystemFile *file; TString fname; TIter next(files);
      while ((file=(TSystemFile*)next())) {
         fname = file->GetName();
         if (!file->IsDirectory() && fname.EndsWith(".dat") && fname.Index("out-wd")==0) {
            std::string s = dirname;
            s += fname.Data();
            ifstream myfile(s.c_str());
            cout << fname << '\n';
            string line;
            std::array<std::vector<int>, 16> scals;
            std::vector<float> thrs;
            while ( getline (myfile,line) ){
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
            myfile.close();

            float peds[16] = {-100};

            outfile << fname.Data() << std::endl;
            outfile << "<TriggerLevel>";
            for(int i=0; i<16; i++){
               peds[i] = -100;

               for(int j=0; j<scals[i].size(); j++){
                  if (peds[i] == -100 && scals[i][j]>2){
                     peds[i] = thrs[j];
                  }
               }

               if(peds[i] != -100){
                  printf("%2d: %lf\n", i,  peds[i]);
                  outfile << peds[i] + absoluteThr;
               }else {
                  printf("%2d: no ped\n", i);
                  outfile << fallbackThr;
                  noped++;
               }
               if(i!=15)
                  outfile << ", ";
            }
            outfile << "</TriggerLevel>" << std::endl;
         }
      }
      cout << noped << " boards without pedestal\n";
   }
   outfile.close();

}
