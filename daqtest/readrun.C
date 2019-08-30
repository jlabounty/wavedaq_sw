#include "TCanvas.h"
#include "TGraph.h"


void readrun(){
   char filename[]="run.txt";
   int nwdb;

   std::map<int, TGraph> tcell;
   FILE*f = fopen(filename, "r");
   fscanf(f, "%3d", &nwdb);
   printf("run with %d wdb\n", nwdb);
   int event, tcb_event_number, tcb_trigger_type;
   int ipoint=0;
   while (fscanf(f, "\n%d %d %d: ", &event, &tcb_event_number, &tcb_trigger_type) != EOF){
      printf("event %d\n", event);
      int firstcell=-1;
      for(int iBoard=0; iBoard<nwdb; iBoard++){
         int wdb_id, wdb_event, wdb_trigger_type, wdb_cell0, wdb_cell1;
         fscanf(f, "%d %d %d %d %d, ",  &wdb_id, &wdb_event, &wdb_trigger_type, &wdb_cell0, &wdb_cell1);
         if(firstcell==-1)
            firstcell = wdb_cell0;
         else {
            int diff =  wdb_cell0-firstcell;
            if(diff>=512) diff -=1024;
            else if(diff<=-512) diff +=1024;
            tcell[wdb_id].SetPoint(ipoint, wdb_event, diff);
            tcell[wdb_id].SetName(Form("tcell board %d", wdb_id));
            tcell[wdb_id].SetTitle(Form("tcell board %d", wdb_id));
         }
         printf("wdb %d\n", wdb_id);
      }
      ipoint++;
   }

   for(auto it: tcell){
      new TCanvas();
      printf("Drawing graph %d (%d point)\n", it.first, it.second.GetN());
      it.second.DrawClone("ALP");
   }

}
