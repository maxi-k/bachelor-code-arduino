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
unsigned int dist = 70;
byte cmd = 0;
bool received = false;

void execCommand() {
  if (!received) {
    return;
  }
  switch(cmd) {
  case left:
    WheelDrive::goLeft(dist);
    /* WheelDrive::setWheelSpeed(WheelDrive::leftWheel, dist); */
    return;
  case right:
    WheelDrive::goRight(dist);
    /* WheelDrive::setWheelSpeed(WheelDrive::rightWheel, dist); */
    return;
  case forward:
    WheelDrive::goForward(dist);
    /* WheelDrive::setWheelSpeed(WheelDrive::backWheel, dist); */
    return;
  case stop:
    WheelDrive::stop();
    return;
  }
  received = false;
}

void commandReceived(int length, byte* data) {
  byte inByte = data[0];
  cmd = inByte;
  received = true;
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


int loopCnt = 0;
void loop() {
  /* for (int i = 0; i < NUM_DISTANCE_SENSORS; ++i) { */
  /*   state->setDistanceFor(i, random(0, 1370)); */
  /* } */

  if (loopCnt == 0)
  {
    if (cmd == 's')
      cmd = 'w';
    else
      cmd = 's';
    received = true;
    execCommand();
  }
  Serial.println(loopCnt);
  WheelDrive::regulatePID();
  WheelDrive::getSpeeds(state->getDistances());
  loopCnt = (loopCnt + 1) % 500;
}
