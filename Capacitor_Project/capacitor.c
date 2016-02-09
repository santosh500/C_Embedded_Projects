/*
 * capacitor.c
 *
 *  Created on: Oct 19, 2015
 *      Author: pcharles
 */

//Include the potentiometer.h
#include "capacitor.h"
#include "buttons.h"
//Stelaris API ADC functions
#include "driverlib/adc.h"

// Stellaris driver libraries required by these local function definitions
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

//Definition of QueueHandle_t
QueueHandle_t cqueue;
int flagUART;
void CapacitorTask(void* pvParameter)
{
	unsigned long ulValue=0;
	int i=0;

	cqueue = xQueueCreate(100,sizeof(unsigned long));


	//SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_1);
	GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_OD);
	GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0x02);//Setting the Pin 0 to "high"

	//Initialize the ADC using functions from the Stellaris API
	//SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	ADCSequenceConfigure(ADC_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 0, 1, ADC_CTL_IE|ADC_CTL_END|ADC_CTL_CH1);
	ADCSequenceEnable(ADC0_BASE, 1);
	//ADCIntEnable(ADC0_BASE, 1);
	ADCIntClear(ADC0_BASE, 1);

	//Trigger from the Processor
	while(true)
	{

		if(flagcap==1)
		{
			GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0x00);//Setting the Pin 0 to "high"
			vTaskDelay(TICK_R*0.5);
			GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0x02);//Setting the Pin 0 to "high"
			i=0;
			flagcap = 0;
			//ADCIntClear(ADC0_BASE, 1);
			while(i<100)
			{
				ADCProcessorTrigger(ADC0_BASE, 1);
				while(!ADCIntStatus(ADC0_BASE, 1, false))
				{
				}
				ADCSequenceDataGet(ADC0_BASE, 1, &ulValue);//Enable ADC sequence 0
				ADCIntClear(ADC0_BASE, 1);
				xQueueSend(cqueue, &ulValue, 0);
				i++;
				vTaskDelay(TICK_R*1.0)
;			}
			flagUART = 1;

		}
		vTaskDelay(TICK_R*10);
	}

}
