################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./Bump.obj" \
"./Clock_DL.obj" \
"./FSM.obj" \
"./FSMSwitchDebounce.obj" \
"./LaunchPad.obj" \
"./Motor_Skeleton.obj" \
"./Nokia5110_skeleton.obj" \
"./PWM.obj" \
"./PushButton.obj" \
"./Reflectance.obj" \
"./SensorFSM.obj" \
"./Switch.obj" \
"./TimerA1_skeleton.obj" \
"./adc14.obj" \
"./aes256.obj" \
"./bme280.obj" \
"./bme280_support.obj" \
"./bmi160.obj" \
"./bmi160_support.obj" \
"./comp_e.obj" \
"./cpu.obj" \
"./crc32.obj" \
"./cs.obj" \
"./demo_sysctl.obj" \
"./dma.obj" \
"./flash.obj" \
"./fpu.obj" \
"./gpio.obj" \
"./i2c.obj" \
"./i2c_driver.obj" \
"./interrupt.obj" \
"./main.obj" \
"./mpu.obj" \
"./opt3001.obj" \
"./pcm.obj" \
"./pmap.obj" \
"./pss.obj" \
"./ref_a.obj" \
"./reset.obj" \
"./rtc_c.obj" \
"./spi.obj" \
"./startup_msp432p401r_ccs.obj" \
"./sysctl.obj" \
"./system_msp432p401r.obj" \
"./systick.obj" \
"./timer32.obj" \
"./timer_a.obj" \
"./tmp007.obj" \
"./uart.obj" \
"./uart_driver.obj" \
"./wdt_a.obj" \
"../msp432p401r.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
WorkingMaze.out \

EXE_OUTPUTS__QUOTED += \
"WorkingMaze.out" \

BIN_OUTPUTS += \
WorkingMaze.hex \

BIN_OUTPUTS__QUOTED += \
"WorkingMaze.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "WorkingMaze.out"

# Tool invocations
WorkingMaze.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"WorkingMaze.map" --heap_size=1024 --stack_size=512 -i"C:/ti/ccs1040/ccs/ccs_base/arm/include" -i"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/lib" -i"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="WorkingMaze_linkInfo.xml" --rom_model -o "WorkingMaze.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

WorkingMaze.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armhex" --memwidth=8 --romwidth=8 --diag_wrap=off -o "WorkingMaze.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "Bump.obj" "Clock_DL.obj" "FSM.obj" "FSMSwitchDebounce.obj" "LaunchPad.obj" "Motor_Skeleton.obj" "Nokia5110_skeleton.obj" "PWM.obj" "PushButton.obj" "Reflectance.obj" "SensorFSM.obj" "Switch.obj" "TimerA1_skeleton.obj" "adc14.obj" "aes256.obj" "bme280.obj" "bme280_support.obj" "bmi160.obj" "bmi160_support.obj" "comp_e.obj" "cpu.obj" "crc32.obj" "cs.obj" "demo_sysctl.obj" "dma.obj" "flash.obj" "fpu.obj" "gpio.obj" "i2c.obj" "i2c_driver.obj" "interrupt.obj" "main.obj" "mpu.obj" "opt3001.obj" "pcm.obj" "pmap.obj" "pss.obj" "ref_a.obj" "reset.obj" "rtc_c.obj" "spi.obj" "startup_msp432p401r_ccs.obj" "sysctl.obj" "system_msp432p401r.obj" "systick.obj" "timer32.obj" "timer_a.obj" "tmp007.obj" "uart.obj" "uart_driver.obj" "wdt_a.obj" 
	-$(RM) "Bump.d" "Clock_DL.d" "FSM.d" "FSMSwitchDebounce.d" "LaunchPad.d" "Motor_Skeleton.d" "Nokia5110_skeleton.d" "PWM.d" "PushButton.d" "Reflectance.d" "SensorFSM.d" "Switch.d" "TimerA1_skeleton.d" "adc14.d" "aes256.d" "bme280.d" "bme280_support.d" "bmi160.d" "bmi160_support.d" "comp_e.d" "cpu.d" "crc32.d" "cs.d" "demo_sysctl.d" "dma.d" "flash.d" "fpu.d" "gpio.d" "i2c.d" "i2c_driver.d" "interrupt.d" "main.d" "mpu.d" "opt3001.d" "pcm.d" "pmap.d" "pss.d" "ref_a.d" "reset.d" "rtc_c.d" "spi.d" "startup_msp432p401r_ccs.d" "sysctl.d" "system_msp432p401r.d" "systick.d" "timer32.d" "timer_a.d" "tmp007.d" "uart.d" "uart_driver.d" "wdt_a.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

