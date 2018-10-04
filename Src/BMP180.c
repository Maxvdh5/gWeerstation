/*#include "BMP180.h"

char BMP180_setup(I2C_HandleTypeDef *i2c_handle)
{

	return 0;
}

uint8_t BMB180_getPressure(I2C_HandleTypeDef *i2c_handle, uint8_t *buf, uint8_t size)
{
	if (HAL_I2C_Master_Transmit(i2c_handle, address, (uint8_t*) (&cmdPressure), 2, 1000) != HAL_OK)
		return (1);

	//    osDelay(20);

	if (HAL_I2C_Master_Receive(i2c_handle, address, buf, 2, 1000) != HAL_OK)
		return (2);

	return (0);
}

char readInt(I2C_HandleTypeDef *i2c_handle, char address, int *value)
{
	if (HAL_I2C_Master_Transmit(i2c_handle, address, (uint16_t*) value, 2, 1000) != HAL_OK)
		return (1);

	//    osDelay(20);

	if (HAL_I2C_Master_Receive(i2c_handle, address, buf, 2, 1000) != HAL_OK)
		return (2);

	return (0);
}

char BMP180_readBytes(I2C_HandleTypeDef *i2c_handle, unsigned char *values, char length)
{
	// Read an array of bytes from device
	// values: external array to hold data. Put starting register in values[0].
	// length: number of bytes to read

	if (HAL_I2C_Master_Transmit(i2c_handle, BMP180_ADDR, (uint16_t*) values[0], 1, 1000) != HAL_OK)
		return (1);

	if (HAL_I2C_Master_Receive(i2c_handle, BMP180_ADDR, values, length, 1000) != HAL_OK)
		return (2);

	return (0);
}
*/
