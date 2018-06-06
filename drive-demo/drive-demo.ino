#include <EEPROM.h>
#include <fuzzy_table.h>
#include <PID_Beta6.h>

#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>

#include <MotorWheel.h>
#include <Omni3WD.h>

irqISR(irq1,isr1);
MotorWheel wheel1(9,8,6,7,&irq1);

irqISR(irq2,isr2);
MotorWheel wheel2(10,11,12,13,&irq2);

irqISR(irq3,isr3);
MotorWheel wheel3(3,2,4,5,&irq3);

Omni3WD Omni(&wheel1,&wheel2,&wheel3);

void setup() {
  TCCR1B=TCCR1B&0xf8|0x01;    // Pin9,Pin10 PWM 31250Hz
  TCCR2B=TCCR2B&0xf8|0x01;    // Pin3,Pin11 PWM 31250Hz

  Omni.PIDEnable(0.26,0.02,0,10);
}
void loop() {

  int speed1 = 50;
  unsigned long now = millis();

  if (now % 7000 == 0) {
    if (Omni.getCarStat() != Omni3WD::STAT_ADVANCE)
      Omni.setCarSlow2Stop(500);
    Omni.setCarAdvance(speed1);
  } else if (now % 3000 == 0)  {
    if (Omni.getCarStat() != Omni3WD::STAT_STOP)
      Omni.setCarSlow2Stop(500);
    // !!!!
    Omni.setCarStop(); // Reverses one wheel instead of stopping all wheels.
    // !!!!
  }
  Omni.PIDRegulate();

}
