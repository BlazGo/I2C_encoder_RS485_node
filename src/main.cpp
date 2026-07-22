#include <Arduino.h>
#include "node_protocol.h"

EncoderManager encoders;
NodeProtocol protocol;

uint32_t t_millis;

void setup() {
  pinMode(MY_LED, OUTPUT);

  encoders.init();
  protocol.begin(NODE_ID, &encoders);

  t_millis = millis();
}

void loop() {
  encoders.update();
  protocol.update();

  if ((millis() - t_millis) > 500){
    digitalWrite(MY_LED, !digitalRead(MY_LED));
    t_millis = millis();
  }
}
