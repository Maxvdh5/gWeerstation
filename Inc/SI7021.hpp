/*
 * SI7021.hpp
 *
 *  Created on: 13 sep. 2018
 *      Author: niels
 */

#ifndef SI7021_HPP_
#define SI7021_HPP_

#include "stm32f0xx_hal.h"
#include "stm32f030x8.h"

class SI7021 {
private:

	I2C_HandleTypeDef hi2c1;

	const uint16_t address = (0x40 << 1);
	const uint8_t cmdHumidity = 0xE5;
	const uint8_t cmdTemperature = 0xE0;
	uint16_t rawHumidity = 0x0000;
	uint16_t rawTemperature = 0x0000;

private:
	void swapBytes(uint16_t *input, uint16_t *output);

public:
	SI7021();
	virtual ~SI7021();
	bool init();
	bool readSensor();
	uint16_t * getHumidity();
	uint16_t * getTemperature();
};

#endif /* SI7021_HPP_ */
