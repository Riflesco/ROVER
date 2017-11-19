#include <Wire.h> //BH1750 IIC Mode
//#include <math.h> 
#include "Sensors.h"

struct SensorData sensData;

void setup() {
    Wire.begin();
    Serial.begin(115200); //init Serial rate
    sensorsInit();
    delay(200);

}

void loop() {
  sensData = sensorsRead();

  //Serial.write((byte *)&sensData, sizeof(struct SensorData));

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
  
  delay(1000);
}
