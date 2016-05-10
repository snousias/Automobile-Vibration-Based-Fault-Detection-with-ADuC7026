#include <ADuC7026.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "definitions.h"
//------------------------------------------------------------------------------
//����� ��� rms
//------------------------------------------------------------------------------
//�������� ��� ������������ ����� �����
float rms(float Input[COL])
{
float p;
p=sqrtf(signalpower(Input));	 //�������� ��� ������� �����
return p;
}
float signalpower(float Input[COL])
{
int i;
float k=0;
float power;
for (i=0;i<COL;i++)	  
{
k+=Input[i]*Input[i]; //����� ���� ����� ��� ��������� ��� ������� ��� ���������
}
power=k/COL;  		  //�������� ��� ����� ��� ������
return power;
}
