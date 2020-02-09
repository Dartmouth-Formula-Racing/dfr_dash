// TOGGLES

//Constants for Toggle 1 (A&B)
const int buttonPinToggle1A = 5;  
const int buttonPinToggle1B = 6;    
const int ledPinToggle1AB =  14;  

//Constants for Toggle 2 (A&B)
const int buttonPinToggle2A = 7;  
const int buttonPinToggle2B = 8;    
const int ledPinToggle2AB =  9; 

//Variables for Toggles
int stateToggle1 = HIGH;      // the current state of the output pin #1
int readingToggle1;           // the current reading from the input pin #1
int previousToggle1 = LOW;    // the previous reading from the input pin #1

int stateToggle2 = HIGH;      // the current state of the output pin #2
int readingToggle2;           // the current reading from the input pin #2
int previousToggle2 = LOW;    // the previous reading from the input pin #2

int flagToggle1 = 0; // 0, the LED is off; 1, LED is on
int flagToggle2 = 0; // 0, the LED is off; 1, LED is on

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;  // the debounce time, increase if the output flickers

void setup()
{
  pinMode(buttonPinToggle1A, INPUT);
  pinMode(buttonPinToggle1B, OUTPUT);
  pinMode(ledPinToggle1AB, OUTPUT);      


  pinMode(buttonPinToggle2A, INPUT);
  pinMode(buttonPinToggle2B, OUTPUT);
  pinMode(ledPinToggle2AB, OUTPUT);      

}

void loop()
{
  readingToggle1 = digitalRead(buttonPinToggle1A);
  readingToggle2 = digitalRead(buttonPinToggle2A);

  // if the input just went from LOW and HIGH, toggle the output pin and remember the time
  
  // Both toggles are HIGH
  if ((readingToggle1 == HIGH && previousToggle1 == LOW) && (readingToggle2 == HIGH && previousToggle2 == LOW) && millis() - time > debounce) {
    // switch toggle state 1 to high
    if (stateToggle1 == HIGH) { stateToggle1 = LOW; }
    else { stateToggle1 = HIGH; }

    // switch toggle state 2 to high
    if (stateToggle2 == HIGH) { stateToggle2 = LOW; }
    else { stateToggle2 = HIGH; }

    // LEDS

    // if the toggle 1 LED is on, turn it off 
    if (flagToggle1 == 0) {
      digitalWrite(ledPinToggle1AB, HIGH);
      flagToggle1 = 1; //change flag variable; LED on
    }
    // if the LED is off, turn it on 
    else if (flagToggle1 == 1){
      digitalWrite(ledPinToggle1AB, HIGH);
      flagToggle1 = 1; //change flag variable; LED on

   // if the toggle 2 LED is on, turn it off 
    if (flagToggle2 == 0) {
      digitalWrite(ledPinToggle2AB, HIGH);
      flagToggle2 = 1; //change flag variable; LED on
    }
    // if the LED is off, turn it on 
    else if (flagToggle2 == 1){
      digitalWrite(ledPinToggle2AB, HIGH);
      flagToggle2 = 1; //change flag variable; LED on  
    
    time = millis();    
  }

  // Toggle 1 is LOW (down) and toggle 2 is HIGH
  else if ((readingToggle1 == LOW && previousToggle1 == HIGH) && (readingToggle2 == HIGH && previousToggle2 == LOW) && millis() - time > debounce) {
    // switch toggle state 1 to low
    if (stateToggle1 == LOW) { stateToggle1 = HIGH; }
    else { stateToggle1 = LOW; }

    // switch toggle state 2 to high
    if (stateToggle2 == HIGH) { stateToggle2 = LOW; }
    else { stateToggle2 = HIGH; }

    // LEDS

    // if the toggle 1 LED is on, turn it off 
    if (flagToggle1 == 0) {
      digitalWrite(ledPinToggle1AB, LOW);
      flagToggle1 = 0; //change flag variable; LED off
    }
    // if the LED is off, turn it on 
    else if (flagToggle1 == 1){
      digitalWrite(ledPinToggle1AB, LOW);
      flagToggle1 = 0; //change flag variable; LED off

   // if the toggle 2 LED is on, turn it off 
    if (flagToggle2 == 0) {
      digitalWrite(ledPinToggle2AB, HIGH);
      flagToggle2 = 1; //change flag variable; LED on
    }
    // if the LED is off, turn it on 
    else if (flagToggle2 == 1){
      digitalWrite(ledPinToggle2AB, HIGH);
      flagToggle2 = 1; //change flag variable; LED on 
    
    time = millis();    
  }

  // Toggle 1 is LOW (down) and toggle 2 is LOW
  else if ((readingToggle1 == LOW && previousToggle1 == HIGH) && (readingToggle2 == LOW && previousToggle2 == HIGH) && millis() - time > debounce) {
    // switch toggle state 1 to low
    if (stateToggle1 == LOW) { stateToggle1 = HIGH; }
    else { stateToggle1 = LOW; }

    // switch toggle state 2 to low
    if (stateToggle2 == LOW) { stateToggle2 = HIGH; }
    else { stateToggle2 = LOW; }

    // LEDS

    // if the toggle 1 LED is on, turn it off 
    if (flagToggle1 == 0) {
      digitalWrite(ledPinToggle1AB, LOW);
      flagToggle1 = 0; //change flag variable; LED off
    }
    // if the LED is off, turn it on 
    else if (flagToggle1 == 1){
      digitalWrite(ledPinToggle1AB, LOW);
      flagToggle1 = 0; //change flag variable; LED off

   // if the toggle 2 LED is on, turn it off 
    if (flagToggle2 == 0) {
      digitalWrite(ledPinToggle2AB, LOW);
      flagToggle2 = 0; //change flag variable; LED off
    }
    // if the LED is off, turn it on 
    else if (flagToggle2 == 1){
      digitalWrite(ledPinToggle2AB, LOW);
      flagToggle2 = 0; //change flag variable; LED off
    
    time = millis();    
  }

  // Toggle 1 is HIGH and toggle 2 is LOW
  else if ((readingToggle1 == HIGH && previousToggle1 == LOW) && (readingToggle2 == LOW && previousToggle2 == HIGH) && millis() - time > debounce) {
    // switch toggle state 1 to high
    if (stateToggle1 == HIGH) { stateToggle1 = LOW; }
    else { stateToggle1 = HIGH; 

    // switch toggle state 2 to low
    if (stateToggle2 == LOW) { stateToggle2 = HIGH; }
    else { stateToggle2 = LOW; }

    // LEDS

    // if the toggle 1 LED is on, turn it off 
    if (flagToggle1 == 0) {
      digitalWrite(ledPinToggle1AB, HIGH);
      flagToggle1 = 1; //change flag variable; LED on
    }
    // if the LED is off, turn it on 
    else if (flagToggle1 == 1){
      digitalWrite(ledPinToggle1AB, HIGH);
      flagToggle1 = 1; //change flag variable; LED on

   // if the toggle 2 LED is on, turn it off 
    if (flagToggle2 == 0) {
      digitalWrite(ledPinToggle2AB, LOW);
      flagToggle2 = 0; //change flag variable; LED off
    }
    // if the LED is off, turn it on 
    else if (flagToggle2 == 1){
      digitalWrite(ledPinToggle2AB, LOW);
      flagToggle2 = 0; //change flag variable; LED off
    
    time = millis();    
  }

  digitalWrite(buttonPinToggle1B, stateToggle1);
  digitalWrite(buttonPinToggle2B, stateToggle2);

  previousToggle1 = readingToggle1;
  previousToggle2 = readingToggle2;
}




void loop(){

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
