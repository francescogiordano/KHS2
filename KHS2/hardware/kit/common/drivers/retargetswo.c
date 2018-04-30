#include "retargetswo.h"

#include "em_cmu.h"
#include "bsp_trace.h"

/**
 * @brief
 *   Output a single character on SWO.
 *
 * @detail
 *   This function will output a character on SWO using ITM channel 0.
 */
int RETARGET_WriteChar(char c)
{
  return ITM_SendChar(c);
}

void RETARGET_WriteString(char* s, int length)
{
	for(int i=0; i<length; i++){
		ITM_SendChar(s[i]);
	}
	ITM_SendChar('\n');
}

/**
 * @brief
 *   This function returns 0 always
 *
 * @details
 *   SWO is a one-way link, it is not possible to read data from SWO.
 */
int RETARGET_ReadChar(void)
{
  return 0;
}

/**
 * @brief
 *   Setup SWO for output
 */
void RETARGET_SwoInit(void)
{
  BSP_TraceSwoSetup();
}
