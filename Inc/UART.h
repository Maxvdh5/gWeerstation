/*
 * UART.hpp
 *
 *  Created on: 13 Sep 2018
 *      Author: Terence
 */
#ifndef UART_H_
#define UART_H_

#include "stm32f0xx_hal.h"

int initUART(uint16_t _baudRate);
int transmit(uint8_t *data, int size);

#endif /* UART_H_ */
