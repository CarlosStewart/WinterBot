#ifndef TRAY_H
#define TRAY_H
#include "main.h"
class Tray {
  state_tray state;
  state_tray lastState;
  const double brakeVelRange = 20.0;

public:
  // "default" constructor
  Tray();

  // enables the controller
  void enable();
  // disables the controller
  void disable();

  // sets the controller to 0
  void setBottom();
  // sets the target height of the controller
  void setTarget(heights_tray tHeight);
  void setTarget(double tHeight);
  // returns the target height of the tray
  double getTarget();
  // returns the current location of the controller
  double getLocation();
  // returns whether or not the tray should be going slow
  bool isInSlowZone();
  // sets the maximum speed of the controller
  void limitSpeedTo(double tMaxSpeed);
  // returns whether or not the controller has settled
  bool controllerSettled();
  // returns the error of the controller
  double controllerGetError();
  // stops the thread until the controller has settled
  void pauseUntilSettled();

  // state Control
  // sets the state
  void setState(state_tray tState);
  // returns the state
  state_tray getState();
};
extern Tray tray;
#endif
