//
//  averager.cpp
//  Robust averager
//
//  Created by Stefan Ritt on 3/2/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "averager.h"

/*----------------------------------------------------------------*/

Averager::Averager(int nx, int ny, int nz, int dim)
{
   fNx = nx;
   fNy = ny;
   fNz = nz;
   fDim = dim;
   
   int size = sizeof(float)*nx*ny*nz * dim;
   fArray = (float *)malloc(size);
   assert(fArray);
   fTmp = (float *)malloc(sizeof(float) * dim);
   assert(fTmp);
   memset(fArray, 0, size);
   size = sizeof(float)*nx*ny*nz;
   fN = (unsigned short *)malloc(size);
   assert(fN);
   memset(fN, 0, size);
}

/*----------------------------------------------------------------*/

Averager::~Averager()
{
   if (fN)
      free(fN);
   if (fArray)
      free(fArray);
   fN = NULL;
   fArray = NULL;
}

/*----------------------------------------------------------------*/

void Averager::Add(int x, int y, int z, float value)
{
   assert(x < fNx);
   assert(y < fNy);
   assert(z < fNz);
   
   int nIndex = (x*fNy + y)*fNz + z;
   if (fN[nIndex] == fDim - 1) // check if array full
      return;
   
   int aIndex = ((x*fNy + y)*fNz + z) * fDim + fN[nIndex];
   fN[nIndex]++;
   fArray[aIndex] = value;
}

/*----------------------------------------------------------------*/

void Averager::Reset()
{
   int size = sizeof(float)*fNx*fNy*fNz * fDim;
   memset(fArray, 0, size);
   size = sizeof(float)*fNx*fNy*fNz;
   memset(fN, 0, size);
}

/*----------------------------------------------------------------*/

int compar(const void *a, const void *b);

int compar(const void *a, const void *b)
{
   if (*((float *)a) == *((float *)b))
      return 0;
   
   return (*((float *)a) < *((float *)b)) ? -1 : 1;
}
           
double Averager::Average(int x, int y, int z)
{
   assert(x < fNx);
   assert(y < fNy);
   assert(z < fNz);

   double a = 0;
   
   int nIndex = (x*fNy + y)*fNz + z;
   int aIndex = ((x*fNy + y)*fNz + z) * fDim;

   for (int i=0 ; i<fN[nIndex] ; i++)
      a += fArray[aIndex + i];
   
   if (fN[nIndex] > 0)
      a /= fN[nIndex];
   
   return a;
}

/*----------------------------------------------------------------*/

double Averager::Median(int x, int y, int z)
{
   assert(x < fNx);
   assert(y < fNy);
   assert(z < fNz);
   
   double m = 0;
   
   int nIndex = (x*fNy + y)*fNz + z;
   int aIndex = ((x*fNy + y)*fNz + z) * fDim;
   
   memcpy(fTmp, &fArray[aIndex], fN[nIndex] * sizeof(float));
   
   qsort(fTmp, fN[nIndex], sizeof(float), compar);
   m = fTmp[fN[nIndex]/2];
   
   return m;
}

/*----------------------------------------------------------------*/

double Averager::RobustAverage(int x, int y, int z)
{
   assert(x < fNx);
   assert(y < fNy);
   assert(z < fNz);
   
   double ra = 0;
   int n = 0;
   
   int nIndex = (x*fNy + y)*fNz + z;
   int aIndex = ((x*fNy + y)*fNz + z) * fDim;
   
   // sort array
   memcpy(fTmp, &fArray[aIndex], fN[nIndex] * sizeof(float));
   qsort(fTmp, fN[nIndex], sizeof(float), compar);

   // average over central 50% of all samples
   for (int i=fN[nIndex]/4 ; i<fN[nIndex]/4*3 ; i++) {
      ra += fTmp[i];
      n++;
   }
   
   if (n > 0)
      ra /= n;

   return ra;
}

/*----------------------------------------------------------------*/

int Averager::SaveNormalizedDistribution(const char *filename, int x)
{
   assert(x < fNx);
   FILE *f = fopen(filename, "wt");
   
   if (!f)
      return 0;
   
   fprintf(f, "X, Y, Z, Min, Max, Ave, Sigma\n");
   
   for (int y=0 ; y<fNy ; y++)
      for (int z=0 ; z<fNz ; z++) {
         
         int nIndex = (x*fNy + y)*fNz + z;
         int aIndex = ((x*fNy + y)*fNz + z) * fDim;
         
         if (fN[nIndex] > 1) {
            fprintf(f, "%d,%d, %d, ", x, y, z);
            
            double s = 0;
            double s2 = 0;
            double min = 0;
            double max = 0;
            int n = fN[nIndex];
            double m = Median(x, y, z);
            
            for (int i=0 ; i<n ; i++) {
               double v = fArray[aIndex + i] - m;
               s += v;
               s2 += v*v;
               if (v < min)
                  min = v;
               if (v > max)
                  max = v;
            }
            double sigma = sqrt((n * s2 - s * s) / (n * (n-1)));
            double average = s / n;
            
            fprintf(f, "%6.4lf, %6.4lf, %6.4lf, %8.6lf, ", min, max, average, sigma);
            
            for (int i=0 ; i<n ; i++)
               fprintf(f, "%6.4lf,", fArray[aIndex + i] - m);
            
            fprintf(f, "\n");
         }
      }
   
   fclose(f);
   return 1;
}
