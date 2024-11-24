################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FATFS/diskio.c \
../FATFS/ff.c \
../FATFS/ff_gen_drv.c \
../FATFS/syscall.c \
../FATFS/unicode.c 

OBJS += \
./FATFS/diskio.o \
./FATFS/ff.o \
./FATFS/ff_gen_drv.o \
./FATFS/syscall.o \
./FATFS/unicode.o 

C_DEPS += \
./FATFS/diskio.d \
./FATFS/ff.d \
./FATFS/ff_gen_drv.d \
./FATFS/syscall.d \
./FATFS/unicode.d 


# Each subdirectory must supply rules for building sources it contributes
FATFS/%.o FATFS/%.su FATFS/%.cyclo: ../FATFS/%.c FATFS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"../Gui files" -I../FATFS -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FATFS

clean-FATFS:
	-$(RM) ./FATFS/diskio.cyclo ./FATFS/diskio.d ./FATFS/diskio.o ./FATFS/diskio.su ./FATFS/ff.cyclo ./FATFS/ff.d ./FATFS/ff.o ./FATFS/ff.su ./FATFS/ff_gen_drv.cyclo ./FATFS/ff_gen_drv.d ./FATFS/ff_gen_drv.o ./FATFS/ff_gen_drv.su ./FATFS/syscall.cyclo ./FATFS/syscall.d ./FATFS/syscall.o ./FATFS/syscall.su ./FATFS/unicode.cyclo ./FATFS/unicode.d ./FATFS/unicode.o ./FATFS/unicode.su

.PHONY: clean-FATFS

