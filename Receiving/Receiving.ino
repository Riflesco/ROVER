// this is a sample code for testing the nrf24l01 modules 

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(8,7);
const uint64_t pipe = 0xE8E8F0F0E1LL;
byte msg[1];
void setup(void)
{
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
  //radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  radio.printDetails();
  radio.powerUp();
}

void loop(void)
{

  //--- receiving the data read from a potentiometer ---
  if(radio.available())
  { 
      radio.read(msg,sizeof(msg[0]));
      Serial.println(msg[0]);
    }
  
}

