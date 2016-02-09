/*
 * buttons.c
 *
 *  Created on: Sep 21, 2015
 *      Author: pcharles
 */

// Header file
#include "buttons.h"

// Speaker file
#include "speaker.h"

// Base library
#include "system.h"

// Stellaris driver libraries required by these local function definitions
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

//defining of pins
#define up GPIO_PIN_3
#define down GPIO_PIN_4
#define left GPIO_PIN_5
#define right GPIO_PIN_6
#define select GPIO_PIN_7
#define buttons (up|down|left|right|select)

//defining of the local forms of target, period and debounce
static unsigned long debounce = 100;
static unsigned long delay=TICK_R;

static unsigned long period1 = 200*TICK_R;
static unsigned long period2 = 50000;
unsigned long c;
unsigned long p=buttons;
unsigned long pp=buttons;

void ButtonsTask(void *pvParameters)
{



	// Enable GPIO Port G and configure it to drive the Button
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    // The GPIOP Port G is attached to 5 pins as input
    GPIOPinTypeGPIOInput(GPIO_PORTG_BASE, buttons);

    GPIOPadConfigSet(GPIO_PORTG_BASE, buttons, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    // Initialize the first execution time for the task by adding to the current SysTickCount
    delay = sysTickCount + delay + TICK_R*1000;///maybe a mistake

	while(true)
	{
		//frequency is used to set the sound for each button
		delay = TICK_R;
		off=1;
		freq = 0;
		//read c from GPIOG
		c = GPIOPinRead(GPIO_PORTG_BASE, buttons);
		//this is the first steady state situation (for when button is pressed)
		if (c != buttons) {
			if(c!=p)
			{
				delay += debounce;
			}
			else {
				if(c!=pp)
				{
					if(!(c & up))
					{
						off=0;
						freq=200;

					}
					else if(!(c & down)) {
						off=0;
						freq=300;

					}
					else if(!(c & left)) {
						off=0;
						freq=400;

					}
					else if(!(c & right)) {
						off=0;
						freq=500;

					}
					else if(!(c & select)) {
						off=0;
						freq=600;

					}
					delay += period1;
				}
			}
		}
		else//this is the first steady state situation (for when button is released)
		{
			if(c!=pp && p!=pp)
			{
				if(!(pp & up)) {
					off=0;
					freq=250;

				}
				else if(!(pp & down)) {
					off=0;
					freq=350;

				}
				else if(!(pp & left)) {
					off=0;
					freq=450;

				}
				else if(!(pp & right)) {
					off=0;
					freq=550;

				}
				else if(!(pp & select)) {
					off=0;
					freq=650;

				}
				delay += period2;
			}
		}
		//This sets them equal to each other, making pp on the same state as c, which turns off the sound
		pp = p;
		p = c;
		vTaskDelay(delay);//substitute for target+=period



	}

}
