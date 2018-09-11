#ifndef STATE_H_DEFINED
#define STATE_H_DEFINED

/**
 * The amount of distance sensors this robot has.
 */
#define NUM_DISTANCE_SENSORS 3

/**
 * Defines the program state relevant for the robot control mechanism.
 */
class State {

 public:
  State();

  /**
   * Set the distance measured by the sonar with index 'index',
   * to the given 'distance'. Returns true if setting it was successful,
   * false if it was not (for example, if the index was out of bounds).
   */
  bool setDistanceFor(int index, int distance);

  /**
   * Return the distance for the sensor at the given 'index'.
   * If the distance could not be retreived, returns a negative
   * number.
   */
  int getDistanceFor(int index);

  /**
   * Set the distances to the array given, which has to have
   * a size of NUM_DISTANCE_SENSORS or more.
   * The first \NUM_DISTANCE_SENSORS' values are copied.
   */
  void setDistances(int* distances);


  /**
   * Return the array holding the distances as a pointer.
   */
  int* getDistances();

 private:
  int* distances;

};

#endif
