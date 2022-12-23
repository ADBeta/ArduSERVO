# ArduSERVO
<b> (c) ADBeta 2022 - 2023 </b>

This library depends on chASM. please find and install it here: [chASM](https://github.com/ADBeta/chASM)  

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

## Usage
To declare an ArduSERVO object.  
`ArduSERVO channel;`  

To set the pin that object should use.  
`channel.setPin( pin );`  

To change the minimum and maximum range to re-map the pulse values to.  
This means you can get values between 0-255, or -255 to 255 for example.
`channel.setMapMinMax(min, max);`  

To enable or disable deadzones. These are useful because the RC Controller has  
deadzones on the sticks, switches and pots to stop jitter, but this is lost over  
the Servo PWM transission due to error, noise and jitter. The demo example shows  
how these settings can be useful. (Is on by default)  
`channel.setDeadzones(endstop, centre);`  

To detect and return the microseconds of the Servo pulse, which will also perform  
deadzone snapping if enabled. This is the fastest way to get data and use it,  
but it outputs 1000 to 2000 so mapping to a range can be useful, see below.  
`channel.getPulseMicros(); //Returns int16_t`  

You can pass the value of getPulseMicros() to map them onto a range that you can  
redefine, see setMapMinMax(). This uses floating point arithmatic, and can slow  
down execution. Default map range is 0-1023 which mimics Arduino analogRead()  
`mapMicrosToRange( pulseMicros ); //Returns int16_t`  

## TODO
* Investiate why every call to getPulseMicros is exactly the same exec time.  
* Make a general user class that allows for a simple array of channels to be  
used and configured.  
* Make the map function not use float artihmetic.  

## Changelog
* 0.0.1 - Getting basic functionality.  
* 0.1.1 - Added some core features with pre-optimization.  
* 0.2.2 - Removed the 8 channel limit. Working on better API  
* 0.2.5 - Fixed an inverted value bug. Finished the pulse detection function.  
* 0.2.6 - Added a deadzone function.  
* 0.2.8 - Rolled deadzone into getPulse, and made it selectable.  
* 0.2.10 - Split deadzones, so endstop and middle deadzones can be independantly  
selected.  
* 0.3.10 - Added a function to map the pulseMicros to a defined range.  
* 1.3.10 - More or less fully functioning initial release.  
* 1.4.10 - chASM pin definition used the same RAM for every channel. Fixed by  
asigning pins via new and heap. Forces unique RAM asign.  

--------------------------------------------------------------------------------
This software is under the GPL v3 licence by ADBeta 2022 - 2023. please read the  
LICENCE file
