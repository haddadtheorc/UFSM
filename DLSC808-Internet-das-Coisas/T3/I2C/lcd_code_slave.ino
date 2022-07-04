#include<Wire.h>
#include <LiquidCrystal.h>

int x;

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(115200);
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
}

void receiveEvent(int bytes) {
  x = Wire.read();
  if(x > 128)
  	x = (256 - x) * (-1);
}

void loop()
{
  lcd.setCursor(2, 0);
  lcd.print("Temperatura:");
  lcd.setCursor(5,1);
  lcd.print(x);
  delay(1000);	
}