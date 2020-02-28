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
void serialPrintData(st_cmd_t *msg);

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

// receive
// Buffer for CAN data
uint8_t Buffer[8] = {};

//Constants for buttons
const int buttonPinDrive = 17;     
const int buttonPinNeutral = 16;     
const int buttonPinReverse = 15;     



// button var
int buttonStateDrive = 0; // will be LOW if pressed
int buttonStateNeutral = 0; // will be LOW if pressed
int buttonStateReverse = 0; // will be LOW if pressed

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

}

void loop() {

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
  serialPrintData(&Msg);


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
  for (int i =0; i<Msg->dlc; i++){
    sprintf(textBuffer,"%02X ",Msg->pt_data[i]);
  }
  
  //Read button state (pressed or not pressed?)
  buttonStateDrive = digitalRead(buttonPinDrive);
  buttonStateNeutral = digitalRead(buttonPinNeutral);
  buttonStateReverse = digitalRead(buttonPinReverse);

  //DRIVE

  //If button the button is pressed, the state is LOW
  if (buttonStateDrive == LOW) { 
    // put in an and condition that of the first bit of CVC is = 0 
    // reset the other buttons to high
    //buttonStateNeutral == HIGH;
    //buttonStateReverse == HIGH;

    // send state of drive to CVC thru CAN
    for (int i=0; i<8; i++){ txBuffer[i] = sendData[i];}

    // set the state to drive
    txBuffer[0] = 0;
    }

  //NEUTRAL

  //If button the button is pressed, the state is LOW
  else if (buttonStateNeutral == LOW) { 
    // reset the other buttons to high
    //buttonStateDrive == HIGH;
    //buttonStateReverse == HIGH;

    // send state to the CVC thru CAN
    for (int i=0; i<8; i++){ txBuffer[i] = sendData[i];}

    // set the state to neutral
    txBuffer[0] = 1;
    
    } 

   //REVERSE

  //If button the button is pressed, the state is LOW
  else if (buttonStateReverse == LOW) { 
    // reset the other buttons to high
    //buttonStateNeutral == HIGH;
    //buttonStateDrive == HIGH;

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
  
}

}
