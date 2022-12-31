import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import climate
from esphome.const import (
  CONF_ID, 
  CONF_PIN
)

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
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await climate.register_climate(var, config)
