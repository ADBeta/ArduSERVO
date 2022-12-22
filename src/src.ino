//Testing ino

#include "ArduSERVO.h"

//ArduSERVO srv(8);
Channel chan;

void setup() {

	Serial.begin(9600);

	chan.setPin(10);
	
	
	//srv.setChannelPin(0, 8);
	//chan.setDeadzones(false, true);

}

void loop() {
	// sense - no deadzone:	19,700
	// sense - deadzone:	19,700 
	// fail - no deadzone:	20,020
	// fail - deadzone:		20,020 (20mic added)
	
	//sense with flat return: 
	/*
	static uint32_t sMicros, eMicros, delta;
	static uint32_t minD = 999999;
	
	sMicros = micros();
	chan.getPulseMicros();
	eMicros = micros();
	
	delta = eMicros - sMicros;
	Serial.println(delta);
	*/
	delay(100);
	Serial.println(chan.mapMicrosToRange(chan.getPulseMicros()));
}
