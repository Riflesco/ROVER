// --- moving 2 servo motors according to readings from a joystick ---

#include <Servo.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(8,7);

const uint64_t pipe = 0xE8E8F0F0E1LL;
byte adresses[][6]={"1Node", "2Node"};
//unsigned char msg[1];

int servoPin1 = 9;
int servoPin2 = 10;
Servo servo1,servo2; 

int x1,x2; // viteza cu care merge servoul1 si servoul2
void setup() {
  // put your setup code here, to run once:
servo1.attach(servoPin1);
servo2.attach(servoPin2);
Serial.begin(115200);

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
  radio.openReadingPipe(1,adresses[0]);
  radio.startListening();
 // radio.printDetails();
  radio.powerUp();
}

void loop() {
  // put your main code here, to run repeatedly:
   if(radio.available())
  { 
      radio.read(x1,sizeof(x1)); // from x axis
      radio.read(x2,sizeof(x2)); //from y axis 
      Serial.println(x1);
      Serial.println(x2);
      
    }
    
    servo1.write(x);
    servo2.write(y);
    
  

}
