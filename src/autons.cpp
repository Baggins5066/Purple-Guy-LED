#include "vex.h"

//JAR constants
  void default_constants(){
    // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
    chassis.set_drive_constants(10, 1.5, 0, 10, 0);
    chassis.set_heading_constants(6, .4, 0, 1, 0);
    chassis.set_turn_constants(12, .4, .03, 3, 15);
    chassis.set_swing_constants(12, .3, .001, 2, 15);

    // Each exit condition set is in the form (settle_error, settle_time, timeout).
    chassis.set_drive_exit_conditions(1.5, 300, 5000);
    chassis.set_turn_exit_conditions(1, 300, 3000);
    chassis.set_swing_exit_conditions(1, 300, 3000);
  }

  void odom_constants(){
    default_constants();
    chassis.drive_max_voltage = 8;
    chassis.drive_settle_error = 3;
  }

  void right_match_constants() {
    // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
    chassis.set_drive_constants(10, 1.5, 0, 5, 0);
    chassis.set_heading_constants(6, .4, 0, 1, 0);
    chassis.set_turn_constants(12, .4, .03, 1.5, 15);
    chassis.set_swing_constants(12, .3, .001, 1.9, 15);

    // Each exit condition set is in the form (settle_error, settle_time, timeout).
    chassis.set_drive_exit_conditions(1.5, 300, 5000);
    chassis.set_turn_exit_conditions(1, 150, 1500);
    chassis.set_swing_exit_conditions(1, 300, 3000);
}

void closeWinPointAuton(){
  //JAR setup
    default_constants();
    chassis.set_coordinates(0, 0, 0);
    chassis.drive_max_voltage = 12;
    chassis.turn_max_voltage = 12;
  Intake.setVelocity(100, percent);
  Intake.spinFor(forward, 720, deg,false);
  chassis.drive_to_point(6,44);
  chassis.turn_to_angle(-90);
  Intake.spin(reverse,100,percent);
  chassis.drive_distance(12);
  Drivetrain.setTimeout(1, seconds);
  chassis.drive_distance(-30);
  Intake.spin(forward,100,percent);
  chassis.turn_to_angle(42);
  chassis.drive_distance(-53);
  chassis.turn_to_angle(135);
  rightWing.set(true);
  chassis.turn_max_voltage = 6;
  chassis.turn_to_angle(0);
  rightWing.set(false);
  chassis.turn_to_angle(100);
  chassis.drive_to_point(-10,-6);
  chassis.drive_to_point(20,-13);
  Intake.spin(reverse,100,percent);
  chassis.turn_to_angle(90);
  chassis.drive_max_voltage = 12;
  chassis.turn_max_voltage = 12;
}

void farWinPointAuton(){
  default_constants();
  chassis.drive_distance(-36);
  Drivetrain.setTimeout(2,seconds);
  chassis.drive_distance(36);
}
  
void skillsSetup() {
  default_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.drive_distance(12);
  chassis.turn_to_angle(60);
  chassis.drive_distance(-20);
  rightWing.set(true);
  Lift.set(true);
}

void skillsAuton() {
  //JAR Setup
    default_constants();
    chassis.drive_max_voltage = 12;
    chassis.turn_max_voltage = 12;
    chassis.set_drive_exit_conditions(1.5, 300, 1000);
    chassis.set_turn_exit_conditions(1, 300, 1000);
  // Cata.spinTo(-130,degrees,100);
  skillsSetup();
  //Shooting
    Cata.spin(reverse,60,percent);
    wait(30, seconds);
    Lift.set(false);
    Cata.stop();
  rightWing.set(false);
  // Cata.spinTo(-130,degrees,100);
  // chassis.drive_max_voltage = 4;
  // chassis.turn_max_voltage = 4;
  chassis.drive_to_point(1, -12);
  chassis.drive_to_point(72,-9);
  chassis.turn_to_angle(-135);
  leftWing.set(true);
  chassis.drive_distance(-24);
  chassis.turn_to_angle(180);
  chassis.drive_to_point(74, 24);
  leftWing.set(false);
  chassis.drive_to_point(72, 10);
  chassis.drive_to_point(76,25);
  chassis.drive_to_point(41, 28);
  chassis.turn_to_angle(-135);
  leftWing.set(true);
  rightWing.set(true);
  chassis.drive_to_point(40, 34);
  chassis.drive_to_point(51, 50);
  chassis.drive_to_point(66, 58);
  leftWing.set(false);
  rightWing.set(false);
  chassis.drive_to_point(44, 57);
  chassis.drive_to_point(36, 70);
  leftWing.set(true);
  chassis.drive_to_point(67, 75);
  leftWing.set(false);
  chassis.drive_to_point(54, 100);
  rightWing.set(true);
  chassis.drive_to_point(77, 111);
  chassis.drive_to_point(89, 94);
  rightWing.set(false);
  chassis.drive_to_point(96, 86);
  chassis.drive_to_point(90, 103);
  Drivetrain.turnFor(360, deg);
  }

//JAR Template autons
  void turn_test(){
    chassis.turn_to_angle(5);
    chassis.turn_to_angle(30);
    chassis.turn_to_angle(90);
    chassis.turn_to_angle(225);
    chassis.turn_to_angle(0);
  }

  void swing_test(){
    chassis.left_swing_to_angle(90);
    chassis.right_swing_to_angle(0);
  }

  void full_test(){
    chassis.drive_distance(24);
    chassis.turn_to_angle(-45);
    chassis.drive_distance(-36);
    chassis.right_swing_to_angle(-90);
    chassis.drive_distance(24);
    chassis.turn_to_angle(0);
  }

  void odom_test(){
    chassis.set_coordinates(0, 0, 0);
    while(1){
      Brain.Screen.clearScreen();
      Brain.Screen.printAt(0,50, "X: %f", chassis.get_X_position());
      Brain.Screen.printAt(0,70, "Y: %f", chassis.get_Y_position());
      Brain.Screen.printAt(0,90, "Heading: %f", chassis.get_absolute_heading());
      Brain.Screen.printAt(0,110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
      Brain.Screen.printAt(0,130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
      task::sleep(20);
    }
  }

  void tank_odom_test(){
    odom_constants();
    chassis.set_coordinates(0, 0, 0);
    chassis.turn_to_point(24, 24);
    chassis.drive_to_point(24,24);
    chassis.drive_to_point(0,0);
    chassis.turn_to_angle(0);
  }

  void holonomic_odom_test(){
    odom_constants();
    chassis.set_coordinates(0, 0, 0);
    chassis.holonomic_drive_to_point(0, 18, 90);
    chassis.holonomic_drive_to_point(18, 0, 180);
    chassis.holonomic_drive_to_point(0, 18, 270);
    chassis.holonomic_drive_to_point(0, 0, 0);
  }