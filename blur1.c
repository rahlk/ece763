/*Code to perform a simple bluring operation on an image.
Author: Rahul Krishna
Date: 01/18/2013 													*/

#include<stdio.h>
#include<ifs.h>

void main() {
int row,col;/*counters */
IFSIMG img1,blur; /*Declare pointers to headers */

/* Read input image.*/
img1=ifspin("synth1.ifs"); 
int M=64; int N=64; /*M and N are the number of rows and columns*/
int len[3]={2, M, N};/*image to be created is two dimensional */

/*Create a kernel for the bluring operation*/
int m=3; int n=3; /*m and n are the number of rows and columns in the kernel*/
int kernel[3][3] = {{1, 1, 1}, {1, 2, 1}, {1, 1, 1}};

/*blur is the output image and is a float*/
blur=ifscreate("float" ,len, IFS_CR_ALL,0);

/*Perform the bluring operation*/
for (row = 0; row < M-m+1; row++ ) { 
  for (col = 0; col < N-n+1; col++ ) {
  int acc= 0;
  int weightsum = 10;
  int i,j; 
  for ( i = 0; i <= 2; i++ ) {
    for ( j = 0; j <= 2; j++ ) {
      int k = kernel[i][j];
      int val = ifsigp(img1, row+i, col+j);
      acc += k * val;	
    }
  } 
  ifsipp(blur, row, col, acc/10);
 }
}
/*Save the image*/
ifspot(blur, "blur.ifs"); 
}

