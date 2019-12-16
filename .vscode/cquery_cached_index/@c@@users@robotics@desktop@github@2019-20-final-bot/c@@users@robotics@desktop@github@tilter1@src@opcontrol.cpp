#include "main.h"
using namespace okapi; // eliminates the need to say okapi:: a hundred times

Controller masterController(ControllerId::master);
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
  static lv_style_t tabview_indic_style;
  tabview_indic_style.body.border.color = LV_COLOR_WHITE;
  tabview_indic_style.body.border.width = 4;
  tabview_indic_style.body.border.part = LV_BORDER_FULL;
  tabview_indic_style.body.border.opa = LV_OPA_100;
  tabview_indic_style.body.padding.inner = 5;
  tabview_indic_style.body.opa = LV_OPA_100;

  static lv_style_t tabview_btn_style;
  lv_style_copy(&tabview_btn_style, &lv_style_plain);
  tabview_btn_style.body.main_color = LV_COLOR_HEX(0xa600ff);
  tabview_btn_style.body.grad_color = LV_COLOR_HEX(0xa600ff);
  tabview_btn_style.text.color = LV_COLOR_WHITE;

  static lv_style_t tabview_btn_tgl_style;
  lv_style_copy(&tabview_btn_tgl_style, &tabview_btn_style);
  tabview_btn_tgl_style.body.border.width = 2;
  tabview_btn_tgl_style.body.border.color = LV_COLOR_WHITE;

  static lv_style_t tabview_btn_pr_style;
  lv_style_copy(&tabview_btn_pr_style, &lv_style_plain);
  tabview_btn_pr_style.body.main_color = LV_COLOR_WHITE;
  tabview_btn_pr_style.body.grad_color = LV_COLOR_WHITE;
  tabview_btn_pr_style.text.color = LV_COLOR_WHITE;

  lv_obj_t *tabview_windows = lv_tabview_create(lv_scr_act(), NULL);
  lv_obj_t *tab_auton = lv_tabview_add_tab(tabview_windows, "Auton");
  lv_obj_t *tab_values = lv_tabview_add_tab(tabview_windows, "Values");

  lv_tabview_set_style(tabview_windows, LV_TABVIEW_STYLE_INDIC,
                       &tabview_indic_style);
  lv_tabview_set_style(tabview_windows, LV_TABVIEW_STYLE_BTN_REL,
                       &tabview_btn_style);
  lv_tabview_set_style(tabview_windows, LV_TABVIEW_STYLE_BTN_PR,
                       &tabview_btn_pr_style);
  lv_tabview_set_style(tabview_windows, LV_TABVIEW_STYLE_BTN_TGL_REL,
                       &tabview_btn_tgl_style);
  lv_tabview_set_style(tabview_windows, LV_TABVIEW_STYLE_BTN_TGL_PR,
                       &tabview_btn_pr_style);

  static lv_style_t switch_team_blue_style;
  lv_style_copy(&switch_team_blue_style, &lv_style_plain);
  switch_team_blue_style.body.main_color = LV_COLOR_BLUE;
  switch_team_blue_style.body.grad_color = LV_COLOR_BLUE;
  switch_team_blue_style.body.radius = LV_RADIUS_CIRCLE;
  switch_team_blue_style.body.border.color = LV_COLOR_WHITE;
  switch_team_blue_style.body.border.part = LV_BORDER_FULL;
  switch_team_blue_style.body.border.width = 2;

  static lv_style_t switch_side_off_style;
  lv_style_copy(&switch_side_off_style, &switch_team_blue_style);
  switch_side_off_style.body.main_color = LV_COLOR_ORANGE;

  static lv_style_t switch_team_red_style;
  lv_style_copy(&switch_team_red_style, &switch_team_blue_style);
  switch_team_red_style.body.main_color = LV_COLOR_RED;
  switch_team_red_style.body.grad_color = LV_COLOR_RED;

  static lv_style_t switch_team_bg_style;
  lv_style_copy(&switch_team_bg_style, &lv_style_plain);
  switch_team_bg_style.body.main_color = LV_COLOR_BLUE;
  switch_team_bg_style.body.grad_color = LV_COLOR_BLUE;
  switch_team_bg_style.body.radius = LV_RADIUS_CIRCLE;

  static lv_style_t switch_team_indic_style;
  lv_style_copy(&switch_team_indic_style, &lv_style_plain);
  switch_team_indic_style.body.main_color = LV_COLOR_RED;
  switch_team_indic_style.body.grad_color = LV_COLOR_RED;
  switch_team_indic_style.body.padding.inner = 0;
  switch_team_indic_style.body.padding.hor = 0;
  switch_team_indic_style.body.padding.ver = 0;
  switch_team_indic_style.body.shadow.width = 0;
  switch_team_indic_style.body.radius = LV_RADIUS_CIRCLE;

  lv_obj_t *label_team = lv_label_create(tab_auton, NULL);
  lv_label_set_text(label_team, "Choose Team Color:");
  lv_obj_align(label_team, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

  lv_obj_t *switch_team = lv_sw_create(tab_auton, NULL);
  lv_sw_off(switch_team);
  lv_obj_align(switch_team, NULL, LV_ALIGN_IN_LEFT_MID, 190, 0);

  lv_sw_set_style(switch_team, LV_SW_STYLE_KNOB_OFF, &switch_team_blue_style);
  lv_sw_set_style(switch_team, LV_SW_STYLE_KNOB_ON, &switch_team_red_style);
  lv_sw_set_style(switch_team, LV_SW_STYLE_BG, &switch_team_bg_style);
  lv_sw_set_style(switch_team, LV_SW_STYLE_INDIC, &switch_team_indic_style);
  ///////////
  lv_obj_t *label_front = lv_label_create(tab_auton, NULL);
  lv_label_set_text(label_front, "Front");
  lv_obj_align(label_team, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 100);

  lv_obj_t *label_back = lv_label_create(tab_auton, NULL);
  lv_label_set_text(label_back, "Back");
  lv_obj_align(label_back, NULL, LV_ALIGN_IN_TOP_LEFT, 220, 100);

  lv_obj_t *switch_side = lv_sw_create(tab_auton, NULL);
  lv_sw_off(switch_side);
  lv_obj_align(switch_side, NULL, LV_ALIGN_IN_LEFT_MID, 190, 100);
  /*
    lv_sw_set_style(switch_side, LV_SW_STYLE_KNOB_OFF, &switch_side_blue_style);
    lv_sw_set_style(switch_side, LV_SW_STYLE_KNOB_ON, &switch_side_red_style);
    lv_sw_set_style(switch_side, LV_SW_STYLE_BG, &switch_side_bg_style);
    lv_sw_set_style(switch_side, LV_SW_STYLE_INDIC, &switch_side_indic_style);
    */

  ////////////////////////////////////
}

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

/////////////////////////////////////////
//          Drivetrain Control         //
/////////////////////////////////////////
namespace drivetrain {
double multiplier = 1;
ControllerButton btnToggle(BTN_TILT_MID);

// control function that is run in a separate thread to prevent interruptions
void controlDrive(void *) {
  // motor definitions
  Motor drive_left_front(DLF_PORT, DLF_REV, BLUE, DEGREES);
  Motor drive_right_front(DRF_PORT, DRF_REV, BLUE, DEGREES);
  Motor drive_left_back(DLB_PORT, DLB_REV, BLUE, DEGREES);
  Motor drive_right_back(DRB_PORT, DRB_REV, BLUE, DEGREES);
  while (true) {
    double ly = masterController.getAnalog(ControllerAnalog::leftY) * 600;
    double lx = masterController.getAnalog(ControllerAnalog::leftX) * 600;
    double rx = masterController.getAnalog(ControllerAnalog::rightX) * 600;

    if (btnToggle.changedToPressed()){
      multiplier = multiplier == 1 ? 0.25 : 1;
    }


    drive_right_front.moveVelocity((ly - rx - lx) * multiplier);
    drive_right_back.moveVelocity((ly - rx + lx) * multiplier);
    drive_left_front.moveVelocity((ly + rx + lx) * multiplier);
    drive_left_back.moveVelocity((ly + rx - lx) * multiplier);
    pros::delay(10);
  }
}
} // namespace drivetrain

/////////////////////////////////////
//          Tilter Control         //
/////////////////////////////////////
/*
namespace tilt {
// Preset heights
const int TILT_UP = 200;   // height to relese stack
const int TILT_DOWN = 100; // normal resting height
const int TILT_LOW = 20;   // height for low towers
const int TILT_MED = 40;   // height for medium towers
const int TILT_HIGH = 60;  // height for tallest tower
// definition of buttons
ControllerButton btnUpAuto(BTN_TILT_UP_AUTO);
ControllerButton btnDownAuto(BTN_TILT_DOWN_AUTO);
ControllerButton btnUp(BTN_TILT_UP);
ControllerButton btnDown(BTN_TILT_DOWN);
ControllerButton btnLow(BTN_TILT_LOW);
ControllerButton btnMed(BTN_TILT_MID);
ControllerButton btnHigh(BTN_TILT_HIGH);
Potentiometer pot(TP_PORT);
auto controller = AsyncControllerFactory::posPID(
    boolToSign(TILT_REV) * TILT_PORT, pot, 0.001, 0.0, 0.0001);

// funtion to be run in opcontrol() to control the tilter
void controlTilt() {
  controller.flipDisable(true);

  if (btnUp.isPressed()) {
    controller.setTarget(200);
    controller.flipDisable(false);
  } else {
    controller.flipDisable(false);
  }

}
} // namespace tilt
*/

/////////////////////////////////////
//       Tilter Control mkII       //
/////////////////////////////////////
/*
namespace tilt2 {
// preset heights
enum heights { up = 920, down = 4095, low = 4095, med = 3800, high = 2700 };
// definition of buttons
ControllerButton btnUp(BTN_TILT_UP);
ControllerButton btnDown(BTN_TILT_DOWN);
ControllerButton btnLow(BTN_TILT_LOW);
ControllerButton btnMed(BTN_TILT_MID);
ControllerButton btnHigh(BTN_TILT_HIGH);
Potentiometer pot(TP_PORT);
// definition of controller
auto controller = AsyncControllerFactory::posPID(
    boolToSign(TILT_REV) * TILT_PORT, pot, 0.005, 0.000, 0.000025);

// funtion to be run in opcontrol() to control the tilter
void controlTilt() {
  if (btnUp.isPressed()) {
    controller.flipDisable(false);
    controller.setTarget(up);
  } else if (btnDown.isPressed()) {
    controller.flipDisable(false);
    controller.setTarget(down);
  } else if (btnLow.isPressed()) {
    controller.flipDisable(false);
    controller.setTarget(low);
  } else if (btnMed.isPressed()) {
    controller.flipDisable(false);
    controller.setTarget(med);
  } else if (btnHigh.isPressed()) {
    controller.flipDisable(false);
    controller.setTarget(high);
  } else {
    controller.flipDisable(true);
  }
  printf("pot: %f\n", pot.get());
}
} // namespace tilt2
*/

/////////////////////////////////////
//       Tilter Control mkII       //
/////////////////////////////////////
namespace tiltP {
// preset heights
enum heights { up = 920, down = 4095, low = 4095, med = 4000, high = 2700 };
// pLoop variables
double target;
double modifier;
// definition of buttons
ControllerButton btnUp(BTN_TILT_UP);
ControllerButton btnDown(BTN_TILT_DOWN);
ControllerButton btnLow(BTN_TILT_LOW);
//ControllerButton btnMed(BTN_TILT_MID);
ControllerButton btnHigh(BTN_TILT_HIGH);

Potentiometer pot(TP_PORT);
Motor motor(boolToSign(TILT_REV) * TILT_PORT);

void setTarget(double t, double m) {
  target = t;
  modifier = m;
}

void controlTilt(void *) {
  double error;
  double kP = 0.5;
  double potVal;
  while (true) {
    if (target == -1) {
      motor.moveVelocity(0);
    } else {
      potVal = pot.get();
      error = target - potVal;
      motor.moveVelocity(error * kP * modifier);
    }
    // printf("pot: %f\n", pot.get());
  }
}

void controlTarget() {
  if (btnUp.changedToPressed()) {
    setTarget(heights::up, 1);
  } else if (btnDown.changedToPressed()) {
    setTarget(heights::down, 1);
  } else if (btnLow.changedToPressed()) {
    setTarget(heights::low, 1);
  // }
  // else if (btnMed.changedToPressed()) {
  //   setTarget(heights::high, 1);
  } else if (btnHigh.changedToPressed()) {
    setTarget(heights::high, 1);
  } else if (btnUp.changedToReleased() || btnDown.changedToReleased() ||
             btnLow.changedToReleased() || btnHigh.changedToReleased()
           //btnMed.changedToReleased()
         ) {
    target = -1;
  }
}
} // namespace tiltP

/////////////////////////////////////
//          Roller Control         //
/////////////////////////////////////
namespace roll {
const int speed = 200;
double targetSpeed = 0;
int toggle = 1;
int brakeToggle = 1;
ControllerButton roll(BTN_ROLL_TOGGLE);
ControllerButton rollIn(BTN_ROLL_IN);
ControllerButton rollOut(BTN_ROLL_OUT);
ControllerButton rollCoast(BTN_ROLL_COAST);
MotorGroup roll_group({boolToSign(ROLLL_REV) * ROLLL_PORT,
                       boolToSign(ROLLR_REV) * ROLLR_PORT});

void controlRoll() {
  if (roll.changedToPressed()) {
    toggle++;
    if (toggle % 2 == 0)
      targetSpeed = speed;
    else
      targetSpeed = 0;
  } else if (rollCoast.changedToPressed()) {
    brakeToggle++;
    if (brakeToggle % 2 == 0)
      roll_group.setBrakeMode(AbstractMotor::brakeMode::coast);
    else
      roll_group.setBrakeMode(AbstractMotor::brakeMode::hold);
  } else if (rollIn.changedToPressed())
    targetSpeed = speed;
  else if (rollOut.changedToPressed())
    targetSpeed = -speed;
  else if (rollIn.changedToReleased() || rollOut.changedToReleased())
    targetSpeed = 0;
  roll_group.moveVelocity(targetSpeed);
}
} // namespace roll

/////////////////////////////////////
//           Macro Control         //
/////////////////////////////////////
namespace macros {
// buttons
ControllerButton btnStack(BTN_MACRO_STACK);

void stack() {
  if (roll::brakeToggle % 2 == 1)
    roll::brakeToggle++;
  roll::roll_group.setBrakeMode(AbstractMotor::brakeMode::coast);
  roll::targetSpeed = 0;
  tiltP::setTarget(tiltP::heights::up, 0.3);
}

void controlMacros() {
  if (btnStack.changedToPressed()) {
    stack();
  }
}
} // namespace macros

void autonomous() {
  // sets up chassis for easy drivetrain control in autonomous
  auto drive = ChassisControllerFactory::create(
      {boolToSign(DLF_REV) * DLF_PORT, boolToSign(DLB_REV) * DLB_PORT},
      {boolToSign(DRF_REV) * DRF_PORT, boolToSign(DRB_REV) * DRB_PORT},
      IterativePosPIDController::Gains{0.002, 0.000001, 0.000050}, // forward
      IterativePosPIDController::Gains{0.002, 0.000001, 0.000050}, // straight
      IterativePosPIDController::Gains{0.002, 0.000001, 0.000050}, // turn
      BLUE * (36.0 / 84.0),
      {6230, 35.5}); //{motor deg to m, motor deg to bot deg}
  auto driveController = AsyncControllerFactory::motionProfile(
      0.7116064, // Maximum linear velocity of the Chassis in m/s
      2.0,       // Maximum linear acceleration of the Chassis in m/s/s
      10.0,      // Maximum linear jerk of the Chassis in m/s/s/s
      drive);    // Chassis Controller

  // FOR TESTING ONLY
  // drive.moveDistance(48_in);
  // drive.turnAngle(360_deg);
  // driveController.moveTo({Point{0_ft, 0_ft, 0_deg}, Point{-3_ft, 0_ft,
  // 0_deg}});

  tiltP::motor.setBrakeMode(AbstractMotor::brakeMode::hold);
  roll::roll_group.moveVelocity(-200);
  pros::delay(500);
  tiltP::motor.moveVelocity(-200);
  pros::delay(1300);
  roll::roll_group.setBrakeMode(AbstractMotor::brakeMode::coast);
  roll::roll_group.moveVelocity(0);
  tiltP::motor.moveVelocity(200);
  pros::delay(800);
  drive.setMaxVelocity(300);
  drive.moveDistanceAsync(-4_ft);
  pros::delay(400);
  tiltP::motor.moveVelocity(0);
  drive.waitUntilSettled();
  drive.moveDistance(4_ft);
  drive.turnAngle(90_deg);
  pros::delay(5000);
  drive.moveDistance(3_ft);
  // driveController.moveTo(
  //     {Point{0_ft, 0_ft, 0_deg}, Point{2_ft, 2.5_ft, 8_deg}});
}

void opcontrol() {
  masterController.clear();
  tiltP::motor.setBrakeMode(AbstractMotor::brakeMode::hold);
  pros::Task taskDrive(drivetrain::controlDrive);
  pros::Task taskTilt(tiltP::controlTilt);
  roll::roll_group.setBrakeMode(AbstractMotor::brakeMode::hold);
  int last = 0;
  while (true) {
    if (roll::brakeToggle != last){
      if (roll::brakeToggle % 2 == 0)
        masterController.setText(0, 0, "PID : OFF");
      else
        masterController.setText(0, 0, "PID : ON ");
    }
    last = roll::brakeToggle;
    tiltP::controlTarget();
    macros::controlMacros();
    roll::controlRoll();
    pros::delay(20);
  }
}
