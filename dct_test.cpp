/*
	Filename: dct_test.h
		Testbench file
		Calls dct() function from dct.cpp
		Compares the output from dct() with out.gold.dat
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "dct.h"
#include "inv_dct.h"
#include "top_dct.h"


void print_arr(float arr[], int W, int  H){
  printf("[");
  for (int i = 0; i < H; i++){
  printf("[");
    for (int j = 0; j < W; j++){
      printf("%f, ",arr[IDX(i,j,W)]);
    }
    printf("]\n");
  }
  printf("]\n\n");
} // no longer needed but used for debugging

void calc_stats(data_t A[], data_t C[], const int N){
  
  unsigned int exact = 0;        // exact integer matches
  unsigned int within1 = 0;      // pixels with abs diff 1 or less
  unsigned int within2 = 0;      
  unsigned int within3 = 0;      
  double sse = 0.0;     // sum of squared error

  for (int i = 0; i < N; ++i) {
    data_t a = A[i];
    data_t c = C[i];
    int d = a - c; // difference
    if (d == 0) ++exact;
    if (d <= 1 && d >= -1) ++within1;
    if (d <= 2 && d >= -2) ++within2;
    if (d <= 3 && d >= -3) ++within3;
    sse += (double)d * (double)d; // for copmuting mse
  }

  double mse = (double)(sse / (double)N);
  double acc = 100.0 * (double)exact / (double)N;
  double acc_within1 = 100.0 * (double)within1 / (double)N;
  double acc_within2 = 100.0 * (double)within2 / (double)N;
  double acc_within3 = 100.0 * (double)within3 / (double)N;
  double psnr = 10.0 * log10((255.0 * 255.0) / mse); // psnr formula

  printf("Pixels: %d \n\n", N); // not sure why need extra /n to print statement below
  printf("Exact matches:   %d (%.2f%%)\n", exact, acc);
  printf("Within ±1:       %d (%.2f%%)\n", within1, acc_within1);
  printf("Within ±2:       %d (%.2f%%)\n", within2, acc_within2);
  printf("Within ±3:       %d (%.2f%%)\n", within3, acc_within3);
  printf("MSE: %.6f\n", mse);
  printf("PSNR: %.6f\n", psnr);

  if (acc_within3 > 50.0){
    fprintf(stdout, "*******************************************\n");
    fprintf(stdout, "PASS: ACCURACY ABOVE THRESHOLD!\n");
    fprintf(stdout, "*******************************************\n");
  } else {
   	fprintf(stdout, "*******************************************\n");
   	fprintf(stdout, "FAIL: ACCURACY TOO LOW!\n");
   	fprintf(stdout, "*******************************************\n");
  }
}

int main () {
  FILE *fp, *fin, *fcoef;
  //open needed files
  fin = fopen("in.dat","r");
  if (!fin) { perror("in.dat"); return 1; }

  fp  = fopen("out.dat","w");
  if (!fp)  { perror("out.dat"); fclose(fin); return 1; }

  fcoef  = fopen("coef.dat","w");
  if (!fcoef)  { perror("coef.dat"); fclose(fcoef); return 1; }

  //read in width and height
  int width, height;
  fscanf(fin, "%d %d", &width, &height);
  fprintf(fp,"%d %d\n",width, height);
  fprintf(fcoef,"%d %d\n",width, height);

  float Q; // quantization, used to reduce int range in dct coef
  int SAMPLES = width * height; // total pixels
  data_t *A, *C; // input arr and reconstructed arr
  coef_t *B; // dct coef arr
  A = new data_t[SAMPLES];
  B = new coef_t[SAMPLES];
  C = new data_t[SAMPLES];

  // take in in pixels
  for (int i=0;i<SAMPLES;i++) {
    int value;
	// fscanf(fin,"%d",&value);
    int err = fscanf(fin, "%d", &value);
    if (err != 1) {
        fprintf(stderr, "error at i=%d (err=%d)\n", i, err);
        return 1; // error reading, stop
    }
    A[i] = value; /// assign
  }
  

  top_dct(A, B, C, width, height, 4, Q); // compute

//   for (int i=0;i<SAMPLES;i++) {
//     fprintf(fcoef,"%d\n",B[i]); 
//   }
  
    // DONT NEED since using arr compare
    // print output to file
    for (int i=0;i<SAMPLES;i++) {
        fprintf(fp,"%d\n",C[i]); 
    }
  
  calc_stats(A, C, SAMPLES); // get stats

  delete[] A;
  delete[] B;
  delete[] C;

  fclose(fp);
  fclose(fin);
  fclose(fcoef);

  // first get rid off weird returns
  // system("tr -d '\r' < out.dat > out.norm");
  // system("tr -d '\r' < in.dat  > in.norm");

//   // convert to png
//   system(
//     "awk 'NR==1 { W=$1; H=$2; print \"P2\"; print W, H; print 255; next } "
//     "{ i = NR-1; printf \"%d\", $1; if ((i % W) == 0) printf \"\\n\"; else printf \" \" }' "
//     "data/out.dat > data/out.pgm\n"
//     "convert data/out.pgm data/out.png"
//   );

  return 0;
}

