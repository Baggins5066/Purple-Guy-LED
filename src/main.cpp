#include "vex.h"
#include "sylib/sylib.hpp"

using namespace vex;

competition Competition;

//LED definitions
  auto coreLEDs = sylib::Addrled(22,6,64); //Creates LEDs sylib object
  auto leftDriveLEDs = sylib::Addrled(16, 1, 55); //Creates LEDs sylib object
  auto rightDriveLEDs = sylib::Addrled(17,1,55); //Creates LEDs sylib object

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
bool desiredLiftPosition = false;

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

void initialize() {
}

void pre_auton(void) {
  vexcodeInit();
}

void autonomous(void) {
}

void usercontrol(void) {
  //Brain Text
    Brain.Screen.setFillColor(purple); //Makes the background of the brain display black
    Brain.Screen.drawRectangle(0, 0, 480, 240); // Define the rectangle's size to cover the entire screen
    Brain.Screen.setFont(mono30);
    Brain.Screen.setPenColor(purple); //Defines the text color
    Brain.Screen.printAt(50, 150, "ULTRAVIOLET");
  color coreColor = purple;
  color LDColor = purple;
  color RDColor = purple;
  Drivetrain.setStopping(brake);
  Cata.setStopping(coast);
  Cata.setVelocity(100, percent);
  while (true) {
    coreColor = cataSensor.color();
    Controller1.ButtonL1.pressed(shootTriball);
    leftDriveLEDs.set_pixel(LDColor,0);
    leftDriveLEDs.rotate(1,false);
    rightDriveLEDs.set_pixel(RDColor,0);
    rightDriveLEDs.rotate(1,false);
    coreLEDs.set_pixel(coreColor,0);
    coreLEDs.rotate(1,false);
    if (Controller1.Axis1.position() > 25) {
      RDColor = white;
    }
    else {
      RDColor = coreColor;
    }
    if (Controller1.Axis1.position() < -25) {
      LDColor = white;
    }
    else {
      LDColor = coreColor;
    }

    // std::uint32_t clock = sylib::millis();
    // sylib::delay_until(&clock, 10);
    wait(10, msec); 
  }
}

int main() {
  sylib::initialize();
  vexcodeInit();
}