################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/kit/common/drivers/h3lis331dl.c \
../hardware/kit/common/drivers/i2cspm.c \
../hardware/kit/common/drivers/lsm6dsl.c \
../hardware/kit/common/drivers/retargetswo.c \
../hardware/kit/common/drivers/s23lc1024.c \
../hardware/kit/common/drivers/udelay.c 

OBJS += \
./hardware/kit/common/drivers/h3lis331dl.o \
./hardware/kit/common/drivers/i2cspm.o \
./hardware/kit/common/drivers/lsm6dsl.o \
./hardware/kit/common/drivers/retargetswo.o \
./hardware/kit/common/drivers/s23lc1024.o \
./hardware/kit/common/drivers/udelay.o 

C_DEPS += \
./hardware/kit/common/drivers/h3lis331dl.d \
./hardware/kit/common/drivers/i2cspm.d \
./hardware/kit/common/drivers/lsm6dsl.d \
./hardware/kit/common/drivers/retargetswo.d \
./hardware/kit/common/drivers/s23lc1024.d \
./hardware/kit/common/drivers/udelay.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/kit/common/drivers/h3lis331dl.o: ../hardware/kit/common/drivers/h3lis331dl.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__NO_SYSTEM_INIT=1' '-DEFR32BG1B232F256GM56=1' -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\halconfig\inc\hal-config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\bootloader\api" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\drivers" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\sleep\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\app\bluetooth_2.6\common\stack_bridge" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\common\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\wdog\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\EFR32BG1_BRD4303A\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\soc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\chip\efr32" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\CMSIS\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\ssd2119" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\gpiointerrupt\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\bsp" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\halconfig" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\inc" -O2 -fno-short-enums -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"hardware/kit/common/drivers/h3lis331dl.d" -MT"hardware/kit/common/drivers/h3lis331dl.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/kit/common/drivers/i2cspm.o: ../hardware/kit/common/drivers/i2cspm.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__NO_SYSTEM_INIT=1' '-DEFR32BG1B232F256GM56=1' -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\halconfig\inc\hal-config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\bootloader\api" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\drivers" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\sleep\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\app\bluetooth_2.6\common\stack_bridge" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\common\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\wdog\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\EFR32BG1_BRD4303A\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\soc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\chip\efr32" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\CMSIS\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\ssd2119" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\gpiointerrupt\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\bsp" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\halconfig" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\inc" -O2 -fno-short-enums -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"hardware/kit/common/drivers/i2cspm.d" -MT"hardware/kit/common/drivers/i2cspm.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/kit/common/drivers/lsm6dsl.o: ../hardware/kit/common/drivers/lsm6dsl.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__NO_SYSTEM_INIT=1' '-DEFR32BG1B232F256GM56=1' -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\halconfig\inc\hal-config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\bootloader\api" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\drivers" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\sleep\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\app\bluetooth_2.6\common\stack_bridge" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\common\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\wdog\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\EFR32BG1_BRD4303A\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\soc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\chip\efr32" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\CMSIS\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\ssd2119" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\gpiointerrupt\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\bsp" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\halconfig" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\inc" -O2 -fno-short-enums -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"hardware/kit/common/drivers/lsm6dsl.d" -MT"hardware/kit/common/drivers/lsm6dsl.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/kit/common/drivers/retargetswo.o: ../hardware/kit/common/drivers/retargetswo.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__NO_SYSTEM_INIT=1' '-DEFR32BG1B232F256GM56=1' -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\halconfig\inc\hal-config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\bootloader\api" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\drivers" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\sleep\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\app\bluetooth_2.6\common\stack_bridge" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\common\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\wdog\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\EFR32BG1_BRD4303A\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\soc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\chip\efr32" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\CMSIS\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\ssd2119" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\gpiointerrupt\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\bsp" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\halconfig" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\inc" -O2 -fno-short-enums -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"hardware/kit/common/drivers/retargetswo.d" -MT"hardware/kit/common/drivers/retargetswo.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/kit/common/drivers/s23lc1024.o: ../hardware/kit/common/drivers/s23lc1024.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__NO_SYSTEM_INIT=1' '-DEFR32BG1B232F256GM56=1' -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\halconfig\inc\hal-config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\bootloader\api" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\drivers" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\sleep\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\app\bluetooth_2.6\common\stack_bridge" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\common\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\wdog\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\EFR32BG1_BRD4303A\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\soc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\chip\efr32" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\CMSIS\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\ssd2119" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\gpiointerrupt\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\bsp" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\halconfig" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\inc" -O2 -fno-short-enums -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"hardware/kit/common/drivers/s23lc1024.d" -MT"hardware/kit/common/drivers/s23lc1024.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/kit/common/drivers/udelay.o: ../hardware/kit/common/drivers/udelay.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__NO_SYSTEM_INIT=1' '-DEFR32BG1B232F256GM56=1' -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\halconfig\inc\hal-config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\bootloader\api" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\drivers" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\sleep\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\app\bluetooth_2.6\common\stack_bridge" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\common\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\wdog\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\EFR32BG1_BRD4303A\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\soc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\chip\efr32" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\CMSIS\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\ssd2119" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\gpiointerrupt\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\bsp" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\halconfig" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\inc" -O2 -fno-short-enums -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"hardware/kit/common/drivers/udelay.d" -MT"hardware/kit/common/drivers/udelay.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


