import esphome.codegen as cg
import esphome.config_validation as cv
import esphome.automation as auto
from esphome.components import light, sensor
from esphome.const import (
    CONF_ID,
    CONF_OUTPUT_ID
)

from .. import sprocklet #CONF_CONTROLLER_ID, #CONF_POSITION, sprocklet_ns, SprockletController
from .. import sprocklet_switch

sprocklet_led5v_ns = sprocklet.sprocklet_ns.namespace("led5v")

MULTI_CONF = True
AUTO_LOAD = ['light', 'sprocklet_switch', 'sensor']
DEPENDENCIES = ['sprocklet']

SprockletLed5V = sprocklet_led5v_ns.class_("SprockletLED5V", light.LightOutput, cg.Component)

CONF_SWITCH = 'switch'
CONF_SPROCKLET_LED_EFFECT_KEY = 'effect'
CONF_SPROCKLET_LED_ACTION_KEY = 'switch_action'

SprockletLed5VEffects = cg.global_ns.enum("DLED5V_EFFECTS")
SprockletLed5VActions = cg.global_ns.enum("DLED5V_SW_ACTION")


LED5V_EFFECTS = {
    "STATIC": SprockletLed5VEffects.DLED5V_EFFECT_STATIC,
    "SLOW_BLINK": SprockletLed5VEffects.DLED5V_EFFECT_SLOW_BLINK,
    "FAST_BLINK": SprockletLed5VEffects.DLED5V_EFFECT_FAST_BLINK,
    "BREATHE": SprockletLed5VEffects.DLED5V_EFFECT_BREATHE,
    "CANDLE": SprockletLed5VEffects.DLED5V_EFFECT_CANDLE,
    "SPARKLE": SprockletLed5VEffects.DLED5V_EFFECT_SPARKLE,
}

LED5V_ACTIONS = {
    "NONE": SprockletLed5VActions.DLED5V_ACTION_NONE,
    "TOGGLE": SprockletLed5VActions.DLED5V_ACTION_TOGGLE_LED,
    "TURNON": SprockletLed5VActions.DLED5V_ACTION_LED_ON,
    "TURNOFF": SprockletLed5VActions.DLED5V_ACTION_LED_OFF,
}


## Schema
CONFIG_SCHEMA = (
    light.BRIGHTNESS_ONLY_LIGHT_SCHEMA.extend({
        cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(SprockletLed5V),
        cv.Required(sprocklet.CONF_CONTROLLER_ID): cv.use_id(sprocklet.SprockletController),
        cv.Required(sprocklet.CONF_POSITION): cv.positive_int,
        cv.Optional(CONF_SPROCKLET_LED_EFFECT_KEY, default='static'): cv.enum(
            LED5V_EFFECTS, upper=True, space="_"
        ),
        cv.Optional(CONF_SPROCKLET_LED_ACTION_KEY, default='none'): cv.enum(
            LED5V_ACTIONS, upper=True, space="_"
        ),
        cv.Optional(CONF_SWITCH): sprocklet_switch.SPROCKLET_SWITCH_SCHEMA,
    }).extend(cv.COMPONENT_SCHEMA)
)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_OUTPUT_ID], config[CONF_ID].id, config[sprocklet.CONF_POSITION])

    cg.add(var.setEffect(config[CONF_SPROCKLET_LED_EFFECT_KEY]))
    cg.add(var.setAction(config[CONF_SPROCKLET_LED_ACTION_KEY]))

    yield cg.register_component(var, config)

    config.pop(
        CONF_SPROCKLET_LED_EFFECT_KEY,
        CONF_SPROCKLET_LED_ACTION_KEY
    )  # drop effect and action as they do not apply to the light component

    yield light.register_light(var, config)
    
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

## Set effect in an automation
SprockletLed5VSetEffectAction = sprocklet_led5v_ns.class_("SprockletLed5VSetEffectAction", auto.Action)
@auto.register_action(
    "sprocklet_led5v.set_effect",
    SprockletLed5VSetEffectAction,
    cv.maybe_simple_value(
        {
            cv.GenerateID(): cv.use_id(SprockletLed5V),
            cv.Required(CONF_SPROCKLET_LED_EFFECT_KEY): cv.enum(
                LED5V_EFFECTS, upper=True, space="_"
            )
        },
        key=CONF_SPROCKLET_LED_EFFECT_KEY
    ),
)
def sprocklet_led5v_set_effect_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg, config[CONF_SPROCKLET_LED_EFFECT_KEY])
    yield cg.register_parented(var, config[CONF_ID])
    yield var
