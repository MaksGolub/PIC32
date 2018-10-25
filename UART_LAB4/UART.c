#include "UART.h"
#include <xc.h>
#include <stdbool.h>

void UART4_init (void){
    RPF8R = 2; // PPS for U4RX from pin F2
    U4RXR = 11; // PPS for U4TX to pin F8
    U4STAbits.UTXEN = 1;   // enable transmit pin
    U4STAbits.URXEN = 1;   // enable receive pin
    U4BRG= ((100 * 1000000) / (16 * 115200)) - 1;// set the baudrate
    U4MODEbits.ON   = 1;   // enable UART
}

char UART4_getc(void) {
    while (!U4STAbits.URXDA); // wait until character received
    return U4RXREG; // read character
}

void UART4_putc (char c){
    while (U4STAbits.UTXBF);  // wait until transmit buffer not full
    U4TXREG = c;  // transmit character
}
void UART4_gets(char * DATA){
	uint32_t cnt = 0;
	char tmp = 0;
	while (1){
		tmp = UART4_getc();
	/* Reading the data from buffer,till meets "ENTER"(13 ASCII) */
		if ((tmp == 13) || (tmp == 0)) {
	/* Put null-terminator into the last place of string */
			DATA[cnt] = '\0';
			break;
		}
		DATA[cnt] = tmp;
		cnt++;
	}
}
void UART4_puts (char *s){
    while (*s != '\0')
        UART4_putc (*s++);
    
}

bool comp_func (char *str1,char *str2){
	bool if_equal = false;
	for (int i = 0;i < BUFFER;i++){	
	/* Comparing if the data are the same */
		if(*(str1+i) == *(str2+i)){	
	/* When we get null-terminator it means that the strings are the same */
			if(*(str1+i) == '\0'){
				if_equal = true;
				return if_equal;
			}
		}else
	/* If we meet inequality,break the cycle,the strings aren't the same */
		break;
	}
	return if_equal;
}