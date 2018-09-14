/*
 * UART.hpp
 *
 *  Created on: 13 Sep 2018
 *      Author: Terence
 */
#include "main.h"
#ifndef UART_HPP_
#define UART_HPP_

class UART{

public:
	void init(uint16_t _baudRate);
	void transmit(uint8_t *data, int size);

private:

};



#endif /* UART_HPP_ */
