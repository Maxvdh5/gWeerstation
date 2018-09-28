#include "main.h"
#include <stdio.h>
#include "UART.hpp"
#include <stdlib.h>

void SystemClock_Config(void) {

	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* No HSE Oscillator on Nucleo, Activate PLL with HSI/2 as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_NONE;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		/* Initialization Error */
		while (1)
			;
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
			| RCC_CLOCKTYPE_PCLK1);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
		/* Initialization Error */
		while (1)
			;
	}
}

int main() {
	int delay = 3000;
	HAL_Init();
	SystemClock_Config();

	UART uart;
	uart.init(115200);

	uint8_t data6[] = "AT+CWQAP\r\n"; //disconect
	int size = sizeof(data6) / sizeof(data6[0]);
	uart.transmit(data6, size);

	HAL_Delay(delay);
	uint8_t data1[] = "AT+CIPMODE=0\r\n"; //mode normal
	size = sizeof(data1) / sizeof(data1[0]);
	uart.transmit(data1, size);
	HAL_Delay(delay);

	uint8_t data2[] = "AT+CIPMUX=0\r\n"; //single connection before connection
	size = sizeof(data2) / sizeof(data2[0]);
	uart.transmit(data2, size);
	HAL_Delay(delay);

	uint8_t data[] = "AT+CWJAP=\"gws\",\"gweerstation\"\r\n";
	size = sizeof(data) / sizeof(data[0]);
	uart.transmit(data, size);
	HAL_Delay(10000);

	uint8_t data3[] = "AT+CIPSTART=\"TCP\",\"www.pellevangils.nl\",80\r\n";
	size = sizeof(data3) / sizeof(data3[0]);
	uart.transmit(data3, size);
	HAL_Delay(delay);

	uint8_t data4[] = "AT+CIPSEND=200\r\n";
	size = sizeof(data4) / sizeof(data4[0]);
	uart.transmit(data4, size);
	HAL_Delay(delay);
	uint8_t data5[] = "POST /insert.php HTTP/1.1\r\nHost: pellevangils.nl\r\nAccept: */*\r\nContent-Length: 66\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\ntemperature=21&humidity=51&pressure=1001&password=XXRp42yM8LHm40zF\r\n";
	//uint8_t data5[] = "GET /insert.php HTTP/1.1\r\nHost: pellevangils.nl\r\n\r\n";
	size = sizeof(data5) / sizeof(data5[0]);
	uart.transmit(data5, size);

//	uint8_t data7[] = "temperature=21.1&humidity=51.1&pressure=1001.1&password=XXRp42yM8LHm40zF";
//
//	size = sizeof(data7) / sizeof(data7[0]);
//	uart.transmit(data7, size);
	return 0;
}
