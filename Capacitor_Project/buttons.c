
/*
 * buttons.c
 *
 *  Created on: Oct 19, 2015
 *      Author: pcharles
 */


/*
 * buttons.c
 *
 *  Created on: Sep 21, 2015
 *      Author: pcharles
 */

// Header file
#include "buttons.h"


// Speaker file
//#include "speaker.h"

// Base library
#include "system.h"

// Stellaris driver libraries required by these local function definitions
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

//defining of pins
#define select GPIO_PIN_7
#define buttons select

//defining of the local forms of target, period and debounce
static unsigned long debounce = 100;
static unsigned long delay=TICK_R;

static unsigned long period1 = 200*TICK_R;
static unsigned long period2 = 1000*TICK_R;
unsigned long c;
unsigned long p=buttons;
unsigned long pp=buttons;


int flagcap = 0;

void ButtonsTask(void *pvParameters)
{

	// Enable GPIO Port G and configure it to drive the Button
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    // The GPIOP Port G is attached to 5 pins as input
    GPIOPinTypeGPIOInput(GPIO_PORTG_BASE, buttons);
    GPIOPadConfigSet(GPIO_PORTG_BASE, buttons, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    // Initialize the first execution time for the task by adding to the current SysTickCount
    vTaskDelay(sysTickCount + TICK_R*1000);///maybe a mistake

	while(true)
	{
		//frequency is used to set the sound for each button
		delay = TICK_R;

		//read c from GPIOG
		c = GPIOPinRead(GPIO_PORTG_BASE, buttons);
		//this is the first steady state situation (for when button is pressed)
		if (c != buttons) {
			if(c != p)
			{
				delay += debounce;
			}

		}
		else//this is the first steady state situation (for when button is released)
		{
			if((c != pp) && (p != pp))
			{
				flagcap = 1;
				delay += period2;
			}
		}
		//This sets them equal to each other, making pp on the same state as c, which turns off the sound
		pp = p;
		p = c;
		vTaskDelay(delay);//substitute for target+=period
	}
}
