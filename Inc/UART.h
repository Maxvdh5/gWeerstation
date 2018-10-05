/*
 * UART.hpp
 *
 *  Created on: 13 Sep 2018
 *      Author: Terence
 */
#ifndef UART_H_
#define UART_H_

#include "stm32f0xx_hal.h"

int transmit(char *data);
void initGPIO();
void ESPwakeUp();
void ESPsleep();
void recieve();
int POST_SENSOR_DATA(uint16_t *humidity, uint16_t *temperature, uint16_t *pressure, char *password);
int initESP();

#endif /* UART_H_ */
