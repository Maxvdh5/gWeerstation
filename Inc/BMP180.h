/*#include "stm32f0xx_hal.h"
//#include "stdint.h"

const uint16_t BMP180_ADDR = (0xEE << 1);
const uint8_t cmdPressure = 0xF4;
const uint8_t cmdTemperature = 0x2E;
uint16_t returnHumidity = 0x00;
uint16_t returnTemperature = 0x00;

int16_t AC1, AC2, AC3, VB1, VB2, MB, MC, MD;
uint16_t AC4, AC5, AC6;
double c5, c6, mc, md, x0, x1, x2, y0, y1, y2, p0, p1, p2;

char BMP180_setup(I2C_HandleTypeDef *i2c_handle);
uint8_t BMB180_getPressure(I2C_HandleTypeDef *i2c_handle, uint8_t *buf,
		uint8_t size);

//char BMP180_readInt(I2C_HandleTypeDef *i2c_handle,char address, int16_t &value);
// read an signed int (16 bits) from a BMP180 register
// address: BMP180 register address
// value: external signed int for returned value (16 bits)
// returns 1 for success, 0 for fail, with result in value

//char BMP180_readUInt(I2C_HandleTypeDef *i2c_handle,char address, uint16_t &value);
// read an unsigned int (16 bits) from a BMP180 register
// address: BMP180 register address
// value: external unsigned int for returned value (16 bits)
// returns 1 for success, 0 for fail, with result in value

char BMP180_readBytes(I2C_HandleTypeDef *i2c_handle,unsigned char *values, char length);
// read a number of bytes from a BMP180 register
// values: array of char with register address in first location [0]
// length: number of bytes to read back
// returns 1 for success, 0 for fail, with read bytes in values[] array

char BMP180_writeBytes(I2C_HandleTypeDef *i2c_handle,unsigned char *values, char length);
// write a number of bytes to a BMP180 register (and consecutive subsequent registers)
// values: array of char with register address in first location [0]
// length: number of bytes to write
// returns 0 for success, 1 for fail
