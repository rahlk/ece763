/*Code to perform detect a circle in an image.
Author: Rahul Krishna
Date: 01/18/2013*/

#include<stdio.h>
#include<ifs.h>
#include<flip.h>
#include<math.h>

void main() {
printf("Detect a Multiple circles in an image.\n Author: Rahul Krishna\n Updated: 04/06/2014\n \n");
int mask;
float param[32][128][128]={0}; // Parameter matrix.
int max_x0=0, max_y0=0, max_R=0, max_param=0;
int r,c;
int row,col;/*counters */
IFSIMG img1,inimg, outImg, edge, edge1, dx, dy, dxy; //Declare pointers to headers 
int thresh;
int pixVal;
int maxCir=10;
int maxRad[2]={10,3};
// Read input image
inimg=ifspin("pcb_lead.ifs");
// Get Image size
int* len=ifssiz(inimg);
int M = *(len+1); 
int N = *(len+2);
int R=M>N?round(M/2):round(N/2); // Maximum radius of a circle is assumed not to be greater than half as much as the image dimension.
img1=ifscreate("float", len, IFS_CR_ALL, 0);
outImg=ifscreate("float", len, IFS_CR_ALL, 0);
dx = ifscreate("float" ,len, IFS_CR_ALL,0);
edge = ifscreate("float" ,len, IFS_CR_ALL,0);
edge1 = ifscreate("float" ,len, IFS_CR_ALL,0);
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
flcp(img1, outImg);
flcp(edge, edge1);
/***********************************************************
// Begin a Master For loop to detect multiple circles.
************************************************************/

for(int numCir=0; numCir<maxCir; numCir++) {

// Create a Parametric Image for the HOUGH TRANSFORM
/* Parameters are R, x0, y0. X and Y are coordinates from the input binary image. x0 and y0 are the centers of the circles and R is the raduis. The Parametric equation of a circle is R = sqrt((X-x0)^2+(Y-y0)^2). We get a 3D matrix for each x0, y0 and X,Y combination.*/

for(int j = 0; j<M; j++) {
 for(int k = 0; k<N; k++) {
  for(r=0; r<M; r++){
   for(c=0; c<N; c++) { 
    mask=ifsfgp(edge1,r,c);
     if(mask) {
     float rad = floor(sqrt(pow(r-j,2)+pow(c-k,2))); 
     pixVal= (int) rad;
     if(pixVal<32 && pixVal>0) 
      param[pixVal][j][k]++;
     }
    }
   }
 }
}  
// Find the midpoint and radius of the circle
for(R=0; R<32; R++) {
 for(r=0; r<128; r++)
  for(c=0; c<128; c++) { 
   if (param[R][r][c]>=max_param) {
   max_x0=r;
   max_y0=c;
   max_R=R;
   max_param=param[R][r][c];
   param[R][r][c]=0;
   }
   else {
   param[R][r][c]=0;
   }
  }
 }
printf("Circle Detected at x0=%d, y0=%d\n Radius=%d\n",max_x0, max_y0, max_R);

// Save image and midpoint of the best circle
ifsfpp(outImg, max_x0, max_y0, 200);
ifspot(outImg, "outimg.ifs");

int lutrad, lutpixVal;
// Draw the circle on the original Image. And delete the edge points to detect the next circle.
for(r=0; r<M; r++)
  for(c=0; c<N; c++) {
  float lutrad = floor(sqrt(pow(r-max_x0,2)+pow(c-max_y0,2))); 
     int lutpixVal= (int) lutrad;
     if (lutpixVal==(int) floor(max_R)){
      ifsfpp(outImg, r, c, 200);
      ifsfpp(edge1, r, c, 0);}
}
// Save image and midpoint of the best circle
ifspot(outImg, "outimg_circ.ifs");
}
}
