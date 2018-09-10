#ifndef SENSOR_H_DEFINED
#define SENDOR_H_DEFINED

#include "state.h"

namespace DistanceSensor {

  enum sonarSensorPosition {
    front,
    left,
    right
  };

  void setup(State *state);

  void update();

  int getDistanceFor(sonarSensorPosition pos);

  int* getDistances();

};

#endif
