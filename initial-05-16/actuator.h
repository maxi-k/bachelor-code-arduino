#ifndef ACTUATOR_H_DEFINED
#define ACTUATOR_H_DEFINED

#include <MotorWheel.h>
#include <Omni3WD.h>

namespace WheelDrive {

  /**
   * Enum abstracting from a particular wheel instance
   * to a nominator for the three wheels built into the robot.
   */
  enum wheel {
    backWheel,
    rightWheel,
    leftWheel
  };

  /**
   * Enum listing all possible drive commands / directions
   * this can handle.
   */
  enum driveCommand {
    cmdLeft = 'a',
    cmdRight = 'd',
    cmdForward = 'w',
    cmdStop = 's',
    cmdRotate = 'r'
  };

  /**
   * Set up the WheelDrive initially
   */
  void setup();

  /**
   * Set the speed for the given 'wheel' to the given 'speed' with
   * the given 'direction'.
   * The speed is given as millimeters per second (MMPS).
   */
  void setSpeed(wheel wheel, unsigned int speed, bool direction);

  /**
   * Set the wheel speeds and directions so that the robot moves left
   * with the given 'speed' (in MMPS).
   */
  void goLeft(unsigned int speed);

  /**
   * Set the wheel speeds and directions so that the robot moves right
   * with the given 'speed' (in MMPS).
   */
  void goRight(unsigned int speed);

  /**
   * Set the wheel speeds and directions so that the robot moves forward
   * with the given 'speed' (in MMPS).
   */
  void goForward(unsigned int speed);

  /**
   * Set the wheel speeds and directions so that the robot rotates
   * with the given 'speed' (in MMPS), that is, each wheel moves
   * with the given speed.
   */
  void rotate(unsigned int speed, bool direction);

  /**
   * Cease all motor functions!
   */
  void stop();

  /**
   * Fill the given array with the current wheel speeds
   * in MMPS, in the order as defined by the wheel enum.
   */
  void getSpeeds(int* speedArray);

  /**
   * Execute the given command defined by the 'driveCommand' enum
   * with the given speed (in MMPS).
   */
  void execCommand(driveCommand dir, int speed);

};

#endif
