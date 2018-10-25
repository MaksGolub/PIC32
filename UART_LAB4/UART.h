#include <stdbool.h>
#define BUFFER 64
/**
* UART4_init
*
* Initialization of UART registers.
*
*/
void UART4_init (void);
/**
* UART4_getc
* 
* Function that allows you to get char from the UART  
*
*/
char UART4_getc(void);
/**
* UART4_putc
* @c - char which will be put to the UART
*
* Function that puts the char into UART
*
*/
void UART4_putc (char c);
/**
* UART4_gets
* @DATA - empty array,that will be filled with data from UART
*
* The function gets the string from UART and puts it in array.
*
*/
void UART4_gets(char * DATA);
/**
* comp_func
* @str1,@str2 strings to compare
*
* Returns true if strings are equal, false if not
* Actually, it's the same as strcmp.
*
*/
bool comp_func (char *str1,char *str2);
/**
* UART4_puts
* @s - string which will be translated through UART
*
* Function which translates the string through UART
*
*/
void UART4_puts (char *s);