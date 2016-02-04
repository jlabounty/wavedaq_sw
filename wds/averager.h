//
//  averager.h
//  Robust averager
//
//  Created by Stefan Ritt on 3/2/16.
//

class Averager {
   int fNx, fNy, fNz, fDim;
   float *fArray, *fTmp;
   unsigned short *fN;
   
public:
   Averager(int nx, int ny, int nz, int dim);
   ~Averager();
   
   void Add(int x, int y, int z, float value);
   void Reset();
   double Average(int x, int y, int z);
   double Median(int x, int y, int z);
   double RobustAverage(int x, int y, int z);
   int SaveNormalizedDistribution(const char *filename, int x);
   int Debug();

};
