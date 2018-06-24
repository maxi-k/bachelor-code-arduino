#include <MotorWheel.h>
#include <PID_Beta6.h>
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>

irqISR(irq1,isr1);
MotorWheel wheel1(9,8,6,7,&irq1);        // Pin9:PWM, Pin8:DIR, Pin6:PhaseA, Pin7:PhaseB

irqISR(irq2,isr2);
MotorWheel wheel2(10,11,14,15,&irq2);    // Pin10:PWM, Pin11:DIR, Pin14:PhaseA, Pin15:PhaseB

irqISR(irq3,isr3);
MotorWheel wheel3(3,2,4,5,&irq3);        // Pin3:PWM, Pin2:DIR, Pin4:PhaseA, Pin5:PhaseB


void setup() {
  TCCR1B=TCCR1B&0xf8|0x01;    // Pin9,Pin10 PWM 31250Hz
  TCCR2B=TCCR2B&0xf8|0x01;    // Pin3,Pin11 PWM 31250Hz

  float p = 0.26;
  float i = 0.02;
  float d = 0;
  int time = 10;

  wheel1.PIDEnable(p, i, d, time);
  wheel2.PIDEnable(p, i, d, time);
  wheel3.PIDEnable(p, i, d, time);

  wheel3.setSpeedMMPS(20, DIR_ADVANCE);
}

void testWheel(MotorWheel *wheel) {
  int times = 100;
  int step = 10;
  int timeout = 500;
  int speed = 10;

  /* wheel->setSpeedMMPS(speed, DIR_ADVANCE); */

  for(int i=0;i<times;++i) {
    wheel->PIDRegulate(true);
    delay(step);
  }
  delay(timeout);

  /* wheel->setSpeedMMPS(0, DIR_ADVANCE); */
  wheel->setSpeedRPM(0, DIR_ADVANCE);
  wheel->runPWM(0, false, false);

  for(int i=0;i<times;++i) {
    wheel->PIDRegulate(true);
    delay(step);
  }
  delay(timeout);

}

void loop() {
  int timeout = 500;

  /* testWheel(&wheel1); */
  /* delay(timeout); */

  /* testWheel(&wheel2); */
  /* delay(timeout); */

  testWheel(&wheel3);
  delay(timeout);
}
