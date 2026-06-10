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
  EncoderManager::_encoder.begin();

  delay(10);
  if (EncoderManager::_encoder.isConnected() == 1){
    // Fill all the values to the actual value
    for (int i=0; i<NUM_MEAS; i++){
      EncoderManager::update();
      delay(5);
    }
    return true;
  }
  else{
    return false;
  }
}

void EncoderManager::update(){
  EncoderManager::_past_angles[_meas_idx] = EncoderManager::_encoder.rawAngle();
  EncoderManager::_meas_idx += 1;
  
  if (EncoderManager::_meas_idx >= NUM_MEAS){
    EncoderManager::_meas_idx = 0;
  }

  float _cum_sum = 0.0f;
  for (uint8_t i=0; i<NUM_MEAS; i++){
    _cum_sum += EncoderManager::_past_angles[i];
  }

  EncoderManager::_latest_angle = (_cum_sum / NUM_MEAS);
}

float EncoderManager::getAngle(){
  return EncoderManager::_latest_angle * AS5600_RAW_TO_DEGREES;
}
