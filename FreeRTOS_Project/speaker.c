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
//*static unsigned long target = 0;
//Period of frequency
static unsigned long delay = SYSTICK_FREQUENCY/(440*2);
//default set of frequency
unsigned long freq = 0;
unsigned long off=0;//variable to turn sound off or not
/*
 *  The initialization and execution functions for this task
 */


void SpeakerTask(void* pvParameters) {

	// Enable GPIO Port H and configure it to drive the Status LED
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
    // Speaker status for Port H Pin 1
    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_1|GPIO_PIN_0);
    //GPIO write and pin assignments for speaker
    GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_1|GPIO_PIN_0, 0x01);

    // Initialize the first execution time for the task by adding to the current SysTickCount
    delay = sysTickCount + delay;
	while(true)
	{
		if(off==0){
		//Frequency and sound for speaker
		delay = SYSTICK_FREQUENCY/(freq*2);
        GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_1|GPIO_PIN_0, GPIOPinRead(GPIO_PORTH_BASE, GPIO_PIN_1|GPIO_PIN_0) ^ 0x03);
        //vTaskDelay(delay);
		}
		vTaskDelay(delay);//substitute for target+=period
	}

}




