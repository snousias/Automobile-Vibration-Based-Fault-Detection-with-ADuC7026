#define channels 4		// Κανάλια
#define COL 16			// Βάθος επεξεργασίας		 
#define ekth 4 				
#define bufferlength 10	 		
#define pi 3.14159265
#define NOB 4		   //  Αριθμός buffers
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
_DECL float Window[COL];		   //Πίνακας Παραθύρου
//Ενδιάμεσοι πίνακες και μεταβλητές------------
_DECL float Intermediate[COL];	//Ενδιάμεσος πίνακας γενικής χρήσης	
//-----------------------------------------------------
_DECL float PSD[COL];		//Πίνακας φασματικής πυκνότητας ισχύος
//-----------------------------------------------------
_DECL int Scrambler[COL][2];	// Πίνακας αναδιάταξης για Ν και για Ν-1 bits
_DECL int ScramblerImd[COL];	//Ενδιάμεσος πίνακας για εξαγωγή του πιν. αναδιάταξης
//-----------------------------------------------------
_DECL int QMatrix[COL/2][ekth+1];	 //Πίνακας των Twindle factors
_DECL int QFactor;				  
_DECL int QPhase;
//-----------------------------------------------------
_DECL int countup _INIT(1);		//Μεταβλητή για εξαγωγή του μέσου όρου πολλών αθροιστέων 
_DECL float Imd _INIT(0);
_DECL float Imd2 _INIT(0);
//-------------------------------------------------------
_DECL float Histogramma[histregions];
//------Complex-Numbers----------------------------------------
struct Complex
{
float real;   //Πραγματικό Μέρος                               
float imag;   //Φανταστικό Μέρος
float magn;   //Μέτρο - Πολική συντεταγμένη          
float phase;  //Γωνία - Πολική συντεταγμένη
};
//--------Channels-------------------------------------------------
struct Channels
{
int data[bufferlength];      //buffer
float G[COL];                //Φιλτραρισμένες τιμές δειγματοληψίας 
float M;                     //Αριθμητικός Μέσος όρος
float rms;                   //Τιμή RMS          
float power;                 //Ισχύς 
float FFT[COL];              //Γρήγορος ΜΤΣ Fourier
float PSD[COL];              //Φασματική πυκνότητα ισχύος
float PowerCepstrum[COL];    //Σαφμα Ισχύος
float Histogram[5];          //Ιστόγραμμα
};
//------References------------------------------------------------------------
struct Reference
{
float power;    //Τιμή Αναφοράς για την ισχύ
};
//----Buffers-----------------------------------------------------------------
struct Buffering
{
int Buffer[channels][COL];			  // Ενταμιευτές
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
//Δήλωση συναρτήσεων
//------------------------------------------------------------------------------
//Αρχικοποιήσεις----------------------------------------------------------------
extern void initreferences(void);		//Αρχικοποίηση τιμών αναφοράς
extern void initmatrices(void);
extern void initbuffer(void);			//Αρχικοποίηση Buffer
extern void initfilter(void);			//Αρχικοποίηση πίνακα φίλτρου
extern void initScrambler(void);		//Αρχικοποίηση πινάκων αρχικοποίησης
extern void initTwindleMatrix(void);   //Αρχικοποίηση πίνακα Twindle factors
extern void initializations(void);	 // Συνάρτηση γενικών αρικοποιήσεων
//Παράθυρο----------------------------------------------------------------------
extern void initwindow(void); // Αρχικοποίηση Παραθύρου
//Ισχύς και rms-----------------------------------------------------------------
extern float rms(float []);	   // Εξαγωγή τιμής rms
extern float signalpower(float []);	  // Εξαγωγή τιμής ισχύος
//Συναρτήσεις Ελέγχου-----------------------------------------------------------
extern void controlvalue(float,float); //Σύγκριση με τιμή αναφοράς
extern void control(void);		   //Έλεγχος με τις τιμές καλής λειτουργίας
//Συναρτήσεις Επεξεργασίας------------------------------------------------------
extern void fftforward(void);	  //Εμπρόσθιος FFT
extern void fftinverse(void);	  //Αντίστροφος  FFT
extern int Scramblefunction(int,int);	 //Εξαγωγή πίνακα αναδιάταξης
extern void WeightRealImag(int,int);	 //Παραγωγή Twindle Factors
//-----------------------------------------------------------------------------
extern float average(float []);		 //Παραγωγή αριθμητικού μέσου
extern void CopyMatrix(float [],float []);	//Αντιγραφή πινάκων
extern void Cepstrum(void);			//Παραγωγή Σαφματος
extern void PowerCepstrum(void);	//Παραγωγή Σάφματος ισχύος
extern float Variance(float []);	//Παραγωγή Διακύμανσης και τυπικής απόκλισης
extern float Peak(float []);	   //Παραγωγή Μέγιστης τιμής σειράς διακριτών τιμών
extern float crest(float []);	   //Παραγωγή Crest Factor
extern void histogram(float []);   //Παραγωγή Ιστογράμματος
extern void process(void);		   //Συνάρτηση καλέσματος συναρτήσεων επεξεργασίας
//Αρχικοποιήσεις συστήματος-----------------------------------------------------
extern void startCpu(void);			//Εκκίνηση CPU
extern void timerconfig(void);		//Ρύθμιση χρονιστών
extern void delay(int);				//Συνάρτηση καθυστέρησης
extern void initports(void);		 //Αρχικοποίηση ports
extern void initmaskinterrupts(void);	//Αρχικοποίηση διακοπών
extern void initsystem(void);		//Γενική αρχικοποίηση συστήματος
//ADC---------------------------------------------------------------------------
extern void ADCpoweron(int);	   //Έναρξη ADC
extern void ADCpowerdown(void);	   //Σβήσιμο ADC
extern void ADCconfig(void);	   //Ρύθμιση ADC


