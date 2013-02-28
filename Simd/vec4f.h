
#include <smmintrin.h> //Contain the SSE compiler intrinsics SSE4
//#include <nmmintrin.h> //Contain the SSE compiler intrinsics SSE4

//typedef short    F16;
typedef float    F32;
typedef double   F64;

struct Vec4f {
	
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
		struct {float x;
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
