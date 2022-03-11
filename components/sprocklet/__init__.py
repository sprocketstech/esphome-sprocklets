import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

MULTI_CONF = True

CONF_CONTROLLER_ID = 'controller_id'
CONF_CHILDREN = 'children'

sprocklet_ns = cg.esphome_ns.namespace("sprocklet")
SprockletController = sprocklet_ns.class_("SprockletController", cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SprockletController),
        cv.Required(CONF_CHILDREN): cv.All(
            cv.ensure_list(cv.string_strict)
        )
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_CHILDREN])
    await cg.register_component(var, config)

