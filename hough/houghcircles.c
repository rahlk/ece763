/*Code to perform detect a circle in an image.
Author: Rahul Krishna
Date: 01/18/2013*/

#include<stdio.h>
#include<ifs.h>
#include<flip.h>
#include<math.h>

void main() {
int mask;
float param[64][128][128]; // Parameter matrix.
int r,c;
int row,col;/*counters */
IFSIMG img1,inimg, edge, dx, dy, dxy; //Declare pointers to headers 
int thresh;
// Read input image
inimg=ifspin("pcb_lead.ifs");
// Get Image size

int* len=ifssiz(inimg);
int M = *(len+1); 
int N = *(len+2);
int R=M>N?round(M/2):round(N/2); // Maximum radius of a circle is assumed not to be greater than half as much as the image dimension.

img1=ifscreate("float", len, IFS_CR_ALL, 0);
dx = ifscreate("float" ,len, IFS_CR_ALL,0);
edge = ifscreate("float" ,len, IFS_CR_ALL,0);
dy = ifscreate("float" ,len, IFS_CR_ALL,0);
dxy = ifscreate("float" ,len, IFS_CR_ALL,0);

// Find X and Y derivatives
ifsany2any(inimg,img1);
flDoG(img1,dx,0.5,1,0); // Derivatives in X, variance 0.5 
flsq(dx,dx); // Square the derivative
flDoG(img1,dy,0.5,1,1); // Derivatives in Y, variance 0.5
flsq(dy,dy); // Square the derivative
fladdv(dx,dy,dxy); // Sum of squares of derivative.
flsqrt(dxy,dxy); // Magnitude of the gradient image. sqrt((dx)^2+(dy)^2).

// Threshold is emperically determined.
thresh=30;

// Edge Detection
for (row = 0; row <M; row++ ) 
 for (col = 0; col <N; col++ ) {
    int outVal = ifsigp(dxy, row, col)>thresh?1:0;
    ifsipp(edge, row, col, outVal);
}
// Save the edge and gradient images.
ifspot(edge, "edge.ifs"); 
ifspot(dxy, "dxy.ifs"); 

// Create a Parametric Image for the HOUGH TRANSFORM
/* Parameters are R, x0, y0. X and Y are coordinates from the input binary image. x0 and y0 are the centers of the circles and R is the raduis. The Parametric equation of a circle is R = sqrt((X-x0)^2+(Y-y0)^2). We get a 3D matrix for each x0, y0 and X,Y combination.*/
printf("%d %d \n",M,N);

for(r=0; r<128; r++){
 for(c=0; c<128; c++) { 
    mask=ifsfgp(edge,r,c); // ***SEGMENTATION FAULT***
    if(mask) {
    for(int j = 0; j<M; j++) {
     for(int k = 0; k<N; k++) {
     int rad = round(sqrt(pow(r-j,2)+pow(c-k,2))); 
     if(!(rad>R))
      param[rad][j][k]++;
     }
    }
   }
  }
 }  
}
