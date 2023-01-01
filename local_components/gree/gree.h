#pragma once

#include "esphome.h"
#include "IRremoteESP8266.h"
#include "IRsend.h"
#include "ir_Gree.h"

namespace esphome {
namespace gree {

class GreeClimate : public climate::Climate, public Component {
private:
  IRGreeAC* transmitter;

  void setClimateMode(const climate::ClimateMode climateMode);
  void setTargetTemperature(const float targetTemperature);
  void setFanMode(const climate::ClimateFanMode fanMode);
  void setSwingMode(const climate::ClimateSwingMode swingMode);

public:
  GreeClimate(InternalGPIOPin *pin);

  void setup() override;
  climate::ClimateTraits traits() override;
  void control(const climate::ClimateCall &call) override;
};

} // namespace gree
} // namespace esphome
