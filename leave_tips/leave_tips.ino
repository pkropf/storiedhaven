/*
  The MIT License (MIT)

  Copyright (c) 2015 Peter Kropf

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

/*
  leave_tips
  turns LEDs on and off following a randomly timed pattern.
 */


const int mLed = 13;       // status led to monitor state changes
unsigned long mTimer = 0;  // time till turning off status led
const int mDuration = 250; // miliseconds to flash status led when state changes

const int led_count = 6;   // number of leds to drive
const int min_on = 1000;   // minimum milliseconds an led can be on / off
const int max_on = 5000;   // maximum milliseconds an led can be on / off

int led[led_count] = {3, 4, 5, 6, 9, 10};
int state[led_count] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
unsigned long timer[led_count] = {0, 0, 0, 0, 0, 0};


void setup() {
  unsigned long now = millis();

  randomSeed(analogRead(0));

  pinMode(mLed, OUTPUT);

  for (int x = 0; x < led_count; x++) {
    pinMode(led[x], OUTPUT);                    // set led pin to output
    digitalWrite(led[x], HIGH);                 // set led pin high (led on)
    timer[x] = now + random(min_on, max_on); // set time when the led is to be turned off
  }
}


void loop() {
  unsigned long now = millis();

  for (int x = 0; x < led_count; x++) {
    if (timer[x] < now) {
      state[x] = ~state[x];
      digitalWrite(led[x], state[x]);
      timer[x] = now + random(min_on, max_on);

      if (mTimer < now) {
        digitalWrite(mLed, HIGH);
        mTimer = now + mDuration;
      }
    }
  }

  if (mTimer < now) {
    digitalWrite(mLed, LOW);
  }
}

