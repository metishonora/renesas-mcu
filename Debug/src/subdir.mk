################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/agt.c \
../src/arrival.c \
../src/button.c \
../src/can.c \
../src/elevator.c \
../src/fnd.c \
../src/gpio.c \
../src/hal_entry.c \
../src/motor.c \
../src/node.c \
../src/sensor.c \
../src/sound.c \
../src/uart.c \
../src/warning.c 

OBJS += \
./src/agt.o \
./src/arrival.o \
./src/button.o \
./src/can.o \
./src/elevator.o \
./src/fnd.o \
./src/gpio.o \
./src/hal_entry.o \
./src/motor.o \
./src/node.o \
./src/sensor.o \
./src/sound.o \
./src/uart.o \
./src/warning.o 

C_DEPS += \
./src/agt.d \
./src/arrival.d \
./src/button.d \
./src/can.d \
./src/elevator.d \
./src/fnd.d \
./src/gpio.d \
./src/hal_entry.d \
./src/motor.d \
./src/node.d \
./src/sensor.d \
./src/sound.d \
./src/uart.d \
./src/warning.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_RA_ -I"C:\Users\SG\e2_studio\workspace\Final\src" -I"C:\Users\SG\e2_studio\workspace\Final\ra\fsp\inc" -I"C:\Users\SG\e2_studio\workspace\Final\ra\fsp\inc\api" -I"C:\Users\SG\e2_studio\workspace\Final\ra\fsp\inc\instances" -I"C:\Users\SG\e2_studio\workspace\Final\ra\arm\CMSIS_5\CMSIS\Core\Include" -I"C:\Users\SG\e2_studio\workspace\Final\ra_gen" -I"C:\Users\SG\e2_studio\workspace\Final\ra_cfg\fsp_cfg\bsp" -I"C:\Users\SG\e2_studio\workspace\Final\ra_cfg\fsp_cfg" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


