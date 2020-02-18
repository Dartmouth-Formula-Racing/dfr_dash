
// DRIVE BUTTON

//Constants for Drive button
const int buttonPinDrive = 17;     

//Constants for Neutral button
const int buttonPinNeutral = 16;     

//Constants for Reverse button
const int buttonPinReverse = 15;     

//Variables for Drive
int buttonStateDrive = 0; // will be LOW if pressed

//Variables for Neutral
int buttonStateNeutral = 0; // will be LOW if pressed

//Variables for Reverse
int buttonStateReverse = 0; // will be LOW if pressed

void setup() {
  //Input or output for Drive
  pinMode(buttonPinDrive, INPUT_PULLUP);  

  //Input or output for Neutral
  pinMode(buttonPinNeutral, INPUT_PULLUP);

  //Input or output for Reverse
  pinMode(buttonPinReverse, INPUT_PULLUP);  
}

void loop(){
  //Read button state (pressed or not pressed?)
  buttonStateDrive = digitalRead(buttonPinDrive);
  buttonStateNeutral = digitalRead(buttonPinNeutral);
  buttonStateReverse = digitalRead(buttonPinReverse);

  //DRIVE

  //If button the button is pressed, the state is LOW
  if (buttonStateDrive == LOW) { 
    // reset the other buttons to high
    buttonStateNeutral == HIGH;
    buttonStateReverse == HIGH;

    // send state to CVC thru CAN

    
    }

  //NEUTRAL

  //If button the button is pressed, the state is LOW
  else if (buttonStateNeutral == LOW) { 
    // reset the other buttons to high
    buttonStateDrive == HIGH;
    buttonStateReverse == HIGH;

    // send state to the CVC thru CAN

    
    } 

   //REVERSE

  //If button the button is pressed, the state is LOW
  else if (buttonStateReverse == LOW) { 
    // reset the other buttons to high
    buttonStateNeutral == HIGH;
    buttonStateDrive == HIGH;

    // send state to CVC thru CAN

    
    } 
  }
