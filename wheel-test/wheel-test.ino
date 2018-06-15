#include <MotorWheel.h>
#include <PID_Beta6.h>
#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>


/* irqISR(irq1,isr1); */
/* MotorWheel wheel1(9,8,6,7,&irq1); */

/* irqISR(irq2,isr2); */
/* MotorWheel wheel2(10,11,12,13,&irq2); */

irqISR(irq3,isr3);
MotorWheel wheel1(3,2,4,5,&irq3);


void setup() {
  TCCR1B=TCCR1B&0xf8|0x01;    // Pin9,Pin10 PWM 31250Hz
  TCCR2B=TCCR2B&0xf8|0x01;    // Pin3,Pin11 PWM 31250Hz
  wheel1.PIDEnable(0.26, 0.02, 0, 10);
}

void loop() {
  wheel1.setSpeedMMPS(40, DIR_ADVANCE);

  for(int i=0;i<1000;++i) {
    wheel1.PIDRegulate();
    delay(10);
  }
  delay(1000);

  wheel1.setSpeedMMPS(80, DIR_ADVANCE);

  for(int i=0;i<1000;++i) {
    wheel1.PIDRegulate();
    delay(10);
  }
  delay(1000);

  wheel1.setSpeedMMPS(0);

  for(int i=0;i<1000;++i) {
    wheel1.PIDRegulate();
    delay(10);
  }
  delay(1000);
}
