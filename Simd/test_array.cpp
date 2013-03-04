//
//  main.cpp
//  Simd
//
//  Created by enea  on 2/4/13.
//  Copyright (c) 2013 enea . All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <ctime>
#include <stdlib.h>
//#include <xmmintrin.h> // Contain the SSE compiler intrinsics
#include <smmintrin.h> //Contain the SSE compiler intrinsics SSE4
#include <nmmintrin.h> //Contain the SSE compiler intrinsics SSE4

//#include <malloc.h>
#include "performance.h"
#include <math.h>
#include <time.h>       /* time */
#include <windows.h>

void myssefunctionSIMD ( float* pArray1, float* pArray2, float* pResult, int nSize);
void myssefunction     ( float* pArray1, float* pArray2, float* pResult, int nSize);
void * malloc_simd     (const size_t size);
void  free_simd       (void * p);

int main(int argc, char *argv[])
{
	using namespace performance;
	
	for (int j = 0; j <= 6; ++j) {
		int array_size = 4 * pow (10.f, j);  //original was 10
		float* m_fArray1 = (float*) malloc_simd(array_size * sizeof(float));
		float* m_fArray2 = (float*) malloc_simd(array_size * sizeof(float));
		float* m_fArray3 = (float*) malloc_simd(array_size * sizeof(float));
	
		printf("# cycles: %d\n", array_size);
		{
			/* initialize random seed: */
			srand (time(NULL));
			for (int i = 0; i < array_size; ++i)
			{
				//original
				m_fArray1[i] = ((float)rand())/RAND_MAX;
				m_fArray2[i] = ((float)rand())/RAND_MAX;
				m_fArray1[i] = i + 1.f;
				m_fArray2[i] = i + 2.f;
			}
			Clock start = Start();
			myssefunction(m_fArray1 , m_fArray2 , m_fArray3, array_size);
			Clock stop = Stop();
			double time = ExecutionTime(start, stop);
			//printf("Execution time without SIMD = %e \n", time);
			printf("\nTime in microseconds Execution time without SIMD= %1.12lf \n",1000000*time);
		}
		
		{
			/* initialize random seed: */
			srand (time(NULL));
			for (int i = 0; i < array_size; ++i)
			{
				//original
				m_fArray1[i] = ((float)rand())/RAND_MAX;
				m_fArray2[i] = ((float)rand())/RAND_MAX;
				m_fArray1[i] = i + 1.f;
				m_fArray2[i] = i + 2.f;
			}
			Clock startSimd = Start();
			myssefunctionSIMD(m_fArray1 , m_fArray2 , m_fArray3, array_size);
			Clock stopSimd = Stop();
			double timeSimd = ExecutionTime(startSimd, stopSimd);
			printf("\nTime in microseconds Execution time with SIMD= %1.12lf \n",1000000*timeSimd);
		}
	
		{
			/* initialize random seed: */
			srand (time(NULL));
			for (int i = 0; i < array_size; ++i)
			{
				//original
				m_fArray1[i] = ((float)rand())/RAND_MAX;
				m_fArray2[i] = ((float)rand())/RAND_MAX;
				m_fArray1[i] = i + 1.f;
				m_fArray2[i] = i + 2.f;
			}
			int a=0;
			Clock startExample = Start();
			Sleep(1000);
			Clock stopExample = Stop();
			double timeExample = ExecutionTime(startExample, stopExample);
			printf("\n Time in microseconds Execution time: Sleep(1000) (1000 milliseconds)= %e \n",1000000 * timeExample);
		}

		free_simd(m_fArray1);
		free_simd(m_fArray2);
		free_simd(m_fArray3);
		
	}
	
	return 0;
}

void * malloc_simd(const size_t size)
{
#if defined WIN32           // WIN32
	return _aligned_malloc(size, 16);
#elif defined __linux__     // Linux
	return memalign(16, size);
#elif defined __MACH__      // Mac OS X
	return malloc(size);
#else                       // other (use valloc for page-aligned memory)
	return valloc(size);
#endif
}

void  free_simd(void * p)
{
#if defined WIN32           // WIN32
	_aligned_free(p);
	return;
#elif defined __linux__     // Linux
	free(p);
#elif defined __MACH__      // Mac OS X
	free(p);
#else                       // other (use valloc for page-aligned memory)
	free(p);
#endif
}

void myssefunctionSIMD
(
 float* pArray1,                   // [in] first source array
 float* pArray2,                   // [in] second source array
 float* pResult,                   // [out] result array
 int nSize                         // [in] size of all arrays
 )
{
	const __m128 m0_5 = _mm_set_ps1(0.5f);        // m0_5[0, 1, 2, 3] = 0.5
	for (size_t index = 0; index < nSize; index += 4)
	{
		__m128 pSrc1 = _mm_load_ps(pArray1 + index); // load 4 elements from memory into SSE register
		__m128 pSrc2 = _mm_load_ps(pArray2 + index); // load 4 elements from memory into SSE register
		
		__m128 m1   = _mm_mul_ps(pSrc1, pSrc1);        // m1 = *pSrc1 * *pSrc1
		__m128 m2   = _mm_mul_ps(pSrc2, pSrc2);        // m2 = *pSrc2 * *pSrc2
		__m128 m3   = _mm_add_ps(m1, m2);                // m3 = m1 + m2
		__m128 m4   = _mm_sqrt_ps(m3);                   // m4 = sqrt(m3)
		__m128 pDest  = _mm_add_ps(m4, m0_5);          // pDest = m4 + 0.5
		
		_mm_store_ps(pResult + index, pDest); // store 4 elements from SSE register to memory.
	}
}

void myssefunction
(
 float* pArray1,                   // [in] first source array
 float* pArray2,                   // [in] second source array
 float* pResult,                   // [out] result array
 int nSize                         // [in] size of all arrays
 )
{
	for (size_t i = 0; i < nSize; i += 1)
	{
		pResult[i] = sqrtf((pArray1[i] * pArray1[i]) + (pArray2[i] * pArray2[i])) + 0.5f;
	}
}
