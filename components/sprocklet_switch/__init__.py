import esphome.codegen as cg
import esphome.config_validation as cv
import esphome.automation as auto
from esphome.components import binary_sensor, sensor
from esphome.const import (
    CONF_TRIGGER_ID,
    UNIT_EMPTY,
    UNIT_MILLISECOND,
    DEVICE_CLASS_DURATION,
    DEVICE_CLASS_EMPTY
)

from ..sprocklet import sprocklet_ns

sprocklet_switch_ns = sprocklet_ns.namespace("switches")

AUTO_LOAD = ['binary_sensor']
DEPENDENCIES = ["sensor"]

## Switch Types
CONF_SPROCKLET_SWITCH_TYPE_KEY = 'type'

SprockletSwitchType = cg.global_ns.enum("DSPROCKLET_SWITCH_TYPE")
SPROCKLET_SWITCH_TYPES = {
    "NONE": SprockletSwitchType.DSPROCKLET_SWITCH_NONE,
    "MOMENTARY": SprockletSwitchType.DSPROCKLET_SWITCH_MOMENTARY,
    "TOGGLE": SprockletSwitchType.DSPROCKLET_SWITCH_TOGGLE,
}

## config
CONF_SPROCKLET_SWITCH_AGE_KEY = 'age'
CONF_SPROCKLET_SWITCH_CLICK_COUNT_KEY = 'click_count'
CONF_SPROCKLET_SWITCH_PRESS_DURATION_KEY = 'press_duration'
CONF_SPROCKLET_LONG_PRESS_THRESHOLD_KEY = 'long_press_threshold'
CONF_SPROCKLET_VERY_LONG_PRESS_THRESHOLD_KEY = 'very_long_press_threshold'

# automations
CONF_SPROCKLET_ON_PRESS_KEY = 'on_press'
CONF_SPROCKLET_ON_DOUBLE_PRESS_KEY = 'on_double_press'
CONF_SPROCKLET_ON_TRIPLE_PRESS_KEY = 'on_triple_press'
CONF_SPROCKLET_ON_LONG_PRESS_KEY = 'on_long_press'
CONF_SPROCKLET_ON_VERY_LONG_PRESS_KEY = 'on_very_long_press'
CONF_SPROCKLET_WHEN_ON_KEY = 'when_on'
CONF_SPROCKLET_WHEN_OFF_KEY = 'when_off'

SprockletSwitch = sprocklet_switch_ns.class_("SprockletSwitch", binary_sensor.BinarySensor, cg.Component)

SprockletSwitchOnPressTrigger = sprocklet_switch_ns.class_(
    "SprockletSwitchOnPressTrigger", auto.Trigger.template()
)

SprockletSwitchOnDoublePressTrigger = sprocklet_switch_ns.class_(
    "SprockletSwitchOnDoublePressTrigger", auto.Trigger.template()
)

SprockletSwitchOnTriplePressTrigger = sprocklet_switch_ns.class_(
    "SprockletSwitchOnTriplePressTrigger", auto.Trigger.template()
)

SprockletSwitchOnLongPressTrigger = sprocklet_switch_ns.class_(
    "SprockletSwitchOnLongPressTrigger", auto.Trigger.template()
)

SprockletSwitchOnVeryLongPressTrigger = sprocklet_switch_ns.class_(
    "SprockletSwitchOnVeryLongPressTrigger", auto.Trigger.template()
)

SprockletSwitchWhenOnTrigger = sprocklet_switch_ns.class_(
    "SprockletSwitchWhenOnTrigger", auto.Trigger.template()
)

SprockletSwitchWhenOffTrigger = sprocklet_switch_ns.class_(
    "SprockletSwitchWhenOffTrigger", auto.Trigger.template()
)

SPROCKLET_SWITCH_SCHEMA = cv.All(
    binary_sensor.binary_sensor_schema(SprockletSwitch)
    .extend(
        {
            ## switch config        
            cv.Optional(CONF_SPROCKLET_SWITCH_TYPE_KEY, default='momentary'): cv.enum(
                SPROCKLET_SWITCH_TYPES, upper=True, space="_"
            ),
            cv.Optional(CONF_SPROCKLET_SWITCH_AGE_KEY): cv.positive_int,
            cv.Optional(CONF_SPROCKLET_LONG_PRESS_THRESHOLD_KEY): cv.positive_int,
            cv.Optional(CONF_SPROCKLET_VERY_LONG_PRESS_THRESHOLD_KEY): cv.positive_int,
            cv.Optional(CONF_SPROCKLET_SWITCH_CLICK_COUNT_KEY): sensor.sensor_schema(
                unit_of_measurement=UNIT_EMPTY,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_EMPTY,
            ),
            cv.Optional(CONF_SPROCKLET_SWITCH_PRESS_DURATION_KEY): sensor.sensor_schema(
                unit_of_measurement=UNIT_MILLISECOND,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_DURATION,
            ),
            ## Automations
            cv.Optional(CONF_SPROCKLET_ON_PRESS_KEY): auto.validate_automation(
                {
                    cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(SprockletSwitchOnPressTrigger),
                }
            ),        
            cv.Optional(CONF_SPROCKLET_ON_DOUBLE_PRESS_KEY): auto.validate_automation(
                {
                    cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(SprockletSwitchOnDoublePressTrigger),
                }
            ),        
            cv.Optional(CONF_SPROCKLET_ON_TRIPLE_PRESS_KEY): auto.validate_automation(
                {
                    cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(SprockletSwitchOnTriplePressTrigger),
                }
            ),        
            cv.Optional(CONF_SPROCKLET_ON_LONG_PRESS_KEY): auto.validate_automation(
                {
                    cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(SprockletSwitchOnLongPressTrigger),
                }
            ),        
            cv.Optional(CONF_SPROCKLET_ON_VERY_LONG_PRESS_KEY): auto.validate_automation(
                {
                    cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(SprockletSwitchOnVeryLongPressTrigger),
                }
            ),
            cv.Optional(CONF_SPROCKLET_WHEN_ON_KEY): auto.validate_automation(
                {
                    cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(SprockletSwitchWhenOnTrigger),
                }
            ),
            cv.Optional(CONF_SPROCKLET_WHEN_OFF_KEY): auto.validate_automation(
                {
                    cv.GenerateID(CONF_TRIGGER_ID): cv.declare_id(SprockletSwitchWhenOffTrigger),
                }
            ),
        }
    )
)

def configure(var, config):
    cg.add(var.setSwitchType(config[CONF_SPROCKLET_SWITCH_TYPE_KEY]))

    if CONF_SPROCKLET_SWITCH_AGE_KEY in config:
        cg.add(var.setSwitchAge(config[CONF_SPROCKLET_SWITCH_AGE_KEY]))

    if CONF_SPROCKLET_LONG_PRESS_THRESHOLD_KEY in config:
        cg.add(var.setLongPressThreshold(config[CONF_SPROCKLET_LONG_PRESS_THRESHOLD_KEY]))
        
    if CONF_SPROCKLET_VERY_LONG_PRESS_THRESHOLD_KEY in config:
        cg.add(var.setVeryLongPressThreshold(config[CONF_SPROCKLET_VERY_LONG_PRESS_THRESHOLD_KEY]))

    yield cg.register_component(var, config)
    yield binary_sensor.register_binary_sensor(var, config)

    for key in [CONF_SPROCKLET_SWITCH_CLICK_COUNT_KEY, CONF_SPROCKLET_SWITCH_PRESS_DURATION_KEY]:
        if key not in config:
            continue

        conf = config[key]
        sens = yield sensor.new_sensor(conf)
        cg.add(getattr(var, f"set_{key}_sensor")(sens))


    if CONF_SPROCKLET_ON_DOUBLE_PRESS_KEY in config:
        for action in config[CONF_SPROCKLET_ON_DOUBLE_PRESS_KEY]:
            trigger = cg.new_Pvariable(
                action[CONF_TRIGGER_ID], var
            )
            yield auto.build_automation(trigger, [], action)
    if CONF_SPROCKLET_ON_TRIPLE_PRESS_KEY in config:            
        for action in config[CONF_SPROCKLET_ON_TRIPLE_PRESS_KEY]:
            trigger = cg.new_Pvariable(
                action[CONF_TRIGGER_ID], var
            )
            yield auto.build_automation(trigger, [], action)
    if CONF_SPROCKLET_ON_LONG_PRESS_KEY in config:            
        for action in config[CONF_SPROCKLET_ON_LONG_PRESS_KEY]:
            trigger = cg.new_Pvariable(
                action[CONF_TRIGGER_ID], var
            )
            yield auto.build_automation(trigger, [], action)
    if CONF_SPROCKLET_ON_VERY_LONG_PRESS_KEY in config:
        for action in config[CONF_SPROCKLET_ON_VERY_LONG_PRESS_KEY]:
            trigger = cg.new_Pvariable(
                action[CONF_TRIGGER_ID], var
            )
            yield auto.build_automation(trigger, [], action)
    if CONF_SPROCKLET_WHEN_ON_KEY in config:
        for action in config[CONF_SPROCKLET_WHEN_ON_KEY]:
            trigger = cg.new_Pvariable(
                action[CONF_TRIGGER_ID], var
            )
            yield auto.build_automation(trigger, [], action)
    if CONF_SPROCKLET_WHEN_OFF_KEY in config:
        for action in config[CONF_SPROCKLET_WHEN_OFF_KEY]:
            trigger = cg.new_Pvariable(
                action[CONF_TRIGGER_ID], var
            )
            yield auto.build_automation(trigger, [], action)
