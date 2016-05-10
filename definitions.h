#define channels 4		// �������
#define COL 16			// ����� ������������		 
#define ekth 4 				
#define bufferlength 10	 		
#define pi 3.14159265
#define NOB 4		   //  ������� buffers
#define histregions 5
#define UNITY 2048

#ifndef VAR_DEFS          // Make sure this file is included only once
#define VAR_DEFS 1

/*----------------------------------------------
Setup variable declaration macros.
----------------------------------------------*/
#ifndef VAR_DECLS
# define _DECL extern
# define _INIT(x)
#else
# define _DECL
# define _INIT(x)  = x
#endif

/*----------------------------------------------
Declare variables as follows:

_DECL [standard variable declaration] _INIT(x);

where x is the value with which to initialize
the variable.  If there is no initial value for
the varialbe, it may be declared as follows:

_DECL [standard variable declaration];
----------------------------------------------*/
_DECL volatile int pos _INIT(0);			 //irq sampling variables
_DECL volatile int NA _INIT(0);
_DECL volatile float addup _INIT(0) ;
_DECL float FIR[bufferlength];	 //filter
//window---------------------------------------------
_DECL float Window[COL];		   //������� ���������
//���������� ������� ��� ����������------------
_DECL float Intermediate[COL];	//���������� ������� ������� ������	
//-----------------------------------------------------
_DECL float PSD[COL];		//������� ���������� ���������� ������
//-----------------------------------------------------
_DECL int Scrambler[COL][2];	// ������� ����������� ��� � ��� ��� �-1 bits
_DECL int ScramblerImd[COL];	//���������� ������� ��� ������� ��� ���. �����������
//-----------------------------------------------------
_DECL int QMatrix[COL/2][ekth+1];	 //������� ��� Twindle factors
_DECL int QFactor;				  
_DECL int QPhase;
//-----------------------------------------------------
_DECL int countup _INIT(1);		//��������� ��� ������� ��� ����� ���� ������ ���������� 
_DECL float Imd _INIT(0);
_DECL float Imd2 _INIT(0);
//-------------------------------------------------------
_DECL float Histogramma[histregions];
//------Complex-Numbers----------------------------------------
struct Complex
{
float real;   //���������� �����                               
float imag;   //���������� �����
float magn;   //����� - ������ ������������          
float phase;  //����� - ������ ������������
};
//--------Channels-------------------------------------------------
struct Channels
{
int data[bufferlength];      //buffer
float G[COL];                //�������������� ����� �������������� 
float M;                     //����������� ����� ����
float rms;                   //���� RMS          
float power;                 //����� 
float FFT[COL];              //�������� ��� Fourier
float PSD[COL];              //��������� ��������� ������
float PowerCepstrum[COL];    //����� ������
float Histogram[5];          //����������
};
//------References------------------------------------------------------------
struct Reference
{
float power;    //���� �������� ��� ��� ����
};
//----Buffers-----------------------------------------------------------------
struct Buffering
{
int Buffer[channels][COL];			  // �����������
};
//----Declarations------------------------------------------------------------
_DECL struct Channels Array[channels];
_DECL struct Reference Ref[channels];
_DECL struct Buffering Buffers[NOB];
//----------------------------------------------------------------------------
_DECL struct Complex FFTInput[COL];
_DECL struct Complex FFTOutput[COL];
_DECL struct Complex TwindleMatrix[COL/2][ekth+1];
#endif
/*----------------------------------------------------------------------------
----------------------------------------------------------------------------*/

//------------------------------------------------------------------------------
//������ �����������
//------------------------------------------------------------------------------
//��������������----------------------------------------------------------------
extern void initreferences(void);		//������������ ����� ��������
extern void initmatrices(void);
extern void initbuffer(void);			//������������ Buffer
extern void initfilter(void);			//������������ ������ �������
extern void initScrambler(void);		//������������ ������� �������������
extern void initTwindleMatrix(void);   //������������ ������ Twindle factors
extern void initializations(void);	 // ��������� ������� �������������
//��������----------------------------------------------------------------------
extern void initwindow(void); // ������������ ���������
//����� ��� rms-----------------------------------------------------------------
extern float rms(float []);	   // ������� ����� rms
extern float signalpower(float []);	  // ������� ����� ������
//����������� �������-----------------------------------------------------------
extern void controlvalue(float,float); //�������� �� ���� ��������
extern void control(void);		   //������� �� ��� ����� ����� �����������
//����������� ������������------------------------------------------------------
extern void fftforward(void);	  //���������� FFT
extern void fftinverse(void);	  //�����������  FFT
extern int Scramblefunction(int,int);	 //������� ������ �����������
extern void WeightRealImag(int,int);	 //�������� Twindle Factors
//-----------------------------------------------------------------------------
extern float average(float []);		 //�������� ����������� �����
extern void CopyMatrix(float [],float []);	//��������� �������
extern void Cepstrum(void);			//�������� ��������
extern void PowerCepstrum(void);	//�������� �������� ������
extern float Variance(float []);	//�������� ����������� ��� ������� ���������
extern float Peak(float []);	   //�������� �������� ����� ������ ��������� �����
extern float crest(float []);	   //�������� Crest Factor
extern void histogram(float []);   //�������� �������������
extern void process(void);		   //��������� ���������� ����������� ������������
//�������������� ����������-----------------------------------------------------
extern void startCpu(void);			//�������� CPU
extern void timerconfig(void);		//������� ���������
extern void delay(int);				//��������� ������������
extern void initports(void);		 //������������ ports
extern void initmaskinterrupts(void);	//������������ ��������
extern void initsystem(void);		//������ ������������ ����������
//ADC---------------------------------------------------------------------------
extern void ADCpoweron(int);	   //������ ADC
extern void ADCpowerdown(void);	   //������� ADC
extern void ADCconfig(void);	   //������� ADC


