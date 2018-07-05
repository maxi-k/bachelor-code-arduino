#ifndef ACTUATOR_H_DEFINED
#define ACTUATOR_H_DEFINED

#include <MotorWheel.h>
#include <Omni3WD.h>

namespace WheelDrive {

  enum wheel {
    backWheel,
    rightWheel,
    leftWheel
  };

  void setup();

  void setSpeed(wheel wheel, unsigned int speed, bool direction);

  void goLeft(unsigned int distance);

  void goRight(unsigned int distance);

  void goForward(unsigned int distance);

  void rotate(unsigned int speed, bool direction);

  void stop();

  void getSpeeds(int* speedArray);

};

#endif
