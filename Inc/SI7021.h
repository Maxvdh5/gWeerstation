/*
 * SI7021.hpp
 *
 *  Created on: 13 sep. 2018
 *      Author: niels
 */

#ifndef SI7021_H_
#define SI7021_H_

#include "stm32f0xx_hal.h"
#include "stm32f030x8.h"

void swapBytes(uint16_t *input, uint16_t *output);

int initSI7021();
int readSensor();
uint16_t * getHumidity();
uint16_t * getTemperature();

#endif /* SI7021_H_ */
