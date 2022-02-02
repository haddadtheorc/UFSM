#include<Wire.h>

int analogRef = 5;
int tempPin = A0;



void setup()
{
  pinMode(tempPin, INPUT);
  
  Serial.begin(9600);
  
  Wire.begin();;
  
  
}

void loop()
{  
   
  int rawTemp = analogRead(tempPin);
  float volts = rawTemp * analogRef/1023.;
  int temp = (volts - 0.5) * 100;
 
  Wire.beginTransmission(9);
  Wire.write(temp);
  Wire.endTransmission();
  
  Serial.print("Temperatura: ");
  Serial.println(temp);
  
}