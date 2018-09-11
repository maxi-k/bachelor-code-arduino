#include "actuator.h"
#include "util.h"

// Defined by MotorWheel.h and used here:
// MAX_PWM
// MAX_SPEEDRPM
// DIR_ADVANCE
// DIR_BACKOFF

// TODO: Better distinguish between
// 'absolute' speed :: (unsigned int) and
// 'directional' speed :: (singed int)
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

    /**
     * Get a pointer to a particular wheel instance
     * based on the wheel enum given
     */
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

    #if ROBOT_CONTROL_DEBUG
    void debugCommand(driveCommand dir, int speed) {
      Serial.println("<executing command>");
      switch(dir) {
      case cmdLeft:
        Serial.println("left");
        break;
      case cmdRight:
        Serial.println("right");
        break;
      case cmdForward:
        Serial.println("forward");
        break;
      case cmdRotate:
        Serial.println("rotate");
        break;
      case cmdStop:
        Serial.println("stop");
        break;
      case cmdBackward:
        Serial.println("backward");
        break;
      }
      Serial.println(speed);
      Serial.println("</executing command:>");
    }
    #endif

    /**
     * Convert millimeters per second into rotations per minute
     * for the given wheel
     */
    int mmpsToRPM(MotorWheel *wheel, int speedMMPS) {
      return int(speedMMPS * 60.0 / wheel->getCirMM());
    }

    /**
     * Inverse of mmpsToRPM
     */
    int rpmToMMPS(MotorWheel *wheel, int rpm) {
      return int(rpm * wheel->getCirMM() / 60.0);
    }

    /**
     * Convert rotations per minute into a PWM Signal
     * strength between 0 and MAX_PWM
     */
    int rpmToPWM(unsigned int speedRPM) {
      // Constants defined in MotorWheel
      return map(speedRPM, 0, MAX_SPEEDRPM, 0, MAX_PWM);
    }

    /**
     * Inverse of rpmToPWM
     */
    unsigned int pwmToRPM(unsigned int pwm) {
      return map(pwm, 0, MAX_PWM, 0, MAX_SPEEDRPM);
    }

    void setWheelSpeed(MotorWheel *wheel, unsigned int speedMMPS, bool direction) {
      // int pwm = rpmToPWM(mmpsToRPM(wheel, speedMMPS));
      wheel->runPWM(speedMMPS, direction);
    }

    int getWheelSpeedMMPS(MotorWheel *wheel) {
      return rpmToMMPS(wheel, pwmToRPM(wheel->getPWM()));
    }

  }

  void setup() {
    // setup PWM
    TCCR1B=TCCR1B&0xf8|0x01;    // Pin9,Pin10 PWM 31250Hz
    TCCR2B=TCCR2B&0xf8|0x01;    // Pin3,Pin11 PWM 31250Hz
    // Omni.PIDEnable(0.26, 0.02, 0, 10);
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

  void goBackward(unsigned int distance) {
    setSpeed(rightWheel, distance, DIR_BACKOFF);
    setSpeed(leftWheel, distance, DIR_ADVANCE);
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
    speedArray[0] = getWheelSpeedMMPS(&wheel1);
    speedArray[1] = getWheelSpeedMMPS(&wheel2);
    speedArray[2] = getWheelSpeedMMPS(&wheel3);
  }

  void execCommand(driveCommand dir, int speed) {
    #if ROBOT_CONTROL_DEBUG
    debugCommand(dir, speed);
    #else
    switch(dir) {
    case cmdLeft:
      goLeft(speed);
      return;
    case cmdRight:
      goRight(speed);
      return;
    case cmdForward:
      goForward(speed);
      return;
    case cmdRotate:
      rotate(speed, true);
      return;
    case cmdStop:
      stop();
      return;
    case cmdBackward:
      goBackward(speed);
      return;
    }
    #endif
  }

}
