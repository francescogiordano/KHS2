#ifndef HALCONFIG_23LC1024_H
#define HALCONFIG_23LC1024_H

#include "hal-config.h"

#if BSP_EXTSRAM_USART == HAL_SPI_PORT_USART0
// USART0
  #define SRAM23LC_USART                USART0
  #define SRAM23LC_USART_CLK            cmuClock_USART0
#elif BSP_EXTSRAM_USART == HAL_SPI_PORT_USART1
// USART1
  #define SRAM23LC_USART                USART1
  #define SRAM23LC_USART_CLK            cmuClock_USART1
#elif BSP_EXTSRAM_USART == HAL_SPI_PORT_USART2
// USART2
  #define SRAM23LC_USART                USART2
  #define SRAM23LC_USART_CLK            cmuClock_USART2
#elif BSP_EXTSRAM_USART == HAL_SPI_PORT_USART3
// USART3
  #define SRAM23LC_USART                USART3
  #define SRAM23LC_USART_CLK            cmuClock_USART3
#elif BSP_EXTSRAM_USART == HAL_SPI_PORT_USART4
// USART4
  #define SRAM23LC_USART                USART4
  #define SRAM23LC_USART_CLK            cmuClock_USART4
#elif BSP_EXTSRAM_USART == HAL_SPI_PORT_USART5
// USART5
  #define SRAM23LC_USART                USART5
  #define SRAM23LC_USART_CLK            cmuClock_USART5
#else
  #error "SPI flash config: Unknown USART selection"
#endif

#define SRAM23LC_PORT_MOSI          BSP_EXTSRAM_MOSI_PORT
#define SRAM23LC_PIN_MOSI           BSP_EXTSRAM_MOSI_PIN
#define SRAM23LC_LOC_TX             BSP_EXTSRAM_MOSI_LOC

#define SRAM23LC_PORT_MISO          BSP_EXTSRAM_MISO_PORT
#define SRAM23LC_PIN_MISO           BSP_EXTSRAM_MISO_PIN
#define SRAM23LC_LOC_RX             BSP_EXTSRAM_MISO_LOC

#define SRAM23LC_PORT_SCLK          BSP_EXTSRAM_CLK_PORT
#define SRAM23LC_PIN_SCLK           BSP_EXTSRAM_CLK_PIN
#define SRAM23LC_LOC_SCLK           BSP_EXTSRAM_CLK_LOC

#define SRAM23LC_PORT_CS            BSP_EXTSRAM_CS_PORT
#define SRAM23LC_PIN_CS             BSP_EXTSRAM_CS_PIN
#define SRAM23LC_LOC_CS             BSP_EXTSRAM_CS_LOC


#define SRAM23LC_BAUDRATE           HAL_EXTSRAM_FREQUENCY

#endif // HALCONFIG_23LC1024_H
