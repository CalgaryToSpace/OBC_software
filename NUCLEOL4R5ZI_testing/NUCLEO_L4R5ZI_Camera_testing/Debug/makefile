################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

BUILD_ARTIFACT_NAME := NUCLEO_L4R5ZI_Camera_testing
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
NUCLEO_L4R5ZI_Camera_testing.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
NUCLEO_L4R5ZI_Camera_testing.list \

OBJCOPY_BIN += \
NUCLEO_L4R5ZI_Camera_testing.bin \


# All Target
all: main-build

# Main-build Target
main-build: NUCLEO_L4R5ZI_Camera_testing.elf secondary-outputs

# Tool invocations
NUCLEO_L4R5ZI_Camera_testing.elf: $(OBJS) $(USER_OBJS) C:\Users\James\Documents\Calgary\ to\ Space\OBC_software\NUCLEOL4R5ZI_testing\NUCLEO_L4R5ZI_Camera_testing\STM32L4R5ZITX_FLASH.ld
	arm-none-eabi-gcc -o "NUCLEO_L4R5ZI_Camera_testing.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\James\Documents\Calgary to Space\OBC_software\NUCLEOL4R5ZI_testing\NUCLEO_L4R5ZI_Camera_testing\STM32L4R5ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="NUCLEO_L4R5ZI_Camera_testing.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

NUCLEO_L4R5ZI_Camera_testing.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "NUCLEO_L4R5ZI_Camera_testing.list"
	@echo 'Finished building: $@'
	@echo ' '

NUCLEO_L4R5ZI_Camera_testing.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "NUCLEO_L4R5ZI_Camera_testing.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY:

-include ../makefile.targets
