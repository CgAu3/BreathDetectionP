/**
 * reference:
 * original author: Husamuldeen <https://github.com/hussamaldean>
 */



#ifndef __i2c_H
#define __i2c_H

#include "stm32f4xx.h"                  // Device header
#include "delay.h"
#include <stdint.h>
#include "stdio.h"
void I2C_Init(void);
char I2C_ReadByte(char saddr,char maddr,char *data);
void I2C_WriteByte(char saddr,char maddr,char data);
void I2C_WriteMulti(char saddr,char maddr,char *buffer, uint8_t length);
void I2C_ReadMulti(char saddr,char maddr, int n, char* data);
void I2C_Bus_scan(void);
#endif

