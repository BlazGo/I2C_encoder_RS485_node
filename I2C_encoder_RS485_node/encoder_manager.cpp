#include "wiring_constants.h"
#include "encoder_types.h"
#include "encoder_manager.h"

EncoderManager::EncoderManager() 
  : _encoder(),
    _meas_idx(0),
    _sum_raw(0)
{
  _latest_measurement = {0.0f, false};

  for (int i=0; i<NUM_MEAS; i++){
    _samples[i] = 0;
  }
}

bool EncoderManager::init(){
  Wire.begin();
  Wire.setClock(I2C_CLOCK);

  _encoder.begin();
  
  if (!_encoder.isConnected() == 1){
    return false;
  }

  uint16_t first = _encoder.rawAngle();

  _sum_raw = 0;
  for (uint8_t i = 0; i < NUM_MEAS; i++) {
    _samples[i] = first;
    _sum_raw += first;
  }

  _latest_measurement.angle_rad = (float)first * AS5600_RAW_TO_RADIANS;
  _meas_idx = 0;
  return true;
}

void EncoderManager::update(){
  uint16_t new_raw = _encoder.rawAngle();
  bool magnet_ok = _encoder.magnetDetected(); // && !_encoder.magnetTooStrong() && !_encoder.magnetTooWeak();

  _sum_raw -= _samples[_meas_idx];
  _samples[_meas_idx] = new_raw;
  _sum_raw += new_raw;

  _meas_idx++;
  if (_meas_idx >= NUM_MEAS) {
    _meas_idx = 0;
  }
  _latest_measurement.angle_rad = (float(_sum_raw) / NUM_MEAS) * AS5600_RAW_TO_RADIANS;
  _latest_measurement.valid = magnet_ok;
}

AngleMeasurement EncoderManager::getAngle(){
  return _latest_measurement;
}
