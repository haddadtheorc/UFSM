const int BLUE_LED = 13;
const int LED_BUTTON = 2;
const int delayLED = 2000;
int button_state = digitalRead(LED_BUTTON);

void setup(){
  pinMode(BLUE_LED, OUTPUT);
  pinMode(LED_BUTTON, INPUT);
}

void loop(){
  
  int beginMillis = millis();
  while( millis() - beginMillis < delayLED){
  	button_state = digitalRead(LED_BUTTON);
    if(button_state == HIGH){
    	digitalWrite(BLUE_LED, HIGH);
    }
    else{
    	digitalWrite(BLUE_LED, LOW);
    }
  }
  
  
  beginMillis = millis();
  while( millis() - beginMillis < delayLED){
    digitalWrite(BLUE_LED, HIGH);
  }
  

}
