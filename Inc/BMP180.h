#include "stm32f0xx_hal.h"

uint8_t BMB180_getPressure(I2C_HandleTypeDef *i2c_handle, uint8_t *buf, uint8_t size);
