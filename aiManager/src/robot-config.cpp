#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftIntake = motor(PORT6, ratio18_1, false);
motor rightIntake = motor(PORT7, ratio18_1, true);
motor bottomRoller = motor(PORT5, ratio18_1, false);
motor topRoller = motor(PORT4, ratio18_1, false);
motor drive_left = motor(PORT2, ratio18_1, false);
motor drive_right = motor(PORT1, ratio18_1, true);
encoder leftEncoder = encoder(Brain.ThreeWirePort.C);
encoder rightEncoder = encoder(Brain.ThreeWirePort.E);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}