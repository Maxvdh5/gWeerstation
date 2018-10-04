/*
 * sensors.c
 *
 *  Created on: Sep 18, 2018
 *      Author: pollop
 */

#include "sensors.h"
#include "i2c.h"
#include "cmsis_os.h"

uint16_t rawHumidity = 0x0000;
uint16_t rawTemperature = 0x0000;
uint16_t rawPressure = 0x0000;


/* Helper function to swap the order of the bytes
 * in SI7021's return values
 */
void swapBytes(uint16_t *input, uint16_t *output)
{
    uint8_t msb = (*input & 0xFF00) >> 8;
    uint8_t lsb = (*input & 0xFF);

    *output = lsb << 8 | msb;
}

int readSensor(uint8_t address, uint8_t command, uint16_t *data)
{
    uint16_t returnData;

    // Request reading
    if (HAL_I2C_Master_Transmit(&hi2c1, (address << 1), (uint8_t*) (&command),
            2, 1000) != HAL_OK)
        return (1);

    // Receive reading
    if (HAL_I2C_Master_Receive(&hi2c1, (address << 1), (uint8_t *) &returnData,
            2, 1000) != HAL_OK)
        return (1);

    // Reading was succesfully read: copy the value
    swapBytes(&returnData, data);

    return 0;
}

int readBMPSensor(uint8_t address, uint8_t command, uint16_t *data)
{
    uint8_t measHum[2] =
    { 0xF4, 0x34 };
    uint8_t getHum = 0xF6;
    uint16_t returnData;

    // Request reading
    if (HAL_I2C_Master_Transmit(&hi2c1, (address << 1), measHum, 2, 1000)
            != HAL_OK)
        return (1);

    osDelay(20);

    if (HAL_I2C_Master_Transmit(&hi2c1, (address << 1), &getHum, 2, 1000)
            != HAL_OK)
        return (1);

    // Receive reading
    if (HAL_I2C_Master_Receive(&hi2c1, (address << 1), (uint8_t *) &returnData,
            2, 1000) != HAL_OK)
        return (1);

    // Reading was succesfully read: copy the value
    swapBytes(&returnData, data);
    //*data /= 4;
    //*data = returnData;

    return 0;
}

int readSensors()
{
    readSensor(SI7021_ADDRESS, CMD_SI7021_HUMIDITY, &rawHumidity);
    readSensor(SI7021_ADDRESS, CMD_SI7021_TEMPERATURE, &rawTemperature);
    readBMPSensor(BMP180_ADDRESS, CMD_BMP180_PRESSURE, &rawPressure);

    return 0;
}

uint16_t * getHumidity()
{
    return &rawHumidity;
}

uint16_t * getTemperature()
{
    return &rawTemperature;
}

uint16_t * getPressure()
{
    return &rawPressure;
}
