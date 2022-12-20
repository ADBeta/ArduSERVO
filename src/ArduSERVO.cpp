/*
* ArduSERVO is an arduino library that allows up to 8 Servo PWM signals to be  
* received and decoded into raw values.
*	
* If this library is in use within another project, please see the original 
* github page: https://github.com/ADBeta/ArduSERVO
* 
* Version 0.1.1
* Last Modified 20 Dec 2022
* (c) ADBeta
*/

#include "ArduSERVO.h"
#include "./chASM.h"

ArduSERVO::ArduSERVO(uint8_t chan) {
	//TODO Max limit

	//Set channel variables
	this->channelNo = chan;
	
	//Set the number of chASM objects
	chASM *chanPin[chan];
}

void ArduSERVO::setChannelPin(uint8_t chan, uint8_t pin) {
	//If the pin passed is higher than we have selected or MAX, then exit.
	if(chan > MAX_CHAN || chan > channelNo) return;	
	
	//Create a new chASM object with the pin that was passed.
	chASM *nPin = new chASM(pin);
	
	//Set the pointer at array index [chan].
	chanPin[chan] = nPin;
	
	//Set the pin variables.
	chanPin[chan]->setMode(INPUT);
}
