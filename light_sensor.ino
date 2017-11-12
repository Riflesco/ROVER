/*Sample code for the BH1750 Light sensor
 
 Connection:
 VCC-5v
 GND-GND
 SCL-SCL(analog pin-5)
 SDA-SDA(analog pin-4)
 ADD-NC <-- to asign a different I2C address to the sensor
*/

#include <Wire.h> //BH1750 IIC Mode
#include <math.h> 
#include "gy30.h"

void setup()
{
   Wire.begin();
   Serial.begin(9600); //init Serial rate
   gy30Init(BH1750address);
   delay(200);
}

void loop()
{
  int i;
  uint16_t val=0;
  val = gy30Read(BH1750address);
  Serial.print(val,DEC);     
  Serial.println("[lx]");  
  delay(150);
}

