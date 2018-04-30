#if defined(HAL_CONFIG)
#include "bsphalconfig.h"
#include "hal-config.h"
#else
#include "bspconfig.h"
#endif

#include "board_features.h"

#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"

#include "bsp.h"
#include "mcu.h"
#include "i2cspm.h"

#include "s23lc1024.h"
#include "lsm6dsl.h"
#include "h3lis331dl.h"

#include "udelay.h"

//**************************   STATIC FUNCTION DEFINIITIONS   *****************

static void initMcu_clocks(void)
{
/*
  // Initialize HFXO
  CMU_HFXOInit_TypeDef hfxoInit = BSP_CLK_HFXO_INIT;
#if defined(BSP_CLK_HFXO_CTUNE) && BSP_CLK_HFXO_CTUNE > -1
  hfxoInit.ctuneStartup = BSP_CLK_HFXO_CTUNE;
  hfxoInit.ctuneSteadyState = BSP_CLK_HFXO_CTUNE;
#endif

  CMU_HFXOInit(&hfxoInit);

  // Set system HFXO frequency
  SystemHFXOClockSet(BSP_CLK_HFXO_FREQ);

  // Enable HFXO oscillator, and wait for it to be stable
  CMU_OscillatorEnable(cmuOsc_HFXO, true, true);

  // Automatically start and select HFXO
  CMU_HFXOAutostartEnable(0, true, true);

  // HFRCO not needed when using HFXO
  CMU_OscillatorEnable(cmuOsc_HFRCO, false, false);


  // Enabling HFBUSCLKLE clock for LE peripherals
  CMU_ClockEnable(cmuClock_HFLE, true);

  // Initialize LFXO
  CMU_LFXOInit_TypeDef lfxoInit = BSP_CLK_LFXO_INIT;
  lfxoInit.ctune = BSP_CLK_LFXO_CTUNE;
  CMU_LFXOInit(&lfxoInit);

  // Set system LFXO frequency
  SystemLFXOClockSet(BSP_CLK_LFXO_FREQ);

  // Set LFXO if selected as LFCLK
  CMU_ClockEnable(cmuClock_CORELE, true);

  // Set LFXO if selected as LFCLK
  CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFXO);
  CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO);
  CMU_ClockSelectSet(cmuClock_LFE, cmuSelect_LFXO);

/**/
/*
	CMU_OscillatorEnable(cmuOsc_HFRCO, true, true);

	CMU_ClockSelectSet(cmuClock_CORE, cmuSelect_HFCLKLE);
	CMU_ClockEnable(cmuClock_CORE, true);

	CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFCLKLE);
	CMU_ClockSelectSet(cmuClock_HFPER, cmuSelect_HFCLKLE);
/**/

		CMU_HFRCOBandSet(CMU_HFRCO_MAX);

	  // Enabling HFBUSCLKLE clock for LE peripherals
	  CMU_ClockEnable(cmuClock_HFLE, true);


	CMU_ClockEnable(cmuClock_CORELE, true);
	CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFRCO);
	CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFRCO);
	CMU_ClockSelectSet(cmuClock_LFE, cmuSelect_LFRCO);

/**/
}
static void initMcu_ports(void){

	#if HAL_VCOM_ENABLE
	  // Enable VCOM if requested
	  GPIO_PinModeSet(BSP_VCOM_ENABLE_PORT, BSP_VCOM_ENABLE_PIN, gpioModePushPull, HAL_VCOM_ENABLE);
	#endif // HAL_VCOM_ENABLE


	#if HAL_SPIDISPLAY_ENABLE
	  // Enable SPI display if requested
	  GPIO_PinModeSet(BSP_SPIDISPLAY_ENABLE_PORT, BSP_SPIDISPLAY_ENABLE_PIN, gpioModePushPull, HAL_SPIDISPLAY_ENABLE);
	#endif // HAL_SPIDISPLAY_ENABLE
}

//**************************   FUNCTION DEFINIITIONS   *****************

void InitMcu(void){

  // Device errata
  CHIP_Init();

  // Set up DC-DC converter
  EMU_DCDCInit_TypeDef dcdcInit = BSP_DCDC_INIT;
  #if HAL_DCDC_BYPASS
  dcdcInit.dcdcMode = emuDcdcMode_Bypass;
  #endif
  EMU_DCDCInit(&dcdcInit);

  // Set up clocks
  initMcu_clocks();

#if defined(_EMU_CMD_EM01VSCALE0_MASK)
  // Set up EM0, EM1 energy mode configuration
  EMU_EM01Init_TypeDef em01Init = EMU_EM01INIT_DEFAULT;
  EMU_EM01Init(&em01Init);
#endif // _EMU_CMD_EM01VSCALE0_MASK

#if defined(_EMU_CTRL_EM23VSCALE_MASK)
  // Set up EM2, EM3 energy mode configuration
  EMU_EM23Init_TypeDef em23init = EMU_EM23INIT_DEFAULT;
  em23init.vScaleEM23Voltage = emuVScaleEM23_LowPower;
  EMU_EM23Init(&em23init);
#endif //_EMU_CTRL_EM23VSCALE_MASK

  initMcu_ports();

}

