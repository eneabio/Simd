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

// Integer types
	#pragma warning (push,0)
	#include <cstdint>
	#pragma warning (pop)
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;

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
			F32 scalar = (float)rand()/RAND_MAX;
			
			start = Start();
			
			Vec4fMultScalar(l, scalar, &result);
			
			stop = Stop();
			current = ExecutionTime(start, stop);
			//WriteDebug("Time for iteration: %1.12lf \n",current);
			
			elapsed += current;
		}
		
		printf("\nTime in microseconds (TestPerformanceMathVec4fMultScalarSIMD without SIMD) = %1.12lf \n",(1000000*elapsed)/count);
		
		current = 0.0;
		elapsed = 0.0;
		for(i=0;i<count;i++){
			/* initialize random seed: */
			srand((U32) time(NULL));
			
			l = Vec4f(((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX, ((float)rand())/RAND_MAX);
			F32 scalar = (float)rand()/RAND_MAX;
			
			start = Start();
			
			Vec4fMultScalarSIMD(l, scalar, &result);
			
			stop = Stop();
			current = ExecutionTime(start,stop);
			//WriteDebug("Time for iteration: %1.12lf \n",current);
			
			elapsed += current;
		}
		
		printf("\nTime in microseconds (TestPerformanceMathVec4fMultScalarSIMD)= %1.12lf \n",(1000000*elapsed)/count);
		
	}
	return 0;
}

