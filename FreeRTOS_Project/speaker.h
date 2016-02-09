/*
 * speaker.h
 *
 *  Created on: Sep 14, 2015
 *      Author: pcharles
 */

#ifndef SRC_SPEAKER_H_
#define SRC_SPEAKER_H_

/*
 *  The initialization and execution functions for the speaker
 */
extern unsigned long freq;//global variable used to test frequency or sound
extern unsigned long off;//variable used to turn sound off
extern void SpeakerTask(void*);


#endif /* SRC_SPEAKER_H_ */
