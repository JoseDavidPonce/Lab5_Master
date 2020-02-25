/* 
 * File:  Header libreria 8bits LCD 
 * Author: José David Ponce
 * Carné: 18187
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __LCD_8BITS_H_
#define	__LCD_8BITS_H_

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000
#endif

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

#define EN PORTDbits.RD7
#define RW PORTDbits.RD6
#define RS PORTDbits.RD5
#define PUERTO PORTB

void LCD_CMD (uint8_t a);
void LCD_CLR (void);
void LCD_SET_CURSOR (uint8_t a, uint8_t b);
void LCD_INIT (void);
void LCD_WRITE_CHAR (char a);
void LCD_WRITE_STRING(char *a);
void LCD_SHIFT_RIGHT(void);
void LCD_SHIFT_LEFT(void);

#endif	/* XC_HEADER_TEMPLATE_H */

