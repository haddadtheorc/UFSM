//SLAVE//

#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char buffer[128];
int counter = 0;

const int myserial_RX = 3;
const int myserial_TX = 2;

SoftwareSerial mySerial(myserial_RX, myserial_TX);

void setup()
{
  lcd.begin(16, 2);
  mySerial.begin(4800);
  delay(500);
}

void loop()
{
  lcd.setCursor(2, 0);
  lcd.print("Temperatura:");
  
  while(mySerial.available()) {
    char message = mySerial.read();
   
    buffer[counter] = message;
    counter++;
    
    if(message == '\0') {
      lcd.setCursor(5,1);
  	  lcd.print(buffer);
      counter = 0;
    }
    delay(10);
  }
}