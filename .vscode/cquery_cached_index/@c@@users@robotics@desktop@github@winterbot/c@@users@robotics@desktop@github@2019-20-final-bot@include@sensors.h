#include "main.h"

#ifndef Sensors_H
#define Sensors_H
class Sensors {
public:
  // accessors
  // grouping tracking wheels
  struct Track {
    double getLeft();
    double getRight();
    // double getSide();
  } track;
};
extern Sensors sensors;
#endif
