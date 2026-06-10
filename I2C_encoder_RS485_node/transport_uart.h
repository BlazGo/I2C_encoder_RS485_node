#ifndef TRANSPORT_UART_H
#define TRANSPORT_UART_H

#include <Arduino.h>
#include "transport.h"

// This will later be replaced by a RS485 implementation

class UartTransport : public Transport {
public:
  explicit UartTransport(HardwareSerial& serial);

  void begin(uint32_t baud) override;
  int available() override;
  int read() override;
  size_t write(const uint8_t* data, size_t len) override;
  void flush() override;

private:
  HardwareSerial& _serial;
};

#endif
