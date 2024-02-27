################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/r_adc/r_adc.c 

OBJS += \
./ra/fsp/src/r_adc/r_adc.o 

C_DEPS += \
./ra/fsp/src/r_adc/r_adc.d 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/r_adc/%.o: ../ra/fsp/src/r_adc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_RA_ -I"C:\Users\SG\e2_studio\workspace\Final\src" -I"C:\Users\SG\e2_studio\workspace\Final\ra\fsp\inc" -I"C:\Users\SG\e2_studio\workspace\Final\ra\fsp\inc\api" -I"C:\Users\SG\e2_studio\workspace\Final\ra\fsp\inc\instances" -I"C:\Users\SG\e2_studio\workspace\Final\ra\arm\CMSIS_5\CMSIS\Core\Include" -I"C:\Users\SG\e2_studio\workspace\Final\ra_gen" -I"C:\Users\SG\e2_studio\workspace\Final\ra_cfg\fsp_cfg\bsp" -I"C:\Users\SG\e2_studio\workspace\Final\ra_cfg\fsp_cfg" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


