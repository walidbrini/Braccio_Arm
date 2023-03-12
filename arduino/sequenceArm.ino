#include "BraccioV2.h"
Braccio arm;
/*
 Basic_Movement.ino - version 0.1
 Written by Lukas Severinghaus
 Demonstrates basic movement of the arm using single joint absolute
 and relative positioning. Also shows the use of safe delay with
 and without custom intervals.
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
//Set these values from the min/max gripper joint values below.
#define GRIPPER_CLOSED 100
#define GRIPPER_OPENED 15

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing... Please Wait");//Start of initialization, see note below regarding begin method.

  //Update these lines with the calibration code outputted by the calibration program.
  arm.setJointCenter(WRIST_ROT, 90);
  arm.setJointCenter(WRIST, 90);
  arm.setJointCenter(ELBOW, 95);
  arm.setJointCenter(SHOULDER, 90);
  arm.setJointCenter(BASE_ROT, 70);
  arm.setJointCenter(GRIPPER, 60);//Rough center of gripper, default opening position

  //Set max/min values for joints as needed. Default is min: 0, max: 180
  //The only two joints that should need this set are gripper and shoulder.
  arm.setJointMax(GRIPPER, 100);//Gripper closed, can go further, but risks damage to servos
  arm.setJointMin(GRIPPER, 15);//Gripper open, can't open further

  //There are two ways to start the arm:
  //1. Start to default position.
  arm.begin(true);// Start to default vertical position.
  //This method moves the arm to the values specified by setJointCenter
  //and by default will make the arm be roughly straight up.

  //2. Start to custom position.
  //arm.begin(false);
  //arm.setAllNow(base_rot_val, shoulder_val, elbow_val, wrist_val, wrist_rot_val, gripper_val);
  //This method allows a custom start position to be set, but the setAllNow method MUST be run
  //immediately after the begin method and before any other movement commands are issued.


  //NOTE: The begin method takes approximately 8 seconds to start, due to the time required
  //to initialize the power circuitry.
  Serial.println("Initialization Complete");
}

void loop() {
  //Begin loop
  //Open the gripper
  openGripper();

  //Delay for 3000ms while still updating movement, by default every 10ms
  arm.safeDelay(3000);

  //Close the gripper
  closeGripper();

  arm.safeDelay(3000);

  //Set the absolute position of the Elbow to 50 degrees
  arm.setOneAbsolute(ELBOW, 50);
  arm.safeDelay(3000);

  //Set the Wrist to a position 30 degrees past its current position
  arm.setOneRelative(WRIST, 30);
  arm.safeDelay(3000);

  //Set the Wrist to a position 30 degrees behind its current position
  arm.setOneRelative(WRIST, -30);

  //Delay for 3000ms while still updating the movement every 20ms
  arm.safeDelay(3000, 20);

  //Set the Elbow to the center position as recorded in the calibration information.
  arm.setOneAbsolute(ELBOW, arm.getCenter(ELBOW));
  arm.safeDelay(3000);
}

void openGripper(){
  //Set the gripper position to open
  arm.setOneAbsolute(GRIPPER, GRIPPER_OPENED);
}

void closeGripper(){
  //Set the gripper position to closed
  arm.setOneAbsolute(GRIPPER, GRIPPER_CLOSED);
}
