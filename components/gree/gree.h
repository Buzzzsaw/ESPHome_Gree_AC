#pragma once

#include "esphome/components/climate/climate.h"
#include "esphome/components/select/select.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/switch/switch.h"
#include "esphome/core/gpio.h"
#include "IRremoteESP8266.h"
#include "IRsend.h"
#include "ir_Gree.h"

namespace esphome {
namespace gree {

class GreeClimate : public climate::Climate, public Component {
private:
  IRGreeAC* transmitter_;
  sensor::Sensor *temperature_sensor_{nullptr};
  switch_::Switch *ifeel_switch_{nullptr};
  select::Select *temperature_display_select_{nullptr};
  std::string current_temperature_display_mode;

  void setClimateMode(const climate::ClimateMode climateMode);
  void setTargetTemperature(const float targetTemperature);
  void setFanMode(const climate::ClimateFanMode fanMode);
  void setSwingMode(const climate::ClimateSwingMode swingMode);
  std::function<void(float)> get_temperature_sensor_callback();
  std::function<void(bool)> get_ifeel_switch_callback();
  std::function<void(std::string, size_t)> get_temperature_display_callback();
  void send_display_temperature(const uint8_t, const uint8_t);

  static uint8_t get_display_temperature_value(std::string);

public:
  GreeClimate(InternalGPIOPin *pin);

  void setup() override;
  climate::ClimateTraits traits() override;
  void control(const climate::ClimateCall &call) override;
  void set_temperature_sensor(sensor::Sensor *sensor) { this->temperature_sensor_ = sensor; }
  void set_ifeel_switch(switch_::Switch *ifeel_switch) { this->ifeel_switch_ = ifeel_switch; }
  void set_temperature_display_select(select::Select *temperature_display_select) { this->temperature_display_select_ = temperature_display_select; }
};

} // namespace gree
} // namespace esphome
