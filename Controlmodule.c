#include <ADuC7026.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "definitions.h"
//----------------------------------------------------------------------
void control(void)
{
int i;
for(i=0;i<channels;i++)
{
if (Ref[i].power!=0)
{
if ((abs(Array[i].power-Ref[i].power)/Ref[i].power)>0.1)GP3DAT|=0x10000;
}
//Σύγκριση με τιμές αναφοράς και άναμα led σε περίπτωση σφάλματος
}

}
//----------------------------------------------------------------------
