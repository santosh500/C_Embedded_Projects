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
static unsigned long target = 0;
static unsigned long period = 10;


static unsigned long period1 = 2000;
static unsigned long period2 = 5000;
unsigned long c;
unsigned long p=buttons;
unsigned long pp=buttons;

void buttonInit(void) {
    // Enable GPIO Port G and configure it to drive the Button
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    // The GPIOP Port G is attached to 5 pins as input
    GPIOPinTypeGPIOInput(GPIO_PORTG_BASE, buttons);

    GPIOPadConfigSet(GPIO_PORTG_BASE, buttons, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    // Initialize the first execution time for the task by adding to the current SysTickCount
    target = sysTickCount + period;
}

void buttonExec(void)
{
	if (sysTickCount >= target) {
		//frequency is used to set the sound for each button
		freq = 0;
		//read c from GPIOG
		c = GPIOPinRead(GPIO_PORTG_BASE, buttons);
		//this is the first steady state situation
		if (c != buttons) {
			if(c!=p)
			{
				target += debounce;
			}
			else {
				if(c!=pp)
				{
					if(!(c & up))
					{
						freq=200;
					}
					else if(!(c & down)) {
						freq=300;
					}
					else if(!(c & left)) {
						freq=400;
					}
					else if(!(c & right)) {
						freq=500;
					}
					else if(!(c & select)) {
						freq=600;
					}
					target += period1;
				}
			}
		}
		else
		{
			if(c!=pp && p!=pp)
			{
				if(!(pp & up)) {
					freq=250;
				}
				else if(!(pp & down)) {
					freq=350;
				}
				else if(!(pp & left)) {
					freq=450;
				}
				else if(!(pp & right)) {
					freq=550;
				}
				else if(!(pp & select)) {
					freq=650;
				}
				target += period2;
			}
		}
		//This sets them equal to each other, making pp on the same state as c, which turns off the sound
		pp = p;
		p = c;
		target += period;
	}

}
