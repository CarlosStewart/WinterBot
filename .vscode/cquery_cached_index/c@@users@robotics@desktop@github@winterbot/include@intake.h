#ifndef INTAKE_H
#define INTAKE_H
#include "main.h"
class Intake {
  state_intk state;
  const double fullSpeed = 200.0;
  double speed;

public:
  // constructors
  // default constuctor with default braketype hold
  Intake();

  // overload constructor
  Intake(bool tHold);

  // control
  // moves the intake in or out, based on the sign (and optional perameter)
  void spin();
  void spin(double tSpeed);
  // moves the intake in (optional perameter)
  void spinIn();
  void spinIn(double tSpeed);
  // moves the intake out (optional perameter)
  void spinOut();
  void spinOut(double tSpeed);
  // if the intake is spinning out, stop; otherwise, spin in
  void toggle();
  // stops the intake with or without braketype hold
  void stop(bool tHold);

  // interfacing
  // sets the speed
  void setSpeed(double tSpeed);
  // returns the speed
  double getSpeed();

  // state control
  // sets the state
  void setState(state_intk tState);
  // returns the state
  state_intk getState();
};
extern Intake intk;
#endif
