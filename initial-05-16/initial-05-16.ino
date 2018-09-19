#include "util.h"
#include "sensor.h"
#include "actuator.h"
#include "communication.h"
#include "state.h"

/**
 * Holds all relevant state of the Robot Control Program,
 * Does not contain irrelevant (internal) state or
 * messaging state (like the last received message).
 * This is initialized in the setup function.
 */
State* state;

/**
 * The length of the last received command.
 * Actual size of the array 'cmd' may be larger,
 * but never smaller.
 */
int cmdLength = Communicator::MAX_REQUEST_LENGTH;
/**
 * Buffer for the last received message.
 */
byte* cmd = new byte[Communicator::MAX_REQUEST_LENGTH];

/**
 * Stores whether a command was received that has not been
 * executed yet.
 */
bool received = false;

/**
 * Execute the command stored in the 'cmd' array.
 * After execution, set the 'received' flag to false,
 * as the command was executed.
 */
void execCommand() {
  if (!received) {
    return;
  }
  char flag = cmd[0];
  #if ROBOT_CONTROL_DEBUG
    Serial.write(cmd, cmdLength);
    Serial.println("");
    Serial.println("----------");
  #endif
  switch(flag) {
  case Communicator::msgDistData:
    break;
  case Communicator::cmdUpdate:
    break;
  case Communicator::cmdSpeed: {
    char dir = cmd[1];
    byte speed_low = cmd[2];
    byte speed_high = cmd[3];
    int speed = speed_low * 256 + speed_high;
    WheelDrive::execCommand((WheelDrive::driveCommand) dir, speed);
    break;
  }
  default:
    #if ROBOT_CONTROL_DEBUG
      Serial.println("Command could not be interpreted!");
    #endif
    break;
  }
  received = false;
}

/**
 * Callback for when a message is received.
 * Stores the received message in the 'cmd' buffer,
 * and sets the 'received' flag to true.
 */
void commandReceived(int length, byte* data) {
  #if ROBOT_CONTROL_DEBUG
    Serial.print("Request length: ");
    Serial.println(length);
  #endif
  int commonLength = min(length, Communicator::MAX_REQUEST_LENGTH);
  for(int i = 0; i < commonLength; ++i) {
    cmd[i] = data[i];
  }
  cmdLength = commonLength;
  received = true;
}

/**
 * Callback for when a message was sent back to the controller.
 * Currently does nothing.
 */
void commandSent(int length, byte* data) {
  // do nothing
}

/**
 * Gets called by the arduino for initial setup.
 * Initialize all state variables, the communication with the controller,
 * as well as the sensors and actuators.
 */
void setup() {
  state = new State();

  Communicator::setup(state, &commandReceived, &commandSent);
  WheelDrive::setup();

  #if ROBOT_CONTROL_DEBUG
    Serial.begin(9600);
    Util::printDataSizes();
  #endif

  DistanceSensor::setup(state);
}


/**
 * Gets called by the arduino over and over ('main loop').
 * Updates state variables and handles any commands received
 * from the controller in the meantime.
 */
void loop() {
  execCommand();
  DistanceSensor::update();
}
