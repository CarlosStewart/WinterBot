#ifndef INTAKE_H
#define INTAKE_H
class Intake {
  const double speed = 200.0;

public:
  // constructors
  // default constuctor with default of PID on
  Intake();

  // overload constructor
  Intake(bool tPID);

  // methods
  // toggles the intake between on or off
  void toggle();
  // sets the intake to on (true) or off (false)
  void toggle(bool tOn);

  // spins the intake in at the default speed
  void spinIn();
  // spins the intake in with a specific speed
  void spinIn(double tSpeed);
  // spins the intake out at the default speed
  void spinOut();
  // spins the intake out with a specific speed
  void spinOut(double tSpeed);
  // sets the intake to a specific speed (in or out)
  void spin(double tSpeed);

  // toggles the intake PID between on or off
  void togglePID();
  // sets the intake PID to on (true) or off (false)
  void togglePID(bool tOn);
};
extern Intake intk;
#endif
