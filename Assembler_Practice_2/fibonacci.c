/*
 * fibonacci.c
 *
 *  Created on: Nov 18, 2015
 *      Author: pcharles
 */

// Header File
#include "fibonacci.h"

// Base library
#include "system.h"

// Stellaris driver libraries
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

// OLED driver library
#include "rit128x96x4.h" // This is a driver for the OLED display extension

// Standard C library
#include "stdio.h"

#include "uartstdio.h"

extern int FIBcompute(int, int);
int F10, F10_c;

void FIBTask(void *pvParameters) {
	const unsigned long delay = TICK_R * 10000;
	int i;

	long X = 58, Y = 35;

	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTStdioInit(0);
	//UARTprintf( "FreeRTOS LM3S1968 starting\r\n" );
	//UARTprintf("\r\nUART connected successfully!\r\n");
	while (true) {



		for (i = 2; i <= 10; i++) {
			F10_c = X + Y;
			X = Y;
			Y = F10_c;
		}
		UARTprintf(" F(10)C=%d\n", F10_c);
		X = 58;
		Y = 35;
		F10 = FIBcompute(X, Y);


		UARTprintf(" F(10)Assembly= %d\n", F10);
		vTaskDelay(delay);

	}
}
