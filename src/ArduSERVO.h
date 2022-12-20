/*
* ArduSERVO is an arduino library that allows up to 8 Servo PWM signals to be  
* received and decoded into raw values.
*	
* If this library is in use within another project, please see the original 
* github page: https://github.com/ADBeta/ArduSERVO
* 
* (c) ADBeta
*/

#ifndef ARDUSERVO_H
#define ARDUSERVO_H

#include <Arduino.h>

class ArduSERVO {
	public:
	//Constructor. Pass number of SERVO Channels.
	ArduSERVO(uint8_t chan);
	
	
	private:
	//Keep track of how many channels are in use
	uint8_t channelNo;
	


}; //class ArduSERVO

#endif
