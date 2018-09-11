#include "sensor.h"

#include <SONAR.h>
#include "util.h"

#define SONAR_PORT 0x11
#define SONAR_COUNT 3

namespace DistanceSensor {

  namespace {

    unsigned long lastUpdateMillis = 0;

    State* stateRef;

    SONAR sonar11(SONAR_PORT), sonar12(SONAR_PORT + 1), sonar13(SONAR_PORT + 2);
    SONAR sonars[SONAR_COUNT] = { sonar11, sonar12, sonar13 };

    unsigned int sonarToUpdate = 0;

    void getSonarData(State* state) {
      SONAR sonar = sonars[sonarToUpdate];

      // SONAR sonar = sonar11;
      // int sdist = 91;
      unsigned int dist = sonar.getDist();
      int sdist = dist = (int) dist;
      state->setDistanceFor(sonarToUpdate, sdist);

      #if ROBOT_CONTROL_DEBUG
      Serial.print("Distance for Sensor ");
      Serial.print(sonarToUpdate);
      Serial.print(" is ");
      Serial.println(sdist);
      #endif
      sonar.trigger();

      // Serial.print("distance: ");
      // Serial.println((int) dist, DEC);

      sonarToUpdate = (sonarToUpdate + 1) % SONAR_COUNT;
    }
  };

  void setup(State* state) {
    stateRef = state;

    // SONAR::init(SONAR_PORT + SONAR_COUNT - 1, 9600);
  }

  void update() {
    if (millis() - lastUpdateMillis >= SONAR::duration) {
      getSonarData(stateRef);
      lastUpdateMillis = millis();
    }
  }


  int getDistanceFor(sonarSensorPosition pos) {
    return stateRef->getDistanceFor((int) pos);
  }

  int* getDistances() {
    return stateRef->getDistances();
  }

}
