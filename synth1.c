#include<stdio.h>
#include<ifs.h>
void main() {
IFSIMG img1,img2; /*Declare pointers to headers */
int len[3]; /*len is an array of dimensions, used by ifscreate*/
int threshold;/*threshold is an int here */ 
int row,col;/*counters */
img1=ifspin("img2.ifs"); /* Read input image.*/ 
len[0]=2;/*image to be created is two dimensional */
len[1]=64;/*image has 64 columns */
len[2]=64;/*image has 64 rows */
img2=ifscreate("u8bit" ,len, IFS_CR_ALL,10) ;/*image is unsigned 8bit */
ifsipp(img2, 0, 0,255);
for(row=16;row< 32;row++) { 
	for(col=16;col< 32;col++) 
		ifsipp(img2,row, col ,100);  
	for(col=32;col< 48;col++) 
		ifsipp(img2,row, col ,150);  
}

for(row=32;row<48;row++) { 
	for(col=16;col< 32;col++) 
		ifsipp(img2,row, col ,50);  
	for(col=32;col< 48;col++) 
		ifsipp(img2,row, col ,20);  
}
	ifspot(img2,"synth1.ifs"); /*write image 2 to disk */
}


