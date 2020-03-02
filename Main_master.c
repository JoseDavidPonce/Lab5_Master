/*
 * File:   Codigo_main_master.c
 * Author: José Ponce
 * Carné: 18187
 * Created on 24 de febrero de 2020, 10:58 AM
 */
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000
#endif
#include <xc.h>
#include <stdint.h>
#include "LCD_8bits.h"
#include "I2C_header.h"

uint8_t address = 0;
uint8_t pot, foto, cont, unipot, deci1pot, deci2pot;
uint8_t a = 0;
uint8_t unifoto, deci1foto, deci2foto;
uint8_t unicont, dececont;
uint16_t tempot, temfoto;
double potf;
double fotof;
char charfoto1, charpot1;
char charfoto2, charpot2;
char charfoto3, charpot3;
char charcont1, charcont2;

void Init_Port(void);
uint8_t obtener_unidades(uint8_t a);
uint8_t obtener_decenas(uint8_t a);
uint8_t obtener_decimal_1(float a);
uint8_t obtener_decimal_2(float a);
uint8_t convertir_a_ascii (uint8_t a);


void main(void) {
    Init_Port();
    Init_I2C_Master(100000);
    LCD_INIT();
    while (1){
        LCD_SET_CURSOR (1,1);
        LCD_WRITE_STRING ("Pot   Foto  Cont");
        
        Start_I2C_Master();
        Write_I2C_Master(0x11);
        pot = I2C_Master_Read(0);
        Stop_I2C_Master();
        __delay_ms(10);

        Start_I2C_Master();
        Write_I2C_Master(0x21);
        foto = I2C_Master_Read(0);
        Stop_I2C_Master();
        __delay_ms(10);
        
        Start_I2C_Master();
        Write_I2C_Master(0x31);
        cont = I2C_Master_Read(0);
        Stop_I2C_Master();
        __delay_ms(10);
        
        potf = pot*(5.0/255);
        fotof = foto*(5.0/255);
                
        
        unipot = obtener_unidades(potf);
        deci1pot = obtener_decimal_1(potf);
        deci2pot = obtener_decimal_2(potf);
        
        unifoto = obtener_unidades(fotof);
        deci1foto = obtener_decimal_1(fotof);
        deci2foto = obtener_decimal_2(fotof);
        
        unicont = obtener_unidades(cont);
        dececont = obtener_decenas(cont);
        
        charpot1 = convertir_a_ascii(unipot);
        charpot2 = convertir_a_ascii(deci1pot);
        charpot3 = convertir_a_ascii(deci2pot);
        
        charfoto1 = convertir_a_ascii(unifoto);
        charfoto2 = convertir_a_ascii(deci1foto);
        charfoto3 = convertir_a_ascii(deci2foto);
        
        charcont1 = convertir_a_ascii(unicont);
        charcont2 = convertir_a_ascii(dececont);

        LCD_SET_CURSOR (2,1);
        LCD_WRITE_CHAR (charpot1);
        LCD_WRITE_STRING(".");
        LCD_WRITE_CHAR (charpot2);
        LCD_WRITE_CHAR (charpot3);
        
        LCD_SET_CURSOR (2,7);
        LCD_WRITE_CHAR (charfoto1);
        LCD_WRITE_STRING(".");
        LCD_WRITE_CHAR (charfoto2);
        LCD_WRITE_CHAR (charfoto3);
        
        LCD_SET_CURSOR (2,13);
        LCD_WRITE_CHAR (charcont1);
        LCD_WRITE_CHAR (charcont2);
    }   
}

void Init_Port(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0;
    TRISD = 0;
    PORTB = 0;
    PORTD = 0;
}


uint8_t obtener_unidades(uint8_t a){
    uint8_t temporal;
    temporal = a%10;
    return temporal;
}
uint8_t obtener_decenas(uint8_t a){
    uint8_t temporal;
    temporal = (a/10)%10;
    return temporal;
}

uint8_t obtener_decimal_1(float a){
    uint16_t temporal;
    temporal = (a*10);
    temporal = temporal%10;
    return temporal;
}
uint8_t obtener_decimal_2(float a){
    uint16_t temporal;
    temporal = (a*100);
    temporal = temporal%10;
    return temporal;
}

uint8_t convertir_a_ascii (uint8_t a){
    char temporal;
    temporal = a+ 0x30;
    return temporal;
}