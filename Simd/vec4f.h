
#include <smmintrin.h> //Contain the SSE compiler intrinsics SSE4
//#include <nmmintrin.h> //Contain the SSE compiler intrinsics SSE4

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
			#define ATTRIBUTE_ALIGNED16(a) __declspec(align(16)) a
			#define ATTRIBUTE_ALIGNED64(a) __declspec(align(64)) a
			#define ATTRIBUTE_ALIGNED128(a) __declspec (align(128)) a
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

//typedef short    F16;
typedef float    F32;
typedef double   F64;



ATTRIBUTE_ALIGNED16(struct)  Vec4f {
	
	Vec4f(float _x,float _y,float _z,float _w) : x(_x),y(_y),z(_z),w(_w) {}
	
	Vec4f() {}
	
	operator const float*() const { return (const float*)(void*)this; }
	operator float* () const { return (float*)(void*)this; }
	
	float& operator()(int index) {
		//assert
		//assert(index >= 0);
		//assert(index < 4);
		return ((float*)this)[index];
	}
	const float& operator()(int index) const {
		//assert
		//assert(index >= 0);
		//assert(index < 4);
		return ((float*)this)[index];
	}
	union {
		ATTRIBUTE_ALIGNED16(struct) {float x;
		float y;
		float z;
			float w;};
		__m128 mVec128;
	};
	
};

void  Vec4fSum           (const Vec4f&  l, const Vec4f&  r, Vec4f*  outVec);
void  Vec4fSub           (const Vec4f&  l, const Vec4f&  r, Vec4f*  outVec);
F32   Vec4fDot           (const Vec4f&  l, const Vec4f&  r);
void Vec4fMultScalar     (const Vec4f&   inVec4f, const F32 scalar, Vec4f* outVec);

// SIMD, only for performance, after will be merge
void  Vec4fSumSIMD        (const Vec4f&  l, const Vec4f&  r, Vec4f*  outVec);
void  Vec4fSumSIMDDirect  (const Vec4f&  l, const Vec4f&  r, Vec4f*  outVec);
void  Vec4fSubSIMD        (const Vec4f&  l, const Vec4f&  r, Vec4f*  outVec);
F32   Vec4fDotSIMD        (const Vec4f&  l, const Vec4f&  r);
F32   Vec4fDotSIMDDirect(const Vec4f&  l, const Vec4f&  r);
F32   Vec4fDotSIMDSSE4(const Vec4f&  l, const Vec4f&  r);
void  Vec4fMultScalarSIMD(const Vec4f&   inVec4f, const F32 scalar, Vec4f* outVec);
