#include "actuator.h"

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
    Omni3WD Omni(&wheel1,&wheel2,&wheel3);

    void setStopSpeed(char state) {
      if (Omni.getCarStat() != state) {
        Omni.setCarSlow2Stop(500);
      }
    }

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
    Omni.PIDEnable(0.26, 0.02, 0, 10);
    // Omni.PIDEnable(0.26, 0, 0, 10);
  }

  void goForward(unsigned int distance) {
    setStopSpeed(Omni3WD::STAT_ADVANCE);
    Omni.setCarAdvance(distance);
  }


  void goLeft(unsigned int distance) {
    setStopSpeed(Omni3WD::STAT_LEFT);
    Omni.setCarLeft(distance);
  }


  void goRight(unsigned int distance) {
    setStopSpeed(Omni3WD::STAT_RIGHT);
    Omni.setCarRight(distance);
  }

  void rotateRight(unsigned int angle) {
    setStopSpeed(Omni3WD::STAT_ROTATERIGHT);
    Omni.setCarRotateRight(angle);
  }

  void stop() {
    Omni.setCarStop();
    // wheel1.setSpeedMMPS(1);
    // wheel2.setSpeedMMPS(1);
    // wheel3.setSpeedMMPS(1);
  }

  void regulatePID() {
    Omni.PIDRegulate();
  }

  unsigned int setWheelSpeed(wheel wheel, unsigned int speed) {
    MotorWheel* instance = getWheel(wheel);
    instance->setSpeedMMPS(speed, DIR_ADVANCE);
    // instance->PIDRegulate();
  }

  void getSpeeds(int* speedArray) {
    speedArray[0] = wheel1.getSpeedMMPS();
    speedArray[1] = wheel2.getSpeedMMPS();
    speedArray[2] = wheel3.getSpeedMMPS();
  }

}
