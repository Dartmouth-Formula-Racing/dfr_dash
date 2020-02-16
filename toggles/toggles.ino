// TOGGLES

//Constants for Toggle 1 (A&B)
const int buttonPinToggle1A = 14;  
const int buttonPinToggle1B = 13;    

//Constants for Toggle 2 (A&B)
const int buttonPinToggle2A = 12;  
const int buttonPinToggle2B = 11;    

//Variables for Toggles
int stateToggle1A = HIGH;      // the current state of the output pin #1
int readingToggle1A;           // the current reading from the input pin #1
int previousToggle1A = LOW;    // the previous reading from the input pin #1

int stateToggle1B = HIGH;      // the current state of the output pin #1
int readingToggle1B;           // the current reading from the input pin #1
int previousToggle1B = LOW;    // the previous reading from the input pin #1

int stateToggle2A = HIGH;      // the current state of the output pin #2
int readingToggle2A;           // the current reading from the input pin #2
int previousToggle2A = LOW;    // the previous reading from the input pin #2

int stateToggle2B = HIGH;      // the current state of the output pin #2
int readingToggle2B;           // the current reading from the input pin #2
int previousToggle2B = LOW;    // the previous reading from the input pin #2

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;  // the debounce time, increase if the output flickers

void setup()
{
  // both toggles are inputs
  pinMode(buttonPinToggle1A, INPUT);
  pinMode(buttonPinToggle1B, INPUT);

  pinMode(buttonPinToggle2A, INPUT);
  pinMode(buttonPinToggle2B, INPUT);
}

void loop()
{
  readingToggle1A = digitalRead(buttonPinToggle1A);
  readingToggle1B = digitalRead(buttonPinToggle1B);

  readingToggle2A = digitalRead(buttonPinToggle2A);
  readingToggle2B = digitalRead(buttonPinToggle2B);

  // if the input just went from LOW and HIGH, toggle the output pin and remember the time

  // TOGGLE 1
  
  // Both toggles 1A and 1B are HIGH
  if ((readingToggle1A == HIGH && previousToggle1A == LOW) && (readingToggle1B == HIGH && previousToggle1B == LOW) && millis() - time > debounce) {
    // switch toggle state 1A to high
    if (stateToggle1A == HIGH) { stateToggle1A = LOW; }
    else { stateToggle1A = HIGH; }

    // switch toggle state 1B to high
    if (stateToggle1B == HIGH) { stateToggle1B = LOW; }
    else { stateToggle1B = HIGH; }
    
    time = millis();    
    }

  // Toggle 1 is LOW (down) and toggle 2 is HIGH
  else if ((readingToggle1A == LOW && previousToggle1A == HIGH) && (readingToggle1B == HIGH && previousToggle1B == LOW) && millis() - time > debounce) {
    // switch toggle state 1A to low
    if (stateToggle1A == LOW) { stateToggle1A = HIGH; }
    else { stateToggle1A = LOW; }

    // switch toggle state 1B to high
    if (stateToggle1B == HIGH) { stateToggle1B = LOW; }
    else { stateToggle1B = HIGH; }
    
    time = millis();    
    }

  // Toggle 1 is HIGH and toggle 2 is LOW
  else if ((readingToggle1A == HIGH && previousToggle1A == LOW) && (readingToggle1B == LOW && previousToggle1B == HIGH) && millis() - time > debounce) {
    // switch toggle state 1A to high
    if (stateToggle1A == HIGH) { stateToggle1A = LOW; }
    else { stateToggle1A = HIGH; }

    // switch toggle state 1B to low
    if (stateToggle1B == LOW) { stateToggle1B = HIGH; }
    else { stateToggle1B = LOW; }
    
    time = millis();    
    }

  // Toggle 1A is LOW and toggle 1B is LOW
  else if ((readingToggle1A == LOW && previousToggle1A == HIGH) && (readingToggle1B == LOW && previousToggle1B == HIGH) && millis() - time > debounce) {
    // switch toggle state 1A to low
    if (stateToggle1A == LOW) { stateToggle1A = HIGH; }
    else { stateToggle1A = LOW; }

    // switch toggle state 1B to low
    if (stateToggle1B == LOW) { stateToggle1B = HIGH; }
    else { stateToggle1B = LOW; }
    
    time = millis();    
    }


  // TOGGLE 2

  // Both toggles 2A and 2B are HIGH
  if ((readingToggle2A == HIGH && previousToggle2A == LOW) && (readingToggle2B == HIGH && previousToggle2B == LOW) && millis() - time > debounce) {
    // switch toggle state 2A to high
    if (stateToggle2A == HIGH) { stateToggle2A = LOW; }
    else { stateToggle2A = HIGH; }

    // switch toggle state 2B to high
    if (stateToggle2B == HIGH) { stateToggle2B = LOW; }
    else { stateToggle2B = HIGH; }
    
    time = millis();    
    }

  // Toggle 2A is LOW (down) and toggle 2B is HIGH
  else if ((readingToggle2A == LOW && previousToggle2A == HIGH) && (readingToggle2B == HIGH && previousToggle2B == LOW) && millis() - time > debounce) {
    // switch toggle state 2A to low
    if (stateToggle2A == LOW) { stateToggle2A = HIGH; }
    else { stateToggle2A = LOW; }

    // switch toggle state 2B to high
    if (stateToggle2B == HIGH) { stateToggle2B = LOW; }
    else { stateToggle2B = HIGH; }
    
    time = millis();    
    }

  // Toggle 2A is HIGH and toggle 2B is LOW
  else if ((readingToggle2A == HIGH && previousToggle2A == LOW) && (readingToggle2B == LOW && previousToggle2B == HIGH) && millis() - time > debounce) {
    // switch toggle state 2A to high
    if (stateToggle2A == HIGH) { stateToggle2A = LOW; }
    else { stateToggle2A = HIGH; }

    // switch toggle state 2B to low
    if (stateToggle2B == LOW) { stateToggle2B = HIGH; }
    else { stateToggle2B = LOW; }
    
    time = millis();    
    }

  // Toggle 2A is LOW and toggle 2B is LOW
  else if ((readingToggle2A == LOW && previousToggle2A == HIGH) && (readingToggle2B == LOW && previousToggle2B == HIGH) && millis() - time > debounce) {
    // switch toggle state 2A to high
    if (stateToggle2A == LOW) { stateToggle2A = HIGH; }
    else { stateToggle2A = LOW; }

    // switch toggle state 2B to low
    if (stateToggle2B == LOW) { stateToggle2B = HIGH; }
    else { stateToggle2B = LOW; }
    
    time = millis();    
    }

  previousToggle1A = readingToggle1A;
  previousToggle1B = readingToggle1B;

  previousToggle2A = readingToggle2A;
  previousToggle2B = readingToggle2B;
}
