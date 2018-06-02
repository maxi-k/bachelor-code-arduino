#include "sensor.h"
#include "actuator.h"
#include "communication.h"
#include "state.h"

enum direction {
  left = 'a',
  right = 'd',
  forward = 'w',
  stop = 's'
};

State* state;
unsigned int dist = 50;

void commandReceived(int length, byte* data) {
  byte inByte = data[0];
  switch(inByte) {
  case left:
    WheelDrive::goLeft(dist);
    break;
  case right:
    WheelDrive::goRight(dist);
    break;
  case forward:
    WheelDrive::goForward(dist);
    break;
  case stop:
  default:
    WheelDrive::stop();
    break;
  }
}

void commandSent(int length, byte* data) {
  // do nothing
}


void setup() {
  state = new State();

  Communicator::setup(state, &commandReceived, &commandSent);
  WheelDrive::setup();

  Serial.begin(9600);
  /* Serial.println("INT SIZE: "); */
  /* Serial.println(sizeof(int)); */
  /* Serial.println("BYTE SIZE: "); */
  /* Serial.println(sizeof(byte)); */
  /* Serial.println("FLOAT SIZE: "); */
  /* Serial.println(sizeof(float)); */
  /* Serial.println("DOUBLE SIZE: "); */
  /* Serial.println(sizeof(double)); */
  /* Serial.println("SHORT SIZE: "); */
  /* Serial.println(sizeof(short)); */
}


void loop() {
  for (int i = 0; i < NUM_DISTANCE_SENSORS; ++i) {
    state->setDistanceFor(i, random(0, 1370));
  }
}
