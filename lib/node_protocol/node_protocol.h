#ifndef NODE_PROTOCOL_H
#define NODE_PROTOCOL_H

#include <Arduino.h>
#include "encoder_manager.h"

#define START_CHAR '<'
#define END_CHAR   '>'

class NodeProtocol {
  public:
    NodeProtocol();

    void begin(uint8_t nodeId, EncoderManager* encoder);
    void update();

  private:
    void processLine(char* line);
    void sendAngleResponse();
    void enableTransmit();
    void disableTransmit();

    uint8_t _nodeId;
    EncoderManager* _encoder;

    static const uint8_t RX_LINE_MAX = 32;
    char _rx_line[RX_LINE_MAX];
    uint8_t _rx_idx;

    enum class RxState { WAITING_FOR_START, RECEIVING_DATA };
    RxState _rxState;
};

#endif // end NODE_PROTOCOL_H
