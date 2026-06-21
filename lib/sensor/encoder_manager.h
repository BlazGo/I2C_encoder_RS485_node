
#ifndef ENCODER_MANAGER_H
#define ENCODER_MANAGER_H

#include <Arduino.h>

#include <MT6701.h>
#include "config.h"

class EncoderManager{
  public:
    EncoderManager();

    bool init();
    void update();
    float getAngle();

  private:
    uint32_t _sample_idx;
    uint8_t _meas_idx;
    float _latest_angle;
    float _past_angles[NUM_MEAS];
    
    MT6701 _encoder;
};

#endif // ENCODER_MANAGER_H 
