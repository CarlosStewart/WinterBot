#include "main.h"

Motor dvtn_left_front_motor(DLF);
Motor dvtn_left_back_motor(DLB);
Motor dvtn_right_front_motor(DRF);
Motor dvtn_right_back_motor(DRB);
MotorGroup dvtn_left_motors({dvtn_left_front_motor, dvtn_left_back_motor});
MotorGroup dvtn_right_motors({dvtn_right_front_motor, dvtn_right_back_motor});
ADIEncoder dvtn_left_track(DLT_TOP, DLT_BOTTOM, DLT_REV);
ADIEncoder dvtn_right_track(DRT_TOP, DRT_BOTTOM, DRT_REV);

// overload constructor
Drivetrain::Drivetrain(double tSlewIncrement) {
  slewIncrement = tSlewIncrement;
  dvtn_left_track.reset();
  dvtn_right_track.reset();
}

// public movement methods
void Drivetrain::updateArcade(double tForwardVel, double tTurnVel,
                              bool tSlewOn) {
  if (tSlewOn) {
    // update target forward velocity
    if (tForwardVel > nextForwardVel) {
      nextForwardVel += slewIncrement;
    } else if (tForwardVel < nextForwardVel) {
      nextForwardVel -= slewIncrement;
    }

    // update target turn velocity
    if (tTurnVel > nextTurnVel) {
      nextTurnVel += slewIncrement;
    } else if (tTurnVel < nextTurnVel) {
      nextTurnVel -= slewIncrement;
    }

    // move the motors at the target velocities
    ctrl.moveArcade(nextForwardVel, nextTurnVel);
  } else {
    ctrl.moveArcade(tForwardVel, tTurnVel);
  }
}

// state Control
// sets the state
void Drivetrain::setState(state_dvtn tState) { state = tState; }
// returns the state
state_dvtn Drivetrain::getState() { return state; }

/////////////////////////
//                     //
//    Control Class    //
//                     //
/////////////////////////

// returns the current heading of the robot in degrees
double Drivetrain::Control::getHeading() {
  return hfix((dvtn_left_track.get() - dvtn_right_track.get()) /
              (LEFT_TRACK_DIST + RIGHT_TRACK_DIST) * 180 / pi);
}

// basic movement methods
// moves the drivetrain forward, and turns at specific velocities
void Drivetrain::Control::moveArcade(double tForwardVel, double tTurnVel) {
  dvtn_left_motors.moveVelocity(tForwardVel + tTurnVel);
  dvtn_right_motors.moveVelocity(tForwardVel - tTurnVel);
}
// moves the drivetrain based on velocities of both sides
void Drivetrain::Control::moveTank(double tLeftVel, double tRightVel) {
  dvtn_left_motors.moveVelocity(tLeftVel);
  dvtn_right_motors.moveVelocity(tRightVel);
}
// sets the speed to 0
void Drivetrain::Control::stop() {
  dvtn_left_motors.moveVelocity(0.0);
  dvtn_right_motors.moveVelocity(0.0);
}
// move the drivetrain to a specific orientation (field centric)
void Drivetrain::Control::turnToFace(QAngle tAngle, double tTurnSuccessRange) {
  double kp = 0.01;
  double ki = 0.0000000000001;
  double kd = 0.0;
  double integralActiveZone = 10.0;
  double target = tAngle.convert(degree);
  double error, lastError, totalError, proportion, integral, deriative;

  do {
    error = target - getHeading();

    if (error < integralActiveZone && error != 0)
      totalError += error;
    else
      totalError = 0;

    if (totalError > 50 / ki)
      totalError = 50 / ki;

    if (error == 0)
      deriative = 0;

    proportion = error * kp;
    integral = totalError * ki;
    deriative = (error - lastError) * kd;

    lastError = error;

    moveArcade(0.0, proportion + integral + deriative);
  } while (abs(error) < tTurnSuccessRange);
}
void Drivetrain::Control::turnToFace(QAngle tAngle) {
  turnToFace(tAngle, turnSuccessRange);
}
// move the drivetrain a specific distance (robot centric)
void Drivetrain::Control::driveDistance(QLength tDistance,
                                        double tStraightSuccessRange) {
  double kp = 0.01;
  double ki = 0.00000000000001;
  double kd = 0.0;
  double integralActiveZone = 7.0;
  double target = tDistance.convert(inch) +
                  dvtn_right_track.get() / 360 * TRACK_DIAMETER * pi;
  double error, lastError, totalError, proportion, integral, deriative;

  do {
    error = target - dvtn_right_track.get();

    if (error < integralActiveZone && error != 0)
      totalError += error;
    else
      totalError = 0;

    if (totalError > 50 / ki)
      totalError = 50 / ki;

    if (error == 0)
      deriative = 0;

    proportion = error * kp;
    integral = totalError * ki;
    deriative = (error - lastError) * kd;

    lastError = error;

    moveArcade(proportion + integral + deriative, 0.0);
  } while (abs(error) < tStraightSuccessRange);
}
void Drivetrain::Control::driveDistance(QLength tDistance) {
  driveDistance(tDistance, straightSuccessRange);
}
// creation of dt object
Drivetrain dvtn(5.0);
