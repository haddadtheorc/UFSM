#include <LiquidCrystal.h>

int analogRef = 5;
int tempPin = A0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



void setup()
{
  lcd.begin(16, 2);
  pinMode(tempPin, INPUT);
  Serial.begin(115200);
}

void loop()
{
  int rawTemp = analogRead(tempPin);
  float volts = rawTemp * analogRef/1023.;
  float temp = (volts - 0.5) * 100; 
 
  Serial.print("Temperatura: ");
  Serial.println(temp);


  lcd.setCursor(2, 0);
  lcd.print("Temperatura:");
  lcd.setCursor(5, 1);
  lcd.print(temp);
  delay(1000);

	
}
