/*
 * speaker.c
 *
 *  Created on: Sep 14, 2015
 *      Author: pcharles
 */


// Header File for speaker and buttons
#include "speaker.h"
#include "buttons.h"
// Base library
#include "system.h"

// Stellaris driver libraries required by these local function definitions
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

//target is used to count the Systick and period
static unsigned long target = 0;
//Period of frequency
static unsigned long period = SYSTICK_FREQUENCY/(440*2);
//default set of frequency
unsigned long freq = 0;

/*
 *  The initialization and execution functions for this task
 */
void speakerInit(void) {
    // Enable GPIO Port H and configure it to drive the Status LED
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
    // The Status LED is attached to G<2> (Port G pin 2) it must be set as output
    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_1|GPIO_PIN_0);
    //GPIO write and pin assignments for speaker
    GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_1|GPIO_PIN_0, 0x01);

    // Initialize the first execution time for the task by adding to the current SysTickCount
    target = sysTickCount + period;
}

void speakerExec(void) {
	//Frequency and sound for speaker
	if(sysTickCount >= target) {
		period = SYSTICK_FREQUENCY/(freq*2);
        GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_1|GPIO_PIN_0, GPIOPinRead(GPIO_PORTH_BASE, GPIO_PIN_1|GPIO_PIN_0) ^ 0x03);
        target += period;
	}
}




