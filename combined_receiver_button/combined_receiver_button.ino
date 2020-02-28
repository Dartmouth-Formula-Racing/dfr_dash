/*
 * CAN port receiver example
 * Receives data on the CAN buss and prints to the serial port
 */


#include <ASTCanLib.h> 
#include <config.h>
#include <can_drv.h>
#include <can_compiler.h>
#include <can_lib.h>
#include <at90can_drv.h>             

#define MESSAGE_ID        256       // Message ID
#define MESSAGE_PROTOCOL  1         // CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
#define MESSAGE_LENGTH    8         // Data length: 8 bytes
#define MESSAGE_RTR       0         // rtr bit

// Function prototypes
//void serialPrintData(st_cmd_t *msg);

// Variables for things received
int buttonStateFromCVC = 0; // default to drive
int r2d_preC_state;
int fault;
byte array[8];

// CAN message object
st_cmd_t Msg;
st_cmd_t txMsg;

// Buffer for CAN data
uint8_t Buffer[8] = {};


// transmit
// Array of data to send
const uint8_t sendData[8] = {0,0,0,0,0,0,0,0}; // default to drive
// Transmit buffer
uint8_t txBuffer[8] = {};

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
  canInit(500000);            // Initialise CAN port. must be before Serial.begin
  Serial.begin(1000000);       // start serial port
  Msg.pt_data = &Buffer[0];    // reference message data to buffer
  
  // Initialise CAN packet.
  // All of these will be overwritten by a received packet
  Msg.ctrl.ide = MESSAGE_PROTOCOL;  // Set CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
  Msg.id.ext   = MESSAGE_ID;        // Set message ID
  Msg.dlc      = MESSAGE_LENGTH;    // Data length: 8 bytes
  Msg.ctrl.rtr = MESSAGE_RTR;       // Set rtr bit

  // we put stuff in here
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

  pinMode(ledPinDrive, OUTPUT);      
  pinMode(buttonPinDrive, INPUT_PULLUP);  

  //Input or output for Neutral
  pinMode(ledPinNeutral, OUTPUT);      
  pinMode(buttonPinNeutral, INPUT_PULLUP);

  //Input or output for Reverse
  pinMode(ledPinReverse, OUTPUT);      
  pinMode(buttonPinReverse, INPUT_PULLUP);  
}

void loop() {
   buttonStateDrive = digitalRead(buttonPinDrive);
   buttonStateNeutral = digitalRead(buttonPinNeutral);
   buttonStateReverse = digitalRead(buttonPinReverse);

  // READ IN BYTES
  // send data only when you receive data:
  if(Serial.available()) {
    while(Serial.available() <=8) {
    for (int i=0; i <=8 ; i++) { array[i] = Serial.read();}

    // Byte 0 = preC and R2D LEDs so need to write the i^2C code to turn the LEDs on or off
    r2d_preC_state = array[0];

    // Byte1 =  check the state the car is at and then check that it is the same as the button state 
    // change the LED if necessary
    buttonStateFromCVC = array[1];

    // Byte2 = faults!!
    buttonStateFromCVC = array[2];


    // button

    //Input or output for buttons
  pinMode(buttonPinDrive, INPUT_PULLUP);  
  pinMode(buttonPinNeutral, INPUT_PULLUP);
  pinMode(buttonPinReverse, INPUT_PULLUP); 

  // transmit data setup
  canInit(500000);                  // Initialise CAN port. must be before Serial.begin
  txMsg.pt_data = &txBuffer[0];     // reference message data to transmit buffer

  // receiver set up
  Msg.pt_data = &Buffer[0];    // reference message data to buffer
  
  // Initialise CAN packet.
  // All of these will be overwritten by a received packet
  Msg.ctrl.ide = MESSAGE_PROTOCOL;  // Set CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
  Msg.id.ext   = MESSAGE_ID;        // Set message ID
  Msg.dlc      = MESSAGE_LENGTH;    // Data length: 8 bytes
  Msg.ctrl.rtr = MESSAGE_RTR;       // Set rtr bit
    

  }
  
  // Clear the message buffer
  clearBuffer(&Buffer[0]);
  
  // Send command to the CAN port controller
  Msg.cmd = CMD_RX_DATA;
  
  // Wait for the command to be accepted by the controller
  while(can_cmd(&Msg) != CAN_CMD_ACCEPTED);
  
  // Wait for command to finish executing
  while(can_get_status(&Msg) == CAN_STATUS_NOT_COMPLETED);
  
  // Data is now available in the message object
  // Print received data to the terminal
  //serialPrintData(&Msg);


  // button 
  // receive information
  // Clear the message buffer
  clearBuffer(&Buffer[0]);
  
  // Send command to the CAN port controller
  Msg.cmd = CMD_RX_DATA;
  
  // Wait for the command to be accepted by the controller
  while(can_cmd(&Msg) != CAN_CMD_ACCEPTED);
  // Wait for command to finish executing
  while(can_get_status(&Msg) == CAN_STATUS_NOT_COMPLETED);

  // puts information into the text buffer
  //for (int i =0; i<Msg->dlc; i++){
    //sprintf(textBuffer,"%02X ",Msg->pt_data[i]);
  //}
  
  //Read button state (pressed or not pressed?)
  buttonStateDrive = digitalRead(buttonPinDrive);
  buttonStateNeutral = digitalRead(buttonPinNeutral);
  buttonStateReverse = digitalRead(buttonPinReverse);

  //DRIVE

  //If button the button is pressed, the state is LOW
  if (buttonStateFromCVC == 0) { 

    // turn neutral LED off
     flagNeutral == 1;
     digitalWrite(ledPinNeutral, LOW);
     flagNeutral = 0; //change flag variable; LED off

    // turn reverse LED off
     flagReverse == 1;
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

    // send state of drive to CVC thru CAN
    for (int i=0; i<8; i++){ txBuffer[i] = sendData[i];}

    // set the state to drive
    txBuffer[0] = 0;
    }

  //NEUTRAL

  //If button the button is pressed, the state is LOW
  else if (buttonStateNeutral == 1) { 
     // turn Drive LED off
     flagDrive == 1;
     digitalWrite(ledPinDrive, LOW);
     flagDrive = 0; //change flag variable; LED off

     // turn reverse LED off
     flagReverse == 1;
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

    // send state to the CVC thru CAN
    for (int i=0; i<8; i++){ txBuffer[i] = sendData[i];}

    // set the state to neutral
    txBuffer[0] = 1;
    
    } 

   //REVERSE

  //If button the button is pressed, the state is LOW
  else if (buttonStateReverse == 2) { 
    flagNeutral == 1;
     digitalWrite(ledPinNeutral, LOW);
     flagNeutral = 0; //change flag variable; LED off

     // turn reverse LED off
     flagDrive == 1;
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

    // send state to CVC thru CAN
    for (int i=0; i<8; i++){ txBuffer[i] = sendData[i];}

    // set the state to reverse
    txBuffer[0] = 2;
    
    } 

  // transmit
  // Setup CAN packet.
  txMsg.ctrl.ide = MESSAGE_PROTOCOL;  // Set CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
  txMsg.id.ext   = MESSAGE_ID;        // Set message ID
  txMsg.dlc      = MESSAGE_LENGTH;    // Data length: 8 bytes
  txMsg.ctrl.rtr = MESSAGE_RTR;       // Set rtr bit
  
  // Send command to the CAN port controller
  txMsg.cmd = CMD_TX_DATA;       // send message
  // Wait for the command to be accepted by the controller
  while(can_cmd(&txMsg) != CAN_CMD_ACCEPTED);
  // Wait for command to finish executing
  while(can_get_status(&txMsg) == CAN_STATUS_NOT_COMPLETED);
  
  }}}
