#include <Wire.h> //BH1750 IIC Mode
#include <math.h> 
#include "Sensors.h"

#define MQ135_PIN A1
#define MQ5_PIN A0

int gas_value;
int oxygen_value;
uint16_t lightVal=0;
struct TempData shtVal;
struct PresData presVal;

struct SensorData sensData;

void setup() {
    Wire.begin();
    Serial.begin(9600); //init Serial rate

    MQ_sensorsInit(MQ135_PIN);
    MQ_sensorsInit(MQ5_PIN);

    gy30Init(BH1750address);

    ms5611Init();
 
    SHT31dInit();

    delay(200);

}

void loop() {
//  oxygen_value=MQ_SensorsRead(MQ135_PIN);
//  gas_value=MQ_SensorsRead(MQ5_PIN);
//  lightVal = gy30Read(BH1750address);
//  presVal = ms5611Read();
//  shtVal= SHT31dRead();

  sensData.mq5 = MQ_SensorsRead(MQ5_PIN);
  sensData.mq135 = MQ_SensorsRead(MQ135_PIN);
  sensData.GY30 = gy30Read(BH1750address);
  sensData.ms5611 = ms5611Read();
  sensData.ShT31D = SHT31dRead();

  Serial.write((byte *)&sensData, sizeof(struct SensorData));

//  Serial.print("CO2:");
//  Serial.println(sensData.mq5);
//  Serial.print("O2: ");
//  Serial.println(sensData.mq135);
//  Serial.print(sensData.GY30,DEC);     
//  Serial.println("[lx]");  
//  Serial.print("Pressure: ");
//  Serial.print(sensData.ms5611.pressure);
//  Serial.print("   :   Altitude: ");
//  Serial.println(sensData.ms5611.altitude);
//  Serial.print("Temp *C = "); 
//  Serial.println(sensData.ShT31D.temp);
//  Serial.print("Hum. % = "); 
//  Serial.println(sensData.ShT31D.humi);
//  Serial.println(); 
//	Serial.println(); 
//  
  delay(1000);
}
