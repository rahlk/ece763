/*Code to perform a simple bluring operation on an image.
Author: Rahul Krishna
Date: 01/18/2013 													*/

#include<stdio.h>
#include<ifs.h>

void main() {
int row,col;/*counters */
IFSIMG img1, edge, blur_xy; /*Declare pointers to headers */

/* Read input image.*/
img1=ifspin("blur.ifs"); 
int M=64; int N=64; /*M and N are the number of rows and columns*/
int len[3]={2, M, N};/*image to be created is two dimensional */
float min=0;
float max=0;
float thresh=0;
unsigned char flag=1;
float outVal=0;
/*Create a kernel for the bluring operation*/
int m=3; int n=3; /*m and n are the number of rows and columns in the kernel*/
int h_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
int h_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

/*blur is the output image and is a float*/
edge = ifscreate("u8bit" ,len, IFS_CR_ALL,10);
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
      int val = ifsigp(img1, row+i, col+j);
      acc_x += k_x * val;	
      acc_y += k_y * val;	
    }
  } 
  acc_xy = pow(acc_x*acc_x+acc_y*acc_y, 0.5);
  if(acc_xy!=0) {
   if(acc_xy>=max) {
   	max = acc_xy;
   	if(flag==1) {
   		min=max; flag=0; } 
    	printf("max = %f \n", max);}
   else if(acc_xy<min)
   	{min = acc_xy; printf("min = %f \n", min);}
  ifsipp(blur_xy, row, col, acc_xy);
  }
 }
}
thresh=min;
for (row = 0; row < M-m+1; row++ )  
  for (col = 0; col < N-n+1; col++ ) {
   outVal = ifsigp(blur_xy, row, col)>thresh?1:0;
   ifsipp(edge, row, col, outVal); printf("%d\n", outVal);
}
/*Save the image*/
ifspot(edge, "edge_blur.ifs"); 
ifspot(blur_xy, "blur_xy_1.ifs"); 
}

