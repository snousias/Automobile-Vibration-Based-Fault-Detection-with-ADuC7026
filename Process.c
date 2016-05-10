#include <ADuC7026.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "definitions.h"
//-----------------------------------------------------------------
//---------------------------------------------------------
//------------------------------------------------------------------------------
//Συνάρτηση αντιγραφής πινάκων
void CopyMatrix(float Matrix[COL],float Target[COL])
{
int i;
for(i=0;i<COL;i++)
{
Target[i]=Matrix[i]	;	//Αντιγραφή πινάκων
}
return;
}
//------------------------------------------------------------------------------
float Variance(float Input[COL])
{
int i;
Imd=average(Input);    
for(i=0;i<COL;i++)     
{
Intermediate[i]=(Input[i]-Imd)*(Input[i]-Imd);
}
Imd=average(Intermediate);
return Imd;
}
//------------------------------------------------------------------------------
float Peak(float Input[COL])
{
int i;
float peak=0;
for (i=0;i<COL;i++)
{
if (abs(Input[i])>peak){peak=Input[i];Imd=peak;Imd2=i;}    
}
return peak;
}
//------------------------------------------------------------------------------
float crest(float Input[COL])
{
float crestfactor;
crestfactor=Peak(Input)/rms(Input);
return crestfactor;
}
//------------------------------------------------------------------------------
void histogram(float Input[COL])
{
int i,j;
float max;
max=Peak(Input);

for (i=0;i<COL;i++)
{
for (j=0;j<histregions;j++)
{
if ((Input[i]>(j/histregions)*max)&&(Input[i]<=((j+1)/histregions)*max))Histogramma[j]+=1;
}
}
for (j=0;j<histregions;j++)
{
Histogramma[j]=Histogramma[j]/COL;
}
return;
}
//-----------------------------------------------------------------------------------------
//--------------------------------------------------------
/*Συνάρτησεις εξαγωγής μέσου όρου */
float average(float Input[COL])
{
int i;
float sum;

sum=0;
for (i=0;i<COL;i++)
{
sum+=Input[i];
} 

return (sum/COL);    
}
//-----------------------------------------------------------
