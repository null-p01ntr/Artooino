int RS=11; //Right Speed
int LS=10; //Left Speed
int pwm=200; 
int RF=6; //Right Forward
int RB=7; //Right Backwards
int LF=5; //Left Forward
int LB=4; //Left Backwards
char data;

int trig=9;
int echo=8;

float t=0;
float d=0;
float threshold=12; //in cm

void distanceMeasure()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW); 

  t=pulseIn(echo, HIGH);
  d=(t/68.3);

  Serial.print(d);Serial.print('\n');
  delay(50);
}

void setup() 
{
  //RCC
  pinMode(RS,OUTPUT);
  pinMode(LS,OUTPUT);
  pinMode(RF,OUTPUT);
  pinMode(RB,OUTPUT);
  pinMode(LF,OUTPUT);
  pinMode(LB,OUTPUT);
  //OD
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  Serial.begin(9600);
}

void loop() 
{
  while(Serial.available())
  {
    data=Serial.read();
    switch(data)
    {
      case 'W': //Forward
      {
        digitalWrite(RF, HIGH);
        digitalWrite(RB, LOW) ;
        digitalWrite(LF, HIGH);
        digitalWrite(LB, LOW);
        analogWrite(RS, pwm);
        analogWrite(LS, pwm);
        break;   
      }
      case 'S': //Backwards
      {
        digitalWrite(RF, LOW);
        digitalWrite(RB, HIGH);
        digitalWrite(LF, LOW);
        digitalWrite(LB, HIGH);
        analogWrite(RS, pwm);
        analogWrite(LS, pwm);
        break;   
      }
      case 'A': //Left
      {
        digitalWrite(RF, HIGH);
        digitalWrite(RB, LOW);
        digitalWrite(LF, LOW);
        digitalWrite(LB, HIGH);
        analogWrite(RS, pwm);
        analogWrite(LS, pwm);
        break;   
      }
      case 'D': //Right
      {
        digitalWrite(RF, LOW);
        digitalWrite(RB, HIGH);
        digitalWrite(LF, HIGH);
        digitalWrite(LB, LOW);
        analogWrite(RS, pwm);
        analogWrite(LS, pwm);
        break;   
      }
      case 'K': //Speed Up
      {
        if(pwm<260)
        {
          pwm = pwm+5;
          break; 
        }
      }
      case 'L': // Slow Down
      {
        if(pwm>0)
        {
          pwm = pwm-5;
          break; 
        }  
      }
      case 'O': //Break
      {
        digitalWrite(RF, LOW);
        digitalWrite(RB, LOW);
        digitalWrite(LF, LOW);
        digitalWrite(LB, LOW);
        break;
      }
    }
  }
  distanceMeasure();
  if(d<threshold && data!='S')
  {
    digitalWrite(RF, LOW);
    digitalWrite(RB, LOW);
    digitalWrite(LF, LOW);
    digitalWrite(LB, LOW);
  }
}
