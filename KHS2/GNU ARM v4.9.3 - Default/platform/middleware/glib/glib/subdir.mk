################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/middleware/glib/glib/bmp.c \
../platform/middleware/glib/glib/glib.c \
../platform/middleware/glib/glib/glib_bitmap.c \
../platform/middleware/glib/glib/glib_circle.c \
../platform/middleware/glib/glib/glib_font_narrow_6x8.c \
../platform/middleware/glib/glib/glib_font_normal_8x8.c \
../platform/middleware/glib/glib/glib_font_number_16x20.c \
../platform/middleware/glib/glib/glib_line.c \
../platform/middleware/glib/glib/glib_polygon.c \
../platform/middleware/glib/glib/glib_rectangle.c \
../platform/middleware/glib/glib/glib_string.c 

OBJS += \
./platform/middleware/glib/glib/bmp.o \
./platform/middleware/glib/glib/glib.o \
./platform/middleware/glib/glib/glib_bitmap.o \
./platform/middleware/glib/glib/glib_circle.o \
./platform/middleware/glib/glib/glib_font_narrow_6x8.o \
./platform/middleware/glib/glib/glib_font_normal_8x8.o \
./platform/middleware/glib/glib/glib_font_number_16x20.o \
./platform/middleware/glib/glib/glib_line.o \
./platform/middleware/glib/glib/glib_polygon.o \
./platform/middleware/glib/glib/glib_rectangle.o \
./platform/middleware/glib/glib/glib_string.o 

C_DEPS += \
./platform/middleware/glib/glib/bmp.d \
./platform/middleware/glib/glib/glib.d \
./platform/middleware/glib/glib/glib_bitmap.d \
./platform/middleware/glib/glib/glib_circle.d \
./platform/middleware/glib/glib/glib_font_narrow_6x8.d \
./platform/middleware/glib/glib/glib_font_normal_8x8.d \
./platform/middleware/glib/glib/glib_font_number_16x20.d \
./platform/middleware/glib/glib/glib_line.d \
./platform/middleware/glib/glib/glib_polygon.d \
./platform/middleware/glib/glib/glib_rectangle.d \
./platform/middleware/glib/glib/glib_string.d 


# Each subdirectory must supply rules for building sources it contributes
platform/middleware/glib/glib/bmp.o: ../platform/middleware/glib/glib/bmp.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__NO_SYSTEM_INIT=1' '-DEFR32BG1B232F256GM56=1' -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\CMSIS\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\bsp" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\app\bluetooth_2.6\common\stack_bridge" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\bootloader\api" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\drivers" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\display" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\ssd2119" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\soc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\EFR32BG1_BRD4303A\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\halconfig" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\chip\efr32" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\common\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\sleep\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\halconfig\inc\hal-config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\gpiointerrupt\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\wdog\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\inc" -O2 -fno-short-enums -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"platform/middleware/glib/glib/bmp.d" -MT"platform/middleware/glib/glib/bmp.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/middleware/glib/glib/glib.o: ../platform/middleware/glib/glib/glib.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__NO_SYSTEM_INIT=1' '-DEFR32BG1B232F256GM56=1' -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\CMSIS\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\bsp" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\app\bluetooth_2.6\common\stack_bridge" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\bootloader\api" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\drivers" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\display" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\ssd2119" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\soc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\EFR32BG1_BRD4303A\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\halconfig" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\chip\efr32" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\common\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\sleep\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\halconfig\inc\hal-config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\gpiointerrupt\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\wdog\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\inc" -O2 -fno-short-enums -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"platform/middleware/glib/glib/glib.d" -MT"platform/middleware/glib/glib/glib.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/middleware/glib/glib/glib_bitmap.o: ../platform/middleware/glib/glib/glib_bitmap.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__NO_SYSTEM_INIT=1' '-DEFR32BG1B232F256GM56=1' -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\CMSIS\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\bsp" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\app\bluetooth_2.6\common\stack_bridge" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\bootloader\api" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\drivers" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\display" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\ssd2119" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\soc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\EFR32BG1_BRD4303A\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\halconfig" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\chip\efr32" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\common\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\sleep\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\halconfig\inc\hal-config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\gpiointerrupt\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\wdog\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\inc" -O2 -fno-short-enums -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"platform/middleware/glib/glib/glib_bitmap.d" -MT"platform/middleware/glib/glib/glib_bitmap.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/middleware/glib/glib/glib_circle.o: ../platform/middleware/glib/glib/glib_circle.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__NO_SYSTEM_INIT=1' '-DEFR32BG1B232F256GM56=1' -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\CMSIS\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\bsp" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\app\bluetooth_2.6\common\stack_bridge" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\bootloader\api" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\drivers" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\display" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\ssd2119" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\soc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\EFR32BG1_BRD4303A\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\halconfig" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\chip\efr32" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\common\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\sleep\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\halconfig\inc\hal-config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\gpiointerrupt\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\wdog\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\inc" -O2 -fno-short-enums -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"platform/middleware/glib/glib/glib_circle.d" -MT"platform/middleware/glib/glib/glib_circle.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/middleware/glib/glib/glib_font_narrow_6x8.o: ../platform/middleware/glib/glib/glib_font_narrow_6x8.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__NO_SYSTEM_INIT=1' '-DEFR32BG1B232F256GM56=1' -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\CMSIS\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\bsp" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\app\bluetooth_2.6\common\stack_bridge" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\bootloader\api" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\drivers" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\display" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\ssd2119" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\soc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\EFR32BG1_BRD4303A\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\halconfig" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\chip\efr32" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\common\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\sleep\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\halconfig\inc\hal-config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\gpiointerrupt\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\wdog\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\inc" -O2 -fno-short-enums -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"platform/middleware/glib/glib/glib_font_narrow_6x8.d" -MT"platform/middleware/glib/glib/glib_font_narrow_6x8.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/middleware/glib/glib/glib_font_normal_8x8.o: ../platform/middleware/glib/glib/glib_font_normal_8x8.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__NO_SYSTEM_INIT=1' '-DEFR32BG1B232F256GM56=1' -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\CMSIS\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\bsp" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\app\bluetooth_2.6\common\stack_bridge" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\bootloader\api" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\drivers" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\display" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\ssd2119" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\soc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\EFR32BG1_BRD4303A\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\halconfig" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\chip\efr32" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\common\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\sleep\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\halconfig\inc\hal-config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\gpiointerrupt\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\wdog\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\inc" -O2 -fno-short-enums -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"platform/middleware/glib/glib/glib_font_normal_8x8.d" -MT"platform/middleware/glib/glib/glib_font_normal_8x8.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/middleware/glib/glib/glib_font_number_16x20.o: ../platform/middleware/glib/glib/glib_font_number_16x20.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__NO_SYSTEM_INIT=1' '-DEFR32BG1B232F256GM56=1' -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\CMSIS\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\bsp" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\app\bluetooth_2.6\common\stack_bridge" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\bootloader\api" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\drivers" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\display" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\ssd2119" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\soc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\EFR32BG1_BRD4303A\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\halconfig" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\chip\efr32" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\common\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\sleep\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\halconfig\inc\hal-config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\gpiointerrupt\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\wdog\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\inc" -O2 -fno-short-enums -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"platform/middleware/glib/glib/glib_font_number_16x20.d" -MT"platform/middleware/glib/glib/glib_font_number_16x20.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/middleware/glib/glib/glib_line.o: ../platform/middleware/glib/glib/glib_line.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__NO_SYSTEM_INIT=1' '-DEFR32BG1B232F256GM56=1' -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\CMSIS\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\bsp" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\app\bluetooth_2.6\common\stack_bridge" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\bootloader\api" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\drivers" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\display" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\ssd2119" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\soc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\EFR32BG1_BRD4303A\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\halconfig" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\chip\efr32" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\common\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\sleep\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\halconfig\inc\hal-config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\gpiointerrupt\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\wdog\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\inc" -O2 -fno-short-enums -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"platform/middleware/glib/glib/glib_line.d" -MT"platform/middleware/glib/glib/glib_line.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/middleware/glib/glib/glib_polygon.o: ../platform/middleware/glib/glib/glib_polygon.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__NO_SYSTEM_INIT=1' '-DEFR32BG1B232F256GM56=1' -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\CMSIS\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\bsp" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\app\bluetooth_2.6\common\stack_bridge" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\bootloader\api" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\drivers" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\display" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\ssd2119" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\soc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\EFR32BG1_BRD4303A\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\halconfig" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\chip\efr32" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\common\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\sleep\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\halconfig\inc\hal-config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\gpiointerrupt\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\wdog\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\inc" -O2 -fno-short-enums -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"platform/middleware/glib/glib/glib_polygon.d" -MT"platform/middleware/glib/glib/glib_polygon.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/middleware/glib/glib/glib_rectangle.o: ../platform/middleware/glib/glib/glib_rectangle.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__NO_SYSTEM_INIT=1' '-DEFR32BG1B232F256GM56=1' -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\CMSIS\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\bsp" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\app\bluetooth_2.6\common\stack_bridge" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\bootloader\api" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\drivers" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\display" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\ssd2119" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\soc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\EFR32BG1_BRD4303A\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\halconfig" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\chip\efr32" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\common\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\sleep\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\halconfig\inc\hal-config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\gpiointerrupt\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\wdog\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\inc" -O2 -fno-short-enums -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"platform/middleware/glib/glib/glib_rectangle.d" -MT"platform/middleware/glib/glib/glib_rectangle.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

platform/middleware/glib/glib/glib_string.o: ../platform/middleware/glib/glib/glib_string.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__NO_SYSTEM_INIT=1' '-DEFR32BG1B232F256GM56=1' -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\CMSIS\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\bsp" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\app\bluetooth_2.6\common\stack_bridge" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emlib\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Include" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\bootloader\api" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\drivers" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\display" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd\ssd2119" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\soc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\EFR32BG1_BRD4303A\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\hardware\kit\common\halconfig" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\radio\rail_lib\chip\efr32" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\common\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\protocol\bluetooth_2.6\ble_stack\inc\common" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\sleep\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\halconfig\inc\hal-config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\middleware\glib\dmd" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\dmadrv\src" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\gpiointerrupt\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\Device\SiliconLabs\EFR32BG1B\Source\GCC" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\uartdrv\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\wdog\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\letimer\inc" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\config" -I"G:\My Drive\R&D\Firmware Design\KHS2\KHS2\platform\emdrv\mstimer\inc" -O2 -fno-short-enums -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=hard -MMD -MP -MF"platform/middleware/glib/glib/glib_string.d" -MT"platform/middleware/glib/glib/glib_string.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


