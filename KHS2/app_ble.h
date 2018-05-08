#ifndef APP_BLE_H
#define APP_BLE_H

#ifdef __cplusplus
extern "C" {
#endif

//**************************   FUNCTION DECLARATIONS   ************************

void InitAppBle(void);
void KhsDataCharStatusChange(uint8_t connection, uint16_t clientConfig);
void KhsHighAccelCharStatusChange(uint8_t connection, uint16_t clientConfig);
void KhsDataCharUpdate(void);
void KhsHighAccelCharUpdate(void);

void KhsDiagInfoCharWrite(void);
void KhsFirmVerCharWrite(void);

#ifdef __cplusplus
};
#endif

#endif // APP_BLE_H
