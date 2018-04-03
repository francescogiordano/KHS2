// standard library headers
#include <stdint.h>
#include <stdbool.h>

// Own header
#include "s23lc1024.h"
#include "payloadbuffer.h"

static uint16_t head = 0;
static uint16_t tail = 0;

//**************************   STATIC FUNCTION DEFINITIONS   ******************

static void incrementHead(void){
	head = (head + 1) % PAYLOAD_BUFFER_SIZE;
}
static void incrementTail(void){
	tail = (tail + 1) % PAYLOAD_BUFFER_SIZE;
}

//**************************   FUNCTION DEFINITIONS   *************************

bool PutPayloadBuffer(uint8_t* data, uint8_t dataSize, uint16_t payloadCounter){
	bool result = true;

	PAYLOAD_BUFFER_Header_t header = {
		(head >> 8) 			& 0xFF,
		(head) 					& 0xFF,
		(payloadCounter >> 8)	& 0xFF,
		(payloadCounter) 		& 0xFF
	};

	//WriteSram(address = head*PAYLOAD_BUFFER_PAGE_SIZE, header, PAYLOAD_BUFFER_HEADER_SIZE);
	//WriteSram(address = head*PAYLOAD_BUFFER_PAGE_SIZE + PAYLOAD_BUFFER_HEADER_SIZE, data, dataSize);

	incrementHead();

	//Verify if head has reached tail
	if(head == tail){
		incrementTail();
	}

	return result;
}
bool GetPayloadBuffer(uint8_t* data, uint8_t dataSize, uint16_t* payloadCounter){
	bool result = false;

	//Verify If Buffer Not empty
	if(!IsEmptyPayloadBuffer()){
		PAYLOAD_BUFFER_Header_t header;

		//ReadSram(address = tail*PAYLOAD_BUFFER_PAGE_SIZE, header, PAYLOAD_BUFFER_HEADER_SIZE);

		if(tail == (header.IdByte1 * 0xFF) + header.IdByte0){
			//ReadSram(address = tail*PAYLOAD_BUFFER_PAGE_SIZE + PAYLOAD_BUFFER_HEADER_SIZE, data, dataSize);

			*payloadCounter = (header.CountByte1 * 0xFF) + header.CountByte0;
			result = true;
			incrementTail();
		}
	}
	return result;
}

bool IsEmptyPayloadBuffer(void){
	bool result = false;

	if(tail == head){
		result = true;
	}

	return result;
}


