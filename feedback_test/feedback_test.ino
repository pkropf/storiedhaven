/*** working prototype of sensor reading with "motor" output (LED brightness
as a function of proximity to sensor)

TBD:
~smoothed state of each proximity sensor with slowly decaying memory
~function to convert d(proximity) into appropriate motor behavior
~sleep mode: when d(proximity) is near zero over time, motors should burst at periodic intervals
  with fibonacci seq (or similar) durations between bursts, up to some point at which the motors sleep
  until next perturbation, ie when d(proximity) surpasses some threshold
*/

#include "hcrs04.h"
#include <Arduino.h>

int trig[] = {3, 5, 7};
int echo[] = {4, 6, 8};
int motor[] = {10, 11, 12}; //make sure these pins have the ~ symbol for PWM
float distance[] = {0.0, 0.0, 0.0};
hcrs04 sensors[3]; 

void setup() {
  int i;
  
  //initialize each sensor and motor
  for (i = 0; i < 3; i = i + 1) {
    sensors[i] = hcrs04(trig[i], echo[i]);
    sensors[i].begin();
    pinMode(motor[i], OUTPUT); 
  }
//  Serial.begin(115200);

}

void loop() {
  int i;

  //check the state of each sensor and update motor accordingly
  for (i = 0; i < 3; i = i + 1) {
    distance[i] = sensors[i].read();
    
    //I used this to control LED brightness via PWM, probably needs work to be more appropriate for motor
    if (distance[i] < 50) {
      analogWrite(motor[i], 255-int(distance[i])*5);
    }
    else
    {
      analogWrite(motor[i],0);
    }
  }
  
//  Serial.print(String(distance[0]) +"; " + String(distance[1]));
//  Serial.println(" cm");
  
  //some minimum buffering, may not be necessary when not doing serial monitor
  delay(10);  

}
