#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <Arduino.h>

class Transport {
  public:
    virtual void begin(uint32_t baud) = 0;
    virtual int available() = 0;
    virtual int read() = 0;
    virtual size_t write(const uint8_t* data, size_t len) = 0;
    virtual void flush() = 0;
};

#endif // end TRANSPORT_H
