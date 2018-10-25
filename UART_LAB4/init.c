#include "init.h"
#ifdef __XC32
    #include <xc.h>      
#endif
void init_bits(void){
	ANSELE = 0x00;//for LED's on shield
	ANSELGbits.ANSG6 = 0;
	ANSELBbits.ANSB11 = 0;
	ANSELGbits.ANSG15 = 0;
	//ANSELEbits.ANSE6 = 0;
	
	TRISE = 0x00;//for LED's on shield
	TRISGbits.TRISG6 = 0;
	TRISBbits.TRISB11 = 0;
	TRISGbits.TRISG15 = 0;
	//TRISEbits.TRISE6 = 0;

	LATGbits.LATG6 = 0;
	LATGbits.LATG15 = 0;
	LATBbits.LATB11 = 0;
   
    // Disable analog mode
	ANSELAbits.ANSA5 = 0;
    // Set directions to input
	TRISAbits.TRISA2 = 1;
	TRISAbits.TRISA3 = 1;
	TRISDbits.TRISD5 = 1;
	TRISFbits.TRISF5 = 1;

}

void CN_interrupts(){
    // Configure peripheral to generate interrupts
    // Enable change notification interrupt in CN
	CNENAbits.CNIEA2 = 1;
	CNENAbits.CNIEA3 = 1;
	CNENDbits.CNIED5 = 1;
	CNENFbits.CNIEF1 = 1;
    // Configure Interrupt Controller
    // Enable change notification  interrupts
	IEC3bits.CNAIE = 1;
	IEC3bits.CNDIE = 1;
	IEC3bits.CNFIE = 1;
    // Set priority
	IPC29bits.CNAIP = 2;
	IPC30bits.CNDIP = 3;
	IPC30bits.CNFIP = 4;
    // Clear interrupt Flag
	IFS3bits.CNAIF = 0;
	IFS3bits.CNDIF = 0;
	IFS3bits.CNFIF = 0;
    //  Set Interrupt Controller for multi-vector mode
	INTCONSET = _INTCON_MVEC_MASK;
    //  Globally enable interrupts
	__builtin_enable_interrupts();
    //  Enable peripheral
    	CNCONAbits.ON = 1;
	CNCONDbits.ON = 1;	
	CNCONFbits.ON = 1;
  
}