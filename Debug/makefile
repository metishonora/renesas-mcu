################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

-include makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include ra_gen/subdir.mk
-include ra/fsp/src/r_sci_uart/subdir.mk
-include ra/fsp/src/r_ioport/subdir.mk
-include ra/fsp/src/r_icu/subdir.mk
-include ra/fsp/src/r_gpt/subdir.mk
-include ra/fsp/src/r_dac/subdir.mk
-include ra/fsp/src/r_can/subdir.mk
-include ra/fsp/src/r_agt/subdir.mk
-include ra/fsp/src/r_adc/subdir.mk
-include ra/fsp/src/bsp/mcu/all/subdir.mk
-include ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif
ifneq ($(strip $(JMP_DEPS)),)
-include $(JMP_DEPS)
endif
ifneq ($(strip $(PP_DEPS)),)
-include $(PP_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(FSY_DEPS)),)
-include $(FSY_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(P_DEPS)),)
-include $(P_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
Final.srec \

SECONDARY_SIZE += \
Final.siz \


# All Target
all: Final.elf secondary-outputs

# Tool invocations
Final.elf: $(OBJS) $(USER_OBJS) $(LINKER_SCRIPT)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU Arm Cross C Linker'
	$(file > Final.elf.in,-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -T "fsp.ld" -Xlinker --gc-sections -L "C:\\Users\\SG\\e2_studio\\workspace\\Final/script" -Wl,-Map,"Final.map" --specs=nano.specs --specs=rdimon.specs -o "Final.elf" -Wl,--start-group $(OBJS) $(USER_OBJS) $(LIBS) -Wl,--end-group)
	arm-none-eabi-gcc @"Final.elf.in"
	@echo 'Finished building target: $@'
	@echo ' '

Final.srec: Final.elf
	@echo 'Invoking: GNU Arm Cross Create Flash Image'
	arm-none-eabi-objcopy -O srec "Final.elf"  "Final.srec"
	@echo 'Finished building: $@'
	@echo ' '

Final.siz: Final.elf
	@echo 'Invoking: GNU Arm Cross Print Size'
	arm-none-eabi-size --format=berkeley "Final.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
ifneq ($(strip $(SRC_DEPS)),)
	-$(file > clean_SRC_DEPS.tmp, $(SRC_DEPS))
	-@ xargs -s 6000 -t -a clean_SRC_DEPS.tmp $(RM)
	-@$(RM) clean_SRC_DEPS.tmp
endif
ifneq ($(strip $(JMP_DEPS)),)
	-$(file > clean_JMP_DEPS.tmp, $(JMP_DEPS))
	-@ xargs -s 6000 -t -a clean_JMP_DEPS.tmp $(RM)
	-@$(RM) clean_JMP_DEPS.tmp
endif
ifneq ($(strip $(PP_DEPS)),)
	-$(file > clean_PP_DEPS.tmp, $(PP_DEPS))
	-@ xargs -s 6000 -t -a clean_PP_DEPS.tmp $(RM)
	-@$(RM) clean_PP_DEPS.tmp
endif
ifneq ($(strip $(SX_DEPS)),)
	-$(file > clean_SX_DEPS.tmp, $(SX_DEPS))
	-@ xargs -s 6000 -t -a clean_SX_DEPS.tmp $(RM)
	-@$(RM) clean_SX_DEPS.tmp
endif
ifneq ($(strip $(FSY_DEPS)),)
	-$(file > clean_FSY_DEPS.tmp, $(FSY_DEPS))
	-@ xargs -s 6000 -t -a clean_FSY_DEPS.tmp $(RM)
	-@$(RM) clean_FSY_DEPS.tmp
endif
ifneq ($(strip $(OBJS)),)
	-$(file > clean_OBJS.tmp, $(OBJS))
	-@ xargs -s 6000 -t -a clean_OBJS.tmp $(RM)
	-@$(RM) clean_OBJS.tmp
endif
ifneq ($(strip $(SECONDARY_FLASH)),)
	-$(file > clean_SECONDARY_FLASH.tmp, $(SECONDARY_FLASH))
	-@ xargs -s 6000 -t -a clean_SECONDARY_FLASH.tmp $(RM)
	-@$(RM) clean_SECONDARY_FLASH.tmp
endif
ifneq ($(strip $(SECONDARY_SIZE)),)
	-$(file > clean_SECONDARY_SIZE.tmp, $(SECONDARY_SIZE))
	-@ xargs -s 6000 -t -a clean_SECONDARY_SIZE.tmp $(RM)
	-@$(RM) clean_SECONDARY_SIZE.tmp
endif
ifneq ($(strip $(ASM_DEPS)),)
	-$(file > clean_ASM_DEPS.tmp, $(ASM_DEPS))
	-@ xargs -s 6000 -t -a clean_ASM_DEPS.tmp $(RM)
	-@$(RM) clean_ASM_DEPS.tmp
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
	-$(file > clean_S_UPPER_DEPS.tmp, $(S_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_S_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_S_UPPER_DEPS.tmp
endif
ifneq ($(strip $(P_DEPS)),)
	-$(file > clean_P_DEPS.tmp, $(P_DEPS))
	-@ xargs -s 6000 -t -a clean_P_DEPS.tmp $(RM)
	-@$(RM) clean_P_DEPS.tmp
endif
ifneq ($(strip $(C_DEPS)),)
	-$(file > clean_C_DEPS.tmp, $(C_DEPS))
	-@ xargs -s 6000 -t -a clean_C_DEPS.tmp $(RM)
	-@$(RM) clean_C_DEPS.tmp
endif
	-$(RM)  Final.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
