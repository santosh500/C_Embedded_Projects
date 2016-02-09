/*
 * uartSend.c
 *
 *  Created on: Oct 19, 2015
 *      Author: pcharles
 */


//Include the potentiometer.h
#include "uartSend.h"
#include "capacitor.h"
//Stelaris API ADC functions
#include "driverlib/adc.h"

// Stellaris driver libraries required by these local function definitions
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#include "system.h"
#include "queue.h"

#include "uartstdio.h"

void UARTTask(void* pvParameter) {

	int i = 0;

	unsigned long ulValue;

	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	UARTStdioInit(0);
	UARTprintf("Connection okay\r\n");

	while (true) {
		if (flagUART == 1) {
			i = 0;
			flagUART=0;
			UARTprintf("Start Sequence\n");
			while (i < 100) {

				xQueueReceive(cqueue, &ulValue, TICK_R*250);

				UARTprintf("%d\r\n", ulValue);
				i++;
			}

		}
		vTaskDelay(TICK_R*1000);
	}


}
