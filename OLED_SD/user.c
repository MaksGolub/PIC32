/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#ifdef __XC32
#include <xc.h>          /* Defines special function registers, CP0 regs  */
#endif

#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "user.h"            /* variables/params used by user.c               */
#include "OLED.h"  
#include <sys/attribs.h>

/******************************************************************************/
/* User Functions                                                             */

/******************************************************************************/
void DelayMs(int t) {
    volatile long int count = t*33356;
    
    while (count--)
        ;
}

void SPI_init()
{
    	SPI3CONbits.ON = 0; // Turn off SPI3 before configuring
    	SPI3CONbits.MSTEN = 1; // Enable Master mode
    	SPI3CONbits.CKP = 1; // Clock signal is active low, idle state is high
    	SPI3CONbits.CKE = 0; // Data is shifted out/in on transition from idle (high) state to active (low) state
    	SPI3CONbits.SMP = 1; // Input data is sampled at the end of the clock signal
    	//SPI3CONbits.ON = 1; // Configuration is done, turn on SPI3 peripheral

// Set up PPS for SPI3 on RB10 and RC4
	SDI3R = 0b0110; // RB10 = SDI3
	RPC4R = 0b0111; // RC4 = SDO3
	SS3R = 0b1100; // RC3 = SS3
	TRISBbits.TRISB10 = 1; // Set RB10 as input because it's SDI3
	TRISCbits.TRISC3 = 0;	
	CNPUBbits.CNPUB10 = 1;
	CNPUBbits.CNPUB14 = 1;
	CNPUCbits.CNPUC3 = 1;
	CNPUCbits.CNPUC4 = 1;	
	SPI3CONbits.ON = 1; // Configuration is done, turn on SPI3 peripheral	 
}

char SPI_send(char data)
{
	SPI3BUF = data; // Send *data* to SPI3BUF.
	while (SPI3STATbits.SPIRBE); // Which the receive buffer is empty, loop
	return (char)SPI3BUF; // Return whatever is in SPI3BUF
}

void InitTimer2(void) {
   T2CON = 0; // clear timer settings to defaults
    T2CONbits.TCKPS = 6; // prescale by factor of 64
    // 1 tick = 640 ns
    TMR2 = 0; // clear timer
    // Timer is not running yet. Need to set ON to 1.

    // No interrupts needed.
}

/*void __ISR(_TIMER_2_VECTOR, IPL3SOFT) ISR_Timer_2 (void) {
    static int LED_state = 1;
    
    // Toggle LED2
    LD2_PORT_BIT = LED_state;
    LED_state = 1-LED_state;
    
    // Reset interrupt flag
    IFS0bits.T2IF = 0;
}*/

void InitGPIO(void) {
    /* Setup functionality and port direction */
    // LED output
    // Disable analog mode
    ANSELGbits.ANSG6 = 0;
    ANSELBbits.ANSB11 = 0;
    ANSELGbits.ANSG15 = 0;
    // Set directions to output
    TRISGbits.TRISG6 = 0;
    TRISBbits.TRISB11 = 0;
    TRISGbits.TRISG15 = 0;
    TRISDbits.TRISD4 = 0;

    // Turn off LEDs for initialization
    LD1_PORT_BIT = 0;
    LD2_PORT_BIT = 0;
    LD3_PORT_BIT = 0;
    LD4_PORT_BIT = 0;

    // Button inputs
    // Disable analog mode
    ANSELAbits.ANSA5 = 0;
    // Set directions to input
    TRISAbits.TRISA5 = 1;
    TRISAbits.TRISA4 = 1;
     
    TRISDCLR = 1<<11;
}

void InitApp(void) {
    // Initialize peripherals
    InitGPIO();
    OledHostInit();
    OledDspInit();
    InitTimer2();
    SPI_init();
 // TODO: Set PREFEN mode
    // 0: Disable, 1: CPU instructions, 2. CPU instrs + data, 3. Any address
    PRECONbits.PREFEN = 3; 
    // TODO: Set PFMWS for wait states
    PRECONbits.PFMWS = 2;

    // Set up Shadow Register Sets
    PRISS = 0x76543210; /* assign shadow set #7-#1 to priority level #7-#1 ISRs */

    // Set Interrupt Controller for multi-vector mode
    INTCONSET = _INTCON_MVEC_MASK;

    // Globally enable interrupts
    __builtin_enable_interrupts();
    // Enable peripherals which can generate an interrupt    

#if 0
    InitTimer2();
    
    // Set Interrupt Controller for multi-vector mode
    INTCONSET = _INTCON_MVEC_MASK;
    // Globally enable interrupts
    __builtin_enable_interrupts();
    // Enable peripherals which can generate an interrupt
    T2CONbits.ON = 1; // Start Timer 2
    
#endif
}
