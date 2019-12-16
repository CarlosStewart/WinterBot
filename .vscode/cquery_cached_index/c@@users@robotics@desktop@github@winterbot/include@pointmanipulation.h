#include "main.h"

#ifndef PointManipulation_H
#define PointManipulation_H
struct PointManipulation : public Point {
  // sets the values for the PointManipulation
  void setPos(QLength t_x, QLength t_y, QAngle t_theta);
  void addPos(QLength t_x, QLength t_y, QAngle t_theta);
};
#endif
