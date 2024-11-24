################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FATFS/src/diskio.c \
../FATFS/src/ff.c \
../FATFS/src/ff_gen_drv.c 

OBJS += \
./FATFS/src/diskio.o \
./FATFS/src/ff.o \
./FATFS/src/ff_gen_drv.o 

C_DEPS += \
./FATFS/src/diskio.d \
./FATFS/src/ff.d \
./FATFS/src/ff_gen_drv.d 


# Each subdirectory must supply rules for building sources it contributes
FATFS/src/%.o FATFS/src/%.su: ../FATFS/src/%.c FATFS/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"../GUI files" -I"C:/Users/jj/Desktop/first code/FATFS/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FATFS-2f-src

clean-FATFS-2f-src:
	-$(RM) ./FATFS/src/diskio.d ./FATFS/src/diskio.o ./FATFS/src/diskio.su ./FATFS/src/ff.d ./FATFS/src/ff.o ./FATFS/src/ff.su ./FATFS/src/ff_gen_drv.d ./FATFS/src/ff_gen_drv.o ./FATFS/src/ff_gen_drv.su

.PHONY: clean-FATFS-2f-src

