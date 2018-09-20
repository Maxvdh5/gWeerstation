/*
 * SI7021.cpp
 *
 *  Created on: 13 sep. 2018
 *      Author: niels
 */

#include <SI7021.hpp>

SI7021::SI7021()
{
	// TODO Auto-generated constructor stub

}

SI7021::~SI7021()
{
	// TODO Auto-generated destructor stub
}

bool SI7021::init()
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
		return false;
	}

	/**Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	{
		return false;
	}

	/**Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
	{
		return false;
	}

	return true; // I2C initialized
}

/* Helper function to swap the order of the bytes
 * in SI7021's return values
 */
void SI7021::swapBytes(uint16_t *input, uint16_t *output)
{
	uint8_t msb = (*input & 0xFF00) >> 8;
	uint8_t lsb = (*input & 0xFF);

	*output = lsb << 8 | msb;
}

bool SI7021::readSensor()
{
	uint16_t humidity, temperature;

	// Request humidity reading
	if (HAL_I2C_Master_Transmit(&hi2c1, address, (uint8_t*) (&cmdHumidity), 2,
			1000) != HAL_OK)
		return (false);

	// Receive humidity reading
	if (HAL_I2C_Master_Receive(&hi2c1, address, (uint8_t *)&humidity, 2, 1000) != HAL_OK)
		return (false);

	// Humidity was succesfully read: copy the value
	swapBytes(&humidity, &rawHumidity);

	// Request temperature reading
	if (HAL_I2C_Master_Transmit(&hi2c1, address, (uint8_t*) (&cmdTemperature),
			2, 1000) != HAL_OK)
		return (false);

	// Receive temperature reading
	if (HAL_I2C_Master_Receive(&hi2c1, address, (uint8_t *)&temperature, 2, 1000) != HAL_OK)
		return (false);

	// Temperature reading was succesfull: copy value
	swapBytes(&temperature, &rawTemperature);

	return true;
}

uint16_t * SI7021::getHumidity()
{
	return &rawHumidity;
}

uint16_t * SI7021::getTemperature()
{
	return &rawTemperature;
}
