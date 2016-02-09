/*
 * buttons.c
 *
 *  Created on: Sep 21, 2015
 *      Author: pcharles
 */

// Header file
#include "joystick.h"


// Base library
#include "system.h"

// Stellaris driver libraries required by these local function definitions
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

//defining of pins
//for PORT D, the pins are from 0 to 3
#define down GPIO_PIN_0
#define up GPIO_PIN_1
#define left GPIO_PIN_2
#define right GPIO_PIN_3
#define buttons (up|down|left|right)

//defining of the local forms of target, period and debounce
static unsigned long debounce = 100;
static unsigned long delay=TICK_R;

static unsigned long period1 = 200*TICK_R;
static unsigned long period2 = 50000;
unsigned long c;
unsigned long p=buttons;
unsigned long pp=buttons;
unsigned long off=1;

long count=5;
long lr=5;

void JoystickTask(void *pvParameters)
{



	// Enable GPIO Port D and configure it to drive the Button
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    // The GPIOP Port D is attached to 5 pins as input
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, buttons);

    GPIOPadConfigSet(GPIO_PORTD_BASE, buttons, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);

    // Initialize the first execution time for the task by adding to the current SysTickCount

    while(true)
	{
		//frequency is used to set the sound for each button
		delay = TICK_R*100;
		off=1;
		//freq = 0;
		//read c from GPIOD
		c = GPIOPinRead(GPIO_PORTD_BASE, buttons);
		//this is the first steady state situation
		if (c != 0) {
			if(c!=p)
			{
				delay = TICK_R*50; //debouncing
			}
			else {
				//if(c!=pp)
				//{
				/*
					if(c == (up|right))
					{
						off=0;
						count++;
						lr++;
					}
					else if(c == (down|right)) {
						off=0;
						count--;
						lr++;

					}
					else if(c == (left|up)) {
						off=0;
						count++;
						lr--;
					}
					else if(c == (down|left)) {
						off=0;
						lr--;
						count--;
					}
					else if((c==up))
					{
						off=0;
						count++;
					}
					else if((c==down)) {
						off=0;
						count--;

					}
					else if((c==left)) {
						off=0;
						lr--;
					}
					else if ((c==right)) {
						off=0;
						lr++;
					}*/
		//diagonals
									if(c == (up|right))
									{
										off=0;
										count++;
										lr++;
									}
									else if(c == (down|right)) {
										off=0;
										count--;
										lr++;

									}
									else if(c == (left|up)) {
										off=0;
										count++;
										lr--;
									}
									else if(c == (down|left)) {
										off=0;
										lr--;
										count++;
									}
									else if((c==up))
									{
										off=0;
										count++;
									}
									else if((c==down)) {
										off=0;
										count--;

									}
									else if((c==left)) {
										off=0;
										lr--;
									}
									else if ((c==right)) {
										off=0;
										lr++;
									}

				//}
			}
		}

		pp = p;
		p = c;
		vTaskDelay(delay);
	}

}
