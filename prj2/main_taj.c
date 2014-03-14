/*Code to perform Anisotropic Diffusion using FLIP Library.
Author: Rahul Krishna
Date: 02/13/2013 													*/

#include<stdio.h>
#include<ifs.h>
#include<math.h>
#include<flip.h>
int main() { 
IFSIMG img1, inimg, inimg1, outimg, outimg1, outimg2, dx_1, flux, dy_1, cdx_1, cdy_1, temp1, temp2, temp3, temp4, temp5, C1, C2, ones, 
diffIm; 
int* len; 
inimg=ifspin("taj.ifs"); // Specify the Image name here. 
len = ifssiz(inimg); 
int M = *(len+1); 
int N = *(len+2); 
outimg=ifscreate("float",len,IFS_CR_ALL,0); 
inimg1=ifscreate("u8bit",len,IFS_CR_ALL,0); 
outimg1=ifscreate("float",len,IFS_CR_ALL,0); 
outimg2=ifscreate("float",len,IFS_CR_ALL,0); 
img1=ifscreate("float",len,IFS_CR_ALL,0); 
dx_1=ifscreate("float",len,IFS_CR_ALL,0); 
dy_1=ifscreate("float",len,IFS_CR_ALL,0); 
temp1=ifscreate("float",len,IFS_CR_ALL,0); 
temp2=ifscreate("float",len,IFS_CR_ALL,0); 
temp3=ifscreate("float",len,IFS_CR_ALL,0); 
temp4=ifscreate("float",len,IFS_CR_ALL,0); 
temp5=ifscreate("float",len,IFS_CR_ALL,0); 
C1=ifscreate("float",len,IFS_CR_ALL,0); 
ones=ifscreate("float",len,IFS_CR_ALL,10000); 
diffIm=ifscreate("float",len,IFS_CR_ALL,0); 
C2=ifscreate("float",len,IFS_CR_ALL,0); 
int i=0,j=0; 
int flag=1; // Convert image to float. 
float min=0; 
float max=0; 

// Rescale the image
/*while(i<M) {
    for(j=0; j<N; j++){
/*    if(ifsfgp(inimg, i,j)>=max)
    	max=ifsfgp(inimg, i,j);
    	printf("Max %f\n", max);
    if(ifsfgp(inimg, i,j)<=min)
    	min=ifsfgp(inimg, i,j);
    	printf("Min %f", min);
    ifsfpp(ones, i, j, 1);
    }
  i=i+1;
}*/
fladds(ones, ones, 1);
ifsany2any(inimg, img1); 
float alpha=0.005; // Specify Aplha
ifspot(ones,"ones.ifs");
diffIm=img1;
ifspot(diffIm, "temp.ifs"); // Save a copy for reference.

int iter=20000;// Specify the number of iterations here.
// Begin iteration

flDoG(diffIm, dx_1, 1, 1, 0); //derivative in x
flDoG(diffIm, dy_1, 1, 1, 1); //derivative in y
//if(flag==1) {
ifspot(dx_1,"temp1.ifs");

// Compute the flux.
flmultv(dx_1, dx_1, temp1);
flmultv(dy_1, dy_1, temp2);
flsqrt(temp1, temp1);
flsqrt(temp2, temp2);
float k = 0.1;

// For conductance C = exp(-k*((|x'|+|y'|) )).

fladdv(temp1,temp2,temp3); // add them 
flmultv(temp3, temp3, temp4); // take square root of the values 
flmults(temp4, temp5, -k); // multiply by k and negate the values 
flexp(temp5, C1); // compute C

// For conductance C = 1(1+k*(|x'|+|y'|)).
flmults(temp3, temp4, k);
fladdv(temp4, ones, temp5);
fldivv(ones, temp5, C2);
ifspot(C2,"flux1.ifs");

for(int i=0;i<iter;i++) {

flDoG(diffIm, dx_1, 1, 1, 0); //derivative in x
flDoG(diffIm, dy_1, 1, 1, 1); //derivative in y

// Use C1 flux equation.

flmultv(C2,dx_1,temp1); // Multiply with the first derivative
flmultv(C2,dy_1,temp2); // Multiply with the first derivative
flDoG(temp1, temp4, 1, 1, 0); //Differentiate again
flDoG(temp2, temp5, 1, 1, 1); //Differentiate again
fladdv(temp4, temp5, outimg); //Add the two
flmults(outimg, outimg1, alpha); //Multiply by alpha
fladdv(outimg1, diffIm, outimg2);
diffIm=outimg2; // Save the image... Repeat Iteration.
}
// End Iteration
ifspot(outimg2,"out.ifs"); // Save the image
}
 
// End of this program
