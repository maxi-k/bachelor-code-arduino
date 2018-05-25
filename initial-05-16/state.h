#ifndef STATE_H_DEFINED
#define STATE_H_DEFINED

#define NUM_DISTANCE_SENSORS 3

class State {

 public:
  State();

  bool setDistanceFor(unsigned int index, int distance);

  int getDistanceFor(unsigned int index);

  void setDistances(int* distances);

  int* getDistances();


 private:
  int* distances;

};

#endif
