/*
  Handles the OLED display objects
*/

Adafruit_SSD1306 OLEDScreen(4); //OLED_RESET

void setupDisplay(){
  // Initialise the OLED display
  // Note: it is necessary to change a value in the Adafruit_SSD1306 library to set the screen size to 128x64
  OLEDScreen.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  OLEDScreen.clearDisplay();

  // Set some default values for writing to the OLED screen
  OLEDScreen.setTextColor(WHITE);

  // Write "ARTBOT" in big
  OLEDScreen.setTextSize(3);
  OLEDScreen.setCursor(20, 10); // this moves our cursor right back to the top left pixel.. we should talk about this.
  OLEDScreen.print("PABLO"); //this copies some text to the screens memory

  // Write "Hello" in small
  OLEDScreen.setTextSize(2);
  OLEDScreen.setCursor(20, 45);
  OLEDScreen.print("Hello :)"); //this copies some text to the screens memory
  OLEDScreen.display();
}

/*
 *
 *  SCREEN HANDLING
 *
 */

void report() {
  OLEDScreen.clearDisplay();

  OLEDScreen.setTextSize(1);
  OLEDScreen.setCursor(36 , 0);
  OLEDScreen.print("< speed >");
  OLEDScreen.setCursor(39 , 28);
  OLEDScreen.print("/ dist \\");

  OLEDScreen.setCursor(50 , 18);
  OLEDScreen.print("+");
  OLEDScreen.setCursor(55 , 18);
  OLEDScreen.print(rotary_increment);

  OLEDScreen.setTextSize(2);

  // write core settings to screen
  OLEDScreen.setTextColor(1);
  OLEDScreen.setCursor(66, 46);
  OLEDScreen.print(setting_right_wheel_distance); //this copies some text to the screens memory
  OLEDScreen.setCursor(103, 3);
  OLEDScreen.print(setting_right_wheel_speed); //this copies some text to the screens memory
  OLEDScreen.setCursor(3, 3);
  OLEDScreen.print(setting_left_wheel_speed); //this copies some text to the screens memory
  OLEDScreen.setCursor(3, 46);
  OLEDScreen.print(setting_left_wheel_distance); //this copies some text to the screens memory

  // mat working on mouse over for 1 encoder
  if (rotaryMode == 0) {
    OLEDScreen.drawRect(64, 43, 63, 20, 1);

  } else if (rotaryMode == 1) {
    OLEDScreen.drawRect(100,0, 28, 20, 1);

  } else if (rotaryMode == 2) {
    OLEDScreen.drawRect(0,0,28,20, 1);

  } else if (rotaryMode == 3) {
    OLEDScreen.drawRect(0, 43 , 63, 20, 1);
  }

  OLEDScreen.display();
}

void message(String text) {
  OLEDScreen.clearDisplay();
  OLEDScreen.setTextSize(1);
  OLEDScreen.setCursor(20, 20);
  OLEDScreen.print(text); //this copies some text to the screens memory
  OLEDScreen.display();
}

void messageLarge(String text) {
  OLEDScreen.clearDisplay();
  OLEDScreen.setTextSize(2);
  OLEDScreen.setCursor(20, 20);
  OLEDScreen.print(text); //this copies some text to the screens memory
  OLEDScreen.display();
}

void message(int text) {
  OLEDScreen.clearDisplay();
  OLEDScreen.setTextSize(1);
  OLEDScreen.setCursor(20, 20);
  OLEDScreen.print(text); //this copies some text to the screens memory
  OLEDScreen.display();
}

void displayStartMessage() {
  displayCountDown(3);
  delay(1000);
  displayCountDown(2);
  delay(1000);
  displayCountDown(1);
  delay(1000);

  OLEDScreen.clearDisplay();
  OLEDScreen.setTextSize(4);
  OLEDScreen.setCursor(40, 20);
  OLEDScreen.print(":)"); //this copies some text to the screens memory

  OLEDScreen.setTextSize(1);
  OLEDScreen.setCursor(0, 0);
  OLEDScreen.print(setting_left_wheel_speed); //this copies some text to the screens memory
  OLEDScreen.setCursor(110, 0);
  OLEDScreen.print(setting_right_wheel_speed); //this copies some text to the screens memory

  OLEDScreen.setCursor(0, 50);
  OLEDScreen.print(setting_left_wheel_distance); //this copies some text to the screens memory

  OLEDScreen.setCursor(110, 50);
  OLEDScreen.print(setting_right_wheel_distance); //this copies some text to the screens memory

  OLEDScreen.display();
}

void displayCountDown(int count) {
  OLEDScreen.clearDisplay();
  OLEDScreen.setTextSize(2);
  OLEDScreen.setCursor(10 , 5);
  OLEDScreen.print("STEP BACK");

  OLEDScreen.setTextSize(1);
  OLEDScreen.setCursor(10 , 40);
  OLEDScreen.print("Starting in: "); //this copies some text to the screens memory

  OLEDScreen.setTextSize(4);
  OLEDScreen.setCursor(94 , 30);
  OLEDScreen.print(count); //this copies some text to the screens memory
  OLEDScreen.display();
}


