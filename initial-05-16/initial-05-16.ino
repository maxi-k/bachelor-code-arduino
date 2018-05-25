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

void commandReceived(int length, char* data) {
  for (int i = 0; i < length; ++i) {
    Serial.print(data[i]);
  }
  Serial.println(' ');
  int* distances = state->getDistances();
  for (int i = 0; i < NUM_DISTANCE_SENSORS; ++i) {
    Serial.print(distances[i]);
    Serial.print(' ');
  }
  Serial.println(' ');
  char inChar = data[0];
  switch(inChar) {
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

void commandSent(int length, char* data) {
  for (int i = 0; i < length; ++i) {
    Serial.print(data[i], DEC);
    Serial.print(' ');
  }
  Serial.println(' ');
}


void setup() {
  int distances[3] = {10, 4, 3};
  state = new State();
  state->setDistances(distances);

  Communicator::setup(state, &commandReceived, &commandSent);
  WheelDrive::setup();

  Serial.begin(9600);
  Serial.println("INT SIZE: ");
  Serial.println(sizeof(int));
  Serial.println("CHAR SIZE: ");
  Serial.println(sizeof(char));
  Serial.println("FLOAT SIZE: ");
  Serial.println(sizeof(float));
  Serial.println("DOUBLE SIZE: ");
  Serial.println(sizeof(double));
  Serial.println("SHORT SIZE: ");
  Serial.println(sizeof(short));
}


void loop() {
  delay(10);
}
