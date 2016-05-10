#include <ADuC7026.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "definitions.h"
//------------------------------------------------------------------------------
//Ισχύς και rms
//------------------------------------------------------------------------------
//Εξαγωγής της τετραγωνικής μέσης τιμής
float rms(float Input[COL])
{
float p;
p=sqrtf(signalpower(Input));	 //Παραγωγή της ενεργού τιμής
return p;
}
float signalpower(float Input[COL])
{
int i;
float k=0;
float power;
for (i=0;i<COL;i++)	  
{
k+=Input[i]*Input[i]; //Ύψωση κάθε τιμής στο τετράγωνο για εξαγωγή της ενέργειας
}
power=k/COL;  		  //Παραγωγή της τιμής της ισχύος
return power;
}
