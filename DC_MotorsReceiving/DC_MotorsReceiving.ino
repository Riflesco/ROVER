#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define LM1 3        // left motor
#define LM2 4       // left motor
#define RM1 5       // right motor
#define RM2 6       // right motor

RF24 radio(8,7);

const uint64_t pipe = 0xE8E8F0F0E1LL;
byte adresses[][6]={"1Node", "2Node"};

int lmotor,rmotor;

void setup()
{
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  
  Serial.begin(115200);
  radio.begin();

      radio.setChannel(1);
  radio.setPALevel(RF24_PA_MAX); // radio.setPALevel(RF24_PA_LOW) -> should be used at last
  radio.setDataRate(RF24_250KBPS);
  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(2,15);                  // Optionally, increase the delay between retries & # of retries
  
  radio.setCRCLength(RF24_CRC_8);          // Use 8-bit CRC for performance
//  radio.setChannel(108);
//  radio.setDataRate(RF24_250KBPS);
//  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(1,adresses[1]);
  radio.startListening();
//  radio.printDetails();
  radio.powerUp();
}

void loop()
{
  if(radio.available())
  { 
    radio.read(&lmotor,sizeof(lmotor)); // x axis
    radio.read(&rmotor,sizeof(rmotor)); // reading the values from the joystick , y axis
    }
  analogWrite(LM1 , lmotor);
  analogWrite(LM2 , 0);
  analogWrite(RM1, rmotor);
  analogWrite(RM2 , 0);


  analogWrite(LM1 , 200);
  analogWrite(LM2 , 0);
  analogWrite(RM1, 200);
  analogWrite(RM2 , 0);

}

