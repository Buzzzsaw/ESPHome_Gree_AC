# Gree HVAC unit control with ESPHome and IRremoteESP8266

## Installation

* Create copy the `gree_ir.h` file in a `config/esphome/gree` directory of your HA installation, where `config` is the HA configuration directory.
* Set the remote transmitter pin to the pin number used on the controller (mine is 4) : `const uint16_t kIrLed = 4;`
* Customize the `smart-ir-remote-0.yaml` to fit your needs (add as many as you have controllers) and place it in the `config/esphome/` directory.
* Add the climate card to your dashboard.
* Start automating stuff 8D

## Hardware for IR remote

* ESP8266-based D1 mini controller
* Simple transistor & IR LED circuit
* See https://esphome.io/ for installing firmware