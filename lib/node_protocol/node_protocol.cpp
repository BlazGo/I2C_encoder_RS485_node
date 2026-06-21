#include "node_protocol.h"

NodeProtocol::NodeProtocol()
  : _nodeId(0),
    _encoder(nullptr),
    _rx_idx(0)
{
  _rx_line[0] = '\0';
}

void NodeProtocol::begin(uint8_t nodeId, EncoderManager* encoder) {
  _nodeId = nodeId;
  _encoder = encoder;
  _rx_idx = 0;
  _rx_line[0] = '\0';

  Serial.begin(UART_BAUDRATE);

  pinMode(MY_LED, OUTPUT);
  pinMode(EN_PIN, OUTPUT);

  disableTransmit();
}

void NodeProtocol::update() {
  // check for any available data
  while (Serial.available() > 0) {
    int b = Serial.read();
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
  if (line[0] == '\0' || line[1] != ' ') return;

  char cmd = line[0];
  if (cmd != 'R') return;

  // Parse integer ID starting at line[2]
  int id = 0;
  for (int i = 2; line[i] >= '0' && line[i] <= '9'; i++) {
    id = id * 10 + (line[i] - '0');
  }

  if (id != _nodeId) return;

  sendAngleResponse();
}

void NodeProtocol::sendAngleResponse() {
  enableTransmit();

   // Build response manually — no snprintf needed
  // Format: "A <id> <millideg>\n"
  char out[32];
  char* p = out;

  *p++ = 'A';
  *p++ = ' ';
  
  // Write node ID (single digit assumed)
  *p++ = '0' + _nodeId;
  *p++ = ' ';

  // Write angle as integer (millidegrees)
  long val = (long)(_encoder->getAngle() * 1000.0f);
  // Handle negative
  if (val < 0) { *p++ = '-'; val = -val; }
  
  // Convert integer to string manually
  char tmp[16];
  int ti = 0;
  if (val == 0) { tmp[ti++] = '0'; }
  while (val > 0) { tmp[ti++] = '0' + (val % 10); val /= 10; }
  // tmp is reversed, copy it forward
  while (ti > 0) { *p++ = tmp[--ti]; }
  
  *p++ = '\n';
  *p = '\0';

  Serial.write((const uint8_t*)out, (size_t)(p - out));
  Serial.flush();

  disableTransmit();
}

void NodeProtocol::enableTransmit(){
  digitalWrite(MY_LED, LOW);
  digitalWrite(EN_PIN, HIGH);
}

void NodeProtocol::disableTransmit(){
  digitalWrite(MY_LED, HIGH);
  digitalWrite(EN_PIN, LOW);
}
