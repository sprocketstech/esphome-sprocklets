#include "SprockletLED5V.h"
#include "BuiltinEffect.h"
#include "esphome.h"

namespace esphome
{
    namespace sprocklet
    {
        namespace led5v
        {
            SprockletLED5V::SprockletLED5V(const char *id, int position) :
                Sprocklet(id, position)
            {
            }

            void SprockletLED5V::setup_state(light::LightState *state)
            {
                if (failed())
                {
                    state->mark_failed();
                }
                
                this->_state = state;
                std::vector<light::LightEffect *> namedEffects =
                {
                    new BuiltinEffect("static", [this]() { this->setEffect(DLED5V_EFFECT_STATIC); }),
                    new BuiltinEffect("slow blink", [this]() { this->setEffect(DLED5V_EFFECT_SLOW_BLINK); }),
                    new BuiltinEffect("fast blink", [this]() { this->setEffect(DLED5V_EFFECT_FAST_BLINK); }),
                    new BuiltinEffect("breathe", [this]() { this->setEffect(DLED5V_EFFECT_BREATHE); }),
                    new BuiltinEffect("candle", [this]() { this->setEffect(DLED5V_EFFECT_CANDLE); }),
                    new BuiltinEffect("sparkle", [this]() { this->setEffect(DLED5V_EFFECT_SPARKLE); })
                };
                this->_state->add_effects(namedEffects);
            }

            light::LightTraits SprockletLED5V::get_traits()
            {
                auto traits = light::LightTraits();
                traits.set_supported_color_modes({light::ColorMode::BRIGHTNESS});
                return traits;
            }
							
            void SprockletLED5V::write_state(light::LightState *state)
            {
                float brightness;
                state->current_values_as_brightness(&brightness);
                _brightness = static_cast<uint32_t>(brightness * (float)this->max_value);
                _brightness = std::max(_brightness.value(), this->min_value);
                publishBrightness();
            }
            
            void SprockletLED5V::setSwitch(switches::SprockletSwitch *sw)
            {
                _switch = sw;
                _switch->configure(address(),
                                    DLED5V_SWITCH_TYPE_REGISTER,
                                    DLED5V_SWITCH_AGE_REGISTER,
                                    DLED5V_SWITCH_TOGGLE_STATE_REGISTER,
                                    DLED5V_SWITCH_MOMENTARY_CLICK_COUNT_REGISTER,
                                    DLED5V_SWITCH_MOMENTARY_PRESS_DURATION_REGISTER);
            }


            void SprockletLED5V::publishStates()
            {
                publishEffect();
                publishBrightness();
                publishAction();
            }

            void SprockletLED5V::setEffect(DLED5V_EFFECTS effect)
            {
                _effect = effect;
                publishEffect();
            }

            void SprockletLED5V::setAction(DLED5V_SW_ACTION action)
            {
                _switchAction = action;
                publishAction();
            }

            void SprockletLED5V::publishBrightness()
            {
                if (address() != SPROCKET_UNADDRESSED && _brightness.dirty())
                {
                    ESP_LOGD("SprockletLED5VLight", "Brightness %d to %d", _brightness.value(), address());
                    Bus::write8(address(), DLED5V_LED_BRIGHTNESS_REGISTER, (uint8_t)_brightness.value());
                    _brightness.clean();
                }
            }

            void SprockletLED5V::publishEffect()
            {
                if (address() != SPROCKET_UNADDRESSED && _effect.dirty())
                {
                    ESP_LOGD("SprockletLED5VLight", "Effect %d to %d", _effect.value(), address());
                    Bus::write8(address(), DLED5V_LED_EFFECT_REGISTER, (uint8_t)_effect.value());
                    _effect.clean();
                }
            }

            void SprockletLED5V::publishAction()
            {
                if (address() != SPROCKET_UNADDRESSED && _switchAction.dirty())
                {
                    ESP_LOGD("SprockletLED5VLight", "Action %d to %d", _switchAction.value(), address());
                    Bus::write8(address(), DLED5V_SWITCH_ACTION_REGISTER, (uint8_t)_switchAction.value());
                    _switchAction.clean();
                }
            }
            
            void SprockletLED5V::onAddressProgrammed(uint8_t address)
            {
                if (_switch != nullptr)
                {
                    _switch->configure(address,
                                        DLED5V_SWITCH_TYPE_REGISTER,
                                        DLED5V_SWITCH_AGE_REGISTER,
                                        DLED5V_SWITCH_TOGGLE_STATE_REGISTER,
                                        DLED5V_SWITCH_MOMENTARY_CLICK_COUNT_REGISTER,
                                        DLED5V_SWITCH_MOMENTARY_PRESS_DURATION_REGISTER);
                }
            }
        }
    }
}