#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "definitions.h"

//------------------------------------------------------------------------------
void process(void)
{
int i,j;
for(i=0;i<channels;i++)
{
//--power-------------------
//Πρόσθεση και διαίρεση για διαρκή παραγωγή μέσου όρου αριθμού όρων ίσου με την τιμή UNITY
Array[i].power+= (signalpower(Array[i].G)-Array[i].power)/countup;
//----frequency-spectrum----
for(j=0;j<COL;j++){FFTInput[j].real=Array[i].G[j];}
fftforward();
for(j=0;j<COL;j++)
{
//Πρόσθεση και διαίρεση για διαρκή παραγωγή μέσου όρου αριθμού όρων ίσου με την τιμή UNITY
Array[i].FFT[j]+=(FFTOutput[j].magn-Array[i].FFT[j])/countup; 
}
}
countup=(countup+1)%UNITY;if(countup==0)countup=1;	   //’υξηση κατα 1 του countup
return; 
}
//------------------------------------------------------------------------------
