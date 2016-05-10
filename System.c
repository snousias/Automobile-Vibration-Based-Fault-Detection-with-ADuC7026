#include <ADuC7026.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "definitions.h"
//-------------------------------------------------------------
//------------------------------------------------------------------------------
//������������ ����������
//------------------------------------------------------------------------------
//������ CPU
void startCpu(void)
{
POWKEY1=0x01;
POWCON=0x00;		  //�������� ��� CPU ��� 41,78MHz
POWKEY2=0xF4;
return ;
}
//------------------------------------------------------------------------------
//������������ timers
void timerconfig(void)	
{
/*�������  timer1 */
//������ ���� timer 1 � ���� 1.
T1LD=0x01;
//External crystal 32.768KHz - Timer1_periodic_mode - Binary format - Source clock/1					
T1CON = 0x2C0;	 				
return ;
 }
//------------------------------------------------------------------------------
//��������� ������������
void delay (int length)
{
while (length >=0)
length--;
return;
}
//------------------------------------------------------------------------------
//������������ �����
void initports(void) 
{
//Configure all GP3 pins  as output.    
GP3CON=0x00;
GP3DAT|=0xFF000000;
return ;        
}		   
//------------------------------------------------------------------------------
//������������ �������� 
void initmaskinterrupts(void)
{
IRQEN=0x80;			//�������� ��� ADC
return ;
}
//------------------------------------------------------------------------------
//ADC
//------------------------------------------------------------------------------
//������  ADC
void ADCpoweron(int time)
{	
ADCCON = 0x20;	 	// power-on the ADC
while (time >=0)	// wait for ADC to be fully powered on
time--;
return ;
}
//------------------------------------------------------------------------------
//������� ADC
void ADCpowerdown(void)
{	
ADCCON = 0x00;	 	// power-down the ADC
return ;
}
//------------------------------------------------------------------------------
//������� ADC
void ADCconfig(void)
{
//ADC configuration
ADCpoweron(20000);				// power on ADC										
ADCCP  = 0x00;					//������� ������� �������� 0
//Eight clocks - Start conversion - ADC-ON - timer 1
ADCCON = 0x2A1;					
REFCON = 0x01;					// ������� ���������� ����� �������� ��� 2.5V ��� VREF pin
return ;
}

//-----�������� �������� ����������---------Sampling-Frequency=4,096KHz----------
void initsystem(void)
{							 
initmaskinterrupts();
initports();
startCpu();
timerconfig();
ADCconfig();
}
//------------------------------------------------------------------------------
