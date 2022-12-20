/*
* ArduSERVO is an arduino library that allows up to 8 Servo PWM signals to be  
* received and decoded into raw values.
*	
* If this library is in use within another project, please see the original 
* github page: https://github.com/ADBeta/ArduSERVO
* 
* (c) ADBeta
*/

#include <Arduino.h>
#include "./chASM.h"

#ifndef ARDUSERVO_H
#define ARDUSERVO_H

//API Servo handler class
class ArduSERVO {
	public:
	//Constructor. Pass number of SERVO Channels. Limits to 7
	ArduSERVO(uint8_t chan);
	
	//Set the pin of a certain channel
	void setChannelPin(uint8_t chan, uint8_t pin);
	
	//Poll a channel pin and return high time.
	
	private:
	//Define some variables for the library
	#define MAX_CHAN 7
	
	//Keep track of how many channels are in use
	uint8_t channelNo;

	//chASM pointer array. Created in constructor.
	chASM *chanPin[];

}; //class ArduSERVO


/** Individual Channel Managment **********************************************/
//Struct handles each channel as a seperate object. Not for user interaction
struct Channel {
		//chASM Object for the chASM pin
		chASM pin;
		
		//Min and Max values for the map function. Defaults to analogRead type.
		int mapMin = 0;
		int mapMax = 1023;
	
	}; //struct Channel

#endif
