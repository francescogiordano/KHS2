#include "adc.h"

#include "em_core.h"
#include "em_cmu.h"
#include "em_adc.h"

#include "ecode.h"

#ifndef ADC_ADC
#define ADC_ADC ADC_ADC0
#endif

#if (ADC_ADC == ADC_ADC0) && (ADC_COUNT >= 1)
#define	ADC	            ADC0
#define ADC_CLK         cmuClock_ADC0
#define ADC_IRQ         ADC0_IRQn
#define ADC_IRQHandler  ADC0_IRQHandler
#endif

#define ADC_MAX   0xFFF

/*
void ADC_IRQHandler(void){
}
*/

Ecode_t InitAdc(void){

	ADC_InitSingle_TypeDef singleInit = ADC_INITSINGLE_DEFAULT;
	CMU_ClockEnable(ADC_CLK, true);

	singleInit.acqTime = adcAcqTime256;
	singleInit.reference = adcRef5V;
	singleInit.posSel = adcPosSelAVDD;
	ADC_InitSingle(ADC, &singleInit);

	//ADC_IntDisable(ADC, ADC_IEN_SINGLE);
	//NVIC_ClearPendingIRQ(ADC_IRQ);
	//NVIC_EnableIRQ(ADC_IRQ);

	return ECODE_EMDRV_ADC_OK;
}
uint32_t GetSingleAdc(void){

	ADC_Start(ADC, adcStartSingle);
	while(ADC->STATUS & ADC_STATUS_SINGLEACT);

	return ADC_DataSingleGet(ADC);
}


