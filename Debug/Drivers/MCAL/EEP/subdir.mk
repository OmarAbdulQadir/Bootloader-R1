################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/MCAL/EEP/EEP_program.c 

OBJS += \
./Drivers/MCAL/EEP/EEP_program.o 

C_DEPS += \
./Drivers/MCAL/EEP/EEP_program.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/MCAL/EEP/%.o: ../Drivers/MCAL/EEP/%.c Drivers/MCAL/EEP/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


