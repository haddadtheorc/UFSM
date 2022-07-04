#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include <SoftwareSerial.h>
const int myserial_RX = 2;
const int myserial_TX = 3;
SoftwareSerial mySerial(myserial_RX, myserial_TX);

float halfDaysPassed = 0.0;
bool isDay = true;
bool receivingLight = false;
float dayDuration = 6000.0;
long lightReceived = 0.0;
long startReceivingLight;
int analogRef = 5;

//user inputs for plant growth
float desiredLightTime = 3.0;
float desiredIdealTemperature = 25.5;
float temperatureTolerance = 5.0;

void setup()
{
  	mySerial.begin(4800);
    lcd.begin(16, 2);
    Serial.begin(9600);
    desiredLightTime *= 1000;
}

void loop()
{

    float ambient_light_sensor = analogRead(A0) / 1010.0;

    float current_temperature = analogRead(A1);
    current_temperature = current_temperature * analogRef / 1023.;
    current_temperature = (current_temperature - 0.5) * 100;

    if ((current_temperature > desiredIdealTemperature + temperatureTolerance))
    {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Quente demais!!!");
      		lcd.clear();
    }
    else if ((current_temperature < desiredIdealTemperature - temperatureTolerance))
    {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Frio demais!!!");
      		lcd.clear();
     }

    if (isDay)
    {

        if (ambient_light_sensor >= 0.4)
        {
            if (receivingLight == false)
            {
                receivingLight = true;
                startReceivingLight = millis();
            }
        }
        else
        {
            if (receivingLight == true)
            {
                receivingLight = false;
                lightReceived += (millis() - startReceivingLight);
            }
        }
    }

    float halfDay = dayDuration / 2;
    long mil = millis();

    float new_day = (mil / halfDay) - halfDaysPassed;

    if (new_day == 1.0)
    {
        halfDaysPassed += 1.0;
        if (isDay == true)
        {
            isDay = false;

            if (receivingLight == true)
            {
                receivingLight = false;
                lightReceived += (millis() - startReceivingLight);
            }
          	lcd.clear();
            lcd.setCursor(0, 0);
  			lcd.print("Acabou o dia.");
          	delay(100);
  
          	lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Luz recebida: ");
          	lcd.setCursor(7, 1);
          	lcd.print(String(lightReceived/1000.0));
	
            if ((desiredLightTime - lightReceived) > 0)
            {
            	mySerial.listen();
                char value [5];
  				dtostrf(desiredLightTime - lightReceived, 4, 2, value);
                
              	for(int i = 0; i < strlen(value); i++) {
    				mySerial.write(value[i]); 
  				}
                mySerial.write((uint8_t)'\0');
            }
         	else{
          		mySerial.listen();
            	char value [5];
  				dtostrf(desiredLightTime - lightReceived, 4, 2, value);
               
            	for(int i = 0; i < strlen(value); i++) {
    				mySerial.write(value[i]); 
  				}
            	mySerial.write((uint8_t)'\0');
          	}
        }
        else
        {
            isDay = true;
            lightReceived = 0.0;
          	
          	lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Comecou o dia.");

        }
    }
}