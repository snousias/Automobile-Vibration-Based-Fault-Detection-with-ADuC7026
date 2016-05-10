#include <ADuC7026.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "definitions.h" 


//-----------------------------------------------------------------------------------
void Cepstrum(void) 
{
int i;
fftforward();		   //���������� FFT
for(i=0;i<COL;i++)
{
FFTInput[i].real=log(FFTOutput[i].magn);
FFTInput[i].imag=FFTOutput[i].phase;
}
fftinverse();		  //����������� FFT
return;  
}
//------------------------------------------------------------------------------------
void PowerCepstrum(void)
{
int i;
fftforward();		//���������� FFT
for (i=0;i<COL;i++)FFTInput[i].real=log(PSD[i]);
fftinverse();	   //����������� FFT
return;
}
//--------------------------------------------------------------------------------------
