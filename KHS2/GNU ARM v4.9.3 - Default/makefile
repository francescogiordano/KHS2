################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include protocol/bluetooth_2.6/lib/EFR32BG1B/EABI/subdir.mk
-include platform/middleware/glib/glib/subdir.mk
-include platform/emlib/src/subdir.mk
-include platform/emdrv/wdog/src/subdir.mk
-include platform/emdrv/uartdrv/src/subdir.mk
-include platform/emdrv/mstimer/src/subdir.mk
-include platform/emdrv/letimer/src/subdir.mk
-include platform/emdrv/gpiointerrupt/src/subdir.mk
-include platform/emdrv/dmadrv/src/subdir.mk
-include platform/emdrv/adc/src/subdir.mk
-include platform/Device/SiliconLabs/EFR32BG1B/Source/GCC/subdir.mk
-include hardware/kit/common/drivers/subdir.mk
-include hardware/kit/common/bsp/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: KHS2.axf

# Tool invocations
KHS2.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -T "G:\My Drive\R&D\Firmware Design\KHS2\KHS2\efr32bg1b232f256gm56.ld" -Xlinker -no-enum-size-warning -Xlinker -no-wchar-size-warning -Xlinker --gc-sections -Xlinker -Map="KHS2.map" -mfpu=fpv4-sp-d16 -mfloat-abi=hard -o KHS2.axf "./advertisement.o" "./app.o" "./app_ble.o" "./app_data.o" "./app_hw.o" "./application_properties.o" "./board.o" "./gatt_db.o" "./init_app.o" "./init_board.o" "./init_mcu.o" "./main.o" "./mcu.o" "./payloadbuffer.o" "./pti.o" "./hardware/kit/common/bsp/bsp_stk.o" "./hardware/kit/common/bsp/bsp_trace.o" "./hardware/kit/common/drivers/h3lis331dl.o" "./hardware/kit/common/drivers/i2cspm.o" "./hardware/kit/common/drivers/lsm6dsl.o" "./hardware/kit/common/drivers/retargetswo.o" "./hardware/kit/common/drivers/s23lc1024.o" "./hardware/kit/common/drivers/udelay.o" "./platform/Device/SiliconLabs/EFR32BG1B/Source/GCC/startup_efr32bg1b.o" "./platform/emdrv/adc/src/adc.o" "./platform/emdrv/dmadrv/src/dmadrv.o" "./platform/emdrv/gpiointerrupt/src/gpiointerrupt.o" "./platform/emdrv/letimer/src/letimer.o" "./platform/emdrv/mstimer/src/mstimer.o" "./platform/emdrv/uartdrv/src/uartdrv.o" "./platform/emdrv/wdog/src/wdog.o" "./platform/emlib/src/em_adc.o" "./platform/emlib/src/em_cmu.o" "./platform/emlib/src/em_cryotimer.o" "./platform/emlib/src/em_gpio.o" "./platform/emlib/src/em_i2c.o" "./platform/emlib/src/em_ldma.o" "./platform/emlib/src/em_letimer.o" "./platform/emlib/src/em_leuart.o" "./platform/emlib/src/em_msc.o" "./platform/emlib/src/em_rtcc.o" "./platform/emlib/src/em_system.o" "./platform/emlib/src/em_timer.o" "./platform/emlib/src/em_usart.o" "./platform/emlib/src/em_wdog.o" "./platform/middleware/glib/glib/bmp.o" "./platform/middleware/glib/glib/glib.o" "./platform/middleware/glib/glib/glib_bitmap.o" "./platform/middleware/glib/glib/glib_circle.o" "./platform/middleware/glib/glib/glib_font_narrow_6x8.o" "./platform/middleware/glib/glib/glib_font_normal_8x8.o" "./platform/middleware/glib/glib/glib_font_number_16x20.o" "./platform/middleware/glib/glib/glib_line.o" "./platform/middleware/glib/glib/glib_polygon.o" "./platform/middleware/glib/glib/glib_rectangle.o" "./platform/middleware/glib/glib/glib_string.o" "G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\lib\EFR32BG1B\EABI\binbootloader.o" "G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\lib\EFR32BG1B\EABI\stack.a" "G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\lib\EFR32BG1B\EABI\binstack.o" "G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\lib\EFR32BG1B\GCC\bgapi.a" -lm -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: KHS2.hex'
	arm-none-eabi-objcopy -O ihex "KHS2.axf" "KHS2.hex"
	@echo ' '

	@echo 'Building bin file: KHS2.bin'
	arm-none-eabi-objcopy -O binary "KHS2.axf" "KHS2.bin"
	@echo ' '

	@echo 'Building s37 file: KHS2.s37'
	arm-none-eabi-objcopy -O srec "KHS2.axf" "KHS2.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "KHS2.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) KHS2.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
