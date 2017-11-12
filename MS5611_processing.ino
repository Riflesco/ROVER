/*
  MS5611 Barometric Pressure & Temperature Sensor. Output for MS5611_processing.pde
  Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/czujnik-cisnienia-i-temperatury-ms5611.html
  GIT: https://github.com/jarzebski/Arduino-MS5611
  Web: http://www.jarzebski.pl
  (c) 2014 by Korneliusz Jarzebski
 */
#include "ms5611_rover.h"

struct PresData readVal;

void setup() 
{
  Serial.begin(9600);
  ms5611Init();
}

void loop()
{
  // Read true temperature & Pressure (without compensation)
  readVal = ms5611Read();
  // Output
  Serial.print(readVal.pressure);
  Serial.print("   ;   ");
  Serial.println(readVal.altitude);
  delay(100);

}

