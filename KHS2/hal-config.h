#ifndef HAL_CONFIG_H
#define HAL_CONFIG_H

#include "board_features.h"
#include "hal-config-board.h"

#ifdef BSP_CLK_LFXO_CTUNE
#undef BSP_CLK_LFXO_CTUNE
#endif
#define BSP_CLK_LFXO_CTUNE                            	(32)

#define HAL_EXTSRAM_FREQUENCY                        	(16000000)
#define HAL_I2CSENSOR_FREQUENCY                     	I2C_FREQ_FAST_MAX

#define HAL_PA_ENABLE                                 	(1)
#define HAL_PA_RAMP                                   	(10)
#define HAL_PA_2P4_LOWPOWER                           	(0)
#define HAL_PA_POWER                                  	(252)
#define HAL_PA_CURVE_HEADER                            	"pa_curves_efr32.h"
#ifdef FEATURE_PA_HIGH_POWER
#define HAL_PA_VOLTAGE                                	(3300)
#else // FEATURE_PA_HIGH_POWER
#define HAL_PA_VOLTAGE                                	(1800)
#endif // FEATURE_PA_HIGH_POWER

#define HAL_PTI_ENABLE                                	(1)
#define HAL_PTI_MODE                                  	(HAL_PTI_MODE_UART)
#define HAL_PTI_BAUD_RATE                             	(1600000)

#define HAL_VCOM_ENABLE                   				(0)
#define HAL_SPI_ENABLE		              				(1)
#define HAL_I2C_ENABLE    		          				(1)
#define HAL_WDOG_ENABLE    		          				(0)

#if HAL_I2C_ENABLE
#define BSP_LSM6DSL_INT_1_PIN							(14)
#define BSP_LSM6DSL_INT_2_PIN							(15)
#define BSP_H3LIS331DL_INT_PIN							(16)
#endif

#endif
