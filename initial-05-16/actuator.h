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

  void goLeft(unsigned int distance);

  void goRight(unsigned int distance);

  void goForward(unsigned int distance);

  void rotateRight(unsigned int angle);

  unsigned int setWheelSpeed(wheel wheel, unsigned int speed);

  void stop();

  void regulatePID();

  void getSpeeds(int* speedArray);

};

#endif
