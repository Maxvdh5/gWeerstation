/*
 * sensors.h
 *
 *  Created on: Sep 18, 2018
 *      Author: pollop
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#include "stm32f0xx_hal.h"

#define BMP180_ADDRESS 0xEE
#define SI7021_ADDRESS 0x40
#define CMD_SI7021_HUMIDITY 0xE5
#define CMD_SI7021_TEMPERATURE 0xE0

int readSensors();
uint16_t * getHumidity();
uint16_t * getTemperature();
uint16_t * getPressure();

#endif /* SENSORS_H_ */
