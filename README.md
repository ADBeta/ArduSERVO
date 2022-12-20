# ArduSERVO
<b> (c) ADBeta 2022 </b>

ArduSERVO is an arduino library that allows RC Servo PWM signals to be  
received and decoded into raw values.  
This is useful when using RC Receivers that only support PWM/Servo outputs,  
but you are using a flight controller or other device were raw values would be  
more versatile.  

You can either call a channel object one at a time, or use the overarching  
'ArduSERVO class to create an array of specified size. See Usage for more info.  

The raw output min and max values can be changed via an API call. The default  
values mimic the arduino analogRead() functons - 0 to 1023.  
See Usage for more information.  

This library is a hobby project. I am open to suggestions for upgrades or fixes.  
It also uses chASM, an assembly hardware handler. You may find it useful: [chASM](https://github.com/ADBeta/chASM)

## Usage

## Changelog
* 0.0.1 - Getting basic functionality.  
* 0.1.1 - Added some core features with pre-optimization.  
* 0.2.2 - Removed the 8 channel limit. Working on better API  

--------------------------------------------------------------------------------
This software is under the GPL v3 licence by ADBeta 2022 - 2023. please read the  
LICENCE file
