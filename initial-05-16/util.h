#ifndef UTIL_H_DEFINED
#define UTIL_H_DEFINED

/**
 * Wheter we are in debug mode.
 * Used in various places to decide
 * whether to print to Serial etc.
 */
// #define ROBOT_CONTROL_DEBUG true

namespace Util {

  #if ROBOT_CONTROL_DEBUG

  /**
   * Print the length of the different
   * data-type sizes on this board to the
   * Serial output (as a multiple of char)
   */
  void printDataSizes();

  #endif

}

#endif
