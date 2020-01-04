#ifndef LIFT_H
#define LIFT_H
#include "main.h"
class Lift {
  state_lift state;
  const double brakeVelRange = 20.0;

public:
  // overload constructor
  Lift(bool tBrakeModeHold);

  // enables the controller
  void enable();
  // disables the controller
  void disable();

  // turns off the controller, and sets the brakeMode to coast
  void rest();
  // sets the target height of the controller
  void setTarget(heights_lift tHeight);
  void setTarget(double tHeight);
  // makes the lift stop as soon as possible without jerking
  void brake();

  // state Control
  // sets the state
  void setState(state_lift tState);
  // returns the state
  state_lift getState();
};
extern Lift lift;
#endif
