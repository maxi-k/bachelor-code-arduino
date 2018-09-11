#include "sensor.h"

#include <SONAR.h>
#include "util.h"

#define SONAR_PORT 11
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

      // Serial.print("SONAR TO UPDATE: ");
      // Serial.println(sonarToUpdate);

      unsigned short dist = sonar.getDist();
      state->setDistanceFor(sonarToUpdate, (int) dist);
      sonar.trigger();
      sonar.showDat();

      // Serial.print("distance: ");
      // Serial.println((int) dist, DEC);

      sonarToUpdate = (sonarToUpdate + 1) % SONAR_COUNT;
    }
  };

  void setup(State* state) {
    stateRef = state;

    // SONARAR(SONAR_PORT + SONAR_COUNT - 1);
    SONAR::init(SONAR_PORT + SONAR_COUNT - 1);
  }

  void update() {
    unsigned long curTime = millis();

    if (curTime - lastUpdateMillis >= SONAR::duration) {
      getSonarData(stateRef);
      lastUpdateMillis = curTime;
    }
  }


  int getDistanceFor(sonarSensorPosition pos) {
    return stateRef->getDistanceFor((int) pos);
  }

  int* getDistances() {
    return stateRef->getDistances();
  }

}
