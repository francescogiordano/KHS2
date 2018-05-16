#ifndef PAYLOADBUFFER_H
#define PAYLOADBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

//**************************   DEFINES   **************************************

#define PAYLOAD_BUFFER_SIZE					512
#define PAYLOAD_BUFFER_PAGE_SIZE			256
#define PAYLOAD_BUFFER_HEADER_SIZE			4
#define PAYLOAD_BUFFER_DATA_SIZE			251

#define PAYLOAD_BUFFER_ID_BYTE_1			0
#define PAYLOAD_BUFFER_ID_BYTE_0			1
#define PAYLOAD_BUFFER_COUNT_BYTE_1			2
#define PAYLOAD_BUFFER_COUNT_BYTE_0			3
#define PAYLOAD_BUFFER_DATA_START			4

//**************************   STRUCTS   **************************************

typedef struct {
  uint8_t	IdByte1;
  uint8_t   IdByte0;
  uint8_t   CountByte1;
  uint8_t   CountByte0;
} PAYLOAD_BUFFER_Header_t;

//**************************   FUNCTION DECLARATIONS   ************************

bool PutPayloadBufferData(uint8_t* data, uint8_t dataSize, uint16_t payloadCounter);
bool GetPayloadBufferData(uint8_t* data, uint8_t dataSize, uint16_t* payloadCounter);
bool IsEmptyPayloadBuffer(void);

#ifdef __cplusplus
};
#endif

#endif // PAYLOADBUFFER_H
