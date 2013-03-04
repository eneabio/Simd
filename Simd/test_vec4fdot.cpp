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

//typedef short    F16;
typedef float    F32;
typedef double   F64;


using namespace performance;
using namespace matrix;

#ifdef _WIN32

		#if defined(__MINGW32__) || defined(__CYGWIN__) || (defined (_MSC_VER) && _MSC_VER < 1300)

			#define SIMD_FORCE_INLINE inline
			#define ATTRIBUTE_ALIGNED16(a) a
			#define ATTRIBUTE_ALIGNED64(a) a
			#define ATTRIBUTE_ALIGNED128(a) a
		#else
			//#define BT_HAS_ALIGNED_ALLOCATOR
			#pragma warning(disable : 4324) // disable padding warning
//			#pragma warning(disable:4530) // Disable the exception disable but used in MSCV Stl warning.
//			#pragma warning(disable:4996) //Turn off warnings about deprecated C routines
//			#pragma warning(disable:4786) // Disable the "debug name too long" warning

			#define SIMD_FORCE_INLINE __forceinline
			#define ATTRIBUTE_ALIGNED16(a)   __declspec(align(16))   a
			#define ATTRIBUTE_ALIGNED64(a)   __declspec(align(64))   a
			#define ATTRIBUTE_ALIGNED128(a)  __declspec (align(128)) a
		#ifdef _XBOX
			#define BT_USE_VMX128

			#include <ppcintrinsics.h>
 			#define BT_HAVE_NATIVE_FSEL
 			#define btFsel(a,b,c) __fsel((a),(b),(c))
		#else

#if (defined (_WIN32) && (_MSC_VER) && _MSC_VER >= 1400) && (!defined (BT_USE_DOUBLE_PRECISION))
			#define BT_USE_SSE
			#ifdef BT_USE_SSE
			//BT_USE_SSE_IN_API is disabled under Windows by default, because 
			//it makes it harder to integrate Bullet into your application under Windows 
			//(structured embedding Bullet structs/classes need to be 16-byte aligned)
			//with relatively little performance gain
			//If you are not embedded Bullet data in your classes, or make sure that you align those classes on 16-byte boundaries
			//you can manually enable this line or set it in the build system for a bit of performance gain (a few percent, dependent on usage)
			//#define BT_USE_SSE_IN_API
			#endif //BT_USE_SSE
			#include <emmintrin.h>
#endif

		#endif//_XBOX

		#endif //__MINGW32__
#endif

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
		int ret = 1;
		
		#if defined (_M_IX86_FP)

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

		#endif  //defined (__SSE4_1__)


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

