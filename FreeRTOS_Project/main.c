/********************************************************************************************
 *
 * 		Author: 		Brad Torrence
 *		Purpose:		Example program that demonstrates:
 *							(1) setting up the system clock and the FreeRTOS system
 * 							(2) initializing peripherals (LED and OLED display)
 *							(3) toggling an LED by reading/writing from/to GPIO pins
 *							(4) creating and displaying a simple image on the OLED
 *							(5) formatting and displaying a string on the OLED
 *
 ********************************************************************************************/

// Project libraries
#include "src/system.h"
#include "src/oled.h"
#include "src/led.h"
#include "src/speaker.h"
#include "src/buttons.h"

//*************************************************************************************************
//	Main program to initialize hardware and execute Tasks.
//*************************************************************************************************
void main(void)  {
	// Create the tasks, the definitions are passed to the scheduler
	xTaskCreate(OLEDTask, "OLEDTask", 512, NULL, 2, NULL); // Note the higher priority for the display
	xTaskCreate(LEDTask, "LEDTask", 32, NULL, 1, NULL);
	xTaskCreate(SpeakerTask, "SpeakerTask", 32, NULL, 1, NULL );//SpeakerTask
	xTaskCreate(ButtonsTask, "ButtonsTask", 32, NULL, 3, NULL);//ButtonTask
	//  Initialize system
	systemInit();


	// Display the initial image
	startScreen();

	// Start the FreeRTOS Scheduler
	vTaskStartScheduler();//Scheduler for FreeRTOS
	// The infinite loop is necessary for the FreeRTOS Scheduler
    while(true);
}

