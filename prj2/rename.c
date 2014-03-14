/*Code to perform a simple bluring operation on an image.
Author: Rahul Krishna
Date: 01/18/2013 													*/

#include<stdio.h>
#include<ifs.h>
#include<math.h>

float medfilt(float arr[3][3]);

void main() {
IFSIMG img1, im1, c, blur_x, blur_y, blur_xy, filtImg, diffIm; /*Declare pointers to headers */
float C, C1;
/* Read input image.*/
img1=ifspin("lymphoma.ifs"); 
img1 = ifsslice(img1,"f", 5);
ifspot(img1,"lymph.ifs");
int* row;
row=ifssiz(img1);
// int cols=ifsdimen(img1,1);
printf("rows=%d cols=%d \n", *(row+1), *(row+2));
}
