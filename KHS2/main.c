#include "init_mcu.h"
#include "init_board.h"
#include "init_app.h"
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

	//InitWdog();
	//LockWdog();

	InitMcu();
	InitBoard();	//Init Mcu ports & IO for PCB
	InitApp();		//Init ICs


	/*
	BSP_LedsInit();				// Initialize LEDs

	#ifndef FEATURE_LED_BUTTON_ON_SAME_PIN
		GPIO_PinModeSet(BSP_BUTTON0_PORT, BSP_BUTTON0_PIN, gpioModeInput, 1);	// Configure pin as input
		GPIO_PinModeSet(BSP_BUTTON1_PORT, BSP_BUTTON1_PIN, gpioModeInput, 1);	// Configure pin as input
	#endif
	 */

	gecko_init(&config);		// Initialize stack

	//LeTimer must be before gecko_init()
	InitLeTimer();
	StartLeTimer();

	/* Test Mode
	if (nrf_gpio_pin_read(ENABLE_TEST_PIN)) {
		printUSART0("Entered Test Mode\n", 0);
		while (nrf_gpio_pin_read(ENABLE_TEST_PIN)) {
			if (readCharUSART0() == 0x61) {

				//Test Mag & Accel IC
				initSensors();

				//Test ADC
				uint32_t value = GetAdcValue();
				if (value >= 156 && value <= 163) {
					printUSART0("R7 ADC [OK]\n", 0);
				}
				else {
					//printUSART0("R7 ADC [FAIL][%d]\n", &value);
					printUSART0("R7 ADC [FAIL]\n", 0);
				}
			}
			tickleWDT();
		}
	}
	*/

	while(1){
		struct gecko_cmd_packet* evt;
		evt = gecko_wait_event();	// Check for stack event
		HandleEventsApp(evt);		// Run application and event handler.
		//FeedWdog();
	}
}
