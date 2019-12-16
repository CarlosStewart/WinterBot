#ifndef Drivetrain_H
#define Drivetrain_H
class Drivetrain {
  double sL;
  double sR;

  // constants
  double slewIncrement;

  // movement targets
  double targetForwardVel;
  double targetTurnVel;
  double targetStrafeVel;

  bool slewOn;

public:
  // default constructor
  Drivetrain();

  // overload constructor
  Drivetrain(double tSlewIncrement, double tSL, double tSR);

  // moves the drivetrain with (or without) slew (for joystick control)
  void updateArcade(double tForwardVel, double tTurnVel);
  // moves the drivetrain with (or without) slew (for joystick control)
  void updateArcade(double tForwardVel, double tTurnVel, double tStrafeVel);

  // other methods
  // toggles slew, with optional forced setting
  void tglSlew();
  // toggles slew, with optional forced setting
  void tglSlew(bool tOn);

  // calculates the orientation from start
  double getTheta();

  class Control {
    double kpF;
    double kiF;
    double kdF;
    double iazF;
    double errF;
    double sErrF;
    double lErrF;
    double tarF;
    double outF;

    double kpT;
    double kiT;
    double kdT;
    double iazT;
    double errT;
    double sErrT;
    double lErrT;
    double tarT;
    double outT;

  public:
    // default constructor for setting PID constants
    Control();

    bool settledF;

    // basic movement methods
    // moves the drivetrain forward, and turns at specific velocities
    void moveArcade(double tForwardVel, double tTurnVel);
    // moves the drivetrain forward, and turns at specific velocities
    void moveArcade(double tForwardVel, double tTurnVel, double tStrafeVel);
    // moves the drivetrain based on velocities of both sides
    void moveTank(double tRPMLeft, double tRPMRight);

    // accessors
    // returns the output of the F PID loop
    double getOutF();
    // returns the output of the T PID loop
    double getOutT();

    // returns if the F PID loop is done
    bool isSettledF();
    // returns if the T PID loop is done
    bool isSettledT();

    // mutators
    // sets the target for the F PID loop
    void setTarF(double tTarF);
    // sets the target for the T PID loop
    void setTarT(double tTarT);

    // steps through the PID for Distance and Angle
    void itteratePIDF();
    void itteratePIDT();

  } ctrl;
};
extern Drivetrain dvtn;
#endif
