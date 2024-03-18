#include "vex.h"
#include "sylib/sylib.hpp"

using namespace vex;

competition Competition;

auto LEDs = sylib::Addrled(22, 6, 64); //Creates LEDs sylib object

void idleLEDs() {
  LEDs.gradient(purple, white,64,0); //Start color, End color, Fade width, Start position
  LEDs.cycle(*LEDs,10,0);
  // LEDs.set_pixel(red,0);
  // LEDs.set_pixel(green,32);
  // LEDs.set_pixel(blue,63);
}

void shootTriball() {
  Cata.spinFor(-180,deg,false);
  LEDs.set_all(orange);
  wait(0.5,sec);
  idleLEDs();
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
  //LEDs
    idleLEDs();
  while (true) {
    Controller1.ButtonL1.pressed(shootTriball);
    wait(20, msec); 
  }
}

int main() {
  sylib::initialize();
  vexcodeInit();
}