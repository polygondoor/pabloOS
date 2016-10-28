/*
  Handles the rotary controller
*/

void setupRotaryEncoder(){
  pinMode(rotaryEncoder1_set_clkPin, INPUT); // clk
  pinMode(rotaryEncoder1_set_dtPin, INPUT); // dt
  pinMode(rotaryEncoder1_set_btnPin, INPUT_PULLUP); // btn
}

/*
 * This method reads all the rotary encoders
 */
void readRotaryEncoders() {
  rotaryEncoder1_read_clkPin = digitalRead(rotaryEncoder1_set_clkPin); // orange cable, CLK
  rotaryEncoder1_read_dtPin = digitalRead(rotaryEncoder1_set_dtPin);

  // rotaryMode; // Can be 0 1 2 or 3 (depending on which value we are changing)

  if ((rotaryEncoder1_read_clkPin != rotaryEncoder1_previousRead_clkPin) && (rotaryEncoder1_read_clkPin == LOW)) { // Knob Rotated l when aVal changes, BUT use only if aVal is LOW.
    if (rotaryEncoder1_read_dtPin == LOW) {
      // INCREMENT
      if (rotaryMode == 0) {
        setting_right_wheel_distance += rotary_increment;
        if (setting_right_wheel_distance > 99999) setting_right_wheel_distance = 99999;
      }
      else if (rotaryMode == 1) {
        setting_right_wheel_speed += 1;
        if (setting_right_wheel_speed > 50) setting_right_wheel_speed = 50;
      }
      else if (rotaryMode == 2) {
        setting_left_wheel_speed += 1;
        if (setting_left_wheel_speed > 50) setting_left_wheel_speed = 50;
      }
      else {
        setting_left_wheel_distance += rotary_increment;
        if (setting_left_wheel_distance > 99999) setting_left_wheel_distance = 99999;
      }
      report();
    }
    else {
      // DECREMENT
      if (rotaryMode == 0) {
        setting_right_wheel_distance -= rotary_increment;
      }
      else if (rotaryMode == 1) {
        setting_right_wheel_speed -= 1;
      }
      else if (rotaryMode == 2) {
        setting_left_wheel_speed -= 1;
      }
      else {
        setting_left_wheel_distance -= rotary_increment;
      }
      report();
    }
  }

  rotaryEncoder1_previousRead_clkPin = rotaryEncoder1_read_clkPin; // Don’t forget this
}

void cycleRotaryIncrement(){
  if (rotary_increment == 1) {
    rotary_increment = 10;
  }
  else if (rotary_increment == 10) {
    rotary_increment = 100; 
  }
  else if (rotary_increment == 100) {
    rotary_increment = 1000;
  }
  else if (rotary_increment == 1000) {
    rotary_increment = 1;
  }
}
