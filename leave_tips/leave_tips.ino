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

