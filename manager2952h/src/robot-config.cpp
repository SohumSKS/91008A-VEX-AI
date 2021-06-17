#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftDriveSmart = motor(PORT2, ratio18_1, false);
motor RightDriveSmart = motor(PORT1, ratio18_1, true);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 381, 279.4, mm, 1);
motor leftIntake = motor(PORT6, ratio18_1, false);
motor rightIntake = motor(PORT7, ratio18_1, true);
motor botOuttake = motor(PORT5, ratio18_1, false);
motor topOuttake = motor(PORT4, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}