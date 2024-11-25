#define LED 6
#define IC2 1
#include <Wire.h>
const unsigned long period = 5000; 
unsigned long currentMillis;  
unsigned long previousMillis = 0; 
int x = 0;

void setup() {
  pinMode(LED, OUTPUT);
  
  Wire.begin(IC2);
  Wire.onReceive(reciveEvent);
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

void loop() {
  currentMillis = millis();
  if (brightness > 0){
    Serial.println(x);
    if(currentMillis - previousMillis >= period){
      Wire.beginTransmission(IC2); 
      Wire.write(1);  
      Serial.println("Message was sent start");  // Отладка
      Wire.endTransmission();
      Serial.println("Message was send start");
      previousMillis  = currentMillis;
      delay(1000);
    }

  }

}
