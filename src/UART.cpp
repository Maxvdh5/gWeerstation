/*
 * UART.cpp
 *
 *  Created on: 13 Sep 2018
 *      Author: Terence
 */
#include "UART.hpp"
#include "main.h"
#include <stdlib.h>
UART_HandleTypeDef UartHandle;

void UART::init(uint32_t _baudRate){
	  /*##-1- Configure the UART peripheral ######################################*/
	  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	  /* UART configured as follows:
	      - Word Length = 8 Bits
	      - Stop Bit = One Stop bit
	      - Parity = None
	      - BaudRate = 9600 baud
	      - Hardware flow control disabled (RTS and CTS signals) */
	  UartHandle.Instance        = USARTx;

	  UartHandle.Init.BaudRate   = _baudRate;
	  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits   = UART_STOPBITS_1;
	  UartHandle.Init.Parity     = UART_PARITY_NONE;
	  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode       = UART_MODE_TX_RX;
	  UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	  HAL_UART_Init(&UartHandle);
}

void UART::transmit(uint8_t *data, int size){

	uint8_t *aTxBuffer = (uint8_t*) calloc(size,sizeof(uint8_t));

	for(int _size = size-1; _size>=0; _size--){
		aTxBuffer[_size] = data[_size];
	}


	HAL_UART_Transmit_DMA(&UartHandle, (uint8_t*) aTxBuffer, size);
}
