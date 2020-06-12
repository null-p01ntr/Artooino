#include <Wire.h>

const int MPU=0x68;

int threshold=10000;

int16_t gyX1, gyY1,gyZ1;
int16_t gyX2, gyY2,gyZ2;

void readData()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);
  
  gyX1=Wire.read() << 8 | Wire.read();
  gyY1=Wire.read() << 8 | Wire.read();
  gyZ1=Wire.read() << 8 | Wire.read();
}

void setup() 
{
 Wire.begin();
 Wire.beginTransmission(MPU);
 Wire.write(0x6B);
 Wire.write(0);
 Wire.endTransmission(true);
 Serial.begin(9600);

 pinMode(8, OUTPUT);
 digitalWrite(8, LOW);
}

void loop() 
{
  readData();
  Serial.print("GyroX: "); Serial.print(gyX1);
  Serial.print(" GyroY: "); Serial.print(gyY1);
  Serial.print(" GyroZ: "); Serial.print(gyZ1);
  Serial.print("\n");

  delay(200);

  gyX2=gyX1;
  gyY2=gyY1;
  gyZ2=gyZ1;
  
  readData();
  
  if(abs(gyX1-gyX2)>threshold || abs(gyY1-gyY2)>threshold || abs(gyZ1-gyZ2)>threshold)
  {
    digitalWrite(8, HIGH);
    delay(500);
    digitalWrite(8, LOW);
  }
}

