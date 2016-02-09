/*
 * potentiometer.h
 *
 *  Created on: Oct 5, 2015
 *      Author: pcharles
 */

#ifndef SRC_POTENTIOMETER_H_
#define SRC_POTENTIOMETER_H_

//base libraries
#include "system.h"

//FreeRTOS queue definitions
#include "queue.h"
/*
 *  The task definition for the potentiometer.h
 */
//extern unsigned long off;//variable used to turn sound off
extern QueueHandle_t pqueue;
extern void PotentioTask(void*);

#endif /* SRC_POTENTIOMETER_H_ */
