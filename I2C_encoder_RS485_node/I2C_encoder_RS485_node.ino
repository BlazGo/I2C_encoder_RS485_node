#include <Arduino.h>
#include <encoder_manager.h>
#include "node_protocol.h"
#include "transport_uart.h"

EncoderManager _encoders;
UartTransport transport(Serial);
NodeProtocol protocol;

uint32_t now = 0;
uint32_t last_print_us = 0;
uint32_t loop_hz = 0;
uint32_t loop_count = 0;

void setup() {
  pinMode(MY_LED, OUTPUT);

  if (!_encoders.init()){
    while(true){
      digitalWrite(MY_LED, HIGH);
      delay(100);
      digitalWrite(MY_LED, LOW);
      delay(100);
      }
  }

  transport.begin(BUS_BAUD);
  protocol.begin(NODE_ID, &_encoders, &transport);
}

void loop() {
  now = micros();

  _encoders.update();
  protocol.update();

  loop_count++;

  if ((now - last_print_us) > 100000){
    digitalWrite(MY_LED, LOW);
    
    //printInfo();
    
    last_print_us = now;
    loop_hz = loop_count;
    loop_count = 0;

    digitalWrite(MY_LED, HIGH);
  }
}

void printInfo(){
    Serial.print(loop_hz);
    Serial.print("\t");
    Serial.print(_encoders.getAngle().angle_rad);
    Serial.print("\t");
    Serial.println(_encoders.getAngle().valid);
}