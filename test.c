#include<stdio.h>
#include<ifs.h>
void main() {
IFSIMG img1,img2; /*Declare pointers to headers */
int len[3]; /*len is an array of dimensions, used by ifscreate*/
int threshold;/*threshold is an int here */ 
int row,col;/*counters */
int v; 
len[0]=2;/*image to be created is two dimensional */
len[1]=128;/*image has 128 columns */
len[2]=128;/*image has 128 rows */
img2=ifscreate("u8bit" ,len, IFS_CR_ALL,0) ;/*image is unsigned 8bit */
threshold=55;/*set some value to threshold */

for(row=32;row< 64;row++) 
	for(col=32;col< 64;col++) {
		ifsipp(img2,row, col ,255); } 
		ifspot(img2,"img2.ifs"); /*write image 2 to disk */
}
