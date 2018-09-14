/*
 * UART.hpp
 *
 *  Created on: 13 Sep 2018
 *      Author: Terence
 */
#ifndef UART_HPP_
#define UART_HPP_

#include "stm32f0xx_hal.h"

class UART{

public:
	bool init(uint16_t _baudRate);
	bool transmit(uint8_t *data, int size);

private:

};



#endif /* UART_HPP_ */
