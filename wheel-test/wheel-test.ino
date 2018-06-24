#include <MotorWheel.h>
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
}

void testWheel(MotorWheel *wheel) {
  int time = 3000; // 3s
  int pwm1 = 254; // max = 255
  int pwm2 = 32; // max = 255

  wheel->runPWM(pwm1, DIR_ADVANCE);
  delay(time);

  wheel->runPWM(pwm2, DIR_BACKOFF);
  delay(time);

}

void loop() {

  testWheel(&wheel1);

  testWheel(&wheel2);

  testWheel(&wheel3);
}
