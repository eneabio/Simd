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
#include <xmmintrin.h> // Contain the SSE compiler intrinsics
//#include <malloc.h>
#include "performance.h"
#include "matrix4x4.h"
#include <math.h>
#include <time.h>       /* time */
#include "vec4f.h"


using namespace performance;
using namespace matrix;

typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef int8_t   I8;
typedef int16_t  I16;
typedef int32_t  I32;
typedef int64_t  I64;

int main(int argc, char *argv[])
{
	int cycles = 10;
	
	for (int index = 1; index <= cycles; ++index) {
		printf("# cycles: %d\n", index);
		
		Vec4f l;
		Vec4f r;
		Vec4f result;
		
		U64 start;
		U64 stop;
		F64 current = 0.0;
		F64 elapsed = 0.0;
		I32 i;
		I32 count = 1000000;
		
		for(i=0;i<count;i++){
			/* initialize random seed: */
			srand((U32) time(NULL));
			
			l = Vec4f(((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX);
			r = Vec4f(((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX);
			
			start = Start();
			
			Vec4fDot(l, r);
			
			stop = Stop();
			current = ExecutionTime(start, stop);
			//WriteDebug("Time for iteration: %1.12lf \n",current);
			
			elapsed += current;
		}
		
		printf("\nTime in microseconds Vec4fDot without SIMD = %1.12lf \n",(1000000*elapsed)/count);
		
		current = 0.0;
		elapsed = 0.0;
		for(i=0;i<count;i++){
			/* initialize random seed: */
			srand((U32) time(NULL));
			
			l = Vec4f(((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX);
			r = Vec4f(((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX);
			l.mVec128 = _mm_set_ps(l.x, l.y, l.z, l.w);
			r.mVec128 = _mm_set_ps(r.x, r.y, r.z, r.w);
			
			start = Start();
			
			Vec4fDotSIMDSSE4(l, r);
			
			
			stop = Stop();
			current = ExecutionTime(start,stop);
			//WriteDebug("Time for iteration: %1.12lf \n",current);
			
			elapsed += current;
		}
		
		printf("\nTime in microseconds Vec4fDotSIMDSSE4= %1.12lf \n",(1000000*elapsed)/count);
//		
		current = 0.0;
		elapsed = 0.0;
		for(i=0;i<count;i++){
			/* initialize random seed: */
			srand((U32) time(NULL));
			
			l = Vec4f(((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX);
			r = Vec4f(((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX);
			
			start = Start();
			
			
			Vec4fDotSIMD(l, r);
			
			stop = Stop();
			current = ExecutionTime(start,stop);
			//WriteDebug("Time for iteration: %1.12lf \n",current);
			
			elapsed += current;
		}
		
		printf("\nTime in microseconds Vec4fDotSIMD= %1.12lf \n",(1000000*elapsed)/count);
		
		current = 0.0;
		elapsed = 0.0;
		for(i=0;i<count;i++){
			/* initialize random seed: */
			srand((U32) time(NULL));
			
			l = Vec4f(((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX);
			r = Vec4f(((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX);
			
			start = Start();
			
			
			Vec4fDotSIMDDirect(l, r);
			
			stop = Stop();
			current = ExecutionTime(start,stop);
			//WriteDebug("Time for iteration: %1.12lf \n",current);
			
			elapsed += current;
		}
		
		printf("\nTime in microseconds Vec4fDotSIMDDirect= %1.12lf \n",(1000000*elapsed)/count);
		
	}
	return 0;
}

