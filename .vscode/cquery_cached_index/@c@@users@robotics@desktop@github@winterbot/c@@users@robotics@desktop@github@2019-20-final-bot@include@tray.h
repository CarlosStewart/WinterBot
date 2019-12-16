#ifndef TRAY_H
#define TRAY_H
class Tray {
  const double brakeVelRange = 20.0;
  const double speed = 200.0;

public:
  // stores the values of the heights of the tray
  enum heights { restPos = 2000, stack = 4000 };

  // makes a new tray object with PID on/off bool (default on)
  Tray();
  // makes a new tray object with PID on/off bool (default on)
  Tray(bool tPID);

  // used to stop the tray, without stopping suddenly (blocking?)
  void brake();

  // move the tray up, with optional speed parameter
  void moveUp();
  // move the tray up, with optional speed parameter
  void moveUp(double tSpeed);
  // move the tray down, with optional speed parameter
  void moveDown();
  // move the tray down, with optional speed parameter
  void moveDown(double tSpeed);
  // move the tray with a specific speed
  void move(double tSpeed);

  // move tray to a specific height (blocking?), with optional speed parameter
  void moveTo(double tHeight);
  // move tray to a specific height (blocking?), with optional speed parameter
  void moveTo(double tHeight, double tVelocity);
  // move tray to a specific height (blocking?), with optional speed parameter
  void moveTo(heights tHeight);
  // move tray to a specific height (blocking?), with optional speed parameter
  void moveTo(heights tHeight, double tVelocity);

  // go the the resting position, with optional speed parameter
  void rest();
  // go the the resting position, with optional speed parameter
  void rest(double tSpeed);
};
extern Tray tray;
#endif
