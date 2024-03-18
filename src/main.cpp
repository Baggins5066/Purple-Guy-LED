#include "vex.h"
#include "sylib/sylib.hpp"

using namespace vex;

competition Competition;

auto LEDs = sylib::Addrled(22, 6, 64); //Creates LEDs sylib object

void initialize() {
  sylib::initialize();
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
  while (true) {
    //Rainbow Lighting
      // myLights.gradient(0xFF0000, 0xFF0005, 0, 0, false, true);
      // myLights.cycle(*myLights, 10);
      // std::uint32_t clock = sylib::millis();
      // while (true) {
      //   sylib::delay_until(&clock, 10);
    wait(20, msec); 
  }
}

int main() {
  sylib::initialize();
  LEDs.turn_on();
  // myLights.set_all(purple);
  // wait(2,sec);
  LEDs.gradient(purple, white,64,0);
  LEDs.cycle(*LEDs,10,0);
  vexcodeInit();
}