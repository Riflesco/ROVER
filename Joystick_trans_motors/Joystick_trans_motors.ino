#define joyX A0 // x axis
#define joyY A1 // y axis
#define LM1 4       // left motor
#define LM2 5       // left motor
#define RM1 6       // right motor
#define RM2 7       // right motor
int xValue, yValue;
void setup() {
  // put your setup code here, to run once:
   pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  xValue = analogRead(joyX); // reading the value from x axis
  yValue = analogRead(joyY); // reading the value from y axis
  analogWrite(LM1 , xValue); // controling the left motor with values read from x axis
  analogWrite(LM2 , 0);
  analogWrite(RM1, yValue); // controlling the right motor with values from y axis
  analogWrite(RM2 , 0);

  
}
