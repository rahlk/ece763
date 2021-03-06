/*Code to perform a simple bluring operation on an image.
Author: Rahul Krishna
Date: 01/18/2013 													*/

#include<stdio.h>
#include<ifs.h>

void main() {
int row,col;/*counters */
IFSIMG img1, blur_x, blur_y, blur_xy; /*Declare pointers to headers */

/* Read input image.*/
img1=ifspin("synth1.ifs"); 
int M=64; int N=64; /*M and N are the number of rows and columns*/
int len[3]={2, M, N};/*image to be created is two dimensional */

/*Create a kernel for the bluring operation*/
int m=3; int n=3; /*m and n are the number of rows and columns in the kernel*/
int h_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
int h_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

/*blur is the output image and is a float*/
blur_x = ifscreate("float" ,len, IFS_CR_ALL,0);
blur_y = ifscreate("float" ,len, IFS_CR_ALL,0);
blur_xy = ifscreate("float" ,len, IFS_CR_ALL,0);

/*Perform the bluring operation for H_x and H_y*/
for (row = 0; row < M-m+1; row++ ) { 
  for (col = 0; col < N-n+1; col++ ) {
  float acc_x= 0;
  float acc_y= 0;
  float acc_xy= 0;
  int weightsum = 10;
  int i,j; 
  for ( i = 0; i <= 2; i++ ) {
    for ( j = 0; j <= 2; j++ ) {
      int k_x = h_x[i][j];
      int k_y = h_y[i][j];
      int val = ifsigp(diffIm, row+i, col+j);
      acc_x += k_x * val;	
      acc_y += k_y * val;	
    }
  } 
  ifsipp(blur_x, row, col, acc_x);
  ifsipp(blur_y, row, col, acc_y);
  acc_xy = pow(acc_x*acc_x+acc_y*acc_y, 0.5);
  ifsipp(blur_xy, row, col, acc_xy);
 }
}

/*Save the image*/
ifspot(, "blur_xy.ifs"); 
}

