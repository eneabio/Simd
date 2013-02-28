#ifndef MATRIX4X4_H__
#define MATRIX4X4_H__

#include <math.h>
#include <xmmintrin.h> // Contain the SSE compiler intrinsics

namespace matrix {
	void InvertGa         (float b[][4], float a[][4]);  //Gaussian elimination
	void InvertCr         (float *mat, float *dst);      //Cramer's rule
	void PIII_Inverse_4x4 (float* src);                  //Cramer's rule and Streaming SIMD Extensions
}

#endif