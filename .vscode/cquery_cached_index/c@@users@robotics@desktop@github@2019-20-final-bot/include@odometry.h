#include "main.h"

#ifndef Odometry_H
#define Odometry_H
class Odometry {
  // constants
  const double sL = 6.0;
  const double sR = 6.0;
  const double sS = 6.0;
  const double TRACK_DIAMETER_IN = 2.75;
  const double TRACK_TO_IN = 0.01;
  // variables for iterate()
  double prevLeft, prevRight, prevSide;
  double left, right, side;
  // PointManipulation object that represents location
  PointManipulation location;

public:
  // default constructor that starts the robot at (0, 0, 0)
  Odometry();

  // overload constructor that accounts for the starting position of the robot
  Odometry(PointManipulation tStart);

  // accessors
  PointManipulation get();

  // iterates the position tracking algorithm
  void iterate();
};
extern Odometry odom;
#endif
