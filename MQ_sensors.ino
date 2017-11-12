#include "MQ_sensors.h"
#define mq135 A0
#define mq5 A1
int gas_value;
int oxygen_value;

void setup()
{
  MQ_sensorsInit(mq135);
  MQ_sensorsInit(mq5);
  Serial.begin(9600);
}

void loop()
{
  oxygen_value=MQ_SensorsRead(mq135);
  gas_value=MQ_SensorsRead(mq5);
  Serial.print("CO2:");
  Serial.println(gas_value);
  Serial.print("O2: ");
  Serial.println(oxygen_value);
  Serial.println();
  delay(100);
}
