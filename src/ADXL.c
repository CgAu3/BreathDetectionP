/*
 * reference:
 * original author: Husamuldeen <https://github.com/hussamaldean>
 */


#include "ADXL.h"
#include "I2C.h"



#define DEVICE_ADDR    			(0x53) /*adxl345 address*/
#define DATA_FORMAT_R   		(0x31) /*data format register*/
#define POWER_CTL_R 			(0x2D) /*Power control register*/
#define DATA_START_ADDR			(0x32) /*Start address to read the values*/

#define	RESET					(0x00) /*Reset value*/
#define SET_MEASURE_B		    (0x08) /*Put adxl345 into measurement mode*/

/*Variables which hold some variable*/
int8_t data_rec[6];
uint8_t acc_range;
int16_t x,y,z;
void adxl345_init(adxl345Parameters param)
	{
		acc_range=param;
		I2C_WriteByte(DEVICE_ADDR, DATA_FORMAT_R, param);
		I2C_WriteByte(DEVICE_ADDR, POWER_CTL_R, RESET);
		I2C_WriteByte(DEVICE_ADDR,POWER_CTL_R, SET_MEASURE_B);
		printf("ADXL_Init OK\n");

	}

void adxl345_update()
	{



		I2C_ReadMulti(DEVICE_ADDR, DATA_START_ADDR, 6, (char*)data_rec);

		x = ((data_rec[1]<<8)|data_rec[0]);
		y = ((data_rec[3]<<8)|data_rec[2]);
		z = ((data_rec[5]<<8)|data_rec[4]);

	}

void adxl345_get_values(accleration_values_t * values)
	{
	float divider;
	switch(acc_range)
	{
		case accl_2g: divider=0.003906; /*1/256*/	break;
		case accl_4g: divider=0.0078125;/*1/128*/	break;
		case accl_8g: divider=0.01563;	/*1/64*/	break;
		case accl_16g: divider=0.03125;	/*1/32*/	break;
		default: divider=0.01;
	}
	divider = 1;

		values->ax=x*divider;
		values->ay=y*divider;
		values->az=z*divider;
	}
