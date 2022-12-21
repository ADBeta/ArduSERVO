//Testing ino

#include "ArduSERVO.h"

//ArduSERVO srv(8);
Channel chan;

void setup() {

	Serial.begin(9600);

	chan.setPin(10);
	
	
	//srv.setChannelPin(0, 8);

}

void loop() {
	Serial.println(chan.pulseDeadzone(chan.getPulseMicros()));
}
