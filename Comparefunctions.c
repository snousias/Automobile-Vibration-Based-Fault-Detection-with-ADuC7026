#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "definitions.h"
//------------------------------------------------------------------
//------------------------------------------------------------------------------
//Συναρτήσεις Σύγκρισης
//------------------------------------------------------------------------------ 
//------------------------------------------------------------------------------
//Συνάρτηση σύγκρισης τιμής
void controlvalue(float Input,float Ref)
{

Imd=abs(Input-Ref);				   //Αποθήκευση στην ενδιάμεση τιμή Imd
if (Ref!=0)
{
Imd2=(abs(Input-Ref))/Ref;
}
else Imd2=0;				   //Αποθήκευση στην ενδιάμεση τιμή Imd2
return;
}
