################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/%.o: ../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F030x8 -I"/media/sf_shared/weerstation/cube_i2c/Inc" -I"/media/sf_shared/weerstation/cube_i2c/Drivers/STM32F0xx_HAL_Driver/Inc" -I"/media/sf_shared/weerstation/cube_i2c/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"/media/sf_shared/weerstation/cube_i2c/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0" -I"/media/sf_shared/weerstation/cube_i2c/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"/media/sf_shared/weerstation/cube_i2c/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/media/sf_shared/weerstation/cube_i2c/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/media/sf_shared/weerstation/cube_i2c/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


