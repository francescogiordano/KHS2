#include "boards.h"
#include "ble-configuration.h"
#include "board_features.h"

/* BG stack headers */
#include "bg_types.h"
#include "native_gecko.h"
#include "gatt_db.h"
#include "aat.h"

/* application specific files */
#include "app.h"

/* libraries containing default gecko configuration values */
#include "em_emu.h"
#include "em_cmu.h"

/* Device initialization header */
#include "hal-config.h"

#if defined(HAL_CONFIG)
#include "bsphalconfig.h"
#else
#include "bspconfig.h"
#endif

#include "bsp.h"

#include "wdog.h"
#include "letimer.h"
#include "udelay.h"

#include "retargetswo.h"
#include "payloadbuffer.h"

#include "adc.h"
#include "app_hw.h"
#include "app_data.h"

#ifndef MAX_CONNECTIONS
#define MAX_CONNECTIONS 4
#endif
uint8_t bluetooth_stack_heap[DEFAULT_BLUETOOTH_HEAP(MAX_CONNECTIONS)];

// Gecko configuration parameters (see gecko_configuration.h)
static const gecko_configuration_t config = {
  .config_flags = 0,
  .sleep.flags = SLEEP_FLAGS_DEEP_SLEEP_ENABLE,
  .bluetooth.max_connections = MAX_CONNECTIONS,
  .bluetooth.heap = bluetooth_stack_heap,
  .bluetooth.heap_size = sizeof(bluetooth_stack_heap),
  .bluetooth.sleep_clock_accuracy = 100, // ppm
  .gattdb = &bg_gattdb_data,
  .ota.flags = 0,
  .ota.device_name_len = 3,
  .ota.device_name_ptr = "OTA",
#if (HAL_PA_ENABLE) && defined(FEATURE_PA_HIGH_POWER)
  .pa.config_enable = 1, // Enable high power PA
  .pa.input = GECKO_RADIO_PA_INPUT_VBAT, // Configure PA input to VBAT
#endif // (HAL_PA_ENABLE) && defined(FEATURE_PA_HIGH_POWER)
};

void main(void){

#if	HAL_WDOG_ENABLE
	InitWdog();
	LockWdog();
#endif

#if DEBUG_ENABLE
	RETARGET_SwoInit();
	//RETARGET_WriteString("Main Enter", 10);
#endif

	InitMcu();
	InitBoard();	//Init Mcu ports & IO for PCB
	InitApp();		//Init ICs


	//gecko_init(&config);		// Initialize stack

	//LeTimer must be after gecko_init()
	InitLeTimer();
	StartLeTimer();

	//Enter Test Mode
	if(GPIO_PinInGet(BSP_TEST_ENABLE_PORT, BSP_TEST_ENABLE_PIN)){
		RETARGET_SwoInit();
		RETARGET_WriteString("Test Mode", 9);

		//while(GPIO_PinInGet(BSP_TEST_ENABLE_PORT, BSP_TEST_ENABLE_PIN)) {
			//if(readCharUSART0() == 0x61){
				//Get Sensor Error Flags
				uint8_t errorFlags = GetAppHwErrorFlags();

				if((errorFlags & ERROR_FLAG_SRAM) == ERROR_FLAG_SRAM){
					RETARGET_WriteString("U3: ERROR", 9);
				}
				else{
					RETARGET_WriteString("U3: OK", 6);
				}
				if((errorFlags & ERROR_FLAG_LOW_GYRO_ACCEL) == ERROR_FLAG_LOW_GYRO_ACCEL){
					RETARGET_WriteString("U4: ERROR", 9);
				}
				else{
					RETARGET_WriteString("U4: OK", 6);
				}
				if((errorFlags & ERROR_FLAG_HIGH_ACCEL) == ERROR_FLAG_HIGH_ACCEL){
					RETARGET_WriteString("U6: ERROR", 9);
				}
				else{
					RETARGET_WriteString("U6: OK", 6);
				}

			//}
		#if	HAL_WDOG_ENABLE
			FeedWdog();
		#endif
		//}

		//When Test Mode Complete Reboot device
		gecko_cmd_system_reset(0);	//0:Normal Reset,1:DFU Reset
		RETARGET_WriteString("Reset", 5);
	}

	while(1){

		//LowAccelGyroAppDataProcessRead();
		//HighAccelGyroAppDataProcessRead();

		//EMU_EnterEM2(true);
		/**/
		struct gecko_cmd_packet* evt;
		evt = gecko_wait_event();	// Check for stack event
		HandleEventsApp(evt);		// Run application and event handler.
		 /**/

	#if	HAL_WDOG_ENABLE
		FeedWdog();
	#endif
	}
}
