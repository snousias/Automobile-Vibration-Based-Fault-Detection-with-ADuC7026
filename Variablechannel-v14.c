//To read comments change in the configuration menu the comment font of the c editor 
//from italic to normal.
//--------------------------------------------------------------------------------------
//Το παρακάτω πρόγραμμα λαμβάνει τιμές από μεταβλητό αριθμό καναλιών του ADC τις οποίες αποθηκεύει σε
//buffers και μετά αφού οι τιμές περάσουν από FIR φίλτρο αποθηκεύονται
//σε πίνακες και μετά επεξεργάζονται.    
//--------------------------------------------------------------------------------------
#include <ADuC7026.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define VAR_DECLS
#include "definitions.h"
//------------------------------------------------------------------------------
void Undef_Handler( void ) {} 
void SWI_Handler(void) {} 
void PAbt_Handler( void ) {}   
void DAbt_Handler( void ) {}
void FIQ_Handler( void ) {} 

//------------------------------------------------------------------------------
//Δειγματοληψία - Sampling
//------------------------------------------------------------------------------
/*Συνάρτηση δειγματοληψίας*/

__irq void IRQ_Handler(void)  
{
Buffers[NA].Buffer[ADCCP][pos]=(ADCDAT >> 16);	  /*αποστολή 1 δείγματος*/
ADCCP=(ADCCP+1)%channels;
if(ADCCP==0)pos=(pos+1)%COL;
if((ADCCP==0)&&(pos==0))NA=(NA+1)%NOB;

return;
}
//-----------------------------------------------------------------------------
void sortFIR(void)
{
int i,j,k,m,n;

i=0;
j=0;
k=0;
m=0;
n=0;
addup=0;
if (NA!=0)j=(NA-1);	   //Επιλογή buffer
if (NA==0)j=(NOB-1);

for(m=0;m<COL;m++)
{
for(i=0;i<channels;i++)
{
for(k=(bufferlength-1);k>0;k--){Array[i].data[k]=Array[i].data[k-1];}	//Ολίσθηση
Array[i].data[0]=Buffers[j].Buffer[i][m];								//Τοποθέτησηση στη δομή δεδομένων από τον buffer
for(n=0;n<bufferlength;n++){addup+=Array[i].data[n]*FIR[n];}			//πέρασμα τιμών από το φίλτρο
Array[i].G[m]=addup;
addup=0;
}		  
}

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Κυρίως πρόγραμμα
int main(void)
{
initializations();
initsystem();
while(1)
{
sortFIR();
process();
control();	
}
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
