#include <SPI.h>   // Comes with Arduino IDE
#include "RF24.h"  // Download and Install (See above)

#include "Sensors.h"

#define SOFT_SPI_MISO_PIN 12
#define SOFT_SPI_MOSI_PIN 11
#define SOFT_SPI_SCK_PIN 13

#define  CE_PIN  7   // The pins to be used for CE and SN
#define  CSN_PIN 8

#define JOYSTICK_X   A0  // The Joystick potentiometers connected to Arduino Analog inputs
#define JOYSTICK_Y   A1
#define JOYSTICK2_X  A2
#define JOYSTICK2_Y  A3

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus (usually) pins 7 & 8 (Can be changed) */
RF24 radio(CE_PIN, CSN_PIN);

byte addresses[][6] = {"1Node", "2Node"}; // These will be the names of the "Pipes"

unsigned long timeNow;  // Used to grab the current time, calculate delays
unsigned long started_waiting_at;
boolean timeout;       // Timeout? True or False

struct dataStruct {
  unsigned long _micros;  // to save response times
  int Xposition;          // The Joystick position values
  int Yposition;
//  int X2position;
//  int Y2position;
//  bool switchOn;          // The Joystick push-down switch
} myData;                 // This can be accessed in the form:  myData.Xposition  etc.


struct SensorData sensData; 

void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(115200);  // MUST reset the Serial Monitor to 115200 (lower right of window )
  
  radio.begin();          // Initialize the nRF24L01 Radio
 // radio.setChannel(108);  // Above most WiFi frequencies
  radio.setDataRate(RF24_250KBPS); // Fast enough.. Better range
  // Set the Power Amplifier Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  // PALevelcan be one of four levels: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
  radio.setPALevel(RF24_PA_LOW);
  //  radio.setPALevel(RF24_PA_MAX);

  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);

  // Start the radio listening for data
  radio.startListening();

}

void loop()
{
  radio.stopListening();                                    // First, stop listening so we can talk.

  /*********************( Read the Joystick positions )*************************/
  myData.Xposition = 1024 - analogRead(JOYSTICK_X);
  myData.Yposition = analogRead(JOYSTICK_Y);
 
  myData._micros = micros();  // Send back for timing

  if (!radio.write( &myData, sizeof(myData) )) {            // Send data, checking for error ("!" means NOT)
    Serial.println(F("Transmit failed "));
  }

  radio.startListening();                                    // Now, continue listening

  started_waiting_at = micros();               // timeout period, get the current microseconds
  timeout = false;                            //  variable to indicate if a response was received or not

  while ( ! radio.available() ) {                            // While nothing is received
    if (micros() - started_waiting_at > 200000 ) {           // If waited longer than 200ms, indicate timeout and exit while loop
      timeout = true;
      break;
    }
  }

  if ( timeout )
  { // Describe the results
    Serial.println(F("Response timed out -  no Acknowledge."));
  }
  else
  {
    // Grab the response, compare, and send to Serial Monitor
    radio.read( &sensData, sizeof(sensData) );
    timeNow = micros();
    Serial.print("CO2:");
    Serial.println(sensData.mq5);
    Serial.print("O2: ");
    Serial.println(sensData.mq135);
    Serial.print(sensData.GY30,DEC);     
    Serial.println("[lx]");  
    Serial.print("Pressure: ");
    Serial.print(sensData.ms5611.pressure);
    Serial.print("   :   Altitude: ");
    Serial.println(sensData.ms5611.altitude);
    Serial.print("Temp *C = "); 
    Serial.println(sensData.ShT31D.temp);
    Serial.print("Hum. % = "); 
    Serial.println(sensData.ShT31D.humi);
    Serial.println(); 
    Serial.println(); 
  }

  // Send again after delay. When working OK, change to something like 100
  delay(5);
}

