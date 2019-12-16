#ifndef Drivetrain_H
#define Drivetrain_H
#include "main.h"
class Drivetrain {
  state_dvtn state;
  double slewIncrement;

  double nextForwardVel;
  double nextTurnVel;

public:
  // overload constructor
  Drivetrain(double tSlewIncrement);

  // moves the drivetrain with or without slew (for joystick control)
  void updateArcade(double tForwardVel, double tTurnVel, bool tSlewOn);

  // state Control
  // sets the state
  void setState(state_dvtn tState);
  // returns the state
  state_dvtn getState();

  class Control {

  public:
    // moves the drivetrain forward, and turns at specific velocities
    void moveArcade(double tForwardVel, double tTurnVel);
    // moves the drivetrain based on velocities of both sides
    void moveTank(double tRPMLeft, double tRPMRight);
    // sets the speed to 0
    void stop();

  } ctrl;
};
extern Drivetrain dvtn;
#endif
