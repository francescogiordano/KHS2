// standard library headers
#include <stdint.h>
#include <stdbool.h>

// Own header
#include "s23lc1024.h"
#include "payloadbuffer.h"

#include "retargetswo.h"

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
	bool result = false;

	if(dataSize <= PAYLOAD_BUFFER_DATA_SIZE){
		PAYLOAD_BUFFER_Header_t header = {head >> 8, head,
										payloadCounter >> 8, payloadCounter};

		WritePayload23lc1024(header, data, dataSize);

		incrementHead();

		if(head >= 512){
			RETARGET_WriteString("Error Head", 10);
		}

		//Verify if head has reached tail
		if(head == tail){
			incrementTail();
		}

		result = true;
	}
	return result;
}
bool GetPayloadBuffer(uint8_t* data, uint8_t dataSize, uint16_t* payloadCounter){
	bool result = false;

	//Verify If Buffer Not empty
	if(!IsEmptyPayloadBuffer()){
		PAYLOAD_BUFFER_Header_t header = {tail >> 8, tail, 0x00, 0x00};

		ReadPayload23lc1024(header, data, dataSize);

		if(tail == (header.IdByte1 * 256) + header.IdByte0){

			*payloadCounter = (header.CountByte1 * 256) + header.CountByte0;
			incrementTail();

			result = true;
		}
		else{
			RETARGET_WriteString("Error Tail", 10);
		}
	}
	else{
		RETARGET_WriteString("Error Empty", 11);
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


