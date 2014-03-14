/*Code to perform a simple bluring operation on an image.
Author: Rahul Krishna
Date: 01/18/2013 													*/

#include<stdio.h>
#include<ifs.h>
#include<math.h>

float medfilt(float arr[3][3]);

void main() {
int row,col;/*counters */
IFSIMG img1, im1, c, blur_x, blur_y, blur_xy, filtImg, diffIm; /*Declare pointers to headers */
float C;
/* Read input image.*/
img1=ifspin("angio.ifs"); 
int M=400; int N=400; /*M and N are the number of rows and columns*/
int len[3]={2, M, N};/*image to be created is two dimensional */
float k = 0.1;
/*Create a kernel for the bluring operation*/ 
int m=3; int n=3; /*m and n are the number of rows and columns in the kernel*/
float h_x_1[3][3] = {{-1, 0 , 1}, {-2, 0, 2}, {-1, 0, 1}};
float h_y_1[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

float h_x_2[3][3] = {{1, -2 , 1}, {1, -2 , 1}, {1, -2 , 1}};
float h_y_2[3][3] = {{1, 1, 1}, {-2, -2, -2}, {1, 1, 1}};

/*blur is the output image and is a float*/
blur_x = ifscreate("float" ,len, IFS_CR_ALL,0);
blur_y = ifscreate("float" ,len, IFS_CR_ALL,0);
blur_xy = ifscreate("float" ,len, IFS_CR_ALL,0);
c = ifscreate("float" ,len, IFS_CR_ALL,0);
filtImg = ifscreate("float" ,len, IFS_CR_ALL,0);
diffIm = ifscreate("float" ,len, IFS_CR_ALL,0);

for(int i=0; i<400; i++)
for(int j=0; j<400; j++)
ifsfpp(diffIm, i, j,  ifsfgp(img1, i, j));

int iter=0;
for(iter=0; iter<1; iter++) {
C=0;
// First compute the first derivative of the image in the x and y direction.
for (row = 0; row < M-m+1; row++ ) { 
  for (col = 0; col < N-n+1; col++ ) {
  float acc_x= 0;
  float acc_y= 0;
  float acc_x_1= 0;
  float acc_y_1= 0;
  float acc_xy= 0;
  int weightsum = 8;
  int i,j; 
  for ( i = 0; i <= 2; i++ ) {
    for ( j = 0; j <= 2; j++ ) {
      int k_x = h_x_1[i][j];
      int k_y = h_y_1[i][j];
      float val = ifsfgp(diffIm, row+i, col+j);
      acc_x += k_x * val;	
      acc_y += k_y * val;	
    }
  }
  ifsfpp(blur_x, row, col, acc_x/8);
  ifsfpp(blur_y, row, col, acc_y/8); 
  }
}
// Let's save the images for reference.
ifspot(blur_x, "blur_x.ifs"); 
ifspot(blur_y, "blur_y.ifs"); 

// Now let we'll compute the scalar multiplier factor, some call it the "flux".
for (row = 0; row < M-m+1; row++ ) { 
  for (col = 0; col < N-n+1; col++ ) {
  float acc_x= 0;
  float acc_y= 0;
  float acc_xy= 0;
  int weightsum = 12;
  int i,j; 
  for ( i = 0; i <= 2; i++ ) {
    for ( j = 0; j <= 2; j++ ) {
      int k_x = h_x_1[i][j];
      int k_y = h_y_1[i][j];
      float val = ifsfgp(diffIm, row+i, col+j);
      acc_x += k_x * val;	
      acc_y += k_y * val;	
    }
  }
 // C = exp(-(abs(acc_x/8)+abs(acc_y/8)));
  C = pow(1+(abs(acc_x/8)+abs(acc_y/8)),-1);
  ifsfpp(c, row, col, C*255); 
  //printf("%f \t", C);
  }
}
// And we'll save that too..
ifspot(c, "flux.ifs"); 
float min, max;
float lam=0.1;
// Finally, compute the heat equation.
for (row = 0; row < M-m+1; row++ ) { 
  for (col = 0; col < N-n+1; col++ ) {
  float acc_x= 0;
  float acc_y= 0;
  float acc_xy= 0;
  int weightsum = 8;
  int i,j; 
  for ( i = 0; i <= 2; i++ ) {
    for ( j = 0; j <= 2; j++ ) {
      int k_x = h_x_1[i][j];
      int k_y = h_y_1[i][j];
      float val_x = ifsfgp(blur_x, row+i, col+j)*ifsfgp(c, row+i, col+j);
      float val_y = ifsfgp(blur_y, row+i, col+j)*ifsfgp(c, row+i, col+j);
      acc_x += k_x * val_x;	
      acc_y += k_y * val_y;	
    }
  } 
  acc_xy = lam*(acc_x + acc_y)/8;
  if(min<acc_xy)
  min=acc_xy;
  
  ifsfpp(diffIm, row, col, 255*(acc_xy));
 }
}
}
/*Save the image*/
ifspot(diffIm, "diffIm.ifs"); 
}
