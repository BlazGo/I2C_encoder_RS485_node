#ifndef ENCODER_MANAGER_H
#define ENCODER_MANAGER_H

#include <Arduino.h>

#include "encoder_types.h"
#include "AS5600.h"
#include "config.h"

class EncoderManager{
  public:
    EncoderManager();

    bool init();
    void update();
    AngleMeasurement getAngle();

  private:
    AS5600 _encoder;

    uint8_t _meas_idx;
    uint16_t _samples[NUM_MEAS];
    uint32_t _sum_raw;

    AngleMeasurement _latest_measurement;
    
};

#endif // ENCODER_MANAGER_H 
