#ifndef TRAY_H
#define TRAY_H
#include "main.h"
class Tray {
  state_tray state;
  state_tray lastState;
  double settledRange;
  const double brakeVelRange = 20.0;

public:
  // "default" constructor
  Tray(double tSettledRange);

  // enables the controller
  void enable();
  // disables the controller
  void disable();

  // turns off the controller, and sets the brakeMode to coast
  void rest();
  // sets the target height of the controller
  void setTarget(heights_tray tHeight);
  void setTarget(double tHeight);
  // makes the tray stop as soon as possible without jerking
  void brake();
  // returns wheather the tray has reached its target
  bool reachedTarget();

  // state Control
  // sets the state
  void setState(state_tray tState);
  // returns the state
  state_tray getState();
};
extern Tray tray;
#endif
