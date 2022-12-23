#include <ArduSERVO.h>

#include "ArduSERVO.h"

ArduSERVO chan1;
ArduSERVO chan2;

void setup() {
	Serial.begin(9600);

	//Define which pins the ArduSERVO Channels use.
	chan1.setPin(8);
	chan2.setPin(9);
	
	//For demo purposes, disable the deadzones for endstops and centre for chanel 1.
	chan1.setDeadzones(false, false);

}

void loop() {
	//Print channel 1 as raw pulseMicros
	Serial.print("Channel 1: ");
	Serial.println(chan1.getPulseMicros());

	//Print channel 2 as a mapped value range
	Serial.print("Channel 2: ");
	Serial.println(chan2.mapMicrosToRange(chan2.getPulseMicros()));
	
	//Blank line
	Serial.println();

	delay(500);
}
