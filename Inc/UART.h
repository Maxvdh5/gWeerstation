/*
 * UART.hpp
 *
 *  Created on: 13 Sep 2018
 *      Author: Terence
 */
#ifndef UART_H_
#define UART_H_

#include "stm32f0xx_hal.h"

int initUART(uint32_t _baudRate);
int transmit(char *data);
void initGPIO();
void ESPwakeUp();
void ESPsleep();
void recieve();
void POST_SENSOR_DATA(uint8_t humidity, uint8_t temperature, uint8_t pressure, char *password);
void initESP();

#endif /* UART_H_ */
