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

  void printEncoders();

  // state Control
  // sets the state
  void setState(state_dvtn tState);
  // returns the state
  state_dvtn getState();

  class Control {
    const double straightSuccessRange = 2.0; // degrees
    const double straightMaxSpeed = 150.0;
    const double straightSlewIncrement = 10;
    const int straightSettledForCounts = 50;

    const double turnMaxSpeed = 200.0;
    const double turnSuccessRange = 1.0; // degrees

    QLength rightArcLength;
    QLength leftArcLength;

  public:
    // returns the current heading of the robot in degrees
    double getHeading();

    // moves the drivetrain forward, and turns at specific velocities
    void moveArcade(double tForwardVel, double tTurnVel);
    // moves the drivetrain based on velocities of both sides
    void moveTank(double tRPMLeft, double tRPMRight);
    // sets the speed to 0
    void stop();

    void calcArcDistances(QLength tChordLength, QAngle tAngle) {
      QLength radius;
      if (tAngle < 0_deg) {
        tAngle += 360_deg;
      }
      if (tAngle > 0_deg && tAngle < 90_deg) {
        radius = tChordLength / (2 * sin(tAngle.convert(radian) / 2));
        rightArcLength = 2 * (radius + RIGHT_TRACK_DIST * inch) *
                         sin(tAngle.convert(radian) / 2);
        leftArcLength = 2 * (radius - LEFT_TRACK_DIST * inch) *
                        sin(tAngle.convert(radian) / 2);
      } else if (angle > 90 && angle < 180) {
        theta = M_PI / 2 - ((180 - angle) * M_PI / 180);
        double leftTarget =
            chordLength * theta / (2 * sin(theta / 2)) - offsetL;
        double rightTarget = leftTarget + (theta * (offsetL + offsetR));
      } else if (angle > 180 && angle < 270) {
        theta = M_PI / 2 - ((angle - 180) * M_PI / 180);
        double leftTarget =
            -1 * (chordLength * theta / (2 * sin(theta / 2)) - offsetL);
        double rightTarget = leftTarget - (theta * (offsetL + offsetR));
      } else {
        theta = M_PI / 2 - ((360 - angle) * M_PI / 180);
        double rightTarget =
            -1 * (chordLength * theta / (2 * sin(theta / 2)) - offsetR);
        double leftTarget = leftTarget - (theta * (offsetL + offsetR));
      }
      somePIDfunction(leftTarget, rightTarget);
    }

    // move the drivetrain to a specific orientation (field centric)
    void turnToFace(QAngle tAngle, double tMaxSpeed);
    void turnToFace(QAngle tAngle);
    // move the drivetrain a specific distance (robot centric)
    void driveDistance(QLength tDistance, double tMaxSpeed,
                       double tSlewIncrement);
    void driveDistance(QLength tDistance, double tMaxSpeed);
    void driveDistance(QLength tDistance);

  } ctrl;
};
extern Drivetrain dvtn;
#endif
