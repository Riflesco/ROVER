// --- a sample code to test the nrf24l01 modules ->transmission ---

#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"
byte msg[1]; // sck - 13 miso - 12 mosi - 11 csn 7 ce 8
RF24 radio(8,7);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int potpin = 0;
byte val;
int currentMillis,previousMillis=0;
int updateMillis;
int reading;
void setup(void) {
  Serial.begin(115200);
  radio.begin();
   radio.setChannel(1);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(2,15);                  // Optionally, increase the delay between retries & # of retries
  
  radio.setCRCLength(RF24_CRC_8);          // Use 8-bit CRC for performance
  //radio.setChannel(108);
  //radio.setDataRate(RF24_250KBPS);
 // radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(pipe);
  radio.printDetails();
  radio.powerUp();
}

void loop(void) {
  currentMillis=millis(); 
  updateMillis=currentMillis-previousMillis;  // calculating how fast the transmission is made
  
  reading = analogRead(potpin); // reading data from potentiometer
  val = map(reading , 0 ,1023 , 0 , 255);
  msg[0]=val;
  radio.write(msg,sizeof(byte));
 Serial.print(msg[0]);
  //delay(300);
  previousMillis=currentMillis;
  Serial.print(" millis: ");
  //
  Serial.println(updateMillis);

}
