int WfExtract(u_int32_t idCode, int channel, u_int32_t A, u_int32_t B){
   int val;

   switch(idCode>>12){
        case 1:
           if(channel < 16){
              //WDB
              int temp = A & 0x3FFFFF;
              if (A & 0x200000){
                 temp -= 1<<22;
              }
              val = temp;

           }else{
              //TCB_1 out
              int temp = A & 0x3FFFFFF;
              if (A & 0x2000000){
                 temp -= 1<<26;
              }
              val = temp;
           }
           break;
        case 2:
           if(channel < 16){
              //from TCB_1
              int temp = A & 0x3FFFFFF;
              if (A & 0x2000000){
                 temp -= 1<<26;
              }
              val = temp;

           }else{
              //TCB_1 out
              int temp = A & 0xFFFFFFF;
              if (A & 0x8000000){
                 temp -= 1<<28;
              }
              val = temp;
           }

           break;
        case 3:
           if(channel < 16){
              //from TCB_2
              int temp = A & 0xFFFFFFF;
              if (A & 0x8000000){
                 temp -= (1<<28);
              }
              val = temp;

           }else{
              //Full QSUM out
             long temp = (int)A;
              if (A & 0x80000000){
                 temp -= (((long)1)<<32);
              }
              val = (int)temp;
           }

           break;
        default:
           printf("unknown idcode");
           val = 0;
           break;
   }

   return val;

}

void drawWf(string filename="dataout.dat"){

        FILE *f = fopen(filename.c_str(), "r");

        u_int32_t idcode;
        int channel, address, dim;
        if(f==NULL){
                printf("cannot open %s\n", filename.c_str());
                return;
        }

        int ret = fscanf(f, "%04x %d %d %d\n", &idcode, &channel, &address, &dim);
        if(ret!=4){
                printf("bad file format\n");
                fclose(f);
                return;
        }

        u_int32_t *memA = (u_int32_t *) malloc(dim*sizeof(u_int32_t));
        u_int32_t *memB = (u_int32_t *) malloc(dim*sizeof(u_int32_t));
        //printf("%04x %d %d %d\n", idcode, channel, address, dim);
        for (int i=0; i<dim; i++){
                ret = fscanf(f, "%08x %08x\n", memB+i, memA+i);
                if(ret!=2){
                        printf("problem with file\n");
                        free(memA);
                        free(memB);
                        fclose(f);
                        return;
                }
                //printf("%d %d\n", memA[i], memB[i]);
        }

        TH1F *h = new TH1F("h", "wf", dim, 0, dim);

        for(int i=0; i<dim; i++){
                int pos = (i+address)%dim;
                int val = WfExtract(idcode, channel, memA[pos], memB[pos]);
                h->SetBinContent(i+1, val);
        }

        h->Draw();

        free(memA);
        free(memB);
        fclose(f);
}
