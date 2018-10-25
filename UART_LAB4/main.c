/******************************************************************************/
/*  Made by Golub M. & Serhiienko A.  DK-62                                   */
/******************************************************************************/
#include <stdint.h>                               
#include <stdbool.h>
#include <xc.h> 
#include "UART.h"
#include "init.h"  
#include "config.h"  

static char uart_data[BUFFER];

/* interrupt handlers */
void __ISR(_CHANGE_NOTICE_A_VECTOR, IPL2SOFT) ISR_PortA_Change(void) {
    
        if (PORTAbits.RA2 == 1)   // Switch is pressed
           UART4_puts("Button 4 pressed\r\n");
        
	if (PORTAbits.RA3 == 1)  // Switch is pressed
           UART4_puts("Button 1 pressed\r\n");
    // Reset interrupt flag
	IFS3bits.CNAIF = 0;
}

void __ISR(_CHANGE_NOTICE_D_VECTOR, IPL3SOFT) ISR_PortD_Change(void) {
        if (PORTDbits.RD5 == 1)   // Switch is pressed
           UART4_puts("Button 2 pressed\r\n");
    // Reset interrupt flag
	IFS3bits.CNDIF = 0;
}

void __ISR(_CHANGE_NOTICE_F_VECTOR, IPL4SOFT) ISR_PortF_Change(void) {
        if (PORTFbits.RF1 == 1)  // Switch is pressed
           UART4_puts("Button 3 pressed\r\n");
    // Reset interrupt flag
	IFS3bits.CNFIF = 0;
}

void main(void)
{
	init_bits();
	CN_interrupts();
	UART4_init();
   	while(1){
 		UART4_gets(uart_data);
		if(comp_func(uart_data,"led1"))
			LATEbits.LATE0 ^=1;
		if(comp_func(uart_data,"led2"))
			LATEbits.LATE1 ^=1;
		if(comp_func(uart_data,"led3"))
			LATEbits.LATE2 ^=1;
		if(comp_func(uart_data,"led4"))
			LATEbits.LATE3 ^=1;
		if(comp_func(uart_data,"led5"))
			LATEbits.LATE4 ^=1;
		if(comp_func(uart_data,"led6"))
			LATEbits.LATE5 ^=1;
		if(comp_func(uart_data,"led7"))
			LATEbits.LATE6 ^=1;
		if(comp_func(uart_data,"led8"))
			LATEbits.LATE7 ^=1;
		if(comp_func(uart_data,"flash"))
			LATE^=0xFF;
				
	}

}
