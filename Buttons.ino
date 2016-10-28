/*
  Handles the array of buttons
*/

void setupButtons(){
  // TODO: These pinModes need to be abstracted to variables
  // OR they should be clearly marked.
  pinMode(buttonIncThousands, INPUT_PULLUP);
  pinMode(buttonIncHundreds, INPUT_PULLUP);
  pinMode(buttonIncTens, INPUT_PULLUP);
  pinMode(buttonIncOnes, INPUT_PULLUP);
  pinMode(buttonDrawingMode, INPUT_PULLUP);
  pinMode(buttonUnused, INPUT_PULLUP);
  pinMode(buttonPresets, INPUT_PULLUP);
  pinMode(buttonStart, INPUT_PULLUP);

}