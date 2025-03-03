import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import climate, sensor
from esphome.const import CONF_ID, CONF_PIN, CONF_SENSOR
from esphome.core import CORE

AUTO_LOAD = ["sensor"]
CODEOWNERS = ["@buzzzsaw"]

gree_ns = cg.esphome_ns.namespace("gree")
GreeClimate = gree_ns.class_("GreeClimate", climate.Climate, cg.Component)

CONFIG_SCHEMA = climate.CLIMATE_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(GreeClimate),
        cv.Required(CONF_PIN): pins.gpio_output_pin_schema,
        cv.Optional(CONF_SENSOR): cv.use_id(sensor.Sensor),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    pin = await cg.gpio_pin_expression(config[CONF_PIN])
    var = cg.new_Pvariable(config[CONF_ID], pin)

    await cg.register_component(var, config)
    await climate.register_climate(var, config)

    if CONF_SENSOR in config:
      temperature_sensor = await cg.get_variable(config[CONF_SENSOR])
      cg.add(var.set_temperature_sensor(temperature_sensor))

    if CORE.is_esp8266 or CORE.is_esp32:
        cg.add_library("crankyoldgit/IRremoteESP8266", "2.8.4")
