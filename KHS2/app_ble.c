// standard library headers
#include <app_timer.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

// BG stack headers
#include "bg_types.h"
#include "gatt_db.h"
#include "native_gecko.h"
#include "infrastructure.h"

// application specific headers
#include "app_hw.h"
#include "payloadbuffer.h"
#include "mstimer.h"
#include "letimer.h"
#include "app_ble.h"

//**************************   DEFINES   **************************************

#define BLE_NO_CONNECTION					0xFF
#define KHS_DATA_CHAR_BYTE_LENGTH_MAX		251

//**************************   STATIC VARIABLES   *****************************

static uint8_t bleClientConnection = BLE_NO_CONNECTION; /* Current connection or 0xFF if invalid */
static uint16_t payloadCounter = 0;

//*************************   STATIC FUNCTION DEFINIITIONS   ******************

//**************************   FUNCTION DEFINIITIONS   ************************

void InitAppBle(void){
	bleClientConnection = BLE_NO_CONNECTION; // Initially no connection is set.
}
void KhsDataCharStatusChange(uint8_t connection, uint16_t clientConfig){
  if (clientConfig) {
	  bleClientConnection = connection; // Save connection ID
	  KhsDataCharUpdate(); // Make initial transfer
  }
}
void KhsDataCharUpdate(void){

	if (BLE_NO_CONNECTION == bleClientConnection){
		return;
	}

	struct gecko_msg_gatt_server_send_characteristic_notification_rsp_t* responseTemp;
	uint8_t tempData[KHS_DATA_CHAR_BYTE_LENGTH_MAX];

	if(IsEmptyPayloadBuffer() == false){
		if(GetPayloadBuffer(tempData, KHS_DATA_CHAR_BYTE_LENGTH_MAX, &payloadCounter)){
			responseTemp = gecko_cmd_gatt_server_send_characteristic_notification(bleClientConnection, gattdb_Data, KHS_DATA_CHAR_BYTE_LENGTH_MAX, tempData);
		}
	}
	else{
		gecko_cmd_hardware_set_soft_timer(TIMER_MS_2_TIMERTICK(KHS_DATA_CHAR_UPDATE_TIMER_PERIOD), KHS_DATA_CHAR_UPDATE_TIMER, true);
	}

	//Using the notification type characteristic and transferring does not prove to be a stable connection
	//Also we do not get any events created for the gecko_evt handler
	/*
	do{
	  //uint64_t dataTemp = GetLeCounter();
	  //uint8_t value[4] = {counter, dataTemp >> 16, dataTemp >> 8, dataTemp};
	  valueTest[counter%KHS_DATA_CHAR_MAX_BYTE_LENGTH] = counter;
	  responseTemp = gecko_cmd_gatt_server_send_characteristic_notification(bleClientConnection, gattdb_LowAccelGyro, KHS_DATA_CHAR_MAX_BYTE_LENGTH, valueTest);
	  tempResult = responseTemp->result;
	  counter++;
	}
	while(responseTemp->result == 0);
	counter--;
	*/
}
void KhsDiagInfoCharWrite(void){
  uint8_t value[3] = {0x00,0x00,0x00};

  if(GetAppHwInitSramErrorFlag()){
	  value[0] = 0x01;
  }
  if(GetAppHwInitLowAccelSensErrorFlag()){
	  value[1] = 0x01;
  }
  if(GetAppHwInitHighAccelSensErrorFlag()){
	  value[2] = 0x01;
  }

  gecko_cmd_gatt_server_write_attribute_value(gattdb_DiagInfo, 0, sizeof(value), (uint8_t *)value);
}


