#include "main.h"

Controller con(ControllerId::master);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() { pros::lcd::initialize(); }

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

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
  dvtn.ctrl.moveArcade(100.0, 0.0);
  pros::delay(2000);
  dvtn.ctrl.moveArcade(-100.0, 0.0);
  pros::delay(3000);
  dvtn.ctrl.moveArcade(0.0, 0.0);
}

void dvtnControl(void *) {
  ControllerButton btn_dt_tgl_slew(BTN_DVTN_TGL_SLEW);

  while (true) {
    if (btn_dt_tgl_slew.changedToPressed())
      dvtn.tglSlew();
    dvtn.updateArcade(con.getAnalog(ControllerAnalog::leftY) * 200,
                      con.getAnalog(ControllerAnalog::rightX) * 200,
                      con.getAnalog(ControllerAnalog::leftX) * 200);
    pros::delay(20);
  }
}

void intkControl(void *) {
  ControllerButton btn_intk_tgl(BTN_INTK_TGL);
  ControllerButton btn_intk_in(BTN_INTK_IN);
  ControllerButton btn_intk_out(BTN_INTK_OUT);

  while (true) {
    if (btn_intk_tgl.changedToPressed()) {
      intk.toggle();
    } else if (btn_intk_in.changedToPressed()) {
      intk.spinIn();
    } else if (btn_intk_out.changedToPressed()) {
      intk.spinOut();
    } else if (btn_intk_in.changedToReleased() ||
               btn_intk_out.changedToReleased()) {
      intk.toggle(false);
    }
    pros::delay(20);
  }
}

void trayControl(void *) {
  ControllerButton btn_tray_up(BTN_TRAY_UP);
  ControllerButton btn_tray_down(BTN_TRAY_DOWN);

  while (true) {
    if (btn_tray_up.changedToPressed()) {
      tray.moveUp();
    } else if (btn_tray_down.changedToPressed()) {
      tray.moveDown();
    } else if (btn_tray_up.changedToReleased() ||
               btn_tray_down.changedToReleased()) {
      tray.brake();
    }
    pros::delay(20);
  }
}

void liftControl(void *) {
  ControllerButton btn_lift_up(BTN_LIFT_UP);
  ControllerButton btn_lift_down(BTN_LIFT_DOWN);
  ControllerButton btn_lift_low(BTN_LIFT_LOW);
  ControllerButton btn_lift_med(BTN_LIFT_MED);
  ControllerButton btn_lift_high(BTN_LIFT_HIGH);

  while (true) {
    if (btn_lift_up.changedToPressed()) {
      lift.moveUp();
    } else if (btn_lift_down.changedToPressed()) {
      lift.moveDown();
    } else if (btn_lift_low.changedToPressed()) {
      lift.moveTo(Lift::heights::low);
    } else if (btn_lift_med.changedToPressed()) {
      lift.moveTo(Lift::heights::med);
    } else if (btn_lift_high.changedToPressed()) {
      lift.moveTo(Lift::heights::high);
    } else if (btn_lift_up.changedToReleased() ||
               btn_lift_down.changedToReleased()) {
      lift.brake();
    }

    pros::delay(20);
  }
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  pros::Task dvtnTask(dvtnControl);
  pros::Task intkTask(intkControl);
  pros::Task trayTask(trayControl);
  pros::Task liftTask(liftControl);

  ControllerButton btn_mcro_stak(BTN_MCRO_STAK);
  while (true) {
    if (btn_mcro_stak.changedToPressed()) {
      dvtnTask.suspend(); // allows drivetrain movement in this macro
      mcroStak();
      dvtnTask.resume(); // returns drivetrain control
    }

    // odom.iterate();
    //
    // pros::lcd::print(0, "x = %f\ny = %f\ntheta = %f",
    //                  odom.get().x.convert(inch), odom.get().y.convert(inch),
    //                  odom.get().theta.convert(degree));

    pros::delay(20);
  }
}
