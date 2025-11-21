/*
	Filename: types.h
	Header file
*/
// #include <ap_int.h>
// #include <ap_fixed.h>

// typedef ap_int<5> data_t;
typedef double	data_t;

typedef int	coef_t;
// typedef ap_int<5> coef_t;

// typedef ap_fixed<30, 16> calc_t
typedef double calc_t;

#ifndef IDX
#define IDX(r,c,W) ((r)*(W) + (c))
#endif

#ifndef AP
#define AP 256
#endif
