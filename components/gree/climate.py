import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import climate, sensor, switch, select
from esphome.const import CONF_ID, CONF_PIN, CONF_SENSOR
from esphome.core import CORE

AUTO_LOAD = ["sensor"]
CODEOWNERS = ["@buzzzsaw"]

CONF_IFEEL_SWITCH = "ifeel_switch"
CONF_TEMPERATURE_DISPLAY_SELECT = "temperature_display_select"

gree_ns = cg.esphome_ns.namespace("gree")
GreeClimate = gree_ns.class_("GreeClimate", climate.Climate, cg.Component)

CONFIG_SCHEMA = climate.CLIMATE_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(GreeClimate),
        cv.Required(CONF_PIN): pins.gpio_output_pin_schema,
        cv.Optional(CONF_SENSOR): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_IFEEL_SWITCH): cv.use_id(switch.Switch),
        cv.Optional(CONF_TEMPERATURE_DISPLAY_SELECT): cv.use_id(select.Select),
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
    
    if CONF_IFEEL_SWITCH in config:
        ifeel_switch = await cg.get_variable(config[CONF_IFEEL_SWITCH])
        cg.add(var.set_ifeel_switch(ifeel_switch))
    
    if CONF_TEMPERATURE_DISPLAY_SELECT in config:
        temperature_display_select = await cg.get_variable(config[CONF_TEMPERATURE_DISPLAY_SELECT])
        cg.add(var.set_temperature_display_select(temperature_display_select))

    if CORE.is_esp8266 or CORE.is_esp32:
        # Should be the fork with expanded gree ifeel
        cg.add_library("crankyoldgit/IRremoteESP8266", "2.8.6")
