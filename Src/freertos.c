/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * Copyright (c) 2018 STMicroelectronics International N.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other
 *    contributors to this software may be used to endorse or promote products
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under
 *    this license is void and will automatically terminate your rights under
 *    this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "rtc.h"
#include "sensors.h"
#include "UART.h"
#include "stm32f0xx_hal.h"
#include "stm32f0xx_nucleo.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
uint8_t sensorTaskDone;
uint8_t wifiTaskDone;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId sensorTaskHandle;
osThreadId wifiTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartSensorTask(void const * argument);
void StartWifiTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
    /* USER CODE BEGIN Init */
    sensorTaskDone = 0;
    wifiTaskDone = 0;
    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* Create the thread(s) */
    /* definition and creation of defaultTask */
    osThreadDef(defaultTask, StartDefaultTask, osPriorityLow, 0, 128);
    defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

    /* definition and creation of sensorTask */
    osThreadDef(sensorTask, StartSensorTask, osPriorityHigh, 0, 128);
    sensorTaskHandle = osThreadCreate(osThread(sensorTask), NULL);

    /* definition and creation of wifiTask */
    osThreadDef(wifiTask, StartWifiTask, osPriorityNormal, 0, 128);
    wifiTaskHandle = osThreadCreate(osThread(wifiTask), NULL);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{

    BSP_LED_On(LED2);
    /* USER CODE BEGIN StartDefaultTask */
    /* Infinite loop */
    while (!sensorTaskDone || !wifiTaskDone)
    {
        osDelay(1);
    }

    MX_RTC_Init();

    // Manually clear the WakeUp flag, since the IRQ handler,
    // which clears it, hasn't been called yet.
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);

    // Enter STANDBY
    HAL_PWR_EnterSTANDBYMode();

    for (;;)
    {
        osDelay(1);
    }
    /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartSensorTask */
/**
 * @brief Function implementing the sensorTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartSensorTask */
void StartSensorTask(void const * argument)
{
    /* USER CODE BEGIN StartSensorTask */
    readSensors();
    sensorTaskDone = 1;
    osThreadTerminate(sensorTaskHandle);
    /* Infinite loop */
    for (;;)
    {
        osDelay(1);
    }
    /* USER CODE END StartSensorTask */
}

/* USER CODE BEGIN Header_StartWifiTask */
/**
 * @brief Function implementing the wifiTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartWifiTask */
void StartWifiTask(void const * argument)
{
    /* USER CODE BEGIN StartWifiTask */
    if( initESP() != 0 ) // Init WiFi connection
    {
    	// Handle error?
    }
    else
    {
    	while( !sensorTaskDone ) // Wait for sensors to be read
    	{
    		osDelay(1);
    	}
    	// send latest sensor data to the cloud storage
    	if( POST_SENSOR_DATA(getTemperature() ,getHumidity() ,getPressure() ,"x0tFeeIUSPIVk50F") != 0 )
    	{
    		// Handle error?
    	}
    }

    wifiTaskDone = 1;
    osThreadTerminate(wifiTaskHandle);
    /* Infinite loop */
    for (;;)
    {
        osDelay(1);
    }
    /* USER CODE END StartWifiTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
