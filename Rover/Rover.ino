#include <SPI.h>   // Comes with Arduino IDE
#include "RF24.h"  // Download and Install (See above)

#include "Sensors.h"
#include <Wire.h>
//#include <math.h>

#define  CE_PIN  49   // The pins to be used for CE and SN
#define  CSN_PIN 53
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus (usually) pins 7 & 8 (Can be changed) */
RF24 radio(CE_PIN, CSN_PIN);

byte addresses[][6] = {"1Node", "2Node"}; // These will be the names of the "Pipes"

struct dataStruct {
  unsigned long _micros;  // to save response times
  int Xposition;          // The Joystick position values
  int Yposition;
//  int X2position;
//  int Y2position;
//  bool switchOn;          // The Joystick push-down switch
} myData; 


#define LM1 10      // left motor
#define LM2 3       // left motor
#define LM3 4       // left motor
#define LM4 5       // left motor
#define RM1 6 //right motors ->
#define RM2 7
#define RM3 8
#define RM4 9

struct SensorData sensData;

void setup() {

  Wire.begin();
  sensorsInit();
  
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(LM3, OUTPUT);
  pinMode(LM4, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(RM3, OUTPUT);
  pinMode(RM4, OUTPUT);

  pinMode(53, OUTPUT);

  Serial.begin(115200);   // set all the motor control pins to outputs

  radio.begin();          // Initialize the nRF24L01 Radio
  //radio.setChannel(108);  // 2.508 Ghz - Above most Wifi Channels
  radio.setDataRate(RF24_250KBPS); // Fast enough.. Better range
  // Set the Power Amplifier Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  // PALevelcan be one of four levels: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
  radio.setPALevel(RF24_PA_LOW);
  //   radio.setPALevel(RF24_PA_MAX);

  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);

  // Start the radio listening for data
  radio.startListening();
}


void move_stop() {
  digitalWrite(LM1 , LOW);
  digitalWrite(LM2 , LOW);
  digitalWrite(LM3 , LOW);
  digitalWrite(LM4 , LOW);
  digitalWrite(RM1 ,LOW);
  digitalWrite(RM2 , LOW);
  digitalWrite(RM3, LOW);
  digitalWrite(RM4 , LOW);
}
void move_right()
{
  digitalWrite(LM1 , LOW);
  digitalWrite(LM2 , HIGH);
  digitalWrite(LM3 , LOW);
  digitalWrite(LM4 , HIGH);
  digitalWrite(RM1 ,LOW);
  digitalWrite(RM2 , HIGH);
  digitalWrite(RM3, LOW);
  digitalWrite(RM4 , HIGH);
}

void move_left()
{
  digitalWrite(LM1 , HIGH);
  digitalWrite(LM2 , LOW);
  digitalWrite(LM3 , HIGH);
  digitalWrite(LM4 , LOW);
  digitalWrite(RM1 ,HIGH);
  digitalWrite(RM2 , LOW);
  digitalWrite(RM3, HIGH);
  digitalWrite(RM4 , LOW);
}

void move_forward()
{
  digitalWrite(LM1 , HIGH);
  digitalWrite(LM2 , LOW);
  digitalWrite(LM3 , HIGH);
  digitalWrite(LM4 , LOW);
  digitalWrite(RM1 ,LOW);
  digitalWrite(RM2 , HIGH);
  digitalWrite(RM3, LOW);
  digitalWrite(RM4 , HIGH);
}

void move_backward()
{
 digitalWrite(LM1 , LOW);
  digitalWrite(LM2 , HIGH);
  digitalWrite(LM3 , LOW);
  digitalWrite(LM4 , HIGH);
  digitalWrite(RM1 ,HIGH);
  digitalWrite(RM2 , LOW);
  digitalWrite(RM3, HIGH);
  digitalWrite(RM4 , LOW);
}

void control_motors();

void loop() 
{
  sensData = sensorsRead();
  if ( radio.available())
  {
    
    while (radio.available())   // While there is data ready to be retrieved from the receive pipe
    {
      radio.read( &myData, sizeof(myData) );             // Get the data
    }

    radio.stopListening();                               // First, stop listening so we can transmit
    radio.write( &sensData, sizeof(sensData) );              // Send the received data back.
    radio.startListening();                              // Now, resume listening so we catch the next packets.

    control_motors();
    Serial.println(myData.Xposition);
    Serial.println(myData.Yposition);
    Serial.print(F("Packet Received - Sent response "));  // Print the received packet data
    Serial.print(myData._micros);
    Serial.print(F("uS X= "));
    Serial.println(myData.Xposition);
    Serial.println(myData.Yposition);
//    Serial.println(myData.Yposition);
    
  } // END radio available
}

void control_motors()
{
   if(myData.Xposition > 700) {
    move_forward();
    delay(50);
  }
  else if(myData.Xposition < 300) {
    move_backward();
    delay(50);
  }
  else if(myData.Yposition > 700) {
    move_right();
    delay(50);
  }
  else if(myData.Yposition < 300) {
    move_left();
    delay(50);
  }
  else {
    move_stop();
    Serial.println("stop");
    delay(50);
  }
}

