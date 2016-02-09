/********************************************************************************************
 *
 * 		Author: 		Brad Torrence
 *		Purpose:		Example program that demonstrates:
 *							(1) setting up the system clock and SysTick Counter
 * 							(2) initializing peripherals (LED and OLED screen) and GPIO pins
 *							(3) toggling an LED by reading/writing from/to GPIO pins
 *							(4) creating and displaying a simple image on the OLED
 *							(5) formatting and displaying a string on the OLED
 *
 ********************************************************************************************/

// Project libraries
#include "src/system.h"
#include "src/led.h"
#include "src/oled.h"
#include "src/speaker.h"
#include "src/buttons.h"


//*************************************************************************************************
//	Main program to initialize hardware and execute Tasks.
//*************************************************************************************************
void main(void)  {
	//  Initialize system counters
	systemInit();

	// Initialize tasks
	OLEDInit();
	LEDInit();
	speakerInit();
	buttonInit();

	// Execute tasks repeatedly
    while(true){
    	OLEDExec();
    	LEDExec();
    	if (freq != 0) {
        	speakerExec();
    	}
    	buttonExec();

    }
}

