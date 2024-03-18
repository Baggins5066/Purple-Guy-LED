#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors //Add definitions to robot-config.h
  controller Controller1 = controller(primary);
  inertial DrivetrainInertial = inertial(PORT15);
  optical cataSensor = optical(PORT10);
  rotation cataRotation = rotation(PORT16);
  //Drivetrain devices
    motor leftMotorA = motor(PORT1, ratio6_1, true);
    motor leftMotorB = motor(PORT2, ratio6_1, true);
    motor leftMotorC = motor(PORT3, ratio6_1, true);
    motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB, leftMotorC);
    motor rightMotorA = motor(PORT6, ratio6_1, false);
    motor rightMotorB = motor(PORT7, ratio6_1, false);
    motor rightMotorC = motor(PORT9, ratio6_1, false);
    motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB, rightMotorC);
    smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainInertial, 319.19, 320, 40, mm, 1);
  motor Cata = motor(PORT12, ratio36_1, false);
  motor Intake = motor(PORT11, ratio6_1, false);
  digital_out Lift = digital_out(Brain.ThreeWirePort.A);
  digital_out barrierHanger = digital_out(Brain.ThreeWirePort.D);
  digital_out leftWing = digital_out(Brain.ThreeWirePort.C);
  digital_out rightWing = digital_out(Brain.ThreeWirePort.B);
  
// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      //Miles' setup:
        // left = Axis3 + Axis1
        // right = Axis3 - Axis1
      //Stock setup:
        // left = -Axis3 + Axis1
        // right = -Axis3 - Axis1
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
      int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}