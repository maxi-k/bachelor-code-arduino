#include "sensor.h"
#include "actuator.h"
#include "communication.h"
#include "state.h"

State* state;
int cmdLength = Communicator::MAX_REQUEST_LENGTH;
byte* cmd = new byte[Communicator::MAX_REQUEST_LENGTH];
bool received = false;

void execCommand() {
  if (!received) {
    return;
  }
  char flag = cmd[0];
  /* Serial.write(cmd, cmdLength); */
  /* Serial.println("----------"); */
  switch(flag) {
  case Communicator::msgDistData:
    // this is the flag used to send distance data back,
    // so it should never be received.
    /* Serial.println("Message dist data command!"); */
    break;
  case Communicator::cmdUpdate:
    // update is sent automatically by communication namespace
    /* Serial.println("Update command!"); */
    break;
  case Communicator::cmdSpeed: {
    char dir = cmd[1];
    byte speed = cmd[2];
    /* Serial.println("Wheel drive!"); */
    WheelDrive::execCommand((WheelDrive::driveCommand) dir, speed);
    break;
  }
  default:
    /* Serial.println("Command could not be interpreted!"); */
    break;
  }
  received = false;
}

void commandReceived(int length, byte* data) {
  // copy data to received buffer
  /* Serial.println("Received message!"); */
  int commonLength = min(length, Communicator::MAX_REQUEST_LENGTH);
  for(int i = 0; i < commonLength; ++i) {
    cmd[i] = data[i];
  }
  cmdLength = commonLength;
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
  for (int i = 0; i < NUM_DISTANCE_SENSORS; ++i) {
    state->setDistanceFor(i, random(0, 1370));
  }

  execCommand();

  /* if (loopCnt == 400) { */
  /*   Serial.println("loop"); */
  /* } */

  /* Serial.println(loopCnt); */
  WheelDrive::getSpeeds(state->getDistances());
  loopCnt = (loopCnt + 1) % 500;
}
