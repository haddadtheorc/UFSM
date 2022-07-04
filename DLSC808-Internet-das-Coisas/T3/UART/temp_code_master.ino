//MASTER//

#include <SoftwareSerial.h>

int analogRef = 5;
int tempPin = A0;
const int myserial_RX = 2;
const int myserial_TX = 3;

SoftwareSerial mySerial(myserial_RX, myserial_TX);

void setup()
{
  mySerial.begin(4800);
  delay(500);
}

void loop()
{
  int rawTemp = analogRead(tempPin);
  float volts = rawTemp * analogRef/1023.;
  float temp = (volts - 0.5) * 100;

  mySerial.listen();
  char value [5];
  dtostrf(temp, 4, 2, value);
  
  for(int i = 0; i < strlen(value); i++) {
    mySerial.write(value[i]); 
  }
  mySerial.write((uint8_t)'\0');
  delay(2000);
}



