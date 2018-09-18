/*
 * SI7021.cpp
 *
 *  Created on: 13 sep. 2018
 *      Author: niels
 */

#include "SI7021.h"

I2C_HandleTypeDef hi2c1;

const uint16_t address = (0x40 << 1);
const uint8_t cmdHumidity = 0xE5;
const uint8_t cmdTemperature = 0xE0;
uint16_t rawHumidity;
uint16_t rawTemperature;

int initSI7021()
{
	// MX_I2C1_Init();

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

int readSensor()
{
	uint16_t humidity, temperature;

	// Request humidity reading
	if (HAL_I2C_Master_Transmit(&hi2c1, address, (uint8_t*) (&cmdHumidity), 2,
			1000) != HAL_OK)
		return (1);

	// Receive humidity reading
	if (HAL_I2C_Master_Receive(&hi2c1, address, (uint8_t *)&humidity, 2, 1000) != HAL_OK)
		return (1);

	// Humidity was succesfully read: copy the value
	swapBytes(&humidity, &rawHumidity);

	// Request temperature reading
	if (HAL_I2C_Master_Transmit(&hi2c1, address, (uint8_t*) (&cmdTemperature),
			2, 1000) != HAL_OK)
		return (1);

	// Receive temperature reading
	if (HAL_I2C_Master_Receive(&hi2c1, address, (uint8_t *)&temperature, 2, 1000) != HAL_OK)
		return (1);

	// Temperature reading was succesfull: copy value
	swapBytes(&temperature, &rawTemperature);

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
