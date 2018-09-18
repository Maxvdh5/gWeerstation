#include "BMP180.h"

const uint16_t address = (0xEE << 1);
const uint8_t cmdPressure = 0xF4;
const uint8_t cmdTemperature = 0x2E;
uint16_t returnHumidity = 0x00;
uint16_t returnTemperature = 0x00;

uint8_t BMB180_getPressure(I2C_HandleTypeDef *i2c_handle,uint8_t *buf, uint8_t size)
{
	if (HAL_I2C_Master_Transmit(i2c_handle, address, (uint8_t*) (&cmdPressure), 2,1000) != HAL_OK)
		return (1);


	if (HAL_I2C_Master_Receive(i2c_handle, address, buf, 2, 1000) != HAL_OK)
		return (2);

	return (0);
}
