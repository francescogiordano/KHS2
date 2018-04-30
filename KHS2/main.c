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

	RETARGET_SwoInit();
	//RETARGET_WriteString("Main Enter", 10);

	InitMcu();
	InitBoard();	//Init Mcu ports & IO for PCB
	InitApp();		//Init ICs

	/*
	BSP_LedsInit();				// Initialize LEDs

	#ifndef FEATURE_LED_BUTTON_ON_SAME_PIN
		GPIO_PinModeSet(BSP_BUTTON0_PORT, BSP_BUTTON0_PIN, gpioModeInput, 1);	// Configure pin as input
		GPIO_PinModeSet(BSP_BUTTON1_PORT, BSP_BUTTON1_PIN, gpioModeInput, 1);	// Configure pin as input
	#endif
	/**/

	//gecko_init(&config);		// Initialize stack

	//LeTimer must be after gecko_init()
	//InitLeTimer();
	//StartLeTimer();

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


	int dataSize = 251;

	uint8 writeAddress[] = {0x00, 0x00, 0x00};
	uint8 readAddress[] = {0x00, 0x00, 0x05};
	uint8 data[dataSize];
	uint8 read[dataSize];

	uint16_t* tempPayloadCounter;
	PAYLOAD_BUFFER_Header_t header;


	for(int i=0; i<1000; i++){

		for(int j=0; j<dataSize;j++){
			data[j] = i;
		}
		PutPayloadBuffer(data, dataSize, i);
	}

	for(int i=0; i<512; i++){
		if(GetPayloadBuffer(read, dataSize, tempPayloadCounter)){
			/*
			for(int j=0; j<dataSize; j++){
				if(read[j] > 0x20 && read[j] < 0x7B){
					RETARGET_WriteChar(read[j]);
				}
				else{
					RETARGET_WriteChar('!');
				}
			}
		    RETARGET_WriteChar('\n');
		    */
		}
	}

	for(int i=0; i<10; i++){
		PutPayloadBuffer(data, dataSize, i);
	}

	for(int i=0; i<15; i++){
		GetPayloadBuffer(read, dataSize, tempPayloadCounter);
	}

	while(1){

		struct gecko_cmd_packet* evt;
		evt = gecko_wait_event();	// Check for stack event
		HandleEventsApp(evt);		// Run application and event handler.

	#if	HAL_WDOG_ENABLE
		FeedWdog();
	#endif
	}
}
