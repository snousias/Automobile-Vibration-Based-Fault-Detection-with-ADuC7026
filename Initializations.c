#include <ADuC7026.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "definitions.h"

//��������������----------------------------------------------------------------
//------------------------------------------------------------------------------
//������������ ������� ���������
void initmatrices(void)
{

int i,j;i=0;j=0;
for(i=0;i<channels;i++)
{    
for(j=0;j<COL;j++) 
{
Array[i].G[j]=0;
Array[i].FFT[j]=0;
}
}
 
return;
}
//------------------------------------------------------------------------------
//��������������
//------------------------------------------------------------------------------
//������������ �������� 
void initreferences(void)
{
int i;
float A[12];
//�������� ����� ��� ��������� ������ ��������  
A[0]=250;A[1]=500;A[2]=50;A[3]=540;
A[4]=500;A[5]=500;A[6]=550;A[7]=300;
A[8]=651;A[9]=1000;A[10]=512;A[11]=425;
for (i=0;i<channels;i++)
{
Ref[i].power=A[i];    
}
}
//------------------------------------------------------------------------------
//������������ ������� ��������������
void initbuffer(void)
{
int i,j;i=0;j=0;
for(i=0;i<channels;i++)
{ 
for(j=0;j<bufferlength;j++)
{
Array[i].data[j]=0;
}
}
return;
}
//------------------------------------------------------------------------------
/*������������ �������*/
void initfilter(void)
{
FIR[0]=0.0161;
FIR[1]=0.0379;
FIR[2]=0.0931;
FIR[3]=0.1559;
FIR[4]=0.1969;
FIR[5]=0.1969;
FIR[6]=0.1559;
FIR[7]=0.0931;
FIR[8]=0.0379;
FIR[9]=0.0161;
return;   
}
//-------------------------------------------------------------------------------
void initScrambler(void)
{
int i;
Scramblefunction(0,ekth);
for(i=0;i<COL;i++)Scrambler[i][1]=ScramblerImd[i];
Scramblefunction(0,ekth-1);
for(i=0;i<(COL/2);i++)Scrambler[i][0]=ScramblerImd[i];
return;
}
//-------------------------------------------------------------------------------
void initTwindleMatrix(void)
{
int i,j;
i=0;
j=0;
for(j=1;j<ekth+1;j++)
{
for(i=0;i<(COL/2);i++)
{
WeightRealImag(i,j);
QMatrix[i][j]=QFactor;	   //�������� ��� Twindle Factor �� ������
TwindleMatrix[i][j].real=cos(QPhase); 		//real
TwindleMatrix[i][j].imag=-(sin(QPhase));	//imaginary
}
}
return;
}
//-------------------------------------------------------------------------------
void initializations(void)
{
initreferences();
initmatrices();
initbuffer();
initScrambler();
initTwindleMatrix();
initwindow();
initfilter();
}
//-------------------------------------------------------------------------------
