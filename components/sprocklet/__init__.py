import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

MULTI_CONF = True

CONF_CONTROLLER_ID = 'controller_id'
CONF_POSITION = 'position'
CONF_BOARD = 'board'

sprocklet_ns = cg.esphome_ns.namespace("sprocklet")
SprockletController = sprocklet_ns.class_("SprockletController", cg.Component)

SprockletBoardType = sprocklet_ns.enum("SprockletBoardType")
SPROCKLET_BOARD_TYPES = {
    "esp12": SprockletBoardType.SprockletESP12
}
validate_sprocklet_board_types = cv.enum(SPROCKLET_BOARD_TYPES, upper=False)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SprockletController),
        cv.Optional(CONF_BOARD, default="esp12"):
            cv.ensure_list(validate_sprocklet_board_types),
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID], config[CONF_BOARD])
    await cg.register_component(var, config)
    cg.add_library("Wire", None)
    cg.add_library(
        name="Sprocklets",
        repository="https://github.com/sprocketstech/sprocklet_sdk",
        version="1.0"
        #repository="file://c:/jm/devel/sprocket_sprocklets/sprocklet_sdk",
        #version=None
    )
