/*
	Filename: dct.cpp

	INPUT:
		A[W*H]: signal matrix

	OUTPUT:
		B[W*H]: dct signal matrix
*/

#include "dct.h"
#include <math.h>

void dct (
  data_t A[],
  coef_t B[],
  int W,
  int H,
  int size, // 4 or 8
  float &Q
  ) {

  const double a0 = 1.0 / sqrt(size); 
  const double an = sqrt(2.0 / size);
  float max = 0.0f;
  // assume perfect tiling
  DCT_Loop: 
  for (int x = 0; x < H; x+=size){ 
    for (int y = 0; y < W; y+=size){ // loops over size x size blocks 
    
      for (int p = 0; p < size; p++){ // loop p idx and get coef for block
          double p_coef;
        if (p == 0) 
          p_coef = a0; 
        else 
          p_coef = an; 
          
        for (int q = 0; q < size; q++){ // loop q idx and get coef for block
          double q_coef;
          if (q == 0) 
            q_coef = a0; 
          else 
            q_coef = an; 
            
          double sum = 0;
          
          for (int m = 0; m < size; m++){ // loop m and n for summation
            double term1 = cos(M_PI * (2.0*m +1.0) * p / (2.0 * size)); 
            
            for (int n = 0; n < size; n++){ 
              double term2 = cos(M_PI * (2.0*n +1.0) * q / (2.0 * size)); 
              sum += (float)A[IDX(m+x,n+y,W)] * term1 * term2; 
            } 
          } 
          B[IDX(p+x,q+y,W)] = (coef_t)(p_coef * q_coef * sum); // conver to coef type
          if (B[IDX(p+x,q+y,W)] > max) {max = B[IDX(p+x,q+y,W)];}
            
        } 
      } 
    } 
  }
  Q = AP / max;
  for (int i = 0; i < H*W; i++){
    B[i] = (coef_t)(Q * B[i]);
  }
  return;
}



