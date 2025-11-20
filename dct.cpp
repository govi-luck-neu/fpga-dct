/*
	Filename: dct.cpp

	INPUT:
		A[W*H]: signal matrix

	OUTPUT:
		B[W*H]: dct signal matrix
*/

#include "dct.h"
#include "types.h"
#include <math.h>

static const calc_t cos_lut_8[8][8] = {
    { 1.0000000000000000,  1.0000000000000000,  1.0000000000000000,  1.0000000000000000,
      1.0000000000000000,  1.0000000000000000,  1.0000000000000000,  1.0000000000000000 },

    { 0.9807852804032304,  0.8314696123025452,  0.5555702330196023,  0.1950903220161283,
     -0.1950903220161282, -0.5555702330196020, -0.8314696123025453, -0.9807852804032304 },

    { 0.9238795325112867,  0.3826834323650898, -0.3826834323650897, -0.9238795325112867,
     -0.9238795325112868, -0.3826834323650903,  0.3826834323650900,  0.9238795325112866 },

    { 0.8314696123025452, -0.1950903220161282, -0.9807852804032304, -0.5555702330196022,
      0.5555702330196020,  0.9807852804032304,  0.1950903220161286, -0.8314696123025455 },

    { 0.7071067811865476, -0.7071067811865475, -0.7071067811865477,  0.7071067811865474,
      0.7071067811865477, -0.7071067811865479, -0.7071067811865472,  0.7071067811865471 },

    { 0.5555702330196023, -0.9807852804032304,  0.1950903220161286,  0.8314696123025455,
     -0.8314696123025452, -0.1950903220161289,  0.9807852804032307, -0.5555702330196015 },

    { 0.3826834323650898, -0.9238795325112868,  0.9238795325112865, -0.3826834323650899,
     -0.3826834323650906,  0.9238795325112874, -0.9238795325112871,  0.3826834323650863 },

    { 0.1950903220161283, -0.5555702330196022,  0.8314696123025455, -0.9807852804032307,
      0.9807852804032304, -0.8314696123025440,  0.5555702330196044, -0.1950903220161251 }
};

void dct (
    data_t A[],
    coef_t B[],
    int W,
    int H,
    int size, // 4 or 8
    float &Q
    ) {

    const calc_t a0 = (calc_t)1.0 / sqrt((calc_t)size); 
    const calc_t an = sqrt((calc_t)2.0 / (calc_t)size);
    float max = 0.0f;
    // assume perfect tiling
    DCT_Loop: 
    for (int x = 0; x < H; x+=size){ 
        for (int y = 0; y < W; y+=size){ // loops over size x size blocks 
        
            for (int p = 0; p < size; p++){ // loop p idx and get coef for block
                calc_t p_coef;
                if (p == 0) 
                    p_coef = a0; 
                else 
                    p_coef = an; 
                
                for (int q = 0; q < size; q++){ // loop q idx and get coef for block
                    calc_t q_coef;
                    if (q == 0) 
                        q_coef = a0; 
                    else 
                        q_coef = an; 
                        
                    calc_t sum = 0;
                    
                    for (int m = 0; m < size; m++){ // loop m and n for summation
                        calc_t term1 = cos_lut_8[p][m];
                        
                        for (int n = 0; n < size; n++){ 
                            calc_t term2 = cos_lut_8[q][n]; 
                            sum += (calc_t)A[IDX(m+x,n+y,W)] * term1 * term2; 
                        } 
                    } 
                    B[IDX(p+x,q+y,W)] = (coef_t)(p_coef * q_coef * sum); // conver to coef type
                    if (B[IDX(p+x,q+y,W)] > max) {max = B[IDX(p+x,q+y,W)];}
                    if (-B[IDX(p+x,q+y,W)] > max) {max = -B[IDX(p+x,q+y,W)];}
                } 
            } 
        } 
    }
    
    Q = AP / max;
    Quant_Loop:
    for (int i = 0; i < H*W; i++){
        B[i] = (coef_t)(Q * B[i]);
    }
    return;
}



