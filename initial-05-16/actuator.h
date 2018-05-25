#ifndef ACTUATOR_H_DEFINED
#define ACTUATOR_H_DEFINED

#include <MotorWheel.h>
#include <Omni3WD.h>

namespace WheelDrive {

  void setup();

  void goLeft(unsigned int distance);

  void goRight(unsigned int distance);

  void goForward(unsigned int distance);

  void rotateRight(unsigned int angle);

  void stop();

};

#endif
