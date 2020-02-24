/*
 * File:   I2C.c
 * Author: José P11
 * Basado fuertemente en la librería de ElectroSome
 * hecha por Ligo George y modificada por Pablo Mazariegos
 * Created on 24 de febrero de 2020, 11:14 AM
 */

#include <xc.h>
#include <stdint.h>
#include "I2C_header.h"

void Init_I2C_Master(const unsigned long b){
    SSPCONbits.SSPM0 = 0;
    SSPCONbits.SSPM1 = 0;
    SSPCONbits.SSPM2 = 0;
    SSPCONbits.SSPM3 = 1;

    SSPCONbits.CKP = 0;
    SSPCONbits.SSPEN = 1;
    SSPCON2 = 0;
    SSPADD = (_XTAL_FREQ/(4*b)) - 1;
    SSPSTAT = 0;
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
}

void Init_I2C_Slave(uint8_t address){
    SSPADD = address;
    SSPCON - 0x36;
    SSPSTAT = 0x80;
    SSPCON2 = 0x01;
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIR1bits.SSPIF = 0;
    PIE1bits.SSPIE = 1;
    
}

void Wait_I2C_Master(){
    while ((SSPSTAT & 0x04) || (SSPCON2 & 01F));
}

void Start_I2C_Master(){
    Wait_I2C_Master();
    SSPCON2bits.SEN = 1;
}

void Restart_I2C(){
    Wait_I2C_Master();
    SSPCON2bits.RSEN = 1;
}

void Stop_I2C_Master(){
    Wait_I2C_Master();
    SSPCON2bits.PEN = 1;
}

void Write_I2C_Master(unsigned a){
    Wait_I2C_Master();
    SSPBUF = a;
}

unsigned short I2C_Master_Read(unsigned short a){
    unsigned short temporal;
    Wait_I2C_Master();
    SSPCON2bits.RCEN = 1;
    Wait_I2C_Master();
    temporal = SSPBUF;
    Wait_I2C_Master();
    
    if (a == 1){
        SSPCON2bits.ACKDT = 0;
    }else{
        SSPCON2bits.ACKDT = 1;
    }
    SSPCON2bits.ACKEN = 1;
    return temporal;
}
