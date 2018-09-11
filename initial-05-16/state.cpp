#include "state.h"

State::State() :
  distances(new int[NUM_DISTANCE_SENSORS]) {
}

bool State::setDistanceFor(int index, int distance) {
  if (index >= 0 && index < NUM_DISTANCE_SENSORS) {
    distances[index] = distance;
    return true;
  }
  return false;
}

int* State::getDistances() {
  return distances;
}

void State::setDistances(int* newDists) {
  for (int i = 0; i < NUM_DISTANCE_SENSORS; i++) {
    distances[i] = newDists[i];
  }
}

int State::getDistanceFor(int index) {
  if (index >= 0 && index < NUM_DISTANCE_SENSORS) {
    return distances[index];
  }
  return -1;
}
