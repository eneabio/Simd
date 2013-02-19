#include "matrix4x4.h"

namespace matrix {
	void InvertGa(float b[][4], float a[][4])
	{
		/********************************************************************
		 *
		 *  input:
		 *    b - pointer to array of 16 single floats (source matrix)
		 *  output:
		 *    a - pointer to array of 16 single floats (invert matrix)
		 *
		 ********************************************************************/
		long indxc[4], indxr[4], ipiv[4];
		long i, icol, irow, j, ir, ic;
		float big, dum, pivinv, temp, bb;
		ipiv[0] = -1;
		ipiv[1] = -1;
		ipiv[2] = -1;
		ipiv[3] = -1;
		a[0][0] = b[0][0];
		a[1][0] = b[1][0];
		a[2][0] = b[2][0];
		a[3][0] = b[3][0];
		a[0][1] = b[0][1];
		a[1][1] = b[1][1];
		a[2][1] = b[2][1];
		a[3][1] = b[3][1];
		a[0][2] = b[0][2];
		a[1][2] = b[1][2];
		a[2][2] = b[2][2];
		a[3][2] = b[3][2];
		a[0][3] = b[0][3];
		a[1][3] = b[1][3];
		a[2][3] = b[2][3];
		a[3][3] = b[3][3];
		for (i = 0; i < 4; i++) {
			big = 0.0f;
			for (j = 0; j < 4; j++) {
				if (ipiv[j] != 0) {
					if (ipiv[0] == -1) {
						if ((bb = (float) fabs(a[j][0])) > big) {
							big = bb;
							irow = j;
							icol = 0;
						}
					} else if (ipiv[0] > 0) {
						return;
					}
					if (ipiv[1] == -1) {
						if ((bb = (float) fabs((float) a[j][1])) > big) {
							big = bb;
							irow = j;
							icol = 1;
						}
					} else if (ipiv[1] > 0) {
						return;
					}
					if (ipiv[2] == -1) {
						if ((bb = (float) fabs((float) a[j][2])) > big) {
							big = bb;
							irow = j;
							icol = 2;
						}
					} else if (ipiv[2] > 0) {
						return;
					}
					if (ipiv[3] == -1) {
						if ((bb = (float) fabs((float) a[j][3])) > big) {
							big = bb;
							irow = j;
							icol = 3;
						}
					} else if (ipiv[3] > 0) {
						return;
					}
				}
			}
			++(ipiv[icol]);
			if (irow != icol) {
				temp = a[irow][0];
				a[irow][0] = a[icol][0];
				a[icol][0] = temp;
				temp = a[irow][1];
				a[irow][1] = a[icol][1];
				a[icol][1] = temp;
				temp = a[irow][2];
				a[irow][2] = a[icol][2];
				a[icol][2] = temp;
				temp = a[irow][3];
				a[irow][3] = a[icol][3];
				a[icol][3] = temp;
			}
			indxr[i] = irow;
			indxc[i] = icol;
			if (a[icol][icol] == 0.0) {
				return;
			}
			pivinv = 1.0f / a[icol][icol];
			a[icol][icol] = 1.0f;
			a[icol][0] *= pivinv;
			a[icol][1] *= pivinv;
			a[icol][2] *= pivinv;
			a[icol][3] *= pivinv;
			if (icol != 0) {
				dum = a[0][icol];
				a[0][icol] = 0.0f;
				a[0][0] -= a[icol][0] * dum;
				a[0][1] -= a[icol][1] * dum;
				a[0][2] -= a[icol][2] * dum;
				a[0][3] -= a[icol][3] * dum;
			}
			if (icol != 1) {
				dum = a[1][icol];
				a[1][icol] = 0.0f;
				a[1][0] -= a[icol][0] * dum;
				a[1][1] -= a[icol][1] * dum;
				a[1][2] -= a[icol][2] * dum;
				a[1][3] -= a[icol][3] * dum;
			}
			if (icol != 2) {
				dum = a[2][icol];
				a[2][icol] = 0.0f;
				a[2][0] -= a[icol][0] * dum;
				a[2][1] -= a[icol][1] * dum;
				a[2][2] -= a[icol][2] * dum;
				a[2][3] -= a[icol][3] * dum;
			}
			if (icol != 3) {
				dum = a[3][icol];
				a[3][icol] = 0.0f;
				a[3][0] -= a[icol][0] * dum;
				a[3][1] -= a[icol][1] * dum;
				a[3][2] -= a[icol][2] * dum;
				a[3][3] -= a[icol][3] * dum;
			}
		}
		if (indxr[3] != indxc[3]) {
			ir = indxr[3];
			ic = indxc[3];
			temp = a[0][ir];
			a[0][ir] = a[0][ic];
			a[0][ic] = temp;
			temp = a[1][ir];
			a[1][ir] = a[1][ic];
			a[1][ic] = temp;
			temp = a[2][ir];
			a[2][ir] = a[2][ic];
			a[2][ic] = temp;
			temp = a[3][ir];
			a[3][ir] = a[3][ic];
			a[3][ic] = temp;
		}
		if (indxr[2] != indxc[2]) {
			ir = indxr[2];
			ic = indxc[2];
			temp = a[0][ir];
			a[0][ir] = a[0][ic];
			a[0][ic] = temp;
			temp = a[1][ir];
			a[1][ir] = a[1][ic];
			a[1][ic] = temp;
			temp = a[2][ir];
			a[2][ir] = a[2][ic];
			a[2][ic] = temp;
			temp = a[3][ir];
			a[3][ir] = a[3][ic];
			a[3][ic] = temp;
		}
		if (indxr[1] != indxc[1]) {
			ir = indxr[1];
			ic = indxc[1];
			temp = a[0][ir];
			a[0][ir] = a[0][ic];
			a[0][ic] = temp;
			temp = a[1][ir];
			a[1][ir] = a[1][ic];
			a[1][ic] = temp;
			temp = a[2][ir];
			a[2][ir] = a[2][ic];
			a[2][ic] = temp;
			temp = a[3][ir];
			a[3][ir] = a[3][ic];
			a[3][ic] = temp;
		}
		if (indxr[0] != indxc[0]) {
			ir = indxr[0];
			ic = indxc[0];
			temp = a[0][ir];
			a[0][ir] = a[0][ic];
			a[0][ic] = temp;
			temp = a[1][ir];
			a[1][ir] = a[1][ic];
			a[1][ic] = temp;
			temp = a[2][ir];
			a[2][ir] = a[2][ic];
			a[2][ic] = temp;
			temp = a[3][ir];
			a[3][ir] = a[3][ic];
			a[3][ic] = temp;
		}
	}
	
	void InvertCr(float *mat, float *dst)
	/************************************************************
	 *
	 *  input:
	 *    mat - pointer to array of 16 floats (source matrix)
	 *  output:
	 *    dst - pointer to array of 16 floats (invert matrix)
	 *
	 *************************************************************/
	{
		float    tmp[12]; /* temp array for pairs                      */
		float    src[16]; /* array of transpose source matrix */
		float    det;     /* determinant                                  */
		/* transpose matrix */
		for (int i = 0; i < 4; i++) {
			src[i]        = mat[i*4];
			src[i + 4]    = mat[i*4 + 1];
			src[i + 8]    = mat[i*4 + 2];
			src[i + 12]   = mat[i*4 + 3];
		}
		/* calculate pairs for first 8 elements (cofactors) */
		tmp[0]  = src[10] * src[15];
		tmp[1]  = src[11] * src[14];
		tmp[2]  = src[9]  * src[15];
		tmp[3]  = src[11] * src[13];
		tmp[4]  = src[9]  * src[14];
		tmp[5]  = src[10] * src[13];
		tmp[6]  = src[8]  * src[15];
		tmp[7]  = src[11] * src[12];
		tmp[8]  = src[8]  * src[14];
		tmp[9]  = src[10] * src[12];
		tmp[10] = src[8]  * src[13];
		tmp[11] = src[9]  * src[12];
		/* calculate first 8 elements (cofactors) */
		dst[0]  = tmp[0]*src[5] + tmp[3]*src[6] + tmp[4]*src[7];
		dst[0] -= tmp[1]*src[5] + tmp[2]*src[6] + tmp[5]*src[7];
		dst[1]  = tmp[1]*src[4] + tmp[6]*src[6] + tmp[9]*src[7];
		dst[1] -= tmp[0]*src[4] + tmp[7]*src[6] + tmp[8]*src[7];
		dst[2]  = tmp[2]*src[4] + tmp[7]*src[5] + tmp[10]*src[7];
		dst[2] -= tmp[3]*src[4] + tmp[6]*src[5] + tmp[11]*src[7];
		dst[3]  = tmp[5]*src[4] + tmp[8]*src[5] + tmp[11]*src[6];
		dst[3] -= tmp[4]*src[4] + tmp[9]*src[5] + tmp[10]*src[6];
		dst[4]  = tmp[1]*src[1] + tmp[2]*src[2] + tmp[5]*src[3];
		dst[4] -= tmp[0]*src[1] + tmp[3]*src[2] + tmp[4]*src[3];
		dst[5]  = tmp[0]*src[0] + tmp[7]*src[2] + tmp[8]*src[3];
		dst[5] -= tmp[1]*src[0] + tmp[6]*src[2] + tmp[9]*src[3];
		dst[6]  = tmp[3]*src[0] + tmp[6]*src[1] + tmp[11]*src[3];
		dst[6] -= tmp[2]*src[0] + tmp[7]*src[1] + tmp[10]*src[3];
		dst[7]  = tmp[4]*src[0] + tmp[9]*src[1] + tmp[10]*src[2];
		dst[7] -= tmp[5]*src[0] + tmp[8]*src[1] + tmp[11]*src[2];
		/* calculate pairs for second 8 elements (cofactors) */
		tmp[0]  = src[2]*src[7];
		tmp[1]  = src[3]*src[6];
		tmp[2]  = src[1]*src[7];
		tmp[3]  = src[3]*src[5];
		tmp[4]  = src[1]*src[6];
		tmp[5]  = src[2]*src[5];
		tmp[6]  = src[0]*src[7];
		tmp[7]  = src[3]*src[4];
		tmp[8]  = src[0]*src[6];
		tmp[9]  = src[2]*src[4];
		tmp[10] = src[0]*src[5];
		tmp[11] = src[1]*src[4];
		/* calculate second 8 elements (cofactors) */
		dst[8]  = tmp[0]*src[13] + tmp[3]*src[14] + tmp[4]*src[15];
		dst[8] -= tmp[1]*src[13] + tmp[2]*src[14] + tmp[5]*src[15];
		dst[9]  = tmp[1]*src[12] + tmp[6]*src[14] + tmp[9]*src[15];
		dst[9] -= tmp[0]*src[12] + tmp[7]*src[14] + tmp[8]*src[15];
		dst[10] = tmp[2]*src[12] + tmp[7]*src[13] + tmp[10]*src[15];
		dst[10]-= tmp[3]*src[12] + tmp[6]*src[13] + tmp[11]*src[15];
		dst[11] = tmp[5]*src[12] + tmp[8]*src[13] + tmp[11]*src[14];
		dst[11]-= tmp[4]*src[12] + tmp[9]*src[13] + tmp[10]*src[14];
		dst[12] = tmp[2]*src[10] + tmp[5]*src[11] + tmp[1]*src[9];
		dst[12]-= tmp[4]*src[11] + tmp[0]*src[9] + tmp[3]*src[10];
		dst[13] = tmp[8]*src[11] + tmp[0]*src[8] + tmp[7]*src[10];
		dst[13]-= tmp[6]*src[10] + tmp[9]*src[11] + tmp[1]*src[8];
		dst[14] = tmp[6]*src[9] + tmp[11]*src[11] + tmp[3]*src[8];
		dst[14]-= tmp[10]*src[11] + tmp[2]*src[8] + tmp[7]*src[9];
		dst[15] = tmp[10]*src[10] + tmp[4]*src[8] + tmp[9]*src[9];
		dst[15]-= tmp[8]*src[9] + tmp[11]*src[10] + tmp[5]*src[8];
		/* calculate determinant */
		det=src[0]*dst[0]+src[1]*dst[1]+src[2]*dst[2]+src[3]*dst[3];
		/* calculate matrix inverse */
		det = 1/det;
		for (int j = 0; j < 16; j++)
			dst[j] *= det;
	}
	
	void PIII_Inverse_4x4(float* src)
	{
		__m128 minor0, minor1, minor2, minor3;
		__m128 row0,   row1,   row2,   row3;
		__m128 det,    tmp1;
		tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src)), (__m64*)(src+ 4));
		row1 = _mm_loadh_pi(_mm_loadl_pi(row1, (__m64*)(src+8)), (__m64*)(src+12));
		row0 = _mm_shuffle_ps(tmp1, row1, 0x88);
		row1 = _mm_shuffle_ps(row1, tmp1, 0xDD);
		tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src+ 2)), (__m64*)(src+ 6));
		row3 = _mm_loadh_pi(_mm_loadl_pi(row3, (__m64*)(src+10)), (__m64*)(src+14));
		row2 = _mm_shuffle_ps(tmp1, row3, 0x88);
		row3 = _mm_shuffle_ps(row3, tmp1, 0xDD);
		// -----------------------------------------------
		tmp1 = _mm_mul_ps(row2, row3);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
		minor0 = _mm_mul_ps(row1, tmp1);
		minor1 = _mm_mul_ps(row0, tmp1);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
		minor0 = _mm_sub_ps(_mm_mul_ps(row1, tmp1), minor0);
		minor1 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor1);
		minor1 = _mm_shuffle_ps(minor1, minor1, 0x4E);
		// -----------------------------------------------
		tmp1 = _mm_mul_ps(row1, row2);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
		minor0 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor0);
		minor3 = _mm_mul_ps(row0, tmp1);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
		minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row3, tmp1));
		minor3 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor3);
		minor3 = _mm_shuffle_ps(minor3, minor3, 0x4E);
		// -----------------------------------------------
		tmp1 = _mm_mul_ps(_mm_shuffle_ps(row1, row1, 0x4E), row3);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
		row2 = _mm_shuffle_ps(row2, row2, 0x4E);
		minor0 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor0);
		minor2 = _mm_mul_ps(row0, tmp1);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
		minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row2, tmp1));
		minor2 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor2);
		minor2 = _mm_shuffle_ps(minor2, minor2, 0x4E);
		// -----------------------------------------------
		tmp1 = _mm_mul_ps(row0, row1);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
		minor2 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor2);
		minor3 = _mm_sub_ps(_mm_mul_ps(row2, tmp1), minor3);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
		minor2 = _mm_sub_ps(_mm_mul_ps(row3, tmp1), minor2);
		minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row2, tmp1));
		// -----------------------------------------------
		tmp1 = _mm_mul_ps(row0, row3);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
		minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row2, tmp1));
		minor2 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor2);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
		minor1 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor1);
		minor2 = _mm_sub_ps(minor2, _mm_mul_ps(row1, tmp1));
		// -----------------------------------------------
		tmp1 = _mm_mul_ps(row0, row2);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
		minor1 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor1);
		minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row1, tmp1));
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
		minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row3, tmp1));
		minor3 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor3);
		// -----------------------------------------------
		det = _mm_mul_ps(row0, minor0);
		det = _mm_add_ps(_mm_shuffle_ps(det, det, 0x4E), det);
		det = _mm_add_ss(_mm_shuffle_ps(det, det, 0xB1), det);
		tmp1 = _mm_rcp_ss(det);
		det = _mm_sub_ss(_mm_add_ss(tmp1, tmp1), _mm_mul_ss(det, _mm_mul_ss(tmp1, tmp1)));
		det = _mm_shuffle_ps(det, det, 0x00);
		minor0 = _mm_mul_ps(det, minor0);
		_mm_storel_pi((__m64*)(src), minor0);
		_mm_storeh_pi((__m64*)(src+2), minor0);
		minor1 = _mm_mul_ps(det, minor1);
		_mm_storel_pi((__m64*)(src+4), minor1);
		_mm_storeh_pi((__m64*)(src+6), minor1);
		minor2 = _mm_mul_ps(det, minor2);
		_mm_storel_pi((__m64*)(src+ 8), minor2);
		_mm_storeh_pi((__m64*)(src+10), minor2);
		minor3 = _mm_mul_ps(det, minor3);
		_mm_storel_pi((__m64*)(src+12), minor3);
		_mm_storeh_pi((__m64*)(src+14), minor3);
	}
}

