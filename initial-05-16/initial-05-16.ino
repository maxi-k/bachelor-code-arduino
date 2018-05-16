#include "sensor.h"
#include "actuator.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WheelDrive.enable();
}

enum direction {
  left = 'a',
  right = 'd',
  forward = 'w',
  stop = 's'
};

unsigned int dist = 50;

void loop() {
  if (Serial.available() > 0) {
    // read incoming serial data:
    char inChar = Serial.read();
    char response;

    switch(inChar) {
    case left:
      WheelDrive.goLeft(dist);
      response = 'l';
      break;
    case right:
      WheelDrive.goRight(dist);
      response = 'r';
      break;
    case forward:
      WheelDrive.goForward(dist);
      response = 'f';
      break;
    case stop:
    default:
      WheelDrive.stop();
      response = 's';
      break;
    }
    Serial.println(response);
  }

}
