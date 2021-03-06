/***********************************************************************************************//**
 * \file   advertisement.c
 * \brief  Functions and data related to advertisement
 ***************************************************************************************************
 * <b> (C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
 ***************************************************************************************************
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 **************************************************************************************************/

#include "boards.h"
#include "ble-configuration.h"
#include "board_features.h"

#ifndef FEATURE_BOARD_DETECTED
#error This sample app only works with a Silicon Labs Board
#endif

#include <stdint.h>
#include <string.h>
#include <stdio.h>

/* BG stack headers */
#include "bg_types.h"
#include "native_gecko.h"
#include "infrastructure.h"

/* Own header */
#include "advertisement.h"


/***************************************************************************************************
   Local Variables
 **************************************************************************************************/

static bool advConnectableMode = true;
static bool advIsConnected = false;

/***************************************************************************************************
   Function Definitions
 **************************************************************************************************/
void advSetup(void){

  if (advConnectableMode == true) {
    /* start advertising */
    gecko_cmd_le_gap_set_mode(le_gap_general_discoverable, le_gap_undirected_connectable);
  }
  advIsConnected = false;
}

void advSwitchAdvMessage(void)
{
  if (!advIsConnected) {
    /* switch mode from beaconing to connectable adv. and vica versa */
    advConnectableMode = (advConnectableMode == true) ? false : true;

    /* stop advertisement*/
    gecko_cmd_le_gap_set_mode(le_gap_non_connectable, le_gap_non_discoverable);
  }
  advSetup();
}

void advConnectionStarted(void){

  advIsConnected = true;
}
