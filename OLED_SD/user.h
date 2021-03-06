#include <stdint.h>
/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

// Add I/O name macros here
#define LD1_PORT_BIT        LATGbits.LATG6
#define LD2_PORT_BIT        LATDbits.LATD4
#define LD3_PORT_BIT        LATBbits.LATB11
#define LD4_PORT_BIT        LATGbits.LATG15

#define BTN1_PORT_BIT       PORTAbits.RA5
#define BTN2_PORT_BIT       PORTAbits.RA4

typedef uint8_t BYTE;

BYTE rgbOledBmp1[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// 0x00
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,	// 0x01
	0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, // 0x02
	0x11, 0x44, 0x00, 0x11, 0x44, 0x00, 0x11, 0x44,	// 0x03
	0x92, 0x45, 0x24, 0x92, 0x45, 0x24, 0x92, 0x45,	// 0x04
	0x49, 0x92, 0x24, 0x49, 0x92, 0x24, 0x49, 0x92, // 0x05
	0x22, 0x11, 0x22, 0x00, 0x22, 0x11, 0x22, 0x00,	// 0x06
	0x11, 0x22, 0x11, 0x00, 0x11, 0x22, 0x11, 0x00,	// 0x07
	0x11, 0x44, 0x00, 0x11, 0x44, 0x00, 0x11, 0x44,	// 0x03
	0x92, 0x45, 0x24, 0x92, 0x45, 0x24, 0x92, 0x45,	// 0x04
	0x49, 0x92, 0x24, 0x49, 0x92, 0x24, 0x49, 0x92, // 0x05
	0x22, 0x11, 0x22, 0x00, 0x22, 0x11, 0x22, 0x00,	// 0x06
	0x11, 0x22, 0x11, 0x00, 0x11, 0x22, 0x11, 0x00	// 0x07
	
};

BYTE rgbOledBmp2[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,	// 0x00
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,	// 0x01
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 0x02
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,	// 0x03
	0x92, 0x45, 0x24, 0x92, 0x45, 0x24, 0x92, 0x45,	// 0x04
	0x49, 0x92, 0x24, 0x49, 0x92, 0x24, 0x49, 0x92, // 0x05
	0x22, 0x11, 0x22, 0x00, 0x22, 0x11, 0x22, 0x00,	// 0x06
	0x11, 0x22, 0x11, 0x00, 0x11, 0x22, 0x11, 0x00,	// 0x07
	0x11, 0x44, 0x00, 0x11, 0x44, 0x00, 0x11, 0x44,	// 0x03
	0x92, 0x45, 0x24, 0x92, 0x45, 0x24, 0x92, 0x45,	// 0x04
	0x49, 0x92, 0x24, 0x49, 0x92, 0x24, 0x49, 0x92, // 0x05
	0x22, 0x11, 0x22, 0x00, 0x22, 0x11, 0x22, 0x00,	// 0x06
	0x11, 0x22, 0x11, 0x00, 0x11, 0x22, 0x11, 0x00,	// 0x07
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,	// 0x00
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,	// 0x01
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 0x02
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,	// 0x03
	0x92, 0x45, 0x24, 0x92, 0x45, 0x24, 0x92, 0x45,	// 0x04
	0x49, 0x92, 0x24, 0x49, 0x92, 0x24, 0x49, 0x92, // 0x05
	0x22, 0x11, 0x22, 0x00, 0x22, 0x11, 0x22, 0x00,	// 0x06
	0x11, 0x22, 0x11, 0x00, 0x11, 0x22, 0x11, 0x00,	// 0x07
	0x11, 0x44, 0x00, 0x11, 0x44, 0x00, 0x11, 0x44,	// 0x03
	0x92, 0x45, 0x24, 0x92, 0x45, 0x24, 0x92, 0x45,	// 0x04
	0x49, 0x92, 0x24, 0x49, 0x92, 0x24, 0x49, 0x92, // 0x05
	0x22, 0x11, 0x22, 0x00, 0x22, 0x11, 0x22, 0x00,	// 0x06
	0x11, 0x22, 0x11, 0x00, 0x11, 0x22, 0x11, 0x00	// 0x07
	
};
/******************************************************************************/
/* User Function Prototypes                                                    /
/******************************************************************************/

void InitApp(void);         /* I/O and Peripheral Initialization */
void DelayMs(int t);
void SPI_init();
char SPI_send(char data);
