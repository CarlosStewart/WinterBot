#include "main.h"

Motor dvtn_left_front_motor(DLF);
Motor dvtn_left_back_motor(DLB);
Motor dvtn_right_front_motor(DRF);
Motor dvtn_right_back_motor(DRB);
MotorGroup dvtn_left_motors({dvtn_left_front_motor, dvtn_left_back_motor});
MotorGroup dvtn_right_motors({dvtn_right_front_motor, dvtn_right_back_motor});

// default constructor
Drivetrain::Drivetrain() {
  slewIncrement = targetForwardVel = targetTurnVel = 0;
  slewOn = false;
}

// overload constructor
Drivetrain::Drivetrain(double tSlewIncrement, double tSL, double tSR) {
  slewIncrement = tSlewIncrement;
  targetForwardVel = targetTurnVel = 0;
  slewOn = false;
}

// public movement methods
void Drivetrain::updateArcade(double tForwardVel, double tTurnVel) {
  if (slewOn) {
    // update target forward velocity
    if (tForwardVel > targetForwardVel) {
      targetForwardVel += slewIncrement;
    } else if (tForwardVel < targetForwardVel) {
      targetForwardVel -= slewIncrement;
    }

    // update target turn velocity
    if (tTurnVel > targetTurnVel) {
      targetTurnVel += slewIncrement;
    } else if (tTurnVel < targetTurnVel) {
      targetTurnVel -= slewIncrement;
    }

    // move the motors at the target velocities
    ctrl.moveArcade(targetForwardVel, targetTurnVel);
  } else {
    ctrl.moveArcade(tForwardVel, tTurnVel);
  }
}
void Drivetrain::updateArcade(double tForwardVel, double tTurnVel,
                              double tStrafeVel) {
  if (slewOn) {
    // update target forward velocity
    if (tForwardVel > targetForwardVel) {
      targetForwardVel += slewIncrement;
    } else if (tForwardVel < targetForwardVel) {
      targetForwardVel -= slewIncrement;
    }

    // update target turn velocity
    if (tTurnVel > targetTurnVel) {
      targetTurnVel += slewIncrement;
    } else if (tTurnVel < targetTurnVel) {
      targetTurnVel -= slewIncrement;
    }

    // update target strafe velocity
    if (tStrafeVel > targetStrafeVel) {
      targetStrafeVel += slewIncrement;
    } else if (tStrafeVel < targetStrafeVel) {
      targetStrafeVel -= slewIncrement;
    }

    // move the motors at the target velocities
    ctrl.moveArcade(targetForwardVel, targetTurnVel, targetStrafeVel);
  } else {
    ctrl.moveArcade(tForwardVel, tTurnVel, tStrafeVel);
  }
}

// calculates the orientation from start
double Drivetrain::getTheta() {
  // return ((sensors.track.getLeft() - sensors.track.getRight()) / (sL + sR) *
  //         radian)
  //     .convert(degree);
  return ((dvtn_left_motors.getPosition() - dvtn_right_motors.getPosition()) /
          (sL + sR) * radian)
      .convert(degree);
}

// other methods
// toggles slew, with optional forced setting
void Drivetrain::tglSlew() { slewOn = !slewOn; }
// toggles slew, with optional forced setting
void Drivetrain::tglSlew(bool tOn) { slewOn = tOn; }

/////////////////////////
//                     //
//    Control Class    //
//                     //
/////////////////////////

// default constructor for setting PID constants
Drivetrain::Control::Control() {
  kpF = 0.1;
  kiF = 0.0;
  kdF = 0.0;
  iazF = 5.0; // 1ft for 4" wheels

  kpT = 0.1;
  kiT = 0.0;
  kdT = 0.0;
  iazT = 20.0;
}
// basic movement methods
// moves the drivetrain forward, and turns at specific velocities
void Drivetrain::Control::moveArcade(double tForwardVel, double tTurnVel) {
  dvtn_left_motors.moveVelocity(tForwardVel + tTurnVel);
  dvtn_right_motors.moveVelocity(tForwardVel - tTurnVel);
}
// moves the drivetrain forward, and turns at specific velocities
void Drivetrain::Control::moveArcade(double tForwardVel, double tTurnVel,
                                     double tStrafeVel) {
  dvtn_left_front_motor.moveVelocity(tForwardVel + tTurnVel + tStrafeVel);
  dvtn_left_back_motor.moveVelocity(tForwardVel + tTurnVel - tStrafeVel);
  dvtn_right_front_motor.moveVelocity(tForwardVel - tTurnVel - tStrafeVel);
  dvtn_right_back_motor.moveVelocity(tForwardVel - tTurnVel + tStrafeVel);
}
// moves the drivetrain based on velocities of both sides
void Drivetrain::Control::moveTank(double tRPMLeft, double tRPMRight) {
  dvtn_left_motors.moveVelocity(tRPMLeft);
  dvtn_right_motors.moveVelocity(tRPMRight);
}

// accessors
// returns the output of the F PID loop
double Drivetrain::Control::getOutF() { return outF; }
// returns the output of the T PID loop
double Drivetrain::Control::getOutT() { return outT; }

// returns if the F PID loop is done
bool Drivetrain::Control::isSettledF() {
  if (errF < 5.0) {
    return true;
  } else {
    return false;
  }
}
// returns if the T PID loop is done
bool Drivetrain::Control::isSettledT() { return abs(errT) < 5; }

// mutators
// sets the target for the F PID loop
void Drivetrain::Control::setTarF(double tTarF) { tarF = tTarF; }
// sets the target for the T PID loop
void Drivetrain::Control::setTarT(double tTarT) { tarT = tTarT; }

// steps through the PID for Distance and Angle
void Drivetrain::Control::itteratePIDF() {
  errF = tarF - dvtn_right_motors.getPosition(); // sensors.track.getLeft();

  // limits the total error to control ki
  // when error is 0, total error is reset
  if (errF < iazF & errF != 0) {
    sErrF += errF;
  } else {
    sErrF = 0;
  }
  // caps the integral term
  if (sErrF > 50 / kiF) {
    sErrF = 50 / kiF;
  }

  // if target is reached, derivative term is 0
  if (errF == 0) {
    lErrF = 0;
    settledF = true;
  }

  outF = errF * kpF + sErrF * kiF + (errF - lErrF) * kdF;
}
void Drivetrain::Control::itteratePIDT() {
  errT = tarT - dvtn.getTheta();

  // limits the total error to control ki
  // when error is 0, total error is reset
  if (errT < iazT & errT != 0) {
    sErrT += errT;
  } else {
    sErrT = 0;
  }
  // caps the integral term
  if (sErrT > 50 / kiT) {
    sErrT = 50 / kiT;
  }

  // if target is reached, derivative term is 0
  if (errT == 0) {
    lErrT = 0;
  }

  outT = errT * kpT + sErrT * kiT + (errT - lErrT) * kdT;
}

// creation of dt object
Drivetrain dvtn(4.0, 6.6, 6.6);
