#include "gree.h"

namespace esphome {
namespace gree {

GreeClimate::GreeClimate(InternalGPIOPin *pin)
{
  this->transmitter = new IRGreeAC(pin->get_pin());
}

void GreeClimate::setup()
{
  this->transmitter->begin();
}

climate::ClimateTraits GreeClimate::traits()
{
  auto traits = climate::ClimateTraits();

  traits.set_supports_current_temperature(false);
  traits.set_supports_two_point_target_temperature(false);
  traits.set_visual_min_temperature(10);
  traits.set_visual_max_temperature(30);
  traits.set_visual_temperature_step(1);

  std::set<climate::ClimateMode> climateModes; 
  climateModes.insert(climate::CLIMATE_MODE_OFF);
  climateModes.insert(climate::CLIMATE_MODE_COOL);
  climateModes.insert(climate::CLIMATE_MODE_HEAT);
  climateModes.insert(climate::CLIMATE_MODE_DRY);
  climateModes.insert(climate::CLIMATE_MODE_FAN_ONLY);
  traits.set_supported_modes(climateModes);

  std::set<climate::ClimateFanMode> climateFanModes; 
  climateFanModes.insert(climate::CLIMATE_FAN_AUTO);
  climateFanModes.insert(climate::CLIMATE_FAN_LOW);
  climateFanModes.insert(climate::CLIMATE_FAN_MEDIUM);
  climateFanModes.insert(climate::CLIMATE_FAN_HIGH);
  climateFanModes.insert(climate::CLIMATE_FAN_FOCUS);
  traits.set_supported_fan_modes(climateFanModes);

  std::set<climate::ClimateSwingMode> climateSwingModes;
  climateSwingModes.insert(climate::CLIMATE_SWING_OFF);
  climateSwingModes.insert(climate::CLIMATE_SWING_VERTICAL);
  traits.set_supported_swing_modes(climateSwingModes);

  return traits;
}

void GreeClimate::control(const climate::ClimateCall &call)
{
  if (call.get_mode().has_value())
  {
    setClimateMode(*call.get_mode());
  }
  if (call.get_target_temperature().has_value())
  {
    setTargetTemperature(*call.get_target_temperature());
  }
  if (call.get_fan_mode().has_value())
  {
    setFanMode(*call.get_fan_mode());
  }
  if (call.get_swing_mode().has_value())
  {
    setSwingMode(*call.get_swing_mode());
  }

  this->transmitter->send();
}

void GreeClimate::setClimateMode(const climate::ClimateMode climateMode)
{
  switch (climateMode)
  {
  case climate::CLIMATE_MODE_HEAT:
    this->transmitter->setMode(kGreeHeat);
    this->transmitter->on();
    break;
  case climate::CLIMATE_MODE_COOL:
    this->transmitter->setMode(kGreeCool);
    this->transmitter->on();
    break;
  case climate::CLIMATE_MODE_DRY:
    this->transmitter->setMode(kGreeDry);
    this->transmitter->on();
    break;
  case climate::CLIMATE_MODE_FAN_ONLY:
    this->transmitter->setMode(kGreeFan);
    this->transmitter->on();
    break;
  case climate::CLIMATE_MODE_OFF:
    this->transmitter->off();
    break;
  }

  this->mode = climateMode;
  this->publish_state();
}

void GreeClimate::setTargetTemperature(const float targetTemperature)
{
  this->transmitter->setTemp(targetTemperature);

  this->target_temperature = targetTemperature;
  this->publish_state();
}

void GreeClimate::setFanMode(const climate::ClimateFanMode fanMode)
{
    switch (fanMode)
    {
    case climate::CLIMATE_FAN_AUTO:
      this->transmitter->setFan(kGreeFanAuto);
      this->transmitter->setTurbo(false);
      break;
    case climate::CLIMATE_FAN_LOW:
      this->transmitter->setFan(kGreeFanMin);
      this->transmitter->setTurbo(false);
      break;
    case climate::CLIMATE_FAN_MEDIUM:
      this->transmitter->setFan(kGreeFanMed);
      this->transmitter->setTurbo(false);
      break;
    case climate::CLIMATE_FAN_HIGH:
      this->transmitter->setFan(kGreeFanMax);
      this->transmitter->setTurbo(false);
      break;
    case climate::CLIMATE_FAN_FOCUS:
      this->transmitter->setFan(kGreeFanMax);
      this->transmitter->setTurbo(true);
      break;
    }

    this->fan_mode = fanMode;
    this->publish_state();
}

void GreeClimate::setSwingMode(const climate::ClimateSwingMode swingMode)
{
  switch (swingMode)
  {
  case climate::CLIMATE_SWING_OFF:
    this->transmitter->setSwingVertical(false, kGreeSwingLastPos);
    break;
  case climate::CLIMATE_SWING_VERTICAL:
    this->transmitter->setSwingVertical(true, kGreeSwingAuto);
    break;
  }

  this->swing_mode = swingMode;
  this->publish_state();
}

} // namespace gree
} // namespace esphome
