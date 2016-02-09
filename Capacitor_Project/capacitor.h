/*
 * capacitor.h
 *
 *  Created on: Oct 19, 2015
 *      Author: pcharles
 */

#ifndef SRC_CAPACITOR_H_
#define SRC_CAPACITOR_H_

//base libraries
#include "system.h"

//FreeRTOS queue definitions
#include "queue.h"
/*
 *  The task definition for the potentiometer.h
 */
//extern unsigned long off;//variable used to turn sound off
extern int flagUART;
extern QueueHandle_t cqueue;
extern void CapacitorTask(void*);

#endif /* SRC_CAPACITOR_H_ */
