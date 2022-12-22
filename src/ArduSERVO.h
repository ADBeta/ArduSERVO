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
class Channel {
		public:
		/** Setters & Getters *************************************************/
		//Set this channels pin, uses Arduino pin numbering
		void setPin(uint8_t pin);
		
		//Set the min and max map values
		void setMapMinMax(int min, int max);
		
		//Enable/disable deadzones for ends and centre.
		void setDeadzones(bool ends, bool centre);
		
		//Get the decoded value of the Servo channel. Calls 2 sub-functions.
		
		
		/** *********************************/
		//Get the HIGH pulse time of the servo pin. Returns -1 on failure.
		int16_t getPulseMicros();
		
		
		
		private:
		//chASM Object for the chASM pin
		chASM *h_pin;
		
		/** Flags and vars ****************************************************/
		bool endDeadzone = true; //Enable deadzone end snapping. Deafult yes.
		bool midDeadzone = true; //Enable deadzone centre snapping. Deafult yes.
		
		//Min and Max values for the map function. Defaults to analogRead type.
		int mapMin = 0;
		int mapMax = 1023;
		
		//Servo timing variables. Change these if you need to.
		#define t_timeout 22000 //Max micros before a timeout.
		
		//Deadzone values pre-defined to increase speed. These can be changed.
		#define dz_maxSnap 2000 //Values to snap to when deadzone triggers
		#define dz_midSnap 1500
		#define dz_minSnap 1000
		
		#define dz_maxHyst 1980 //Values that will trigger a snap to deadzones
		#define dz_minHyst 1020
		//
		#define dz_midHystHi 1520
		#define dz_midHystLo 1480
		
		/** Functions *********************************************************/
		//Snap input values to a desired value, hystDelta controls the amount.
		int16_t pulseDeadzone(int16_t pulseMicros);
		
		
}; //class Channel

#endif
