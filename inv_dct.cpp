/*
	Filename: inv_dct.cpp

	INPUT:
		A[W*H]: dct signal matrix

	OUTPUT:
		B[W*H]: reconstruct pixel matrix
*/

#include "inv_dct.h"
#include <math.h>

void inv_dct (
  data_t A[],
  coef_t B[],
  int W,
  int H,
  int size, // 4 or 8
  float Q
  ) {

  const double a0 = 1.0 / sqrt(size); 
  const double an = sqrt(2.0 / size);

  for (int i = 0; i < H*W; i++){
    A[i] /= Q;
  }

  // assume perfect tiling
  INV_DCT_Loop: 
  for (int x = 0; x < H; x+=size){ 
    for (int y = 0; y < W; y+=size){ // loops over size x size blocks 
    
      for (int m = 0; m < size; m++){ // loop m and n for summation
        for (int n = 0; n < size; n++){  
      
          double sum = 0;
          
          for (int p = 0; p < size; p++){  // loop p and q within summation
            double p_coef;
            if (p == 0) 
              p_coef = a0; 
            else 
              p_coef = an; 
            double term1 = cos(M_PI * (2.0*m +1.0) * p / (2.0 * size)); 
            
            for (int q = 0; q < size; q++){ 
              double q_coef;
              if (q == 0) 
                q_coef = a0; 
              else 
                q_coef = an;
                
              double term2 = cos(M_PI * (2.0*n +1.0) * q / (2.0 * size));  
              sum += p_coef * q_coef * A[IDX(p+x,q+y,W)] * term1 * term2; 
            } 
          } 
            
          B[IDX(m+x,n+y,W)] = (data_t)(sum + 0.5f); // conver to data type, 0.5 for rounding not truncate
            
        } 
      } 
    } 
  }
  return;
}



