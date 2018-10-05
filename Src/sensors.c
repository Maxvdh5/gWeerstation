/*
 * sensors.c
 *
 *  Created on: Sep 18, 2018
 *      Author: pollop
 *
 *      TODO: sensor data struct
 */

#include "sensors.h"
#include "i2c.h"
#include "cmsis_os.h"
#include "bmp180.h"

uint16_t humidity = 0x0000;
uint16_t temperature = 0x0000;
uint16_t pressure = 0x0000;

/* Helper function to swap the order of the bytes
 * in SI7021's return values
 */
void swapBytes(uint16_t *input, uint16_t *output)
{
    uint8_t msb = (*input & 0xFF00) >> 8;
    uint8_t lsb = (*input & 0xFF);

    *output = lsb << 8 | msb;
}

/*
 * Read one of the data registers on the SI7021 module
 */
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

/*
 * Wrapper function for HAL_I2C_Mem_write() for use by the Bosch Sensortec lib
 */
int8_t i2cBmpWrite(uint8_t deviceAddr, uint8_t registerAddr,
        uint8_t *registerData, uint8_t writeLength)
{
    if (HAL_I2C_Mem_Write(&hi2c1, deviceAddr, registerAddr,
            I2C_MEMADD_SIZE_8BIT, registerData, writeLength, 1000) != HAL_OK)
        return 1;

    return 0;
}

/*
 * Wrapper function for HAL_I2C_Mem_Read() for use by the Bosch Sensortec lib
 */
int8_t i2cBmpRead(uint8_t deviceAddr, uint8_t registerAddr,
        uint8_t *registerData, uint8_t writeLength)
{
    if (HAL_I2C_Mem_Read(&hi2c1, deviceAddr, registerAddr, I2C_MEMADD_SIZE_8BIT,
            registerData, writeLength, 1000) != HAL_OK)
        return 1;

    return 0;
}

/*
 * Wrapper function for osDelay() for use by the Bosch Sensortec lib
 */
void bmpDelayMsec(uint32_t delay)
{
    osDelay(delay);
}

/*
 * Read air pressure from the BMP180 sensor
 * based on the template function in the Bosch SensorTec BMP180 lib
 *
 * Even though we do not use the temperature readout from this sensor
 * it is neccesary to call 'bmp180_get_temperature()' before
 * 'bmp_get_pressure()' for accurate readings.
 *
 * return: air pressure in Pa
 */
int readBMPSensor(uint8_t address, int32_t *data)
{
    struct bmp180_t bmp180;
    int32_t com_rslt = E_BMP_COMM_RES;
    uint16_t v_uncomp_temp_u16 = BMP180_INIT_VALUE;
    uint32_t v_uncomp_press_u32 = BMP180_INIT_VALUE;

    // Set up function pointers
    bmp180.bus_write = i2cBmpWrite;
    bmp180.bus_read = i2cBmpRead;
    bmp180.dev_addr = address;
    bmp180.delay_msec = bmpDelayMsec;

    com_rslt = bmp180_init(&bmp180);
    com_rslt += bmp180_get_calib_param();

    v_uncomp_temp_u16 = bmp180_get_uncomp_temperature();
    v_uncomp_press_u32 = bmp180_get_uncomp_pressure();

    com_rslt += bmp180_get_temperature(v_uncomp_temp_u16);

    *data = bmp180_get_pressure(v_uncomp_press_u32) / 10;

    return 0;
}

/*
 * Read out all the available sensors
 * calculations are as specified in the sensor's datasheets.
 * results are multiplied by 10 so we can send integer values to the database
 */
int readSensors()
{
    uint16_t rawHumidity, rawTemperature;
    int32_t rawPressure;

    readSensor(SI7021_ADDRESS, CMD_SI7021_HUMIDITY, &rawHumidity);
    humidity = (((125.0 * rawHumidity) / 65536) - 6) * 10;

    readSensor(SI7021_ADDRESS, CMD_SI7021_TEMPERATURE, &rawTemperature);
    temperature = (((175.72 * rawTemperature) / 65536) - 46.85) * 10;

    readBMPSensor(BMP180_ADDRESS, &rawPressure);
    pressure = rawPressure / 10; // divide by 10 because Pascal -> millibar

    return 0;
}

uint16_t * getHumidity()
{
    return &humidity;
}

uint16_t * getTemperature()
{
    return &temperature;
}

uint16_t * getPressure()
{
    return &pressure;
}
