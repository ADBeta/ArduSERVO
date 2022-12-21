/*
* ArduSERVO is an arduino library that allows up to 8 Servo PWM signals to be  
* received and decoded into raw values.
*	
* If this library is in use within another project, please see the original 
* github page: https://github.com/ADBeta/ArduSERVO
* 
* Version 0.2.6
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
	/****** Variables and flags setup ******/
	//Current and last state of the servo pin 
	bool crntState, lastState;
	
	//Set last sate to a known wrong value, to force a trigger instantly, this
	//improves speed as it skips the idle LOW periods before a pulse.  
	lastState = 0xae;
	
	//Flag if a low state has been detected.
	bool beenLow = false;
	
	//Current micros and micros since last activity on the line.
	//Rising edge and falling edge micros. Used when measuring pulse time.
	uint32_t crntMicros, actvMicros, riseMicros, fallMicros;
	
	/****** Runtime ******/
	//While the timeout limit is not being exceeded, poll for activity.
	do {
		crntMicros = micros();
		crntState = h_pin->read();
		
		//If the pin state changes, reset timeout micros, and check if a rising 
		//or falling edge has taken place. 
		if(crntState != lastState) {			
			//If the pin is LOW, set the beenLow flag to detect a rising edge.
			if(crntState == LOW) beenLow = true;
			
			//If the pin is HIGH, AND there has been a low state, trigger a 
			//measurment. This switches to a high speed methodology.
			if(crntState == HIGH && beenLow == true) {
				//Get micros of rising edge
				riseMicros = micros();
				//Wait until the pin is LOW again.
				while(h_pin->read() != LOW);
				//Falling edge micros
				fallMicros = micros();
				
				//Return the difference between rising and falling edge
				return fallMicros - riseMicros;
			}
			
			//Reset states for the next loop.
			actvMicros = crntMicros;
			lastState = crntState;
		}
	} while(crntMicros - actvMicros < t_timeout);
	
	//If while loop exits, timeout has happened
	return -1;
}

int16_t Channel::pulseDeadzone(int16_t pulseMicros) {
	//Exit if the pulse from receiver is a failstate.
	if(pulseMicros == -1) return -1;
	
	int16_t deadzonedMicros;
	
	//Check if the input value is within a range to the desired value.
	//Mid snap needs to be in a range
	if(pulseMicros < dz_midHystHi && pulseMicros > dz_midHystLo) {
		deadzonedMicros = dz_midSnap;
	} else 
	
	//Max snap at upper bound
	if(pulseMicros > dz_maxHyst) {
		deadzonedMicros = dz_maxSnap;
	} else 
	
	//Min snap at lower bound
	if(pulseMicros < dz_minHyst) {
		deadzonedMicros = dz_minSnap;
	} else 
	
	//If the input isn't within a deadzone, pass the input through.
	{ deadzonedMicros = pulseMicros; }
	
	return deadzonedMicros;
}
