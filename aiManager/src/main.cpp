/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       sohum                                                     */
/*    Created:      Mon Aug 31 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include <cmath>
using namespace vex;

competition Competition;

ai::jetson  jetson_comms;

ai::robot_link link(PORT9, "robot_91008A", linkType::manager );

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          Auto_Isolation Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous isolation  */
/*  phase of a VEX AI Competition.                                           */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void auto_Isolation(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                        Auto_Interaction Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous interaction*/
/*  phase of a VEX AI Competition.                                           */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


void auto_Interaction(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          AutonomousMain Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/

bool firstAutoFlag = true;

void autonomousMain(void) {
  // ..........................................................................
  // The first time we enter this function we will launch our Isolation routine
  // When the field goes disabled after the isolation period this task will die
  // When the field goes enabled for the second time this task will start again
  // and we will enter the interaction period. 
  // ..........................................................................

  if(firstAutoFlag)
    auto_Isolation();
  else 
    auto_Interaction();

  firstAutoFlag = false;
}


/*----------------------------------------------------------------------------*/
FILE *fp = fopen("/dev/serial2","wb");

static MAP_RECORD local_map;
int rot(double inches){
  return double(inches/12.57);
}
int getClosestIndex(){
  jetson_comms.get_data( &local_map );
  int indexClosest = 0;
  for(int i = 0; i < local_map.mapnum; i++) {
    float mindistx = std::abs(local_map.mapobj[0].positionX - local_map.pos.x);
    float mindisty = std::abs(local_map.mapobj[0].positionY - local_map.pos.y);
    if(std::abs(local_map.mapobj[i].positionX - local_map.pos.x) + std::abs(local_map.mapobj[i].positionY - local_map.pos.y) < mindistx + mindisty){
      mindistx = std::abs(local_map.mapobj[i].positionX - local_map.pos.x);
      mindisty = std::abs(local_map.mapobj[i].positionY - local_map.pos.y);
      indexClosest = i;
    }
  }
  return indexClosest;
}
void driveTo(float rotations, float inches, float speed, bool directionfw){
  leftEncoder.resetRotation();
  rightEncoder.resetRotation();
  int rotationval;
  if(rotations == 0){
    rotationval = rot(inches);
  }
  else{
    rotationval = rotations;
  }
  if(directionfw){
    drive_left.spin(forward, speed, percent);
    drive_right.spin(forward, speed, percent);
  }
  else{
    drive_left.spin(reverse, speed, percent);
    drive_right.spin(reverse, speed, percent);
  }
  while(leftEncoder.rotation(rotationUnits::rev) == rotationval && rightEncoder.rotation(rotationUnits::rev) == rotationval){
    drive_left.stop();
    drive_right.stop();
  }
}

void rotateToHeading(float head, bool dir){
  float x, y, heading;
  link.get_local_location(x, y, heading);
  while(std::abs(head - (180 - (heading / (-2 * M_PI ) * 360))) != 5){
    if(dir){
      drive_left.spin(reverse, 5, percent);
      drive_right.spin(forward, 5, percent);
    }
    else{
      drive_left.spin(forward, 5, percent);
      drive_right.spin(reverse, 5, percent);
    }
  }
  drive_left.stop();
  drive_right.stop();
}
int closestBlue;
bool blueFound = false;
void checkBlue() {
  while(true){
    int closestBlue;
    bool blueFound = false;

    fprintf(fp,"ID: %ld\n",local_map.boxobj[0].classID);
    fprintf(fp,"X: %ld\n",local_map.boxobj[0].x);

    for(int i=0; i<local_map.boxnum; i++) {
      if(local_map.boxobj[i].classID == 1 && !blueFound) {
        closestBlue = i;
        blueFound = true;
      }
    }
    this_thread::sleep_for(300);
  }
}
void getNearestBall(int colorID) {
  // Find the box obj corresponding to the nearest ball, comparing by depth from the box objects

  MAP_RECORD mapRecord;
  jetson_comms.get_data(&mapRecord);
  jetson_comms.request_map();

  fifo_object_box nearestBall;
  float minDistance = -1;

  for (int i = 0; i < mapRecord.boxnum; i++) {
    fifo_object_box box = mapRecord.boxobj[i];

    if (box.classID == colorID) {
      float distance = box.depth / 25.4; // depth of object in inches

      if (minDistance == -1 || minDistance > distance) {
        nearestBall = box;
        minDistance = distance;
      }
    }
  }
}
void firstBall() {
    driveTo(0, 56, 10, true);
    vex::task::sleep(1000);
    rightIntake.rotateTo(5, rotationUnits::rev, 50, vex::velocityUnits::pct, false);
    leftIntake.rotateTo(5, rotationUnits::rev, 50, vex::velocityUnits::pct, true);
    rotateToHeading(120, true);
}
void driveToBlue() {
  while(true){
    while(!blueFound) {
      drive_left.spin(forward, 5, percent);
      drive_right.spin(reverse, 5, percent);
    }
    drive_left.stop();
    drive_right.stop();
    while(local_map.boxobj[closestBlue].x < 120) {
       drive_left.spin(reverse, 5, percent);
       drive_right.spin(forward, 5, percent);
    }
    drive_left.stop();
    drive_right.stop();
    while(local_map.boxobj[closestBlue].x > 200) {
      drive_left.spin(forward, 5, percent);
      drive_right.spin(reverse, 5, percent);
    }      
    drive_left.stop();
    drive_right.stop();
    while(local_map.boxobj[closestBlue].depth > 200) {
      drive_left.spin(forward, 5, percent);
      drive_right.spin(reverse, 5, percent);
    }
  }
}


int main() {

    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    // local storage for latest data from the Jetson Nano
    static MAP_RECORD       local_map;

    // RUn at about 15Hz
    int32_t loop_time = 66;

    // start the status update display
    thread t1(dashboardTask);
    
    thread t2 = thread(firstBall);
    thread t3 = thread(checkBlue);

    // Set up callbacks for autonomous and driver control periods.
    //Competition.autonomous(autonomousMain);

    // print through the controller to the terminal (vexos 1.0.12 is needed)
    // As USB is tied up with Jetson communications we cannot use
    // printf for debug.  If the controller is connected
    // then this can be used as a direct connection to USB on the controller
    // when using VEXcode.

    while(1) {
        // get last map data
        jetson_comms.get_data( &local_map );

        // set our location to be sent to partner robot
        link.set_remote_location( local_map.pos.x, local_map.pos.y, local_map.pos.az );

        //fprintf(fp, "%.2f %.2f %.2f\n", local_map.pos.x, local_map.pos.y, local_map.pos.az  );

        // request new data    
        // NOTE: This request should only happen in a single task.    
        jetson_comms.request_map();

        // Allow other tasks to run
        this_thread::sleep_for(loop_time);
    }
      
      //while(local_map.mapobj[indexClosest].positionX)
}