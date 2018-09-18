/*
 * sensors.c
 *
 *  Created on: Sep 18, 2018
 *      Author: pollop
 */

#include "sensors.h"

uint16_t rawHumidity = 0x0000;
uint16_t rawTemperature = 0x0000;
uint16_t rawPressure = 0x0000;

int I2C1_Init()
{

	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing = 0x0020098E;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		return 1;
	}

	/**Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	{
		return 1;
	}

	/**Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
	{
		return 1;
	}

	return 0; // I2C initialized
}

/* Helper function to swap the order of the bytes
 * in SI7021's return values
 */
void swapBytes(uint16_t *input, uint16_t *output)
{
	uint8_t msb = (*input & 0xFF00) >> 8;
	uint8_t lsb = (*input & 0xFF);

	*output = lsb << 8 | msb;
}

int readSensor(uint8_t address, uint8_t command, uint16_t *data)
{
	uint16_t returnData;

	// Request reading
	if (HAL_I2C_Master_Transmit(&hi2c1, (address << 1), (uint8_t*) (&command), 2,
			1000) != HAL_OK)
		return (1);

	// Receive reading
	if (HAL_I2C_Master_Receive(&hi2c1, (address << 1), (uint8_t *)&returnData, 2, 1000) != HAL_OK)
		return (1);

	// Reading was succesfully read: copy the value
	swapBytes(&returnData, data);


	return 0;
}

int readSensors()
{
	readSensor(SI7021_ADDRESS, CMD_SI7021_HUMIDITY, &rawHumidity);
	readSensor(SI7021_ADDRESS, CMD_SI7021_TEMPERATURE, &rawTemperature);
	readSensor(BMP180_ADDRESS, CMD_BMP180_PRESSURE, &rawPressure);

	return 0;
}

uint16_t * getHumidity()
{
	return &rawHumidity;
}

uint16_t * getTemperature()
{
	return &rawTemperature;
}

uint16_t * getPressure()
{
	return &rawPressure;
}
