import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import climate
from esphome.const import (
  CONF_ID, 
  CONF_PIN
)
from esphome.core import CORE

CODEOWNERS = ["@buzzzsaw"]

gree_ns = cg.esphome_ns.namespace("gree")
GreeClimate = gree_ns.class_("GreeClimate", climate.Climate)

CONFIG_SCHEMA = climate.CLIMATE_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(GreeClimate),
        cv.Optional(CONF_PIN): pins.gpio_output_pin_schema,
    }
)


async def to_code(config):
    pin = await cg.gpio_pin_expression(config[CONF_PIN])
    var = cg.new_Pvariable(config[CONF_ID], pin)

    await climate.register_climate(var, config)

    if CORE.is_esp8266 or CORE.is_esp32:
        cg.add_library("crankyoldgit/IRremoteESP8266", "2.8.4")
