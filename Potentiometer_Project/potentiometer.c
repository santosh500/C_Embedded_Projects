/*
 * potentiometer.c
 *
 *  Created on: Oct 5, 2015
 *      Author: pcharles
 */
//Include the potentiometer.h
#include "potentiometer.h"
//Stelaris API ADC functions
#include "driverlib/adc.h"

// Stellaris driver libraries required by these local function definitions
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

//Definition of QueueHandle_t
QueueHandle_t pqueue;




void PotentioTask(void* pvParameter)
{
	unsigned long ulValue=0;

	pqueue = xQueueCreate(5,sizeof(unsigned long));

	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0);
	GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD);
	GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0x01);//Setting the Pin 0 to "high"

	//Initialize the ADC using functions from the Stellaris API

	ADCSequenceConfigure(ADC_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_IE|ADC_CTL_END|ADC_CTL_CH0);
	ADCSequenceEnable(ADC0_BASE, 0);
	ADCIntEnable(ADC0_BASE, 0);
	ADCIntClear(ADC0_BASE, 0);
	//Trigger from the Processor
	while(true)
	{

		ADCProcessorTrigger(ADC0_BASE, 0);
		while(!ADCIntStatus(ADC0_BASE, 0, false))
		{
		}
		ADCSequenceDataGet(ADC0_BASE, 0, &ulValue);//Enable ADC sequence 0
		xQueueSend(pqueue, &ulValue, 0);
		ADCIntClear(ADC0_BASE, 0);
		vTaskDelay(TICK_R*1000);
	}

}





