#include "main.h"

void PointManipulation::setPos(QLength t_x, QLength t_y, QAngle t_theta) {
  x = t_x;
  y = t_y;
  theta = t_theta;
}

void PointManipulation::addPos(QLength t_x, QLength t_y, QAngle t_theta) {
  x += t_x;
  y += t_y;
  theta += t_theta;
}
