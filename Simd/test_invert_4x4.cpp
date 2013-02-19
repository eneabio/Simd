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


using namespace performance;
using namespace matrix;

int main(int argc, char *argv[])
{
	int cycles = 1;

	for (int index = 1; index <= cycles; ++index) {
		printf("# cycles: %d\n", index);
		
		//InvertGa
		{
			float inMat [4][4];
			for (int row=0; row < 4; ++row) {
				for (int column = 0; column < 4; ++column) {
					if (row == column)
						inMat[row][column] = ((float)rand())/RAND_MAX;
					else
						inMat[row][column] = ((float)rand())/RAND_MAX;
				}
			}
			//print inMatrix
			//for (int row=0; row < 4; ++row) {
			//	for (int column = 0; column < 4; ++column) {
			//		printf("# inMat[%d][%d]: %f\n", row, column, inMat[row][column]);
			//	}
			//}
			float outMat[4][4];
			/* initialize random seed: */
			srand (time(NULL));
			uint64_t start = Start();
			InvertGa(inMat, outMat);
			uint64_t stop = Stop();
			double time = ExecutionTime(start, stop);
			printf("Execution time Ga = %e \n", time);
			//print outMatrix
			//for (int row=0; row < 4; ++row) {
			//	for (int column = 0; column < 4; ++column) {
			//		printf("# outMat[%d][%d]: %f\n", row, column, outMat[row][column]);
			//	}
			//}
		}
		
		//InvertCr
		{
			float inMat [16];
			for (int i=0; i < 16; ++i) {
				inMat[i] = ((float)rand())/RAND_MAX;;
			}
			//print inMatrix
			//for (int i=0; i < 16; ++i) {
			//	printf("# inMat[%d]: %f\n", i, inMat[i]);
			//}
			float outMat[16];
			/* initialize random seed: */
			srand (time(NULL));
			uint64_t start = Start();
			InvertCr(inMat, outMat);
			uint64_t stop = Stop();
			double time = ExecutionTime(start, stop);
			printf("Execution time Cr = %e \n", time);
			//print outMatrix
			//for (int i=0; i < 16; ++i) {
			//	printf("# outMat[%d]: %f\n", i, outMat[i]);
			//}
		}
		
		//Invert SIMD
		{
			float inMat [16];
			for (int i=0; i < 16; ++i) {
				inMat[i] = ((float)rand())/RAND_MAX;;
			}
			//print inMatrix
			//for (int i=0; i < 16; ++i) {
			//	printf("# inMat[%d]: %f\n", i, inMat[i]);
			//}
			/* initialize random seed: */
			srand (time(NULL));
			uint64_t start = Start();
			PIII_Inverse_4x4(inMat);
			uint64_t stop = Stop();
			double time = ExecutionTime(start, stop);
			printf("Execution time SIMD = %e \n", time);
			//print outMatrix
			//for (int i=0; i < 16; ++i) {
			//	printf("# inMat[%d]: %f\n", i, inMat[i]);
			//}
		}
	}
	return 0;
}

