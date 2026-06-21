#include <Arduino.h>
#include "node_protocol.h"

EncoderManager encoders;
NodeProtocol protocol;

void setup() {
    encoders.init();
    protocol.begin(NODE_ID, &encoders);
}

void loop() {
  encoders.update();
  protocol.update();
}
