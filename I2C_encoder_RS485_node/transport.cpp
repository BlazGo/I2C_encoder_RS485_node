#include "transport_uart.h"

UartTransport::UartTransport(HardwareSerial& serial)
  : _serial(serial) {
}

void UartTransport::begin(uint32_t baud) {
  _serial.begin(baud);
}

int UartTransport::available() {
  return _serial.available();
}

int UartTransport::read() {
  return _serial.read();
}

size_t UartTransport::write(const uint8_t* data, size_t len) {
  return _serial.write(data, len);
}

void UartTransport::flush() {
  _serial.flush();
}
