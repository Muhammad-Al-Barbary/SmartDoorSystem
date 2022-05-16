################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MC2.c \
../buzzer.c \
../external_eeprom.c \
../gpio.c \
../i2c.c \
../motor.c \
../timer.c \
../uart.c 

OBJS += \
./MC2.o \
./buzzer.o \
./external_eeprom.o \
./gpio.o \
./i2c.o \
./motor.o \
./timer.o \
./uart.o 

C_DEPS += \
./MC2.d \
./buzzer.d \
./external_eeprom.d \
./gpio.d \
./i2c.d \
./motor.d \
./timer.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


