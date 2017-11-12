/*************************************************** 
  This is an example for the SHT31-D Humidity & Temp Sensor

  Designed specifically to work with the SHT31-D sensor from Adafruit
  ----> https://www.adafruit.com/products/2857

  These sensors use I2C to communicate, 2 pins are required to  
  interface
 ****************************************************/
 
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"
#include "SHT31d.h"

void setup() {
  Serial.begin(9600);

  while (!Serial)
    delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("SHT31 test");
  SHT31dInit();
}


void loop() {
  struct TempData readVal;
  readVal = SHT31dRead();
  Serial.print("Temp *C = "); 
  Serial.println(readVal.temp);
  Serial.print("Hum. % = "); 
  Serial.println(readVal.humi);
  delay(10);
}
