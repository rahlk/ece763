/*Code to a add gaussian noise to an image.
Author: Rahul Krishna
Date: 01/18/2013 													*/
 
#include <stdio.h>
#include <ifs.h>
#include <math.h>
double gaussrand(int mean, int var);
void main() {
int row,col;/*counters */
IFSIMG img1,blur1_v1; /*Declare pointers to headers */
/* Read input image.*/
img1=ifspin("synth1.ifs");
int dim = 2;
int N= ifsdimen(img1, 0); /*No of columns in img1*/
int M = ifsdimen(img1, 1);    /*No of rows in img1*/ 
int len[3]={dim, M, N}; /*image to be created is two dimensional */
blur1_v1=ifscreate("int" ,len, IFS_CR_ALL,0);
for(row=0; row<M; row++) {
	for(col=0; col<N; col++) {
	int noise;
	noise = gaussrand(0,3)+ifsigp(img1, row, col);
	ifsipp(blur1_v1,row, col, noise);
} 
}
/*Save the image*/
ifspot(blur1_v1, "blur1_v1.ifs"); 
}
double gaussrand(int mean, int var) {
	static double V1, V2, S;
	static int phase = 0;
	double X;
	if(phase == 0) {
		do {
			double U1 = (double)rand() / RAND_MAX;
			double U2 = (double)rand() / RAND_MAX;
			V1 = 2 * U1 - 1; V2 = 2 * U2 - 1;			
			S = V1 * V1 + V2 * V2;
			} while(S >= 1 || S == 0);
		X = V1 * sqrt(-2 * log(S) / S);
	} else
		X = V2 * sqrt(-2 * log(S) / S);
	phase = 1 - phase;
	return (X*var+mean);
}



