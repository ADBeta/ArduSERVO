/*
	This example is purely to objectively show and measure the speed difference
	between the built-in functions vs my library.
	
	An oscilloscope, frequency counter or some other form of external equipment
	in order to measure the signals.
	
	****************************************************************************
	My measurments showed a default speed of between 250KHz and 333KHz
	depending on the pin used - and a library speed of 1.500MHz on every pin.
	   
	This is an improvent of between 6x and 4.5x
	****************************************************************************
	
	ADBeta 10 Nov 2022
*/

#include <chASM.h>

//Declare both pins, one is a chASM pin the other is a built-in pin
#define slowPin 10
chASM fastPin(10);

void setup() {
	//Configure the pin to be an OUTPUT
	fastPin.setMode(OUTPUT);
	
	//Unrolled the loop so speed is more directly comparable per test.	
	//Uncomment the test you wish to test
	while(true) {
		/** Fast pin **/
		/*
		fastPin.write(1);
		fastPin.write(0);
		fastPin.write(1);
		fastPin.write(0);
		fastPin.write(1);
		fastPin.write(0);
		fastPin.write(1);
		fastPin.write(0);
		*/
		
		/** Slow Pin **/
		///*
		digitalWrite(slowPin, HIGH);
		digitalWrite(slowPin, LOW);
		digitalWrite(slowPin, HIGH);
		digitalWrite(slowPin, LOW);
		digitalWrite(slowPin, HIGH);
		digitalWrite(slowPin, LOW);
		digitalWrite(slowPin, HIGH);
		digitalWrite(slowPin, LOW);
		//*/
	}
}

void loop() {
}
