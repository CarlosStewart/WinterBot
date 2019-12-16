#include "main.h"

// default constructor
Odometry::Odometry() {
  // variables for iterate()
  double prevLeft, prevRight, prevSide = 0;
  double left, right, side = 0;
  location.setPos(0_in, 0_in, 0_deg);
}

// overload constructor that accounts for the starting position of the robot
Odometry::Odometry(PointManipulation tStart) {
  // variables for iterate()
  double prevLeft, prevRight, prevSide = 0.0;
  double left, right, side = 0.0;
  location.setPos(tStart.x, tStart.y, tStart.theta);
}

// accessors
PointManipulation Odometry::get() { return location; }

// iterates the position tracking algorithm
void Odometry::iterate() {
  // updates recent wheel change in distance
  left = (sensors.track.getLeft() - prevLeft) * TRACK_DIAMETER_IN / 360.0;
  right = (sensors.track.getRight() - prevRight) * TRACK_DIAMETER_IN / 360.0;
  side = (sensors.track.getSide() - prevSide) * TRACK_DIAMETER_IN / 360.0;

  // stores the last encoder values for the next cycle
  prevLeft = sensors.track.getLeft();
  prevRight = sensors.track.getRight();
  prevSide = sensors.track.getSide();

  double c;                              // chord based on right track
  double i;                              // half of angle change
  double c2;                             // chord based on side track
  double t = (left - right) / (sL + sR); // updates angle change (radians)
  if (t) {
    double r = right / t; // radius of the right side arc
    i = t / 2.0;
    double sinI = sin(i);
    c = ((r + sR) * sinI) * 2.0;

    double r2 = side / t;
    c2 = ((r2 + sS) * sinI) * 2.0;
  } else {
    c = right;
    i = 0.0;
    c2 = side;
  }

  double m = i + location.theta.convert(radian);
  double cosM = cos(m);
  double sinM = sin(m);

  location.addPos(c * sinM * inch, c * cosM * inch, 0_rad);
  location.addPos(c2 * cosM * inch, c2 * -sinM * inch, t * radian);
}

Odometry odom(PointManipulation{0_in, 0_in, 0_deg});
