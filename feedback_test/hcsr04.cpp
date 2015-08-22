/***
 * hcrs04.cpp - Ultrasonic Distance Module Library
 * Written By: Sheldon Will
 * Date: 02/03/14
 * Version: 1.0
 *
 * License: MIT License
 */

//#include "Energia.h"
#include "hcrs04.h"
#include <Arduino.h>

//EBR added null definition
hcrs04::hcrs04()
{
  _trig = 0;
  _echo = 0;
}

hcrs04::hcrs04(uint8_t trig, uint8_t echo)
{
	_trig = trig;
	_echo = echo;
}

void hcrs04::begin()
{
	pinMode(_trig, OUTPUT);
	pinMode(_echo, INPUT);
}

float hcrs04::distance()
{
	return _distance;
}

float hcrs04::read()
{
	//_distance = 0;
	float duration, distance;
	digitalWrite(_trig, LOW);
	delayMicroseconds(2);
	digitalWrite(_trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(_trig, LOW);
	duration = pulseIn(_echo, HIGH);
	distance = (duration/2) / 29.41176;
	return distance;
}
