import esphome.codegen as cg
import esphome.config_validation as cv
import esphome.automation as auto
from esphome.components import binary_sensor, output
from esphome.const import (
    CONF_ID,
    CONF_NAME,
    CONF_TRIGGER_ID,
)

from ..sprocklet import SprockletController, CONF_CONTROLLER_ID

MULTI_CONF = True
AUTO_LOAD = ['binary_sensor', 'output']
DEPENDENCIES = ['sprocklet']



sprocklet_ns = cg.esphome_ns.namespace("sprocklet")
SprockletLed5V = sprocklet_ns.class_("SprockletLED5V", binary_sensor.BinarySensor, output.FloatOutput, cg.Component)

## Switch Types
CONF_SWITCH_TYPE_KEY = 'switch_type'
SprockletLed5VSwitchType = cg.global_ns.enum("DLED5V_SWITCH_TYPE")
LED5V_SWITCH_TYPES = {
    "NONE": SprockletLed5VSwitchType.DLED5V_SWITCH_NONE,
    "MOMENTARY": SprockletLed5VSwitchType.DLED5V_SWITCH_MOMENTARY,
    "TOGGLE": SprockletLed5VSwitchType.DLED5V_SWITCH_TOGGLE,
}

## Effects
CONF_EFFECT_KEY = 'effect'
SprockletLed5VEffects = cg.global_ns.enum("DLED5V_EFFECTS")
LED5V_EFFECTS = {
    "STATIC": SprockletLed5VEffects.DLED5V_EFFECT_STATIC,
    "SLOW_BLINK": SprockletLed5VEffects.DLED5V_EFFECT_SLOW_BLINK,
    "FAST_BLINK": SprockletLed5VEffects.DLED5V_EFFECT_FAST_BLINK,
    "BREATHE": SprockletLed5VEffects.DLED5V_EFFECT_BREATHE,
    "CANDLE": SprockletLed5VEffects.DLED5V_EFFECT_CANDLE,
    "SPARKLE": SprockletLed5VEffects.DLED5V_EFFECT_SPARKLE,
}

# Press detection
CONF_DETECT_LONG_KEY = 'detect_long_press'
CONF_DETECT_VERY_LONG_KEY = 'detect_very_long_press'
CONF_DETECT_DOUBLE_KEY = 'detect_double_press'
CONF_DETECT_TRIPLE_KEY = 'detect_triple_press'

# automations
CONF_BUTTON_ON_PRESS_KEY = 'on_press'
CONF_BUTTON_ON_DOUBLE_PRESS_KEY = 'on_double_press'
CONF_BUTTON_ON_TRIPLE_PRESS_KEY = 'on_triple_press'
CONF_BUTTON_ON_LONG_PRESS_KEY = 'on_long_press'
CONF_BUTTON_ON_VERY_LONG_PRESS_KEY = 'on_very_long_press'
CONF_BUTTON_WHEN_ON_KEY = 'when_on'
CONF_BUTTON_WHEN_OFF_KEY = 'when_off'

SprockletLed5VOnPressTrigger = sprocklet_ns.class_(
    "SprockletLed5VOnPressTrigger", auto.Trigger.template()
)

SprockletLed5VOnDoublePressTrigger = sprocklet_ns.class_(
    "SprockletLed5VOnDoublePressTrigger", auto.Trigger.template()
)

SprockletLed5VOnTriplePressTrigger = sprocklet_ns.class_(
    "SprockletLed5VOnTriplePressTrigger", auto.Trigger.template()
)

SprockletLed5VOnLongPressTrigger = sprocklet_ns.class_(
    "SprockletLed5VOnLongPressTrigger", auto.Trigger.template()
)

SprockletLed5VOnVeryLongPressTrigger = sprocklet_ns.class_(
    "SprockletLed5VOnVeryLongPressTrigger", auto.Trigger.template()
)

SprockletLed5VWhenOnTrigger = sprocklet_ns.class_(
    "SprockletLed5VWhenOnTrigger", auto.Trigger.template()
)


SprockletLed5VWhenOffTrigger = sprocklet_ns.class_(
    "SprockletLed5VWhenOffTrigger", auto.Trigger.template()
)

## Schema
CONFIG_SCHEMA = cv.ENTITY_BASE_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(SprockletLed5V),
        cv.Required(CONF_CONTROLLER_ID): cv.use_id(SprockletController),
## switch config        
        cv.Optional(CONF_SWITCH_TYPE_KEY, default='momentary'): cv.enum(
            LED5V_SWITCH_TYPES, upper=True, space="_"
        ), 
## LED config        
        cv.Optional(CONF_EFFECT_KEY, default='static'): cv.enum(
            LED5V_EFFECTS, upper=True, space="_"
        ),
## Press detection        
        cv.Optional(CONF_DETECT_LONG_KEY, default=False): cv.boolean,
        cv.Optional(CONF_DETECT_VERY_LONG_KEY, default=False): cv.boolean,
        cv.Optional(CONF_DETECT_DOUBLE_KEY, default=False): cv.boolean,
        cv.Optional(CONF_DETECT_TRIPLE_KEY, default=False): cv.boolean,
## Automations
        cv.Optional(CONF_BUTTON_ON_PRESS_KEY): auto.validate_automation(
            {
                cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(SprockletLed5VOnPressTrigger),
            }
        ),        
        cv.Optional(CONF_BUTTON_ON_DOUBLE_PRESS_KEY): auto.validate_automation(
            {
                cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(SprockletLed5VOnDoublePressTrigger),
            }
        ),        
        cv.Optional(CONF_BUTTON_ON_TRIPLE_PRESS_KEY): auto.validate_automation(
            {
                cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(SprockletLed5VOnTriplePressTrigger),
            }
        ),        
        cv.Optional(CONF_BUTTON_ON_LONG_PRESS_KEY): auto.validate_automation(
            {
                cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(SprockletLed5VOnLongPressTrigger),
            }
        ),        
        cv.Optional(CONF_BUTTON_ON_VERY_LONG_PRESS_KEY): auto.validate_automation(
            {
                cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(SprockletLed5VOnVeryLongPressTrigger),
            }
        ),
        cv.Optional(CONF_BUTTON_WHEN_ON_KEY): auto.validate_automation(
            {
                cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(SprockletLed5VWhenOnTrigger),
            }
        ),
        cv.Optional(CONF_BUTTON_WHEN_OFF_KEY): auto.validate_automation(
            {
                cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(SprockletLed5VWhenOffTrigger),
            }
        ),
    } 
).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_ID].id, config[CONF_SWITCH_TYPE_KEY])
    cg.add(var.setEffect(config[CONF_EFFECT_KEY]))
    cg.add(var.detectLong(config[CONF_DETECT_LONG_KEY]))
    cg.add(var.detectVeryLong(config[CONF_DETECT_VERY_LONG_KEY]))
    cg.add(var.detectDouble(config[CONF_DETECT_DOUBLE_KEY]))    
    cg.add(var.detectTriple(config[CONF_DETECT_TRIPLE_KEY]))
    yield cg.register_component(var, config)
    yield binary_sensor.register_binary_sensor(var, config)
    paren = yield cg.get_variable(config[CONF_CONTROLLER_ID])
    cg.add(paren.register_child(var))


    if CONF_BUTTON_ON_DOUBLE_PRESS_KEY in config:
        for action in config[CONF_BUTTON_ON_DOUBLE_PRESS_KEY]:
            trigger = cg.new_Pvariable(
                action[CONF_TRIGGER_ID], var
            )
            yield auto.build_automation(trigger, [], action)
    if CONF_BUTTON_ON_TRIPLE_PRESS_KEY in config:            
        for action in config[CONF_BUTTON_ON_TRIPLE_PRESS_KEY]:
            trigger = cg.new_Pvariable(
                action[CONF_TRIGGER_ID], var
            )
            yield auto.build_automation(trigger, [], action)
    if CONF_BUTTON_ON_LONG_PRESS_KEY in config:            
        for action in config[CONF_BUTTON_ON_LONG_PRESS_KEY]:
            trigger = cg.new_Pvariable(
                action[CONF_TRIGGER_ID], var
            )
            yield auto.build_automation(trigger, [], action)
    if CONF_BUTTON_ON_VERY_LONG_PRESS_KEY in config:
        for action in config[CONF_BUTTON_ON_VERY_LONG_PRESS_KEY]:
            trigger = cg.new_Pvariable(
                action[CONF_TRIGGER_ID], var
            )
            yield auto.build_automation(trigger, [], action)
    if CONF_BUTTON_WHEN_ON_KEY in config:
        for action in config[CONF_BUTTON_WHEN_ON_KEY]:
            trigger = cg.new_Pvariable(
                action[CONF_TRIGGER_ID], var
            )
            yield auto.build_automation(trigger, [], action)
    if CONF_BUTTON_WHEN_OFF_KEY in config:
        for action in config[CONF_BUTTON_WHEN_OFF_KEY]:
            trigger = cg.new_Pvariable(
                action[CONF_TRIGGER_ID], var
            )
            yield auto.build_automation(trigger, [], action)

## Set effect in an automation
SprockletLed5VSetEffectAction = sprocklet_ns.class_("SprockletLed5VSetEffectAction", auto.Action)
@auto.register_action(
    "sprocklet_led5v.set_effect",
    SprockletLed5VSetEffectAction,
    cv.maybe_simple_value(
        {
            cv.GenerateID(): cv.use_id(SprockletLed5V),
            cv.Required(CONF_EFFECT_KEY): cv.enum(
                LED5V_EFFECTS, upper=True, space="_"
            )
        },
        key=CONF_EFFECT_KEY
    ),
)
def sprocklet_led5v_set_effect_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id, template_arg, config[CONF_EFFECT_KEY])
    yield cg.register_parented(var, config[CONF_ID])
    yield var
