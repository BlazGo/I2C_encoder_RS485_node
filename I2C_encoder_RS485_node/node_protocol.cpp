#include "node_protocol.h"

NodeProtocol::NodeProtocol()
  : _nodeId(0),
    _encoder(nullptr),
    _transport(nullptr),
    _rx_idx(0)
{
  _rx_line[0] = '\0';
}

void NodeProtocol::begin(uint8_t nodeId, EncoderManager* encoder, Transport* transport) {
  _nodeId = nodeId;
  _encoder = encoder;
  _transport = transport;
  _rx_idx = 0;
  _rx_line[0] = '\0';
}

void NodeProtocol::update() {
  // check for any available data
  while (_transport->available() > 0) {
    digitalWrite(MY_LED, HIGH);
    int b = _transport->read();
    if (b < 0) {
      return;
    }

    char c = (char)b;

    // check if carriage return?
    if (c == '\r') {
      continue;
    }

    // check for end of msg/newline
    if (c == '\n') {
      _rx_line[_rx_idx] = '\0';
      processLine(_rx_line);
      _rx_idx = 0;
      _rx_line[0] = '\0';
      continue;
    }

    // If we overfill the buffer
    if (_rx_idx < (RX_LINE_MAX - 1)) {
      _rx_line[_rx_idx++] = c;
    } else {
      _rx_idx = 0;
      _rx_line[0] = '\0';
    }
  }
}

void NodeProtocol::processLine(char* line) {
  char cmd = 0;
  int id = -1;

  if (sscanf(line, "%c %d", &cmd, &id) != 2) {
    return;
  }

  if (cmd != 'R') {
    return;
  }

  if (id != _nodeId) {
    return;
  }

  sendAngleResponse();
}

void NodeProtocol::sendAngleResponse() {
  AngleMeasurement m = _encoder->getAngle();

  int32_t angle_millirad = (int32_t)(m.angle_rad * 1000.0f);

  char out[32];
  int len = snprintf(out, sizeof(out), "A %u %u %ld\n",
                     _nodeId,
                     m.valid ? 1 : 0,
                     (long)angle_millirad);

  if (len > 0) {
    _transport->write((const uint8_t*)out, (size_t)len);
    _transport->flush();
  }
}
