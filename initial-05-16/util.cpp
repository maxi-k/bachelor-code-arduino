#include "util.h"
#include <Arduino.h>

namespace Util {

  #if ROBOT_CONTROL_DEBUG

  void printDataSizes() {
    Serial.println("CHAR SIZE: ");
    Serial.println(sizeof(char));
    Serial.println("INT SIZE: ");
    Serial.println(sizeof(int));
    Serial.println("BYTE SIZE: ");
    Serial.println(sizeof(byte));
    Serial.println("FLOAT SIZE: ");
    Serial.println(sizeof(float));
    Serial.println("DOUBLE SIZE: ");
    Serial.println(sizeof(double));
    Serial.println("SHORT SIZE: ");
    Serial.println(sizeof(short));
  }

  #endif

}
