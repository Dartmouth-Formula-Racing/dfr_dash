/*
 * CAN port receiver example
 * Receives data on the CAN buss and prints to the serial port
 */

 

#include <ASTCanLib.h>              

#define MESSAGE_ID        0       // Message ID
#define MESSAGE_PROTOCOL  1       // CAN protocol (0: CAN 2.0A, 1: CAN 2.0B)
#define MESSAGE_LENGTH    8       // Data length: 8 bytes
#define MESSAGE_RTR       0       // rtr bit

// Function prototypes
void serialPrintData(st_cmd_t *msg);

// Variables for things received
int buttonStateFromCVC = 0; // default to drive
int r2d_preC_state;
int fault;
byte array[8];

// CAN message object
st_cmd_t Msg;

// Buffer for CAN data
uint8_t Buffer[8] = {};

// instance variables
int incomingByte = -1; // for incoming serial data

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
  
}

}
