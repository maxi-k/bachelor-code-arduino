
#include <IR.h>
#include <SONAR.h>

#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>

#include <fuzzy_table.h>
#include <PID_Beta6.h>

#include <EEPROM.h>

//#define _NAMIKI_MOTOR  //for Namiki 22CL-103501PG80:1

#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>

#include <fuzzy_table.h>
#include <PID_Beta6.h>

#include <MotorWheel.h>


irqISR(irq1,isr1);
MotorWheel wheel1(3,2,4,5,&irq1); // Motor PWM:Pin9, DIR:Pin8,
// Encoder A:Pin6, B:Pin7

void setup() {
  // TCCR1B=TCCR1B&0xf8|0x01; // Pin9,Pin10 PWM 31250Hz, Silent PWM

  //wheel1.PIDEnable(0.31,0.02,0,5);
  wheel1.PIDEnable(KC,TAUI,TAUD,5);

  //wheel1.setSpeedMMPS(100,DIR_BACKOFF);

  Serial.begin(19200);
  //digitalWrite(2, HIGH);
}

void loop() {
  wheel1.setSpeedMMPS(50, DIR_ADVANCE);
  for(int i=0;i<2000;i+=10) {
    wheel1.PIDRegulate();
    delay(10);
  }
  /* Serial.println(wheel1.getCurrPulse(),DEC); */
  /* Serial.println(wheel1.getSpeedMMPS(),DEC); */



  wheel1.setSpeedMMPS(0, DIR_BACKOFF);
  for(int i=0;i<2000;i+=10) {
    wheel1.PIDRegulate();
    delay(10);
  }
  /* Serial.println(wheel1.getCurrPulse(),DEC); */
  /* Serial.println(wheel1.getSpeedMMPS(),DEC); */

}
