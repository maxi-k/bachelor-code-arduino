#include "actuator.h"

// Defined by MotorWheel.h and used here:
// MAX_PWM
// DIR_ADVANCE
// DIR_BACKOFF

namespace WheelDrive {

  /**
   * Anonymous inner namespace for namespace-private variables and functions
   */
  namespace {
    // Pin9:PWM, Pin8:DIR, Pin6:PhaseA, Pin7:PhaseB
    irqISR(irq1,isr1);
    MotorWheel wheel1(9,8,6,7,&irq1);

    // Pin10:PWM, Pin11:DIR, Pin14:PhaseA, Pin15:PhaseB
    irqISR(irq2,isr2);
    MotorWheel wheel2(10,11,14,15,&irq2);

    // Pin3:PWM, Pin2:DIR, Pin4:PhaseA, Pin5:PhaseB
    irqISR(irq3,isr3);
    MotorWheel wheel3(3,2,4,5,&irq3);

    // Set up Omni wheel drive with those wheels
    // Omni3WD Omni(&wheel1,&wheel2,&wheel3);

    MotorWheel* getWheel(wheel w) {
      switch(w) {
      case backWheel:
        return &wheel1;
      case rightWheel:
        return &wheel2;
      case leftWheel:
        return &wheel3;
      }
    }
  }

  void setup() {
    TCCR1B=TCCR1B&0xf8|0x01;    // Pin9,Pin10 PWM 31250Hz
    TCCR2B=TCCR2B&0xf8|0x01;    // Pin3,Pin11 PWM 31250Hz
    // Omni.PIDEnable(0.26, 0.02, 0, 10);
  }

  int mmpsToRPM(MotorWheel *wheel, int speedMMPS) {
    return int(speedMMPS * 60.0 / wheel->getCirMM());
  }

  int rpmToPWM(unsigned int speedRPM) {
    // Constants defined in MotorWheel
    return map(speedRPM, 0, MAX_SPEEDRPM, 0, MAX_PWM);
  }

  void setWheelSpeed(MotorWheel *wheel, unsigned int speedMMPS, bool direction) {
    // int pwm = rpmToPWM(mmpsToRPM(wheel, speedMMPS));
    wheel->runPWM(speedMMPS, direction);
  }

  void setSpeed(wheel which, unsigned int speedMMPS, bool direction) {
    setWheelSpeed(getWheel(which), speedMMPS, direction);
  }

  void rotate(unsigned int angle, bool direction) {
    setSpeed(leftWheel, angle, direction);
    setSpeed(rightWheel, angle, direction);
    setSpeed(backWheel, angle, direction);
  }

  void goForward(unsigned int distance) {
    setSpeed(rightWheel, distance, DIR_ADVANCE);
    setSpeed(leftWheel, distance, DIR_BACKOFF);
  }

  void goLeft(unsigned int distance) {
    setSpeed(rightWheel, distance, DIR_ADVANCE);
    setSpeed(backWheel, distance, DIR_BACKOFF);
  }

  void goRight(unsigned int distance) {
    setSpeed(leftWheel, distance, DIR_ADVANCE);
    setSpeed(backWheel, distance, DIR_BACKOFF);
  }

  void stop() {
    setSpeed(leftWheel, 0, DIR_ADVANCE);
    setSpeed(rightWheel, 0, DIR_ADVANCE);
    setSpeed(backWheel, 0, DIR_ADVANCE);
  }

  void getSpeeds(int* speedArray) {
    speedArray[0] = wheel1.getPWM();
    speedArray[1] = wheel2.getPWM();
    speedArray[2] = wheel3.getPWM();
  }

}
