#include "SprockletLEDWS.h"

#include "esphome.h"

namespace esphome
{
    namespace sprocklet
    {
        namespace ledws
        {
            SprockletLEDWS::SprockletLEDWS(const char *id, int position) :
                Sprocklet(id, position)
            {
            }

            void SprockletLEDWS::write_state(light::LightState *state)
            {
                this->publishNumLeds();
                if (address() != SPROCKET_UNADDRESSED)
                {
                    BusWriter writer(address(), DLEDWS_RGB_START_REGISTER);
                    for (int i=0; i < _numLeds.value(); ++i)
                    {
                        writer.write(_leds[i].g);
                        writer.write(_leds[i].r);
                        writer.write(_leds[i].b);
                    }
                    writer.end();
                    this->mark_shown_();
                }
                else
                {
                    this->schedule_show();
                }
            }

            void SprockletLEDWS::clear_effect_data()
            {
                for (int i = 0; i < this->size(); i++)
                {
                    this->_effectData[i] = 0;
                }
            }

            light::LightTraits SprockletLEDWS::get_traits()
            {
                auto traits = light::LightTraits();
                traits.set_supported_color_modes({
                    light::ColorMode::RGB
                });
                return traits;
            }

            void SprockletLEDWS::setSwitch(switches::SprockletSwitch *sw)
            {
                _switch = sw;
                _switch->configure(address(),
                                    DLEDWS_SWITCH_TYPE_REGISTER,
                                    DLEDWS_SWITCH_AGE_REGISTER,
                                    DLEDWS_SWITCH_TOGGLE_STATE_REGISTER,
                                    DLEDWS_SWITCH_MOMENTARY_CLICK_COUNT_REGISTER,
                                    DLEDWS_SWITCH_MOMENTARY_PRESS_DURATION_REGISTER);
            }

            void SprockletLEDWS::setAction(DLEDWS_SW_ACTION action)
            {
                _switchAction = action;
                publishAction();
            }


            void SprockletLEDWS::setNumLeds(uint8_t numLeds)
            {
                ESP_LOGD("SprockletLEDWSLight", "NumLEDs %d to %d", numLeds, address());
                _numLeds = numLeds;
                _leds = new cRGB[numLeds];
                _effectData = new uint8_t[numLeds];

                // initialize the LED colors
                for (int i = 0; i < numLeds; i++) {
                    this->_leds[i].r = 0;
                    this->_leds[i].b = 0;
                    this->_leds[i].g = 0;
                }

                publishNumLeds();
            }

            void SprockletLEDWS::publishAction()
            {
                if (address() != SPROCKET_UNADDRESSED && _switchAction.dirty())
                {
                    ESP_LOGD("SprockletLEDWSLight", "Action %d to %d", _switchAction.value(), address());
                    Bus::write8(address(), DLEDWS_SWITCH_ACTION_REGISTER, _switchAction.value());
                    _switchAction.clean();
                }
            }

            void SprockletLEDWS::publishNumLeds()
            {
                if (address() != SPROCKET_UNADDRESSED && _numLeds.dirty())
                {
                    ESP_LOGD("SprockletLEDWSLight", "Num Leds %d to %d", _numLeds.value(), address());
                    Bus::write8(address(), DLEDWS_NUM_LEDS_REGISTER, _numLeds.value());
                    _numLeds.clean();
                }
            }

            light::ESPColorView SprockletLEDWS::get_view_internal(int32_t index) const
            {
                return {
                        &this->_leds[index].r,
                        &this->_leds[index].g,
                        &this->_leds[index].b,
                        nullptr,
                        &this->_effectData[index],
                        &this->correction_
                       };
            }

            void SprockletLEDWS::onAddressProgrammed(uint8_t address)
            {
                if (_switch != nullptr)
                {
                    _switch->configure(address,
                                        DLEDWS_SWITCH_TYPE_REGISTER,
                                        DLEDWS_SWITCH_AGE_REGISTER,
                                        DLEDWS_SWITCH_TOGGLE_STATE_REGISTER,
                                        DLEDWS_SWITCH_MOMENTARY_CLICK_COUNT_REGISTER,
                                        DLEDWS_SWITCH_MOMENTARY_PRESS_DURATION_REGISTER);
                }
                publishNumLeds();
                publishAction();
            }
        }
    }
}