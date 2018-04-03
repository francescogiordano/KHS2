#ifndef APP_HW_H
#define APP_HW_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

/***********************************************************************************************//**
 *  \brief  Initialize buttons and Temperature sensor.
 **************************************************************************************************/
void InitAppHw(void);
void appHwTick(void);

/***********************************************************************************************//**
 *  \brief  Perform a temperature measurement.  Return the measurement data.
 *  \param[out]  tempData  Result of temperature conversion.
 *  \return  0 if Temp Read successful, otherwise -1
 **************************************************************************************************/
int32_t appHwReadTm(int32_t* tempData);

/***********************************************************************************************//**
 *  \brief  Initialise temperature measurement.
 *  \return  true if a Si7013 is detected, false otherwise
 **************************************************************************************************/

bool GetAppHwErrorFlag(void);
#ifdef __cplusplus
};
#endif

#endif /* APP_HW_H */
