#include <ADuC7026.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "definitions.h" 
//------------------------------------------------------------------------------
//Συναρτήσεις επεξεργασίας
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*Συνάρτηση γρήγορου μετασχηματισμού Fourier(The Decimation-in-Time Butterfly Algorithm)*/
 /* 8=2^3--->3+2
    16=2^4-->4+2
    32=2^5-->5+2
    64=2^6-->6+2 
 */

void fftforward(void)
{
int i,j; 
int v1,v2;
static int counter,Mf,Hf,bf;	
static float Sf=0;
static struct Complex Y[COL][ekth+2]; //64=COL 8=ekth+2=log2(64)+2
static struct Complex W;
//****************************************************
//Αρχικοποίηση κεντρικού πίνακα πίνακα Y
for(i=0;i<COL;i++)
{
for(j=0;j<ekth+2;j++)
{
Y[i][j].real=0.0;
Y[i][j].imag=0.0;
}         			
}  			
/*Εφαρμογή παραθύρου*/
for (i=0;i<COL;i++)
{
Y[i][0].real=FFTInput[i].real*Window[i];
Y[i][0].imag=FFTInput[i].imag*Window[i];	 
}
for (i=0;i<COL;i++)
{
Y[i][1].real=Y[(Scrambler[i][1])][0].real;
Y[i][1].imag=Y[(Scrambler[i][1])][0].imag;
}

//---------------------------------------------------------------------------------
//FFT
/*Το bf παίζει  ρόλο  ρυθμιστή*/
/* 2<=b=<7<8=log2(COL)+2 ----> 64,8 */
/* 2<=b=<6<7=log2(COL)+2 ----> 32,7 */
for (bf=2;bf<ekth+2;bf++)
{
counter=0;
Mf=(int)(pow(2,(bf-2)));
Hf=2*Mf;
Sf=(COL/Hf);						//Το H είναι το κάθετο μήκος υπο επεξεργασία
for(j=0;j<Sf;j++)				//Το S είναι ο αριθμός που το Η χωράει στο COL				   
{

for(i=0;i<Mf;i++)
{
v1=(Hf*j)+i;
v2=(Hf*j)+i+Mf;
W.real=TwindleMatrix[counter][bf-1].real;
W.imag=TwindleMatrix[counter][bf-1].imag;
Y[v1][bf].real=Y[v1][bf-1].real+(W.real*Y[v2][bf-1].real-W.imag*Y[v2][bf-1].imag);//real part
Y[v1][bf].imag=Y[v1][bf-1].imag+(W.real*Y[v2][bf-1].imag+W.imag*Y[v2][bf-1].real);//imaginary part
Y[v2][bf].real=Y[v1][bf-1].real-(W.real*Y[v2][bf-1].real-W.imag*Y[v2][bf-1].imag);//real part	
Y[v2][bf].imag=Y[v1][bf-1].imag-(W.real*Y[v2][bf-1].imag+W.imag*Y[v2][bf-1].real);//imaginary part
counter++;
}	
}
}
//------------------------------------------------------------------------------------------ 
for(i=0;i<COL;i++)
{
FFTOutput[i].real=Y[i][ekth+1].real;									//Real Values
FFTOutput[i].imag=Y[i][ekth+1].imag;		  							//Imaginary Values
FFTOutput[i].magn=sqrtf((FFTOutput[i].real*FFTOutput[i].real)+(FFTOutput[i].imag*FFTOutput[i].imag));  //Magnitude
FFTOutput[i].phase=atan(FFTOutput[i].imag/FFTOutput[i].real);  // Angle
// Το τελικό αποτέλεσμα εξάγεται σε έναν πίνακα FFT
}
return ;
}
//-------------------------------------------------------------------------------------------
/*
Τιμές των M,H,S,b
M=1; H=2; S=32; b=2;
M=2; H=4;S=16; b=3;
M=4; H=8; S=8; b=4;
M=8; H=16; S=4; b=5;
M=16; H=32; S=2; b=6;
M=32; H=64; S=0; b=7;
*/
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void WeightRealImag(int k,int stage)
{
float Q2;
int Q3;
Q2=k*(pow(2,stage)/COL);
Q3=(int)Q2;
QFactor=Scrambler[Q3][0];
QPhase=(2*pi*QFactor)/COL;	   //Φάση των Twindle Factors σε πολική μορφή
Imd=cos(QPhase);
Imd2=-(sin(QPhase));		   //Εξαγωγή των Twindle Factors
return ;
}
//------------------------------------------------------------------------------
int Scramblefunction(int input,int exponent)
{
int j=0;
int d=0;
int i=0;

//********************************************************
//Scrambler - αναδιάταξη για εφαρμογή του FFT
//Για κάθε n στοιχεία δημιουργούνται 2n .
//Οι τιμές των πρώτων n πολ/νται x2 και οι τιμές των επόμενων n πολ/νται x2 και 
//προστιθεται 1 
for(i=0;i<COL;i++)ScramblerImd[i]=0;
ScramblerImd[0]=0;
ScramblerImd[1]=2;
ScramblerImd[2]=1;
ScramblerImd[3]=3;
//Το (ekth-2) αφορά την διαφορά της δύναμης του 2 από το COL(=32=2^5=2^exponent) στο
//΄μήκος του αρχικού πίνακα (=4=2^2) 
for (j=0;j<exponent-2;j++)
{
d=4*pow(2,j);     /*=2^j*/   /*Η τιμή 4 αφορά το μήκος του αρχικού πίνακα*/
for (i=0;i<d;i++)
{
ScramblerImd[d+i]=2*ScramblerImd[i]+1;  //Τα τελευταία n x2+1
}
for (i=0;i<d;i++)
{
ScramblerImd[i]=2*ScramblerImd[i];		//Τα πρώτα n x2
}
}
return ScramblerImd[input];
}
//---Αντίστροφος FFT με τη χρήση του εμπρόσθιου------------------------------------------
void fftinverse(void)
{
int i;
for(i=0;i<COL;i++)FFTInput[i].imag=-FFTInput[i].imag;
fftforward();
for(i=0;i<COL;i++)
{
FFTOutput[i].real=(FFTOutput[i].real/COL);
FFTOutput[i].imag=-(FFTInput[i].imag/COL);
FFTOutput[i].magn=sqrtf((FFTOutput[i].real*FFTOutput[i].real)+(FFTOutput[i].imag*FFTOutput[i].imag));
FFTOutput[i].phase=atan(FFTOutput[i].imag/FFTOutput[i].real);
}
return;
}
//-----------------------------------------------------------------------

