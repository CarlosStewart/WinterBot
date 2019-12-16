#ifndef LIFT_H
#define LIFT_H
class Lift {
  const double brakeVelRange = 20.0;
  const double speed = 200.0;

public:
  // stores the values of the heights of the lift
  enum heights { restPos = 30, low = 200, med = 1000, high = 2000 };

  // constructors
  // default (PID on)
  Lift();
  // overload
  Lift(bool tPID);

  // used to stop the lift, without stopping suddenly (blocking?)
  void brake();

  // move the lift up, with optional speed parameter
  void moveUp();
  // move the lift up, with optional speed parameter
  void moveUp(double tSpeed);
  // move the lift down, with optional speed parameter
  void moveDown();
  // move the lift down, with optional speed parameter
  void moveDown(double tSpeed);
  // move the lift with a specific speed
  void move(double tSpeed);

  // move lift to a specific height (blocking?), with optional speed parameter
  void moveTo(double tHeight);
  // move lift to a specific height (blocking?), with optional speed parameter
  void moveTo(double tHeight, double tVelocity);
  // move lift to a specific height (blocking?), with optional speed parameter
  void moveTo(heights tHeight);
  // move lift to a specific height (blocking?), with optional speed parameter
  void moveTo(heights tHeight, double tVelocity);

  // turns the lift PID on/off with optional toggle perameter
  void togglePID();
  // turns the lift PID on/off with optional toggle perameter
  void togglePID(bool tOn);

  // go the the resting position, with optional speed parameter
  void rest();
  // go the the resting position, with optional speed parameter
  void rest(double tSpeed);
};
extern Lift lift;
#endif
