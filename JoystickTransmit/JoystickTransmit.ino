#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"


byte adresses[][6]={"1Node", "2Node"}; // sck - 13 miso - 12 mosi - 11 csn 7 ce 8
RF24 radio(8,7);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int potpin = 0;
byte val;
int x,y;

#define JOYSTICK_X A0
#define JOYSTICK_Y A1

void setup(void) {
  Serial.begin(115200);
  // put your setup code here, to run once:
  radio.begin();
  radio.setChannel(1);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(2,15);                  // Optionally, increase the delay between retries & # of retries
  
  radio.setCRCLength(RF24_CRC_8);          // Use 8-bit CRC for performance
//  radio.setChannel(108);
//  radio.setDataRate(RF24_250KBPS);
//  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(adresses[0]);
  //radio.printDetails();
  radio.powerUp();
}

void loop(void) {
  // put your main code here, to run repeatedly:
  x = analogRead(JOYSTICK_X);
  x= map(x,0,1023,0,179);
  y = analogRead(JOYSTICK_Y);
  y=map(y,0,1023,0,179);
  //val = map(reading , 0 ,1023 , 0 , 255);
  //msg[0]=val;
  radio.write(&x,sizeof(x)); // transmitting the value from x axis
  Serial.println(x); //this is optional
  radio.write(&y,sizeof(y)); // transmitting the value from y axis
  Serial.println(y); // this is optional

}
