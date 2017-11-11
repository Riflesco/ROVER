/*------ Program for Line Follower Robot using Arduino----- */


/*-------definning Outputs------*/
#define LM1 4       // left motor
#define LM2 5       // left motor
#define RM1 6       // right motor
#define RM2 7       // right motor

void setup()
{
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
}

void loop()
{

  for(int i=0; i<=255 ; i=i+7) // using PWD to control the DC motors : left -> one way , right -> the other way
   {
        analogWrite(LM1, i);
        analogWrite(LM2, 0);
        analogWrite(RM1, 0);
        analogWrite(RM2, i);
        
   }
   delay(3000);
    
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
  
  delay(3000);

    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
  delay(3000);

    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
  
  delay(3000);

    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
 delay(3000);
}                                                                
