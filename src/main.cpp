#include "vex.h"
#include "sylib/sylib.hpp"

using namespace vex;

competition Competition;

//LED definitions
  auto coreLEDs = sylib::Addrled(22,6,64); //Creates LEDs sylib object
  auto leftDriveLEDs = sylib::Addrled(16, 1, 55); //Creates LEDs sylib object
  auto rightDriveLEDs = sylib::Addrled(17,1,55); //Creates LEDs sylib object

bool desiredLiftPosition = false;

void UVGradient() {
  leftDriveLEDs.gradient(purple, white,64,0);
  leftDriveLEDs.cycle(*leftDriveLEDs,10,0);
}

void shootTriball() {
  Cata.spinFor(-180,deg,false);
  leftDriveLEDs.set_all(orange);
  rightDriveLEDs.set_all(orange);
  coreLEDs.set_all(orange);
}

void toggleLeftWing() {
  if (leftWing.value() == false) {
    leftWing.set(true);
  }
  else {
    leftWing.set(false);
  }
}

void toggleRightWing() {
  if (rightWing.value() == false) {
    rightWing.set(true);
    
  }
  else {
    rightWing.set(false);
  }
}

void toggleBarrierHanger() {
  if (barrierHanger.value() == false) {
    barrierHanger.set(true);
  }
  else {
    barrierHanger.set(false);
  }
}

void toggleLift() {
  if (Lift.value() == false) {
    Lift.set(true);
    desiredLiftPosition = true;
  }
  else {
    Lift.set(false);
    desiredLiftPosition = false;
  }
}

void retractAllWings() {
  barrierHanger.set(false);
  leftWing.set(false);
  rightWing.set(false);
}

Drive chassis(
  ZERO_TRACKER_ODOM, 
  motor_group(leftMotorA, leftMotorB, leftMotorC), 
  motor_group(rightMotorA, rightMotorB, rightMotorC), 
  PORT15,
  3.25,
  0.6,
  360,
  PORT1,     
  -PORT2,
  PORT3,     
  -PORT4, 3, 2.75, -2, 1, -2.75, 5.5
);

void initialize() {
}

void pre_auton(void) {
  vexcodeInit();
}

void autonomous(void) {
  leftDriveLEDs.set_all(purple);
  rightDriveLEDs.set_all(purple);

  // closeWinPointAuton();
  // farWinPointAuton();
  // skillsAuton();
}

void usercontrol(void) {
  //BRAIN TEXT
    Brain.Screen.setFillColor(purple); //Makes the background of the brain display black
    Brain.Screen.drawRectangle(0, 0, 480, 240); // Define the rectangle's size to cover the entire screen
    Brain.Screen.setFont(mono30);
    Brain.Screen.setPenColor(purple); //Defines the text color
    Brain.Screen.printAt(50, 150, "ULTRAVIOLET");
  default_constants();
  color coreColor = purple;
  color LDColor = purple;
  color RDColor = purple;
  chassis.set_coordinates(0, 0, 0);
  Drivetrain.setStopping(brake);
  Cata.setStopping(coast);
  Cata.setVelocity(100, percent);

  // skillsSetup(); //Uncomment when running Skills Auton

  Cata.setTimeout(1, seconds);
  Intake.setVelocity(100,percent);
  while (true) {
    Brain.Screen.printAt(50, 100, "BATTERY CHARGE: %d%%", Brain.Battery.capacity(), "%");
    Brain.Screen.printAt(50, 150, "X: %.1f", chassis.get_X_position());
    Brain.Screen.printAt(50, 200, "Y: %.1f", chassis.get_Y_position());
    // coreColor = cataSensor.color();
    //LEDs
      leftDriveLEDs.set_pixel(LDColor,0);
      leftDriveLEDs.rotate(1,false);
      rightDriveLEDs.set_pixel(RDColor,0);
      rightDriveLEDs.rotate(1,false);
      if (((Controller1.Axis3.position() > 25) or (Controller1.Axis3.position() < -25)) and !((Controller1.Axis1.position() < -25) or (Controller1.Axis1.position() > 25))) {
        LDColor = white;
        RDColor = white;
      }
      else if ((Controller1.Axis1.position() < -25) and !((Controller1.Axis3.position() > 25) or (Controller1.Axis3.position() < -25))) {
        LDColor = orange;
        RDColor = purple;
      }
      else if ((Controller1.Axis1.position() > 25) and !((Controller1.Axis3.position() > 25) or (Controller1.Axis3.position() < -25))) {
        LDColor = purple;
        RDColor = orange;
      }
      else if ((Controller1.Axis1.position() < -25) and ((Controller1.Axis3.position() > 25) or (Controller1.Axis3.position() < -25))) {
        LDColor = orange;
        RDColor = white;
      }
      else if ((Controller1.Axis1.position() > 25) and ((Controller1.Axis3.position() > 25) or (Controller1.Axis3.position() < -25))) {
        LDColor = white;
        RDColor = orange;
      }
      else {
        LDColor = purple;
        RDColor = purple;
      }
    //CATA CONTROLS
      if (Controller1.ButtonL1.pressing()) {
        Lift.set(true);
        Cata.spin(reverse,60,percent);
      }
      else {
        if (cataSensor.isNearObject()) {
          Cata.spin(reverse,60,percent);
        }
        else {
          Cata.stop();
        }
        if (desiredLiftPosition == true) {
          Lift.set(true);
        }
        else {
          Lift.set(false);
        }
      }
      if (cataSensor.isNearObject()) {
        cataSensor.setLight(ledState::off);
      }
      else {
        cataSensor.setLight(ledState::on);
      }
    //LIFT CONTROLS
      Controller1.ButtonL2.pressed(toggleLift);
    //INTAKE CONTROLS
      if (Controller1.ButtonR1.pressing()) {
        Intake.spin(forward);
      }
      else if (Controller1.ButtonR2.pressing()) {
        Intake.spin(reverse);
      }
      else {
        Intake.stop();
      }
    //WING CONTROLS
      Controller1.ButtonDown.pressed(retractAllWings);
      Controller1.ButtonA.pressed(toggleLeftWing);
      Controller1.ButtonA.pressed(toggleRightWing);
      //LEFT WING
        Controller1.ButtonLeft.pressed(toggleLeftWing);
      //RIGHT WING
        Controller1.ButtonRight.pressed(toggleRightWing);
      //BARRIER HANGER
        Controller1.ButtonUp.pressed(toggleBarrierHanger);
    wait(10, msec); 
  }
}

int main() {
  sylib::initialize();
  vexcodeInit();
}