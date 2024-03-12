#include "vex.h"
#include "sylib/sylib.hpp"

using namespace vex;

competition Competition;

auto myLights = sylib::Addrled(20, 1, 64);
// addressable_led addrled(vex::triport(PORT20).A, 60 );
// digital_out PortA = digital_out(Brain.ThreeWirePort.A);

void pre_auton(void) {
  vexcodeInit();
  sylib::initialize();
}

void autonomous(void) {

}

void usercontrol(void) {
  Brain.Screen.setFillColor(purple); //Makes the background of the brain display black
  Brain.Screen.drawRectangle(0, 0, 480, 240); // Define the rectangle's size to cover the entire screen
  Brain.Screen.setFont(mono30);
  Brain.Screen.setPenColor(purple); //Defines the text color

  sylib::initialize();
  myLights.turn_on();
  // PortA.set(true);
  myLights.set_all(purple);
  // Brain.Screen.printAt(50, 150, "A: %f", PortA.value());
  while (true) {
    //Rainbow Lighting
      // myLights.gradient(0xFF0000, 0xFF0005, 0, 0, false, true);
      // myLights.cycle(*myLights, 10);
      // std::uint32_t clock = sylib::millis();
      // while (true) {
      //   sylib::delay_until(&clock, 10);
      // }
    wait(20, msec); 
  }
}

int main() {
  vexcodeInit();
}