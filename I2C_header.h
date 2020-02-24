/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000
#endif

#ifndef __I2C_HEADER_H
#define	__I2C_HEADER_H

#include <xc.h>  
#include <stdint.h>

void Init_I2C_Master(const unsigned long b);
void Init_I2C_Slave(uint8_t address);
void Wait_I2C_Master();
void Start_I2C_Master();
void Restart_I2C();
void Stop_I2C_Master();
void Write_I2C_Master(unsigned a);
unsigned short I2C_Master_Read(unsigned short a);


#endif	/* __I2C_HEADER_H */

