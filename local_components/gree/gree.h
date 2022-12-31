#pragma once

#include "esphome.h"
#include "IRremoteESP8266.h"
#include "IRsend.h"
#include "ir_Gree.h"

namespace esphome {
namespace gree {

class GreeClimate : public Component, public Climate
{
private:
  IRGreeAC* transmitter;

  void setClimateMode(const ClimateMode climateMode);
  void setTargetTemperature(const float targetTemperature);
  void setFanMode(const ClimateFanMode fanMode);
  void setSwingMode(const ClimateSwingMode swingMode);

public:
  GreeClimate(const uint16_t irPinNumber);
  void setup() override;
  climate::ClimateTraits traits();
  void control(const ClimateCall &call) override;
};

} // namespace gree
} // namespace esphome
