#include <Arduino.h>
#include <encoder_manager.h>

EncoderManager _encoders;

#define MY_LED PA4
uint32_t start, stop, last_print;
uint32_t iterations = 0;

void setup() {
  pinMode(MY_LED, OUTPUT);

  Serial.begin(115200);
  while (!Serial);  // Wait for Serial to be ready
  Serial.println("Initializing");
  
  Wire.begin();
  Wire.setClock(400000);
  if (_encoders.init()){
    Serial.println("Encoders connected");
  }
  else{
    Serial.println("Encoders ERROR");
  }
  last_print = micros();
}

void loop() {

  start = micros();
  _encoders.update();
  stop = micros();
  iterations += 1;

  if ((stop - last_print) > 100000){
    digitalWrite(MY_LED, LOW);
    Serial.print(iterations);
    Serial.print("\t");
    Serial.print(stop - start);
    Serial.print("\t");
    Serial.println(_encoders.getAngle());
    last_print = stop;
    iterations = 0;
    digitalWrite(MY_LED, HIGH);
  }
}
