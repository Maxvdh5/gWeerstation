/*
 * sensors.h
 *
 *  Created on: Sep 18, 2018
 *      Author: pollop
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#include "stm32f0xx_hal.h"

#define SI7021_ADDRESS 0x40
#define CMD_SI7021_HUMIDITY 0xE5
#define CMD_SI7021_TEMPERATURE 0xE0

#define BMP180_ADDRESS 0x77
#define CMD_BMP180_PRESSURE 0xF7

I2C_HandleTypeDef hi2c1;

int I2C1_Init();
int readSensor(uint8_t address, uint8_t command, uint16_t *data);
int readSensors();
uint16_t * getHumidity();
uint16_t * getTemperature();
uint16_t * getPressure();

#endif /* SENSORS_H_ */
