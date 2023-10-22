################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/MCAL/GI/GI_program.c 

OBJS += \
./Drivers/MCAL/GI/GI_program.o 

C_DEPS += \
./Drivers/MCAL/GI/GI_program.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/MCAL/GI/%.o: ../Drivers/MCAL/GI/%.c Drivers/MCAL/GI/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


