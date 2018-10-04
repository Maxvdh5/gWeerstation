/*
 * UART.cpp
 *
 *  Created on: 13 Sep 2018
 *      Author: Terence
 */
#include "UART.h"
#include "usart.h"
#include "cmsis_os.h"
#include <stdlib.h>
#include <string.h>

#define GPIOA_MODER	(*(unsigned int *)(0x48000000 + 0x00))
#define GPIOA_ODR	(*(unsigned int *)(0x48000000 + 0x14))
#define RCC_AHBENR	(*(unsigned int *)(0x40021000 + 0x14))

void initGPIO() {
	RCC_AHBENR |= (1 << 17); 		    // Enable clock for GPIO port A
	GPIOA_MODER |= (1 << (5 * 2));  	// CLK
	GPIOA_MODER |= (1 << (7 * 2));		// MOSI

	GPIOA_ODR &= ~(1 << 5);
}

void ESPwakeUp() {
	GPIOA_ODR |= (1 << 5);
	HAL_Delay(100);
	GPIOA_ODR &= ~(1 << 5);
}

void ESPsleep() {
	transmit("AT+GSLP=300000\r\n");
}

void recieve() {

}

int POST_SENSOR_DATA(uint8_t humidity, uint8_t temperature, uint8_t pressure,
		char *password) {

	char dataString[40];
	sprintf(dataString, "%d%d%d%s", humidity, temperature, pressure,
			(char*) password);
	uint8_t dataSize = strlen((char*) dataString);

	char postRequest[255];
	uint8_t size = 176 + dataSize//176 is the size of postrequest without any values given to the 4 variabales
			, contentValue = dataSize + 43;	//43 is the size of the base dataSize is amount of digits from the 4 variabales
	char ATCIPSEND[17];

	sprintf(ATCIPSEND, "AT+CIPSEND=%d\r\n", size);
	if( transmit(ATCIPSEND) != 0 )
	{
		return 1;
	}
	osDelay(1000);
	sprintf(postRequest,
			"POST /insert.php HTTP/1.1\r\nHost: pellevangils.nl\r\nAccept: */*\r\nContent-Length: %d\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\ntemperature=%d&humidity=%d&pressure=%d&password=%s\r\n",
			contentValue, humidity, temperature, pressure, password);
	if( transmit(postRequest) != 0 )
	{
		return 1;
	}

	return 0;
}
/*
 * Connect to the WiFi access-point ->
 * wait for a connection to be established ->
 * Open a HTTP connection with the cloudstorage website
 *
 * TODO: Get feedback from the wifi module to see whether a connection was succesful
 */
int initESP() {

	if( transmit("AT+CWJAP_CUR=\"gws\",\"gweerstation\"\r\n") != 0) //connect to wifi wait a long time
	{
		return 1;
	}

	osDelay(7000);

	if( transmit("AT+CIPSTART=\"TCP\",\"www.pellevangils.nl\",80\r\n") != 0 )
	{
		return 1;
	}
	osDelay(1000);

	return 0;
}

/*
 * Send a string of data to USART1 with a 1s timeout
 *
 * TODO: Get feedback from the wifi module whether a command was received and interpreted correctly
 */
int transmit(char *data) {
	if (HAL_UART_Transmit(&huart1, (uint8_t*) data, strlen(data), 1000)
			!= HAL_OK) {

		return 1;
	}

	return 0;
}
