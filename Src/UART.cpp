/*
 * UART.cpp
 *
 *  Created on: 13 Sep 2018
 *      Author: Terence
 */
#include "UART.hpp"

UART_HandleTypeDef UartHandle;

bool UART::init(uint16_t _baudRate){
	  /*##-1- Configure the UART peripheral ######################################*/
	  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	  /* UART configured as follows:
	      - Word Length = 8 Bits
	      - Stop Bit = One Stop bit
	      - Parity = None
	      - BaudRate = configurable
	      - Hardware flow control disabled (RTS and CTS signals) */
	  UartHandle.Instance = USART1;
	  UartHandle.Init.BaudRate = _baudRate;
	  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits = UART_STOPBITS_1;
	  UartHandle.Init.Parity = UART_PARITY_NONE;
	  UartHandle.Init.Mode = UART_MODE_TX_RX;
	  UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	  UartHandle.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	  UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	  if (HAL_UART_Init(&UartHandle) != HAL_OK)
	  {
	    return false;
	  }

	  return true;
}

bool UART::transmit(uint8_t *data, int size){

	uint8_t aTxBuffer[size];

	for(int _size = size-1; _size>=0; _size--){
		aTxBuffer[_size] = data[_size];
	}

	if( HAL_UART_Transmit(&UartHandle, aTxBuffer, size, 1000) != HAL_OK )
	{
		return false;
	}

	return true;
}
