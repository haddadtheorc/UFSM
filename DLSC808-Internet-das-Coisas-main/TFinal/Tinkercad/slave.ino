#include <SoftwareSerial.h>
const int myserial_RX = 3;
const int myserial_TX = 2;
SoftwareSerial mySerial(myserial_RX, myserial_TX);
char buffer[128];
int counter = 0;

int pushButton = 2;
int ledWater = 12;
int ledLight = 13;
long startTime = 0;

bool available;
bool time = true;
bool light = false;
bool water = false;
// aqui constam informacoes recebidas do arduino MESTRE
float requiredLight;
float requiredWater = 1500;

void setup() {
  mySerial.begin(4800);
  //initialize serial communication at 9600 buts per second
  Serial.begin(9600);
  pinMode(pushButton,INPUT);
  pinMode(ledLight, OUTPUT);
  pinMode(ledWater, OUTPUT);
}

void loop() {
  
  available = mySerial.available(); 
  
  while(available) {
    char message = mySerial.read();
   
    buffer[counter] = message;
    counter++;
    
    if(message == '\0') {
      counter = 0;
      requiredLight = atof(buffer);
      water = true;
      light = true;
      time = true;
      available = false;

    }    
    delay(10);
  }

    
  if (time) {
    startTime = millis();
	time = false;
  }
  
  while (light || water){

    
    if (millis() - startTime >= requiredLight){
      digitalWrite(ledLight,LOW);
      light = false;
      
      
    } else{
      digitalWrite(ledLight,HIGH);
    }
    
    if (millis() - startTime >= requiredWater){
      	
      	digitalWrite(ledWater,LOW);
     	water = false;
  	} else  digitalWrite(ledWater,HIGH);
    
	}
}