/*
 * oled.c
 *
 *  Created on: Aug 28, 2015
 *      Author: Brad Torrence
 */

// Header File
#include "oled.h"
#include "joystick.h"
// Base library
#include "system.h"

// Stellaris driver libraries
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

// OLED driver
#include "rit128x96x4.h" // This is a driver for the OLED display extension

// Standard C library
#include "stdio.h"

// The function to generate and hold the initial start screen
void startScreen(void){
    /*
	 * The RIT128x96x4** functions are a part of the driver API for the OLED
	 * The details for this API can be found in drivers/rit128x96x4.c
	 *
     * Create a frame for the OLED display
     * 		The ImageDraw function takes an array of unsigned char
     * 		each 8-bit char represents 2 pixels (side-by-side)
     * 		so, 4 of these bits represent a single pixel's brightness
     * 		with valid brightness values ranging (0-15)
     * 		and the pixels are represented in pairs.
     *
     *  Since the pixels are represented in pairs along the horizontal,
     *  	and the OLED is 128x96 pixels,
     *  	the horizontal frame only needs 64 elements (64 * 2 = 128).
     *  However the vertical frames will require two separate arrays,
     *  	each will have 94 elements (the OLED is 96 pixels high
     *  	but we have taken care of the two ends with the horizontal lines)
     *  The left frame will set the right column of pixels to zero,
     *  	and the right frame will set the left column of pixels to zero.
     *  The blank array elements are initialized to 0 to turn-off pixels later.
     *  It only needs 62 elements because we don't want to erase the frame.
     */
    unsigned char lframe[94], rframe[94], hframe[64], blank[62];

    // The loop is used to initialize the arrays
    unsigned int i;
    for(i = 0; i < 94; i++){
    	lframe[i] = 0xF0; 				// Vertical line for the left edge
    	rframe[i] = 0x0F; 				// Vertical line for the right edge
    	if(i < 64) hframe[i] = 0xFF; 	// Horizontal line for top and bottom
    	if(i < 62) blank[i] = 0x00; 	// The blank line used to clear the screen
    }

    //  Initialize the OLED display
    RIT128x96x4Init(1000000);
    /*
     *  Draw the frame
     *  ImageDraw takes an array of unsigned char as the first argument
     *  	the next two arguments are the x and y coordinates (respectively)
     *  	of the screen position to start drawing, and the final two arguments
     *  	are the width and height (respectively) to which the image is scaled.
     */
    // Draw upper frame starting at (0,0) with width = 128 pixels and height = 1 pixel
    // 	(width and height should match the size of array measured in pixels)
    RIT128x96x4ImageDraw(hframe, 0, 0, 128, 1);
    // Draws lower frame starting at (0,95) width = 128, height = 1
    RIT128x96x4ImageDraw(hframe, 0, 95, 128, 1);
    // Draws left frame starting at (0,1) width = 2, height = 94
    RIT128x96x4ImageDraw(lframe, 0, 1, 2, 94);
    // Draws right frame starting at (127,1) width = 2, height = 94
    RIT128x96x4ImageDraw(rframe, 127, 1, 2, 94);

    /*
     * 	Draw the message
     * 	StringDraw takes a string as the first argument
     * 		the next two arguments are again the x and y coordinates of the starting position
     * 		and the final argument is pixel brightness for the
     * 	The first function writes the first part of the message at (32,24)
     * 		with a brightness of 15 (full brightness)
     */
	RIT128x96x4StringDraw(" Paul Charles", 32, 24, 15);
	RIT128x96x4StringDraw("Maze Game", 16, 33, 15);
	//RIT128x96x4StringDraw("Project 2", 16, 33, 15);
	RIT128x96x4StringDraw("EECS 388 Lab", 32, 42, 15);

	// Enable the select button, wait for the press, then disable and reset the port
	// The button is disabled after the splash screen and the port is reset to default for future use.
	GPIOPinTypeGPIOInput(GPIO_PORTG_BASE, GPIO_PIN_7); 	// Set the select button signal PG7 as input
	while(GPIOPinRead(GPIO_PORTG_BASE, GPIO_PIN_7));	// Wait until the signal changes (button pressed)
	SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOG);

	/*
	 *  When the select button is pressed we need to wipe the message leaving the frame on the OLED.
	 *   The loop sets the pixels to 0 everywhere except the screen's edges.
	 */
	for(i = 24; i < 50; i++)
		RIT128x96x4ImageDraw(blank, 2, i, 124, 1);
}

// The OLED Task definition
void OLEDTask(void *pvParameters){
	// The delay between executions
	unsigned long delay = TICK_R * 100.0;
	char sysTickStr[32];
	char leftright[32];
	char map[10][10];
	int o;
	unsigned int wvc=0;
	unsigned char vblank[94];
	unsigned int q;
	for(q = 1; q < 90; q++){
	    	 	// Horizontal line for top and bottom
	    	if(q < 90) vblank[q] = 0x00; 	// The blank line used to clear the screen
	    }

	unsigned char olframe[9];
	unsigned int t;
	for(t=0;t<9;t++)
	{
		if(t<9) olframe[t]=0xFF;
	}
	RIT128x96x4ImageDraw(olframe, 9,0, 5, 1);
	while(true) {
		/*
		*  Save the tick count into a string (character array)
		*  The length is 32 because each character is 8x8 pixels,
		*  		and since the OLED screen is 128 pixels wide
		*  		32 (128 / 8) is the number of characters that will
		*  		successfully fit on a single line of the OLED screen.

		*/
		for(o = 0; o < 93; o++)
		{
				RIT128x96x4ImageDraw(vblank, 0, o, 124, 1);
		}
		// sprintf is a standard C function that builds strings from other arguments

		//sprintf(leftright, "L/R: %d", lr);
		unsigned char lrframe[10], jhframe[20], kframe[15], dframe[25], uframe[25], vlframe[25], oqframe[45], ddlframe[8], dd45frame[16],dd16frame[20],dd98frame[25], dd54frame[25], dd200frame[26], finalframe[41];
		 unsigned int i;
		    for(i = 0; i < 70; i++){
		    	//kframe[i] = 0xF0; 				// Vertical line for the left edge
		    	if(i<10) lrframe[i] = 0xF0;
		    	if(i<25) dframe[i] = 0xF0;
		    	if(i<25) vlframe[i] = 0xF0;
		    	if(i<8) ddlframe[i] = 0xF0;
		    	if(i<16) dd45frame[i] = 0xF0;
		    	if(i<25) dd98frame[i] = 0xF0;
		    	if(i<26) dd200frame[i] = 0xF0;
		    	//if(i<5) olframe[i]=0xFF;
		    	// Vertical line for the right edge
		    	if(i <20) jhframe[i] = 0xFF;
		    	if(i <15) kframe[i] = 0xFF;
		    	if(i <25) uframe[i] = 0xFF;
		    	if(i <45) oqframe[i] = 0xFF;
		    	if(i <20) dd16frame[i] = 0xFF;
		    	if(i <20) dd54frame[i] = 0xFF;
		    	if(i <41) finalframe[i] = 0xFF;

		    	// Horizontal line for top and bottom
		    	//if(i < 62) ablank[i] = 0x00; 	// The blank line used to clear the screen
		    }

		    	RIT128x96x4ImageDraw(jhframe, 1, 15, 20, 1);
		    	RIT128x96x4ImageDraw(kframe, 22, 30, 20, 1);
		    	RIT128x96x4ImageDraw(uframe, 43, 56, 25, 1);
		    	RIT128x96x4ImageDraw(oqframe, 65, 84, 45, 1);
		    	RIT128x96x4ImageDraw(dd16frame, 45, 16, 20, 1);
		    	RIT128x96x4ImageDraw(dd54frame, 66, 42, 20, 1);
		    	RIT128x96x4ImageDraw(finalframe, 86, 66, 41, 1);
		        // Draws lower frame starting at (0,95) width = 128, height = 1
		    	//RIT128x96x4ImageDraw(jhframe, 0, 9, 128, 1);
		    	//RIT128x96x4ImageDraw(jhframe, 0, 18, 128, 1);

		        // Draws left frame starting at (0,1) width = 2, height = 94
		        //RIT128x96x4ImageDraw(lrframe, 0, 1, 2, 90);
		        // Draws right frame starting at (127,1) width = 2, height = 94
		        //RIT128x96x4ImageDraw(kframe, 127, 1, 2, 90);

		        		        // Draws lower frame starting at (0,95) width = 128, height = 1
		        		    	RIT128x96x4ImageDraw(lrframe, 22, 15, 2, 15);
		        		    	RIT128x96x4ImageDraw(dframe, 45, 31, 2, 25);
		        		    	RIT128x96x4ImageDraw(vlframe, 65, 56, 2, 25);
		        		    	RIT128x96x4ImageDraw(ddlframe, 107, 85, 2, 8);
		        		    	RIT128x96x4ImageDraw(dd45frame, 45, 0, 2, 16);
		        		    	RIT128x96x4ImageDraw(dd98frame, 65, 16, 2, 25);
		        		    	RIT128x96x4ImageDraw(dd200frame, 86, 43, 2, 26);
		        		    	/*RIT128x96x4ImageDraw(lrframe, 9, 0, 2, 90);
		        		    	RIT128x96x4ImageDraw(lrframe, 18, 0, 2, 90);
		        		    	RIT128x96x4ImageDraw(lrframe, 27, 0, 2, 90);
		        		    	RIT128x96x4ImageDraw(lrframe, 36, 0, 2, 90);
		        		    	RIT128x96x4ImageDraw(lrframe, 45, 0, 2, 90);
		        		    	RIT128x96x4ImageDraw(lrframe, 54, 0, 2, 90);
		        		    	RIT128x96x4ImageDraw(lrframe, 63, 0, 2, 90);
		        		    	RIT128x96x4ImageDraw(lrframe, 72, 0, 2, 90);
		        		        RIT128x96x4ImageDraw(lrframe, 81, 0, 2, 90);
		        		        RIT128x96x4ImageDraw(lrframe, 90, 0, 2, 90);*/
		  /*  int k=0;
		    int v=0;
		    unsigned int w;
		    unsigned int j;
		    for(v=0; v <= 90; v++)
		    {
		    	RIT128x96x4ImageDraw(jhframe, 0, v, 90, 1);
		    	v=v+9;
		    }


		    for(k=0; k <= 90; k++)
		    {
		    	RIT128x96x4ImageDraw(lrframe, k, 0, 1, 90);

		    	k=k+9;
	    	}
*/
		        		    	RIT128x96x4ImageDraw(olframe, count, lr, 9, 1);
		        		    	/*
		    if((count < 90) && (lr < 90))
		    {

		    	}

		    else
		    {
		    	count=9;
		    	lr=0;
		    	RIT128x96x4ImageDraw(olframe, count, lr, 9, 1);

		    }*/

		    //horizontal line boundaries
		    if(lr==15)
		    {
		    	unsigned int y;
		    	for(y=0; y<20; y++)
		    	{
		    		if(count==y)

		    		{

		    			wvc=1;
		    			count = 1;
		    			lr=9;
		    					break;
		    		}

		    	}
		    }

		    if(lr==55)
		   		    {
		   		    	unsigned int y;
		   		    	for(y=43; y<68; y++)
		   		    	{
		   		    		if(count==y)

		   		    		{

		   		    			wvc=1;
		   		    			count = 1;
		   		    			lr=9;
		   		    					break;
		   		    		}

		   		    	}
		   		    }
		    if(lr==81)
		    		   		    {
		    		   		    	unsigned int y;
		    		   		    	for(y=68; y<105; y++)
		    		   		    	{
		    		   		    		if(count==y)

		    		   		    		{

		    		   		    			wvc=1;
		    		   		    			count = 1;
		    		   		    			lr=9;
		    		   		    					break;
		    		   		    		}

		    		   		    	}
		    		   		    }
		    if(lr==30)
		    		   		    {
		    		   		    	unsigned int y;
		    		   		    	for(y=22; y<43; y++)
		    		   		    	{
		    		   		    		if(count==y)

		    		   		    		{

		    		   		    			wvc=1;
		    		   		    			count = 1;
		    		   		    			lr=9;
		    		   		    					break;
		    		   		    		}

		    		   		    	}
		    		   		    }


		    //vertical lines
		    if(count==22)
		   		    {
		   		    	unsigned int y;
		   		    			    	for(y=17; y<33; y++)
		   		    			    	{
		   		    			    		if(lr==y)

		   		    			    		{

		   		    			    			wvc=1;
		   		    			    			count = 1;
		   		    			    			lr=9;
		   		    			    					break;
		   		    			    		}

		   		    			    	}
		   		    }
		    if(count==67)
		    {
		    	unsigned int y;
		    			    	for(y=58; y<83; y++)
		    			    	{
		    			    		if(lr==y)

		    			    		{

		    			    			wvc=1;
		    			    			count = 1;
		    			    			lr=9;
		    			    					break;
		    			    		}

		    			    	}
		    }
		    if(lr==90)
		    		    {



		    	RIT128x96x4StringDraw(" You win", 32, 24, 15);
		    		    			    			wvc=2;

		    		    			    					break;



		    		    }
		    if(count==43)
		    		    {
		    		    	unsigned int y;
		    		    			    	for(y=32; y<57; y++)
		    		    			    	{
		    		    			    		if(lr==y)

		    		    			    		{

		    		    			    			wvc=1;
		    		    			    			count = 1;
		    		    			    			lr=9;
		    		    			    					break;
		    		    			    		}

		    		    			    	}
		    		    }


		    //upper boundary lines
		    if(lr==16)
		    		    		   		    {
		    		    		   		    	unsigned int y;
		    		    		   		    	for(y=45; y<65; y++)
		    		    		   		    	{
		    		    		   		    		if(count==y)

		    		    		   		    		{

		    		    		   		    			wvc=1;
		    		    		   		    			count = 1;
		    		    		   		    			lr=9;
		    		    		   		    					break;
		    		    		   		    		}

		    		    		   		    	}
		    		    		   		    }
		    if(lr==43)
		    		    		    		   		    {
		    		    		    		   		    	unsigned int y;
		    		    		    		   		    	for(y=65; y<85; y++)
		    		    		    		   		    	{
		    		    		    		   		    		if(count==y)

		    		    		    		   		    		{

		    		    		    		   		    			wvc=1;
		    		    		    		   		    			count = 1;
		    		    		    		   		    			lr=9;
		    		    		    		   		    					break;
		    		    		    		   		    		}

		    		    		    		   		    	}
		    		    		    		   		    }
		    if(lr==66)
		    		    		    		    		   		    {
		    		    		    		    		   		    	unsigned int y;
		    		    		    		    		   		    	for(y=86; y<122; y++)
		    		    		    		    		   		    	{
		    		    		    		    		   		    		if(count==y)

		    		    		    		    		   		    		{

		    		    		    		    		   		    			wvc=1;
		    		    		    		    		   		    			count = 1;
		    		    		    		    		   		    			lr=9;
		    		    		    		    		   		    					break;
		    		    		    		    		   		    		}

		    		    		    		    		   		    	}
		    		    		    		    		   		    }
		    if(count==39)
		    		    		    {
		    		    		    	unsigned int y;
		    		    		    			    	for(y=0; y<16; y++)
		    		    		    			    	{
		    		    		    			    		if(lr==y)

		    		    		    			    		{

		    		    		    			    			wvc=1;
		    		    		    			    			count = 1;
		    		    		    			    			lr=9;
		    		    		    			    					break;
		    		    		    			    		}

		    		    		    			    	}
		    		    		    }
		    if(count==58)
		    		    		    		    {
		    		    		    		    	unsigned int y;
		    		    		    		    			    	for(y=17; y<42; y++)
		    		    		    		    			    	{
		    		    		    		    			    		if(lr==y)

		    		    		    		    			    		{

		    		    		    		    			    			wvc=1;
		    		    		    		    			    			count = 1;
		    		    		    		    			    			lr=9;
		    		    		    		    			    					break;
		    		    		    		    			    		}

		    		    		    		    			    	}
		    		    		    		    }

		    if(count==80)
		    		    		    		    		    {
		    		    		    		    		    	unsigned int y;
		    		    		    		    		    			    	for(y=43; y<70; y++)
		    		    		    		    		    			    	{
		    		    		    		    		    			    		if(lr==y)

		    		    		    		    		    			    		{

		    		    		    		    		    			    			wvc=1;
		    		    		    		    		    			    			count = 1;
		    		    		    		    		    			    			lr=9;
		    		    		    		    		    			    					break;
		    		    		    		    		    			    		}

		    		    		    		    		    			    	}
		    		    		    		    		    }

		    if(wvc==1)
		    {
		    	RIT128x96x4StringDraw(" Game Over", 32, 24, 15);
		    	break;
		    }
		    else if(wvc==2)
		    {
		    	RIT128x96x4StringDraw("You win", 32, 24, 15);
		    	break;
		    }

	/**/


		//  Draw the string on the OLED display
	   //
	   //RIT128x96x4StringDraw(leftright,  8, 50, 15);
        //	Advance next execution time

	    vTaskDelay(delay);
	}
}

