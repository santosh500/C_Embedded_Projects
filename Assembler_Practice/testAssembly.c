/*
 * testAssembly.c
 *
 *  Created on: Nov 2, 2015
 *      Author: Brad Torrence
 */

#include "testAssembly.h"
#include "system.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#include "uartstdio.h"

#define MAX 10

// Forward declaration of the Assembly Version of the computation
extern int asmCompute(int, int, int, int);

void testAssemblyTask(void *pvParameters){
	const unsigned long delay = TICK_R * 1000;
	long a, b, c, d, x, y, cValue, asmValue;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTStdioInit(0);
    UARTprintf( "FreeRTOS LM3S1968 starting\r\n" );
    UARTprintf("\r\nUART connected successfully!\r\n");

	while(true){
		UARTprintf("Starting a new computation cycle... \n");
		for(a = 0; a < MAX; a++)
			for(b = 0; b < MAX; b++)
				for(c = 0; c < MAX; c++)
					for(d = 0; d < MAX; d++){
	// Change the X and Y expressions, so they match the ones you are given
						x = c*b/c & d & a*a;
						y = a+a-d|a-c;
	// DO NOT CHANGE ANYTHING ELSE!!!
						cValue = x + y;
	// The following invokes your assembly function to compute the same expression
						asmValue = asmCompute(a, b, c, d);
	// The assmebly computation result is compared to the result of the C computation
						if(cValue != asmValue)
							UARTprintf("INCORRECT!! C Value(%d) does not equal ASM Value (%d)\n", cValue, asmValue);
						else
							UARTprintf("CORRECT!! Values Match! (%d)!\n", asmValue);

						vTaskDelay(delay);
					}
	}
}
