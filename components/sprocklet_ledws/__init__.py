import esphome.codegen as cg
import esphome.config_validation as cv
import esphome.automation as auto
from esphome.components import light
from esphome.const import (
    CONF_ID,
    CONF_OUTPUT_ID,
    CONF_NUM_LEDS
)

from .. import sprocklet #CONF_CONTROLLER_ID, #CONF_POSITION, sprocklet_ns, SprockletController
from .. import sprocklet_switch

sprocklet_ledws_ns = sprocklet.sprocklet_ns.namespace("ledws")

MULTI_CONF = True
AUTO_LOAD = ['light', 'sprocklet_switch', 'sensor']
DEPENDENCIES = ['sprocklet']

SprockletLedWS = sprocklet_ledws_ns.class_("SprockletLEDWS", light.LightOutput, cg.Component)

CONF_SWITCH = 'switch'
CONF_SPROCKLET_LED_ACTION_KEY = 'switch_action'

SprockletLedWSActions = cg.global_ns.enum("DLEDWS_SW_ACTION")

LEDWS_ACTIONS = {
    "NONE": SprockletLedWSActions.DLEDWS_ACTION_NONE,
    "TOGGLE": SprockletLedWSActions.DLEDWS_ACTION_TOGGLE_LED,
    "TURNON": SprockletLedWSActions.DLEDWS_ACTION_LED_ON,
    "TURNOFF": SprockletLedWSActions.DLEDWS_ACTION_LED_OFF,
}


## Schema
CONFIG_SCHEMA = (
    light.ADDRESSABLE_LIGHT_SCHEMA.extend({
        cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(SprockletLedWS),
        cv.Required(sprocklet.CONF_CONTROLLER_ID): cv.use_id(sprocklet.SprockletController),
        cv.Required(sprocklet.CONF_POSITION): cv.positive_int,
        cv.Required(CONF_NUM_LEDS): cv.positive_not_null_int,
        cv.Optional(CONF_SPROCKLET_LED_ACTION_KEY, default='none'): cv.enum(
            LEDWS_ACTIONS, upper=True, space="_"
        ),
        cv.Optional(CONF_SWITCH): sprocklet_switch.SPROCKLET_SWITCH_SCHEMA,
    }).extend(cv.COMPONENT_SCHEMA)
)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_OUTPUT_ID], config[CONF_ID].id, config[sprocklet.CONF_POSITION])

    cg.add(var.setAction(config[CONF_SPROCKLET_LED_ACTION_KEY]))

    yield light.register_light(var, config)
    yield cg.register_component(var, config)

    cg.add(var.setNumLeds(config[CONF_NUM_LEDS]))

    if CONF_SWITCH in config:        
        switch = cg.new_Pvariable(config[CONF_SWITCH][CONF_ID])
        yield sprocklet_switch.configure(switch, config[CONF_SWITCH])
        cg.add(getattr(var, f"setSwitch")(switch))


    paren = yield cg.get_variable(config[sprocklet.CONF_CONTROLLER_ID])
    cg.add(paren.register_child(var))
    cg.add_library(
            name="Sprocklets",
            repository="https://github.com/sprocketstech/sprocklet_sdk",
            version="1.0"
            #repository="file://c:/jm/devel/sprocket_sprocklets/sprocklet_sdk",
            #version=None
        )
