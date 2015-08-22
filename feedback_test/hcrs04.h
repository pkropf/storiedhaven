/***
 * hcrs04.h - Ultrasonic Distance Module Library
 * Written By: Sheldon Will
 * Date: 02/03/14
 * Version: 1.0
 *
 * License: MIT License
 */

#ifndef hcrs04_h
#define hcrs04_h

//#include "Energia.h"
#include <Arduino.h>

class hcrs04
{
public:
  hcrs04(); //EBR added null definition
	hcrs04(uint8_t trig, uint8_t echo);
	void begin();
	float read();
	float distance();

private:
	uint8_t _trig;
	uint8_t _echo;
	float _distance;
};

#endif
