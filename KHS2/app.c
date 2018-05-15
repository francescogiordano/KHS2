#include <app_timer.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

// BG stack headers
#include "bg_types.h"
#include "native_gecko.h"
#include "gatt_db.h"

// em library
#include "em_system.h"

// application specific headers
#include "app.h"
#include "app_data.h"
#include "app_ble.h"
#include "app_hw.h"
#include "advertisement.h"
#include "board_features.h"

#include "app_extsignals.h"

//**************************   STATIC FUNCTION DECLARATIONS   *****************

void InitApp(void){

	/*	Silabs - Update Unique Device ID

	// Unique device ID
	uint16_t devId;
	struct gecko_msg_system_get_bt_address_rsp_t* btAddr;
	char devName[APP_DEVNAME_LEN + 1];

	// Init device name
	// Get the unique device ID
	// Create the device name based on the 16-bit device ID

	btAddr = gecko_cmd_system_get_bt_address();
	devId = *((uint16*)(btAddr->address.addr));
	//snprintf(devName, APP_DEVNAME_LEN + 1, APP_DEVNAME, devId);
	//gecko_cmd_gatt_server_write_attribute_value(gattdb_device_name, 0, strlen(devName), (uint8_t *)devName);
	*/

	InitAppHw();
	InitAppData();
	InitAppBle();
}
void HandleEventsApp(struct gecko_cmd_packet *evt){

  // Flag for indicating DFU Reset must be performed
  static uint8_t boot_to_dfu = 0;

  switch (BGLIB_MSG_ID(evt->header)) {

	case gecko_evt_system_external_signal_id:
		switch(evt->data.evt_system_external_signal.extsignals){
			case APP_DATA_1_MS_TIMER:
				HighAccelGyroAppDataProcessRead();

				if(GetLeCounter()%5 == 0){
					LowAccelGyroAppDataProcessRead();
				}
				break;

			case APP_DATA_LOW_ACCEL_GYRO:
				LowAccelGyroAppDataProcessRead();
				break;

			case APP_DATA_HIGH_ACCEL:
				HighAccelGyroAppDataProcessRead();
				break;

			default:
				break;
		}
		break;

    /* Boot event and connection closed event */
    case gecko_evt_system_boot_id:
    case gecko_evt_le_connection_closed_id:

		//InitApp();
		advSetup();

		/* Enter to DFU OTA mode if needed */
		if (boot_to_dfu) {
		gecko_cmd_system_reset(2);	//API reference manual says to boot to DFU value should be 1
		}

		//Potentially Shutdown the MCU/Sensors if there is no ble connection
		//gecko_cmd_hardware_set_soft_timer(TIMER_MS_2_TIMERTICK(SHUTDOWN_TIMER_PERIOD), SHUTDOWN_TIMER, true);

		break;

    /* Connection opened event */
    case gecko_evt_le_connection_opened_id:

    	gecko_cmd_le_connection_set_parameters(evt->data.evt_le_connection_opened.connection, 0x0006, 0x000C, 0x0000, 0x00C8); //(min = 6*1.25ms, max = 12*1.25ms, latency = 0, timeout = 200*10ms
    	/* Call advertisement.c connection started callback */
    	advConnectionStarted();
    	break;

    /* Value of attribute changed from the local database by remote GATT client */
    case gecko_evt_gatt_server_attribute_value_id:
		// Check if changed characteristic is the Immediate Alert level

		/*
		if ( gattdb_alert_level == evt->data.evt_gatt_server_attribute_value.attribute) {
		// Write the Immediate Alert level value
		iaImmediateAlertWrite(&evt->data.evt_gatt_server_attribute_value.value);
		}
		*/
		break;

    // Indicates the changed value of CCC or received characteristic confirmation
	case gecko_evt_gatt_server_characteristic_status_id:
		// Check if changed client char config is for the temperature measurement
		if((gattdb_Data == evt->data.evt_gatt_server_attribute_value.attribute)
		  && (evt->data.evt_gatt_server_characteristic_status.status_flags == gatt_server_client_config)) {
		// Call LowAccelGyro characteristic status changed callback
		KhsDataCharStatusChange(
			evt->data.evt_gatt_server_characteristic_status.connection,
			evt->data.evt_gatt_server_characteristic_status.client_config_flags);
		}
		else if((gattdb_Data == evt->data.evt_gatt_server_attribute_value.attribute) &&
			  (evt->data.evt_gatt_server_characteristic_status.status_flags == gatt_server_confirmation)){
			KhsDataCharUpdate();
		}
		break;

    // Software Timer event
    case gecko_evt_hardware_soft_timer_id:
		/* Check which software timer handle is in question */
		switch (evt->data.evt_hardware_soft_timer.handle) {
			case ADV_TIMER: /* Advertisement Timer */
				advSetup();
				break;
			case HW_TIMER:
				//AppHwTick();
				break;
			case KHS_DATA_CHAR_UPDATE_TIMER:
				KhsDataCharUpdate();
				break;
			case SHUTDOWN_TIMER:
				//Place MCU & Sensors shutdown code
				break;
			default:
			  break;
		}
		break;

    /* User write request event. Checks if the user-type OTA Control Characteristic was written.
     * If written, boots the device into Device Firmware Upgrade (DFU) mode. */
    case gecko_evt_gatt_server_user_write_request_id:
		/* Handle OTA */
		if (evt->data.evt_gatt_server_user_write_request.characteristic == gattdb_ota_control) {
			/* Set flag to enter to OTA mode */
			boot_to_dfu = 1;

			/* Send response to Write Request */
			gecko_cmd_gatt_server_send_user_write_response(
			  evt->data.evt_gatt_server_user_write_request.connection,
			  gattdb_ota_control,
			  bg_err_success);

			/* Close connection to enter to DFU OTA mode */
			gecko_cmd_endpoint_close(evt->data.evt_gatt_server_user_write_request.connection);
		}
		break;

    case gecko_evt_gatt_server_user_read_request_id:
		if (evt->data.evt_gatt_server_user_read_request.characteristic == gattdb_DiagInfo) {

			KhsDiagInfoCharWrite();

			/*
			gecko_cmd_gatt_server_send_user_read_response(
				evt->data.evt_gatt_server_user_read_request.connection,
				evt->data.evt_gatt_server_user_read_request.characteristic,
				0x00,	//Success Code
				5,		//Length
				gecko_cmd_gatt_server_read_attribute_value(gattdb_DiagInfo,0)->value);
			*/
		}
		break;

    default:
      break;
  }
}
