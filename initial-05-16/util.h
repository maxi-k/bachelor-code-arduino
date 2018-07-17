#ifndef UTIL_H_DEFINED
#define UTIL_H_DEFINED

/**
 * Wheter we are in debug mode.
 * Used in various places to decide
 * whether to print to Serial etc.
 */
#define DEBUG true

namespace Util {

  #if DEBUG

  void printDataSizes();

  #endif

}

#endif
