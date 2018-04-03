#if defined(HAL_CONFIG)
#include "bsphalconfig.h"
#include "hal-config.h"
#else
#include "bspconfig.h"
#endif

#include "bsp.h"
#include "i2cspm.h"
#include "pti.h"

#include "app_data.h"
#include "letimer.h"

void InitApp(void){

	configEnablePti();

	#if defined(HAL_VCOM_ENABLE)
		// Enable VCOM if requested
		GPIO_PinModeSet(BSP_VCOM_ENABLE_PORT, BSP_VCOM_ENABLE_PIN, gpioModePushPull, HAL_VCOM_ENABLE);
	#endif // HAL_VCOM_ENABLE

	#if (HAL_I2CSENSOR_ENABLE)
		// Initialize I2C peripheral
		I2CSPM_Init_TypeDef i2cInit = I2CSPM_INIT_DEFAULT;
		I2CSPM_Init(&i2cInit);
	#endif // HAL_I2CSENSOR_ENABLE

	#if defined(HAL_I2CSENSOR_ENABLE)
		// Enable I2C sensor if requested
		GPIO_PinModeSet(BSP_I2CSENSOR_ENABLE_PORT, BSP_I2CSENSOR_ENABLE_PIN, gpioModePushPull, HAL_I2CSENSOR_ENABLE);
	#endif // HAL_I2CSENSOR_ENABLE

	#if defined(HAL_SPIDISPLAY_ENABLE)
		// Enable SPI display if requested
		GPIO_PinModeSet(BSP_SPIDISPLAY_ENABLE_PORT, BSP_SPIDISPLAY_ENABLE_PIN, gpioModePushPull, HAL_SPIDISPLAY_ENABLE);
	#endif // HAL_SPIDISPLAY_ENABLE

	InitLeTimer();
	StartLeTimer();
	InitAppData();
}
