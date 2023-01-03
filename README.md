# Gree HVAC unit control with ESPHome and IRremoteESP8266

This repository contains an ESPHome external component that can simulate an IR remote to control a Gree HVAC unit. The component uses a standard `climate` card and expects to use an IR LED circuit hooked to an ESP8266.

## Installation

* Create a `local_components` directory in your ESPHome HA config directory (typically `/config/esphome/`). If you are already using [external components](https://esphome.io/components/external_components.html) in your ESPHome setup, simply change the source in your `.yaml` config accordingly.
* Drop the `local_components/gree/' directory and all its content in your previously created local external components directory. There shouldn't be anything to adjust in the files.
* Adopt your ESP devices and use the `gree-climate-with-sensor.yaml` config file as a reference.
* Add the climate cards to your dashboards.
* Start automating stuff 8D

## Configuration

The `Gree Climate` component is based on the `Climate` component for its configuration schema and adds the two following configuration items : 

* **pin** (**Required**, [Pin](https://esphome.io/components/remote_transmitter.html?highlight=remote_transmitter)) : the GPIO pin on the ESP device that controls the state of the IR LED.
* **sensor** (*Optional*, [ID](https://esphome.io/guides/configuration-types.html#config-id)) : The ID of the sensor that is used to measure the current temperature. This is only for reporting the current temperature in the climate card, and does not affect the actual operation of the unit.

Please refer to `gree-climate-with-sensor.yaml` for a more elaborate example.

## Hardware for IR remote

* ESP8266 controller or ESP8266-based development board (I use the D1 mini in my config but I'm expecting it to work for other similar boards).
* An actual InfraRed LED with an IR circuit hooked to the ESP. The ESP doesn't have enough juice on its GPIO pins to drive an IR LED, so you'll need either a transistor driving circuit ([this is similar to what I have](https://www.letscontrolit.com/wiki/images/4/47/IRLEDcircuit.png)) or an all-in-one IR LED board.
* Ideally some cute little enclosure like the Hammond 1593 and a power supply.