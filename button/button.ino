/* Learn to use pushbutton (button switch) with Arduino - Tutorial
   More info and circuit schematic: http://www.ardumotive.com/arduino-tutorials/category/button
   Dev: Michalis Vasilakis / Date: 19/10/2014  
   UPDATED 2/6/2016 - LED to Arduino pin 3 and button to Arduino pin 4*/

// DRIVE BUTTON

//Constants for Drive button
const int buttonPinDrive = 17;     
const int ledPinDrive =  12;     

//Constants for Neutral button
const int buttonPinNeutral = 16;     
const int ledPinNeutral =  11; 

//Constants for Reverse button
const int buttonPinReverse = 15;     
const int ledPinReverse =  10; 

//Variables for Drive
int buttonStateDrive = 0; // will be LOW if pressed
int flagDrive = 0; // 0, the LED is off; 1, LED is on

//Variables for Neutral
int buttonStateNeutral = 0; // will be LOW if pressed
int flagNeutral = 0; // 0, the LED is off; 1, LED is on

//Variables for Reverse
int buttonStateReverse = 0; // will be LOW if pressed
int flagReverse = 0; // 0, the LED is off; 1, LED is on

void setup() {
  //Input or output for Drive
  pinMode(ledPinDrive, OUTPUT);      
  pinMode(buttonPinDrive, INPUT_PULLUP);  

  //Input or output for Neutral
  pinMode(ledPinNeutral, OUTPUT);      
  pinMode(buttonPinNeutral, INPUT_PULLUP);

  //Input or output for Reverse
  pinMode(ledPinReverse, OUTPUT);      
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

    // turn neutral LED off
    flagNeutral == 1
    digitalWrite(ledPinNeutral, LOW);
    flagNeutral = 0; //change flag variable; LED off

    // turn reverse LED off
    flagReverse == 1
    digitalWrite(ledPinReverse, LOW);
    flagReverse = 0; //change flag variable; LED off

    // if the Drive LED is on, turn it off 
    if (flagDrive == 0) {
      digitalWrite(ledPinDrive, HIGH);
      flagDrive = 1; //change flag variable; LED on
    }
    // if the LED is off, turn it on 
    else if (flagDrive == 1){
      digitalWrite(ledPinDrive, LOW);
      flagDrive = 0; //change flag variable; LED off
    }

  //NEUTRAL

  //If button the button is pressed, the state is LOW
  else if (buttonStateNeutral == LOW) { 
    // reset the other buttons to high
    buttonStateDrive == HIGH;
    buttonStateReverse == HIGH;

    // turn Drive LED off
    flagDrive == 1
    digitalWrite(ledPinDrive, LOW);
    flagDrive = 0; //change flag variable; LED off

    // turn reverse LED off
    flagReverse == 1
    digitalWrite(ledPinReverse, LOW);
    flagReverse = 0; //change flag variable; LED off
    
    // if the LED is on, turn it off 
    if (flagNeutral == 0) {
      digitalWrite(ledPinNeutral, HIGH);
      flagNeutral = 1; //change flag variable; LED on
    }
    // if the LED is off, turn it on 
    else if (flagNeutral == 1){
      digitalWrite(ledPinNeutral, LOW);
      flagNeutral = 0; //change flag variable; LED off
    } 

   //REVERSE

  //If button the button is pressed, the state is LOW
  else if (buttonStateReverse == LOW) { 
    // reset the other buttons to high
    buttonStateNeutral == HIGH;
    buttonStateDrive == HIGH;

    // turn neutral LED off
    flagNeutral == 1
    digitalWrite(ledPinNeutral, LOW);
    flagNeutral = 0; //change flag variable; LED off

    // turn reverse LED off
    flagDrive == 1
    digitalWrite(ledPinDrive, LOW);
    flagDrive = 0; //change flag variable; LED off
    
    // if the LED is on, turn it off 
    if (flagReverse == 0) {
      digitalWrite(ledPinReverse, HIGH);
      flagReverse = 1; //change flag variable; LED on
    }
    // if the LED is off, turn it on 
    else if (flagReverse == 1){
      digitalWrite(ledPinReverse, LOW);
      flagReverse = 0; //change flag variable; LED off
    } 
  }
