#include <chASM.h>

//Define a chASM Pin, Pin 13 aka the LED pin
chASM LED_PIN(13);

void setup() {
	//Set the pin to output
	LED_PIN.setMode(OUTPUT);
}

void loop() {
	//Write LED HIGH, then wait
	LED_PIN.write(1);
	delay(1000);
	
	//Write LED LOW, then wait
	LED_PIN.write(0);
	delay(1000);
}
