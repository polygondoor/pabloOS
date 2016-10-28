/*
 * Handles the motors
 */

// wheel diameter of robot
float wheelDiam = 79;

// Default configurations for stepper motor control
float maxSpeedLeft = 400;
float accelerationLeft = 100;

float maxSpeedRight = 400;
float accelerationRight = 100;

// register the number of steps by processing the captured settings
long steps = 0;

/*
 * This method captures all the knob settings
 * and gives them to the steppers.
 */
void captureSettings() {

  // so if I make the the knob think in mm, then
  // 1 turn is  (wheelDiam * 3.1416)
  // So, if someone says 100mm, then how many turns is that?
  // turns = configuredDistance / (wheelDiam * 3.1416)
  // given that 1 turn is 2048 steps then
  // turns in steps = 2048 * configuredDistance / (wheelDiam * 3.1416)

  // RIGHT WHEEL
  stepper_r.setMaxSpeed(setting_right_wheel_speed * 10); // max 400
  stepper_r.setAcceleration(accelerationRight);
  // calculate how many steps to go (here we divide by 2 because the bounce goes fowards and backwards)
  steps = (setting_right_wheel_distance * 2048 / (wheelDiam * 3.1416) / 2);
  stepper_r.moveTo(steps);
  // message(String(steps) );

  // LEFT WHEEL
  stepper_l.setMaxSpeed(setting_left_wheel_speed * 10); // max 400
  stepper_l.setAcceleration(accelerationLeft);
  steps = (setting_left_wheel_distance * 2048 / (wheelDiam * 3.1416) / 2);
  stepper_l.moveTo(steps);
}

float speed_l;
float speed_r;
/*
 * Allows programing the Artbot by defining how far each wheel will move
 * Both wheels are moved that distance within the same time frame
 */
void turn_wheels_mm(long distance_l, long distance_r, float top_speed){

  set_wheels_mm(distance_l, distance_r, top_speed);

  // Could make the check "> 1" so that the infinitesimal stop is not perceivable
  while(stepper_l.distanceToGo() != 0 || stepper_r.distanceToGo() != 0){
    stepper_l.run();
    stepper_r.run();
  }

  // reset the steppers to position 0
  stepper_r.setCurrentPosition(0);
  stepper_l.setCurrentPosition(0);
}

void turn_wheels_mm(long distance_l, long distance_r){
  turn_wheels_mm( distance_l, distance_r, 300.0);
}

/*
 * Sets the wheels to turn without turning them
 */
void set_wheels_mm(long distance_l, long distance_r,  float top_speed) {
  // calculate if there is a differential in the speeds
  if (abs(distance_l) >= abs(distance_r) ) {
    speed_l = top_speed;
    speed_r = top_speed * ((float)abs(distance_r) / (float)abs(distance_l));
  } else {
    speed_r = top_speed;
    speed_l = top_speed * ((float)abs(distance_l) / (float)abs(distance_r));
  }

  // translate distance into steps
  stepper_l.setMaxSpeed(speed_l);
  stepper_l.setAcceleration(100000);
  stepper_r.setMaxSpeed(speed_r);
  stepper_r.setAcceleration(100000);

  stepper_l.moveTo(distanceToSteps(distance_l));
  stepper_r.moveTo(distanceToSteps(distance_r));
}

void set_wheels_mm(long distance_l, long distance_r){
  set_wheels_mm( distance_l, distance_r, 300.0);
}

/*
 * Allows finding out when wheels should be stopped.
 */
bool wheels_still_turning(){
    // Could make the check "> 1" so that the infinitesimal stop is not perceivable
  if(stepper_l.distanceToGo() != 0 || stepper_r.distanceToGo() != 0){
    stepper_l.run();
    stepper_r.run();
    return true;
  } else {
    // reset the steppers to position 0
    stepper_r.setCurrentPosition(0);
    stepper_l.setCurrentPosition(0);
    return false;
  }

}

/*
 * Converts distance covered by wheel into steps for stepper driver.
 */
long distanceToSteps(long mm) {
  return mm * 2048 / (wheelDiam * 3.1416);
}

/*
 * Utility to stop steppers, and set them back to a 0 position
 */
void stopAndResetSteppers() {
  // stop everything
  stepper_r.stop(); // Stop as fast as possible: sets new target
  stepper_l.stop(); // Stop as fast as possible: sets new target

  // set fast accelerations
  stepper_l.setAcceleration(200);
  stepper_r.setAcceleration(200);

  // leep going until everything has stopper
  while(stepper_l.distanceToGo() > 0 || stepper_r.distanceToGo() > 0){
    stepper_l.run();
    stepper_r.run();
  }

  // reset the steppers to position 0
  stepper_r.setCurrentPosition(0);
  stepper_l.setCurrentPosition(0);

  // tell the system that we are no longer drawing
  isDrawing = false;
  delay(1000);
}
