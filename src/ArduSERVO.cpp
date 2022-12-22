/*
* ArduSERVO is an arduino library that allows up to 8 Servo PWM signals to be  
* received and decoded into raw values.
*	
* If this library is in use within another project, please see the original 
* github page: https://github.com/ADBeta/ArduSERVO
* 
* Version 0.2.10
* Last Modified 22 Dec 2022
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

/** Individual Channel Class **************************************************/
/** Setters and Getters *******************************************************/
void Channel::setPin(uint8_t pin) {
	//Create a new chASM object with pin, and set h_pin to reference it
	static chASM pinPtr(pin);
	h_pin = &pinPtr;
	
	//Set some pin variables.
	h_pin->write(LOW); //TODO not needed?
	h_pin->setMode(INPUT);
}

void Channel::setDeadzones(bool ends, bool centre) {
	this->endDeadzone = ends;
	this->midDeadzone = centre;
}

void Channel::setMapMinMax(int min, int max) {
	mapMin = min;
	mapMax = max;
}

/** API Function **************************************************************/
int16_t Channel::getPulseMicros() {
	/****** Variables and flags setup ******/
	//Current and last state of the servo pin 
	uint8_t crntState, lastState;
	
	//Set last sate to a known wrong value, to force a trigger instantly, this
	//improves speed as it skips the idle LOW periods before a pulse.  
	lastState = 0xaa;
	
	//Flag if a low state has been detected.
	bool beenLow = false;
	
	//Current micros and micros since last activity on the line.
	//Rising edge and falling edge micros. Used when measuring pulse time.
	uint32_t crntMicros, actvMicros, riseMicros, fallMicros;
		
	/****** Runtime ******/
	//Set active and current micros. Ensures no presistant RAM failures.
	actvMicros = micros();
	crntMicros = actvMicros; //TODO
	
	//While the timeout limit is not being exceeded, poll for activity.
	 while(crntMicros - actvMicros < t_timeout) {
		crntMicros = micros();
		crntState = h_pin->read();
		
		//If the pin state changes, reset timeout micros, and check if a rising 
		//or falling edge has taken place. 
		if(crntState != lastState) {
			//Reset states for the next loop.
			actvMicros = crntMicros;
			lastState = crntState;
			
			//If the pin is LOW, set the beenLow flag to detect a rising edge.
			if(crntState == LOW) beenLow = true;
		
			//If the pin is HIGH, AND there has been a low state, trigger a 
			//measurment. This switches to a high speed methodology.
			if(beenLow == true && crntState == HIGH) {
				//Get micros of rising edge
				riseMicros = micros();
				//Wait until the pin is LOW again.
				while(h_pin->read() == HIGH);
				//Falling edge micros
				fallMicros = micros();
				
				//pass the difference between rising and falling edge to 
				//the deadzone function, then return that value
				return pulseDeadzone(fallMicros - riseMicros);
			}
		}
	}
	
	//If the while loop exits, the timemout condition is met. return an error.
	return -1;
}

int16_t Channel::pulseDeadzone(int16_t pulseMicros) {
	//Exit if the pulse from receiver is a failstate.
	if(pulseMicros == -1) return -1;
	
	//Centre deadzone snap 
	if(pulseMicros < dz_midHystHi && pulseMicros > dz_midHystLo) {
		//Only change values if the flag is set. This order method is faster.
		if(midDeadzone) {
			pulseMicros = dz_midSnap;
			//Premature return, saves some if comparisons.
			return pulseMicros;
		}
	}
	
	//Endstop deadzone snap.
	if(endDeadzone) {
		//Max snap at upper bound
		if(pulseMicros > dz_maxHyst) {
			pulseMicros = dz_maxSnap;
		}
		
		//Min snap at lower bound
		if(pulseMicros < dz_minHyst) {
			pulseMicros = dz_minSnap;
		}
	}
	
	//If the deadzoning isn't enabled, the value should not have been modified.
	return pulseMicros;
}
