/*
* ArduSERVO is an arduino library that allows up to 8 Servo PWM signals to be  
* received and decoded into raw values.
*	
* If this library is in use within another project, please see the original 
* github page: https://github.com/ADBeta/ArduSERVO
* 
* Version 0.2.2
* Last Modified 20 Dec 2022
* (c) ADBeta
*/

#include "ArduSERVO.h"
#include "./chASM.h"

/*
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

*/

/** Individual Channel Handler ************************************************/
void Channel::setPin(uint8_t pin) {
	//Create a new chASM object with pin, and set h_pin to reference it
	static chASM pinPtr(pin);
	h_pin = &pinPtr;
	
	//Set some pin variables.
	h_pin->setMode(INPUT);
}


int16_t Channel::getPulseMicros() {
	/* Functional description: Keep track of the state of the pin, if the pin 
	doesn't change state within t_timeout micros, then exit with a failure.
	
	Only trigger a measurment if we have have had at least one cycle of LOW 
	state. This prevents measuring at some point in the middle of a cycle.
		
	If everything is ready, note the rising and falling edge of the pin, 
	subtract these values to get the length in micros of the servo pulse. */
	
	//Current state of the channel pin 
	bool cState = 0;
	//TODO
	//Last state of the channel pin. Set to a known false value to force a check  
	bool lState = 0xff;
	
	//Flag if a low state has been detected.
	bool beenLow = false;
	
	//Current micros and micros since last activity on the line.
	uint32_t cMicros, actMicros;
	
	//While there is activity on the line
	do {
		//Keep track of current micros.
		cMicros = micros();
	
		//Get the current state of the pin.
		cState = h_pin->read();	
		
		//If the pin state changes, reset the actMicros gap and note the change. 
		if(cState != lState) {		
			actMicros = cMicros;
			lState = cState;
			
			//If the pin is LOW, set the beenLow flag.
			if(cState == LOW) beenLow = true;
			
			//If the pin is HIGH, AND there has been a low state, trigger a 
			//measurment.
			if(cState == HIGH && beenLow == true) {
				Serial.println("trig");
			}
		}
	} while(cMicros - actMicros < t_timeout);
	
	//If while loop exits, timeout has happened
	return -1;
}


