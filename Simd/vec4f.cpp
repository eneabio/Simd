

#include "vec4f.h"

void Vec4fSum(const Vec4f&  l, const Vec4f&  r, Vec4f*  outVec) {
	outVec->x = r.x + l.x;
	outVec->y = r.y + l.y;
	outVec->z = r.z + l.z;
	outVec->w = r.w + l.w;
}

void Vec4fSumSIMD(const Vec4f&  l, const Vec4f&  r, Vec4f*  outVec) {
	__m128 in[2];
	//load elements
	in[0] = _mm_loadu_ps(l);
	in[1] = _mm_loadu_ps(r);
	//add
	__m128 somma = _mm_add_ps(in[0], in[1]);
	//store
	//it it would be better use _mm_store_ps instead of _mm_storeu_ps? but it doesn't work ...
	_mm_storeu_ps((float *) outVec[0], somma);
}

void Vec4fSumSIMDDirect(const Vec4f&  l, const Vec4f&  r, Vec4f*  outVec) {
	//__m128 in[2];
	//load elements
	//in[0] = _mm_loadu_ps(l);
	//in[1] = _mm_loadu_ps(r);
	//add
	//__m128 somma = _mm_add_ps(in[0], in[1]);
	//store
	//it it would be better use _mm_store_ps instead of _mm_storeu_ps? but it doesn't work ...
	//_mm_storeu_ps((float *) outVec[0], somma);
	outVec->data = _mm_add_ps(l.data,r.data);
}

void Vec4fSub(const Vec4f&  l, const Vec4f&  r, Vec4f*  outVec) {
	outVec->x = l.x - r.x;
	outVec->y = l.y - r.y;
	outVec->z = l.z - r.z;
	outVec->w = l.w - r.w;
}

void Vec4fSubSIMD(const Vec4f&  l, const Vec4f&  r, Vec4f*  outVec) {

	__m128 in[2];
	//load elements
	//it would be better using _mm_load_ps instead of _mm_loadu_ps but it doesn't work
	in[0] = _mm_loadu_ps(l);
	in[1] = _mm_loadu_ps(r);
	//add
	__m128 sub = _mm_sub_ps(in[0], in[1]);
	//store
	//it it would be better use _mm_store_ps instead of _mm_storeu_ps? but it doesn't work ...
	_mm_storeu_ps((float *) outVec[0], sub);
}

F32 Vec4fDot(const Vec4f&  l, const Vec4f&  r) {
	F32 xMul = l.x * r.x;
	F32 yMul = l.y * r.y;
	F32 zMul = l.z * r.z;
	F32 wMul = l.w * r.w;
	F32 res = xMul + yMul + zMul + wMul;
	return res;
}

F32 Vec4fDotSIMD(const Vec4f&  l, const Vec4f&  r) {
	__m128 in[2];
	//load elements
	//it would be better using _mm_load_ps instead of _mm_loadu_ps but it doesn't work
	in[0] = _mm_loadu_ps(l);
	in[1] = _mm_loadu_ps(r);
	//dot
	__m128 m = _mm_mul_ps(in[0], in[1]);
	__m128 t = _mm_add_ps(m, _mm_shuffle_ps(m, m, _MM_SHUFFLE(2, 3, 0, 1)));
	__m128 result = _mm_add_ps(t, _mm_shuffle_ps(t, t, _MM_SHUFFLE(1, 0, 3, 2)));
	return _mm_cvtss_f32(result);
}

F32 Vec4fDotSIMDSSE4(const Vec4f&  l, const Vec4f&  r) {
	__m128 in[2];
	//load elements
	//it would be better using _mm_load_ps instead of _mm_loadu_ps but it doesn't work
	in[0] = _mm_loadu_ps(l);
	in[1] = _mm_loadu_ps(r);
#if defined (__SSE4_1__)
#include <smmintrin.h>
	__m128 result = _mm_dp_ps(in[0], in[0], 0xF3);
	return (F32) result[0];
#endif
}

void Vec4fMultScalar(const Vec4f&   inVec4f, const F32 scalar, Vec4f* outVec){

	outVec->x = scalar * inVec4f.x;
	outVec->y = scalar * inVec4f.y;
	outVec->z = scalar * inVec4f.z;
	outVec->w = scalar * inVec4f.w;

	
}

void Vec4fMultScalarSIMD(const Vec4f&   inVec4f, const F32 scalar, Vec4f* outVec){
#if defined(FDK_USE_SSE_IN_API) && defined (FDK_USE_SSE) && (FDK_OS_OSX)
	__m128 in;
	//load elements
	in = _mm_loadu_ps(inVec4f);
	__m128	vs = _mm_load_ss(&scalar);	//	(S 0 0 0)
	vs = _mm_shuffle_ps(vs, vs, 0x00);	//	(S S S S)
	__m128 res = _mm_mul_ps(in, vs);
	_mm_storeu_ps((float *) outVec[0], res);
#elif defined(FDK_USE_NEON) && defined(FDK_OS_IOS)
	//mVec128 = vmulq_n_f32(mVec128, s);
#else
	outVec->x = scalar * inVec4f.x;
	outVec->y = scalar * inVec4f.y;
	outVec->z = scalar * inVec4f.z;
	outVec->w = scalar * inVec4f.w;
#endif
	
}
