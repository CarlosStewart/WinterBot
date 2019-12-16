#include "main.h"
using namespace okapi;
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  // sets up chassis for easy drivetrain control in autonomous
  auto drive = ChassisControllerFactory::create(
      {boolToSign(DLF_REV) * DLF_PORT, boolToSign(DLB_REV) * DLB_PORT},
      {boolToSign(DRF_REV) * DRF_PORT, boolToSign(DRB_REV) * DRB_PORT},
      BLUE * (36.0 / 84.0),
      // IterativePosPIDController::Gains{0.001, 0, 0.0001},
      // IterativePosPIDController::Gains{0.001, 0, 0.0001},
      // IterativePosPIDController::Gains{0.001, 0, 0.0001}, BLUE,
      {-6230, 38}); //{motor deg to m, motor deg to bot deg}

  // FOR TESTING ONLY
  drive.moveDistance(72_in);
  drive.turnAngle(360_deg);
}
