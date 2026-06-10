#ifndef NODE_PROTOCOL_H
#define NODE_PROTOCOL_H

#include <Arduino.h>
#include "encoder_types.h"
#include "encoder_manager.h"
#include "transport.h"

static const uint8_t MSG_START = 0xAA;
static const uint8_t CMD_GET_ANGLE = 0x01;
static const uint8_t CMD_ANGLE_RESPONSE = 0x81;

class NodeProtocol{
  public:
    NodeProtocol();

    void begin(uint8_t nodeId, EncoderManager* encoder, Transport* transport);
    void update();

  private:
  void processLine(char* line);
    void sendAngleResponse();

    uint8_t _nodeId;
    EncoderManager* _encoder;
    Transport* _transport;

    static const uint8_t RX_LINE_MAX = 32;
    char _rx_line[RX_LINE_MAX];
    uint8_t _rx_idx;
};

#endif // end NODE_PROTOCOL_H
