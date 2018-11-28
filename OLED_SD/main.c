/******************************************************************************/
/*  Made by Golub M.  DK-62                                 		      */
/******************************************************************************/

/******************************************************************************/
/*  Files to Include                                                          */
/******************************************************************************/
#ifdef __XC32
    #include <xc.h>          /* Defines special function registers, CP0 regs  */
#endif

#include <stdint.h>         /* For uint32_t definition                        */
#include <stdbool.h>        /* For true/false definition                      */

#include "user.h"           /* User funct/params, such as InitApp             */
#include "OLED.h"
#include "OledGrph.h"
#include "stdio.h"
#include "config.h"
#include "ff.h"
#include "diskio.h"
#include <math.h>

/******************************************************************************/
/* Global Variable Declaration 						      */                                             
/******************************************************************************/

// Global variables
FIL file; // File handle for the file we open
DIR dir; // Directory information for the current directory
FATFS fso; // File System Object for the file system we are reading from
FILINFO fileInfo; // Information for the file we have opened 

void init_disk()
{
    	// Wait for the disk to initialise
   	LATGbits.LATG6 = 1;
    	while(disk_initialize(0));
   	LATGbits.LATG6 = 0; // Check end of init disk
    	// Mount the disk
    	f_mount(&fso, "", 0);
    	// Change dir to the root directory
    	f_chdir("/");
    	// Open the directory
    	f_opendir(&dir, ".");
}

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int32_t main(void)
{
    	uint8_t pattern[5]= {0x0, 0x11, 0x99, 0xbb, 0xff};
    	char buffer[32];
	TCHAR time_out[16];
	int t_int=0;
    	char buffer2[16];
    	int x=8,y=8;
    	int n, i=0, j=0;
	int numread;
    	/* Initialize I/O 
     	* and Peripherals
     	* for application */
	ANSELB = 0;
    	ANSELC = 0;
    	InitApp();
	init_disk();
	FRESULT FOpenRes;
    	char file1name[]= "TEXT.TXT";
    	FOpenRes=f_open(&file, "TEXT.TXT", FA_CREATE_ALWAYS| FA_READ | FA_WRITE);
	FOpenRes = f_lseek(&file, 0);
    
   	OledDvrInit();
	
   	T2CONbits.ON = 1; // Start Timer 2
    	TMR2 = 0; // Clear Timer 2. Each tick is 640 ns
    	OledSetDrawColor(0);
    	OledSetDrawMode(modOledSet);
    	OledSetFillPattern(OledGetStdPattern(3));
    	//OledMoveTo(0,0);
	OledSetCursor(0,0);

	for(i=0; i<4; i++){
		for(j=0; j<5; j++) {	
			T2CONbits.ON = 1; // Start Timer 2
			OledPutBmp(x, y, rgbOledBmp2);
			OledUpdate();
			t_int = TMR2; // Measure elapsed time
			T2CONbits.ON = 0; // Stop Timer 2
			f_printf (&file, "%d\n", t_int);
			x+=25;
		}
		y+=8;		
	}


	t_int = TMR2; // Measure elapsed time
    	T2CONbits.ON = 0; // Stop Timer 2
 	OledSetCursor(0, 3);
 
	sprintf(buffer2, "Int: %6d", t_int);	
    	OledPutString(buffer2);


	//FOpenRes = f_write(&file, time_out, 16, &numread);
	f_printf (&file, "%d", t_int);

     	f_close(&file);

    	// Unmount filesystem

     	f_mount(0, "", 0); 
 	while(1);
}
