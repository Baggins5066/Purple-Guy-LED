using namespace vex;

extern brain Brain;

// VEXcode devices
    extern controller Controller1;
    //Drivetrain 
        extern smartdrive Drivetrain;
        extern motor leftMotorA;
        extern motor leftMotorB;
        extern motor leftMotorC;
        extern motor rightMotorA;
        extern motor rightMotorB;
        extern motor rightMotorC;
        extern motor_group leftDriveMotors;
        extern motor_group rightDriveMotors;
    //Wings
        extern digital_out leftWing;
        extern digital_out rightWing;
        extern digital_out barrierHanger;
    extern motor Cata;
    extern motor Intake;
    extern digital_out Lift;
    extern optical cataSensor;
    
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );