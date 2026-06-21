#include "encoder_manager.h"

EncoderManager::EncoderManager() 
  : _encoder(),
    _sample_idx(0),
    _meas_idx(0)
{
  for (int i=0; i<NUM_MEAS; i++){
    _past_angles[i] = 0.0f;
  }
}

bool EncoderManager::init(){
  Wire.begin();
  Wire.setClock(I2C_SPEED);
  _encoder.initializeI2C();
  return true;
}

void EncoderManager::update(){
  _latest_angle = _encoder.angleRead();

  _past_angles[_meas_idx] = _encoder.angleRead();
  _meas_idx += 1;
  
  if (_meas_idx >= NUM_MEAS){
    _meas_idx = 0;
  }

  float _cum_sum = 0.0f;
  for (uint8_t i=0; i<NUM_MEAS; i++){
    _cum_sum += _past_angles[i];
  }

  _latest_angle = (_cum_sum / NUM_MEAS);
}

float EncoderManager::getAngle(){
  return _latest_angle;
}
