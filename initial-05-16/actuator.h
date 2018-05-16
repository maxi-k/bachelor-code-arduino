#ifndef ACTUATOR_H_DEFINED
#define ACTUATOR_H_DEFINED

#include <MotorWheel.h>
#include <Omni3WD.h>

class WheelDriveClass {

 public:
  void enable();

  void goLeft(unsigned int distance);

  void goRight(unsigned int distance);

  void goForward(unsigned int distance);

  void rotateRight(unsigned int angle);

  void stop();

 private:
  void setStopSpeed(char state);

  void regulatePID();

};

extern WheelDriveClass WheelDrive;

#endif
