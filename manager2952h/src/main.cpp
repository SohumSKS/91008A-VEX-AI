/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Sep 25 2019                                           */
/*    Description:  Clawbot Template (Drivetrain, No Gyro)                    */
/*                                                                            */
/*    Name:                                                                   */
/*    Date:                                                                   */
/*    Class:                                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    2, 1            
// leftIntake           motor         6               
// rightIntake          motor         7               
// botOuttake           motor         5               
// topOuttake           motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Drivetrain.driveFor(forward, double(56), inches, 25, vex::velocityUnits::pct, false);
  vex::task::sleep(1000);
  rightIntake.rotateTo(5, rotationUnits::rev, 50, vex::velocityUnits::pct, false);
  leftIntake.rotateTo(5, rotationUnits::rev, 50, vex::velocityUnits::pct, true);
  Drivetrain.turnFor(double(90), deg);
}
