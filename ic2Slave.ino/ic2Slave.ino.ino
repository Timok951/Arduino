#define LED 6
#define IC2 1
#include <Wire.h>
const unsigned long period = 5000; 
unsigned long currentMillis;  
unsigned long previousMillis = 0; 
int x = 0;
int y = 0;

void setup() {
  pinMode(LED, OUTPUT);
  
  Wire.begin(IC2);
  Wire.onReceive(reciveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(9600);

}
int brightness;
void reciveEvent(int bytes){
  while(Wire.available()){
    x = Wire.read();
    brightness = map(x, 0, 1023, 0, 255);
    analogWrite(LED, brightness);
  }
}


void requestEvent() {
  Wire.write(y);  // Отправляем данные мастеру (в данном случае просто переменную x)
  Serial.println("Message was send start" + y);

}


void loop() {
  currentMillis = millis();
  if (brightness > 0){
    Serial.println(x);
    if(currentMillis - previousMillis >= period){
      y = 1;
      previousMillis  = currentMillis;
    }

  }
  else{
    y = 0;
    previousMillis  = currentMillis;

  }

}
