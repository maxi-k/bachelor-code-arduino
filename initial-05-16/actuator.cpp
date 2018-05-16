#include "actuator.h"

/**
 *
 * OMNI WHEEL DRIVE
 *
 */



// Define Motors

irqISR(irq1,isr1);
MotorWheel wheel1(9,8,6,7,&irq1);        // Pin9:PWM, Pin8:DIR, Pin6:PhaseA, Pin7:PhaseB

irqISR(irq2,isr2);
MotorWheel wheel2(10,11,14,15,&irq2);    // Pin10:PWM, Pin11:DIR, Pin14:PhaseA, Pin15:PhaseB

irqISR(irq3,isr3);
MotorWheel wheel3(3,2,4,5,&irq3);        // Pin3:PWM, Pin2:DIR, Pin4:PhaseA, Pin5:PhaseB


// Set up Omni wheel drive with those wheels

Omni3WD Omni(&wheel1,&wheel2,&wheel3);

// Implement the Wheel Drive class defined in actuator.h

void WheelDriveClass::setStopSpeed(char state) {
  if (Omni.getCarStat() != state) {
    Omni.setCarSlow2Stop(500);
  }
}

void WheelDriveClass::regulatePID() {
  Omni.PIDRegulate();
}

// API

void WheelDriveClass::enable() {
  Omni.PIDEnable(0.26, 0.02, 0, 10);
}

void WheelDriveClass::goForward(unsigned int distance) {
  setStopSpeed(Omni3WD::STAT_ADVANCE);
  Omni.setCarAdvance(distance);
  regulatePID();
}


void WheelDriveClass::goLeft(unsigned int distance) {
  setStopSpeed(Omni3WD::STAT_LEFT);
  Omni.setCarLeft(distance);
  regulatePID();
}


void WheelDriveClass::goRight(unsigned int distance) {
  setStopSpeed(Omni3WD::STAT_RIGHT);
  Omni.setCarRight(distance);
  regulatePID();
}

void WheelDriveClass::rotateRight(unsigned int angle) {
  setStopSpeed(Omni3WD::STAT_ROTATERIGHT);
  Omni.setCarRotateRight(angle);
  regulatePID();
}

void WheelDriveClass::stop() {
  Omni.setCarStop();
  regulatePID();
}

WheelDriveClass WheelDrive;
