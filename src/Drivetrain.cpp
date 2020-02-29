#include "main.h"

Motor dvtn_left_front_motor(DLF);
Motor dvtn_left_back_motor(DLB);
Motor dvtn_right_front_motor(DRF);
Motor dvtn_right_back_motor(DRB);
MotorGroup dvtn_left_motors({dvtn_left_front_motor, dvtn_left_back_motor});
MotorGroup dvtn_right_motors({dvtn_right_front_motor, dvtn_right_back_motor});
ADIEncoder dvtn_left_track(DLT_TOP, DLT_BOTTOM, DLT_REV);
ADIEncoder dvtn_right_track(DRT_TOP, DRT_BOTTOM, DRT_REV);
pros::Imu imu(IMU);

// overload constructor
Drivetrain::Drivetrain(double tSlewIncrement) {
  slewIncrement = tSlewIncrement;
  dvtn_left_track.reset();
  dvtn_right_track.reset();
}

// public movement methods
void Drivetrain::updateArcade(double tForwardVel, double tTurnVel,
                              bool tSlewOn) {

  tForwardVel = adjustControl(tForwardVel, 2.0, 50.0, 200.0);
  tTurnVel = adjustControl(tTurnVel, 2.0, 20.0, 200.0);

  pros::lcd::print(5, "forward: %f", tForwardVel);
  pros::lcd::print(6, "turn: %f", tTurnVel);

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

void Drivetrain::printEncoders() {
  printf("left encoder: %f          right encoder: %f\n", dvtn_left_track.get(),
         dvtn_right_track.get());
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
  return imu.get_rotation();
  // 1.393015905679 * (dvtn_left_track.get() - dvtn_right_track.get()) /
  //        (LEFT_TRACK_DIST + RIGHT_TRACK_DIST);
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
void Drivetrain::Control::turnToFace(QAngle tAngle, double tMaxSpeed) {
  double kp = 1.3;
  double ki = 0.0;
  double kd = 0.1;
  double integralActiveZone = 10.0;
  double target = tAngle.convert(degree);
  double error, lastError, totalError, proportion, integral, deriative,
      totalSpeed;

  do {
    error = target - getHeading();

    if (abs(error) < integralActiveZone && error != 0)
      totalError += error;
    else
      totalError = 0;

    if (totalError > 50 / ki)
      totalError = 50 / ki;
    else if (totalError < -50 / ki)
      totalError = 50 / ki;

    if (error == 0)
      deriative = 0;

    proportion = error * kp;
    integral = totalError * ki;
    deriative = (error - lastError) * kd;

    totalSpeed = proportion + integral + deriative;

    if (totalSpeed > tMaxSpeed)
      totalSpeed = tMaxSpeed;

    lastError = error;

    pros::lcd::print(0, "target: %f     error: %f", target, error);
    pros::lcd::print(1, "heading: %f", getHeading());
    pros::lcd::print(2, "p: %f   i: %f   d: %f", proportion, integral,
                     deriative);
    pros::lcd::print(3, "totatSpeed: %f", totalSpeed);
    pros::lcd::print(4, "turnSuccessRange: %f", turnSuccessRange);
    pros::lcd::print(5, "t: %i   f: %i   cdtinl: %i", true, false,
                     abs(error) > turnSuccessRange);

    moveArcade(0.0, totalSpeed);

    pros::delay(20);
  } while (abs(error) > turnSuccessRange);
}
void Drivetrain::Control::turnToFace(QAngle tAngle) {
  turnToFace(tAngle, turnMaxSpeed);
}
// move the drivetrain a specific distance (robot centric)
void Drivetrain::Control::driveDistance(QLength tDistance, double tMaxSpeed,
                                        double tSlewIncrement) {
  double kp = 0.46;
  double ki = 0.0;
  double kd = 1;
  double integralActiveZone = 500.0;
  double target = tDistance.convert(inch) * 360 / (TRACK_DIAMETER * pi) +
                  dvtn_right_track.get();
  double error, lastError, totalError, proportion, integral, deriative,
      totalSpeed, lastTotalSpeed;

  do {
    error = target - dvtn_right_track.get();

    if (abs(error) < integralActiveZone && error != 0)
      totalError += error;
    else
      totalError = 0;

    if (totalError > 50 / ki)
      totalError = 50 / ki;
    else if (totalError < -50 / ki)
      totalError = 50 / ki;

    if (error == 0)
      deriative = 0;

    proportion = error * kp;
    integral = totalError * ki;
    deriative = (error - lastError) * kd;

    lastError = error;

    totalSpeed = proportion + integral + deriative;

    if (tDistance > 0_in && totalSpeed > lastTotalSpeed + tSlewIncrement)
      totalSpeed = lastTotalSpeed + tSlewIncrement;
    else if (totalSpeed < lastTotalSpeed - tSlewIncrement)
      totalSpeed = lastTotalSpeed - tSlewIncrement;

    if (totalSpeed > tMaxSpeed)
      totalSpeed = tMaxSpeed;
    else if (totalSpeed < -tMaxSpeed)
      totalSpeed = -tMaxSpeed;

    lastTotalSpeed = totalSpeed;

    moveArcade(totalSpeed, 0.0);

    pros::delay(20);
  } while (abs(error) > straightSuccessRange);
  moveArcade(0.0, 0.0);
}
void Drivetrain::Control::driveDistance(QLength tDistance, double tMaxSpeed) {
  driveDistance(tDistance, tMaxSpeed, straightSlewIncrement);
}
void Drivetrain::Control::driveDistance(QLength tDistance) {
  driveDistance(tDistance, straightMaxSpeed, straightSlewIncrement);
}

void Drivetrain::Control::driveDistanceSpecial(QLength tDistance,
                                               double tMaxSpeed,
                                               QLength tTurnDistance) {
  if (tTurnDistance.convert(inch) < 0) {
    double kp = 0.46;
    double ki = 0.0;
    double kd = 1;
    double integralActiveZone = 500.0;
    double target = tDistance.convert(inch) * 360 / (TRACK_DIAMETER * pi) +
                    dvtn_right_track.get();
    double turnDistanceDegrees =
        tTurnDistance.convert(inch) * -360 / (TRACK_DIAMETER * pi);
    double error, lastError, totalError, proportion, integral, deriative,
        totalSpeed, lastTotalSpeed;

    do {
      error = target - dvtn_right_track.get();

      if (abs(error) < integralActiveZone && error != 0)
        totalError += error;
      else
        totalError = 0;

      if (totalError > 50 / ki)
        totalError = 50 / ki;
      else if (totalError < -50 / ki)
        totalError = 50 / ki;

      if (error == 0)
        deriative = 0;

      proportion = error * kp;
      integral = totalError * ki;
      deriative = (error - lastError) * kd;

      lastError = error;

      totalSpeed = proportion + integral + deriative;

      if (tDistance > 0_in &&
          totalSpeed > lastTotalSpeed + straightSlewIncrement)
        totalSpeed = lastTotalSpeed + straightSlewIncrement;
      else if (totalSpeed < lastTotalSpeed - straightSlewIncrement)
        totalSpeed = lastTotalSpeed - straightSlewIncrement;

      if (totalSpeed > tMaxSpeed)
        totalSpeed = tMaxSpeed;
      else if (totalSpeed < -tMaxSpeed)
        totalSpeed = -tMaxSpeed;

      lastTotalSpeed = totalSpeed;

      if (abs(error) < turnDistanceDegrees) {
        dvtn_left_motors.moveVelocity(0.0);
        dvtn_right_motors.moveVelocity(totalSpeed);
      } else {
        moveArcade(totalSpeed, 0.0);
      }

      pros::delay(20);
    } while (abs(error) > straightSuccessRange);
  } else {
    double kp = 0.46;
    double ki = 0.0;
    double kd = 1;
    double integralActiveZone = 500.0;
    double target = tDistance.convert(inch) * 360 / (TRACK_DIAMETER * pi) +
                    dvtn_left_track.get();
    double turnDistanceDegrees =
        tTurnDistance.convert(inch) * 360 / (TRACK_DIAMETER * pi);
    double error, lastError, totalError, proportion, integral, deriative,
        totalSpeed, lastTotalSpeed;

    do {
      error = target - dvtn_left_track.get();

      if (abs(error) < integralActiveZone && error != 0)
        totalError += error;
      else
        totalError = 0;

      if (totalError > 50 / ki)
        totalError = 50 / ki;
      else if (totalError < -50 / ki)
        totalError = 50 / ki;

      if (error == 0)
        deriative = 0;

      proportion = error * kp;
      integral = totalError * ki;
      deriative = (error - lastError) * kd;

      lastError = error;

      totalSpeed = proportion + integral + deriative;

      if (tDistance > 0_in &&
          totalSpeed > lastTotalSpeed + straightSlewIncrement)
        totalSpeed = lastTotalSpeed + straightSlewIncrement;
      else if (totalSpeed < lastTotalSpeed - straightSlewIncrement)
        totalSpeed = lastTotalSpeed - straightSlewIncrement;

      if (totalSpeed > tMaxSpeed)
        totalSpeed = tMaxSpeed;
      else if (totalSpeed < -tMaxSpeed)
        totalSpeed = -tMaxSpeed;

      lastTotalSpeed = totalSpeed;

      if (abs(error) < turnDistanceDegrees) {
        dvtn_left_motors.moveVelocity(totalSpeed);
        dvtn_right_motors.moveVelocity(0.0);
      } else {
        moveArcade(totalSpeed, 0.0);
      }

      pros::delay(20);
    } while (abs(error) > straightSuccessRange);
  }
  moveArcade(0.0, 0.0);
}
// creation of dt object
Drivetrain dvtn(5.0);
