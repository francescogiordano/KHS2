#ifndef __BSP_H
#define __BSP_H

#include <stdbool.h>
#if defined(HAL_CONFIG)
#include "bsphalconfig.h"
#else
#include "bspconfig.h"
#endif
#if defined(BSP_STK) || defined(BSP_WSTK)
#include "em_usart.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define BSP_STATUS_OK                 0     /**< BSP API return code, no errors. */
#define BSP_STATUS_ILLEGAL_PARAM      (-1)  /**< BSP API return code, illegal input parameter. */
#define BSP_STATUS_NOT_IMPLEMENTED    (-2)  /**< BSP API return code, function not implemented (dummy). */
#define BSP_STATUS_UNSUPPORTED_MODE   (-3)  /**< BSP API return code, unsupported BSP mode. */
#define BSP_STATUS_IOEXP_FAILURE      (-4)  /**< BSP API return code, io-expander communication failed */

/* Initialization flag bitmasks for BSP_Init(). */
#define BSP_INIT_DK_SPI     0x01  /**< Mode flag for @ref BSP_Init(), init DK in SPI mode (DK3x50 only). */
#define BSP_INIT_DK_EBI     0x02  /**< Mode flag for @ref BSP_Init(), init DK in EBI mode (DK3x50 only). */
#define BSP_INIT_BCC        0x04  /**< Mode flag for @ref BSP_Init(), init board controller communication. */
#define BSP_INIT_IOEXP      0x08  /**< Mode flag for @ref BSP_Init(), init io-expander on some radio boards */

#if defined(BSP_STK)

/** Peripherals control structure for WSTK's with onboard I/O expander. */
typedef enum {
  BSP_IOEXP_LEDS,     /**< LED control */
  BSP_IOEXP_SENSORS,  /**< Humidity & temperature sensor control */
  BSP_IOEXP_DISPLAY,  /**< Memory LCD control */
  BSP_IOEXP_VCOM,     /**< VCOM (virtual com port) control */
} BSP_Peripheral_TypeDef;

/** @} */
#endif /* BSP_STK */

int             BSP_Disable                 (void);
int             BSP_Init                    (uint32_t flags);

#if defined(BSP_GPIO_EXTLEDARRAY_INIT)
uint32_t        BSP_ExtLedGet               (int ledNo);
void            BSP_ExtLedSet               (int ledNo, uint32_t subLeds);
#endif

int             BSP_PeripheralAccess        (BSP_Peripheral_TypeDef perf, bool enable);

#if defined(BSP_STK) || defined(BSP_WSTK)
/***************************************************************************//**
 * @addtogroup BSP_STK
 * @{
 ******************************************************************************/
int             BSP_BccDeInit               (void);
int             BSP_BccInit                 (void);
bool            BSP_BccPacketReceive        (BCP_Packet *pkt);
int             BSP_BccPacketSend           (BCP_Packet *pkt);
void            BSP_BccPinsEnable           (bool enable);
float           BSP_CurrentGet              (void);
int             BSP_EbiDeInit               (void);
int             BSP_EbiInit                 (void);
float           BSP_VoltageGet              (void);
uint32_t        BSP_IOExpGetDeviceId        (void);

#endif


#ifdef __cplusplus
}
#endif

#endif /* __BSP_H */
