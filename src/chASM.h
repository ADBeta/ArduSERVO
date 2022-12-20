/*
	chASM - control hardware /with/ ASM
	Low level hardware functions using Direct Port Manipulation for max speed.
	The safety features of the arduino system calls are abandoned for speed too.
	Please read the README.md file for more information
	
	**** If this library is in use within another project, please see the
	original github page: https://github.com/ADBeta/chASM
	
	//TODO Add usage to readme
	//TODO Add timer control? (at least kill timer?)
	
	Version 3.1.4
	Last Modified 10 Nov 2022
	(c) ADBeta
*/

#ifndef chASM_H
#define chASM_H

#include <Arduino.h>

//Each pin is treated as an object, this is so each function call doesn't need
//to initialise the ports and bit position per call. do it once per construction
class chASM {
	public:
	/*** Constructor for the object. Pass the arduino pin to be used **********/
	chASM(uint8_t pin);
	
	/*** Simple input/output functions ****************************************/
	//Writes a binary state to the pin
	void write(bool state);
	//Reads and returns a binary state from the pin
	bool read(void);
	
	/*** Pin Mode Register functions ******************************************/
	//Use existing INPUT/OUTPUT/INPUT_PULLUP defines
	//Set the mode register of the pin
	void setMode(uint8_t mode);
	
	private:
	/* Note: Removing the bitwise inversion during exec is faster, so I define
	variables for pre-computing those numbers */
	uint8_t _asm_mask_nom; //Bitmask of the chASM pin - Normal form, eg 00010
	uint8_t _asm_mask_inv; //Bitmask inverted eg 11101
	
	uint8_t _asm_port; //Which hardware port the pin belongs to
	
	volatile uint8_t *_asm_ddr; //Data Direction Register (for input/output)
	volatile uint8_t *_asm_opr; //Output register for the pin
	volatile uint8_t *_asm_ipr; //Input register for the pin
}; //class chASM

#endif
