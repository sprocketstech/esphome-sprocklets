#include "SprockletLED5V.h"
#include "esphome.h"
#include <Wire.h>
namespace esphome
{
    namespace sprocklet
    {
        void SprockletLED5V::setup()
        {
            ESP_LOGD("SprockletLED5VLight", "Switch type %d", _switchType);
            Wire.beginTransmission(address());
            Wire.write(DLED5V_SW_TYPE_REGISTER);
            Wire.write((uint8_t)_switchType);
            Wire.endTransmission();
            delay(1);
            update();
        }

        void SprockletLED5V::update()
        {
            DLED5V_SWITCH_STATE state = _lastState;
            // read the state
            Wire.beginTransmission(address());
            // start reading at the state register
            Wire.write(DLED5V_SW_STATE_REGISTER);
            Wire.endTransmission(false);
            Wire.requestFrom(address(), (uint8_t)1, true);
            if (Wire.available() >= 1)
            {
                state = (DLED5V_SWITCH_STATE)Wire.read();
            }
            Wire.endTransmission();
            delay(1);

            auto on = state == DLED5V_SWITCH_ON ||
                      state == DLED5V_SWITCH_PRESS ||
                      state == DLED5V_SWITCH_LONG_PRESS ||
                      state == DLED5V_SWITCH_VERY_LONG_PRESS ||
                      state == DLED5V_SWITCH_DOUBLE_PRESS ||
                      state == DLED5V_SWITCH_TRIPLE_PRESS;
            publish_state(on);

            if (_lastState != state)
            {
                ESP_LOGD("SprockletLED5V", "Got state %d from address %d", state, address());
                switch (state)
                {
                case DLED5V_SWITCH_PRESS:
                    _onPressCallbacks.call();
                    break;
                case DLED5V_SWITCH_LONG_PRESS:
                    _onLongPressCallbacks.call();
                    break;
                case DLED5V_SWITCH_VERY_LONG_PRESS:
                    _onVeryLongPressCallbacks.call();
                    break;
                case DLED5V_SWITCH_DOUBLE_PRESS:
                    _onDoublePressCallbacks.call();
                    break;
                case DLED5V_SWITCH_TRIPLE_PRESS:
                    _onTriplePressCallbacks.call();
                    break;
                case DLED5V_SWITCH_ON:
                    _whenOnCallbacks.call();
                    break;
                case DLED5V_SWITCH_OFF:
                    _whenOffCallbacks.call();
                    break;
                }
                _lastState = state;
            }

            if (_effectDirty)
            {
                publishEffect();
            }
            if (_configDirty)
            {
                publishConfig();
            }
            if (_brightnessDirty)
            {
                publishBrightness();
            }
        }

        void SprockletLED5V::dump_config()
        {
        }

        void SprockletLED5V::write_state(float bright)
        {
            _brightness = static_cast<uint32_t>(bright * this->max_value);
            _brightness = std::max(_brightness, this->min_value);
            publishBrightness();
        }

        void SprockletLED5V::setEffect(DLED5V_EFFECTS effect)
        {
            _effect = effect;
            publishEffect();
        }

        void SprockletLED5V::detectLong(bool detect)
        {
            if (detect)
            {
                _switchConfig |= DLED5V_SWITCH_DETECT_LONG;
            }
            else
            {
                _switchConfig &= ~DLED5V_SWITCH_DETECT_LONG;
            }
            publishConfig();
        }

        void SprockletLED5V::detectVeryLong(bool detect)
        {
            if (detect)
            {
                _switchConfig |= DLED5V_SWITCH_DETECT_VERYLONG;
            }
            else
            {
                _switchConfig &= ~DLED5V_SWITCH_DETECT_VERYLONG;
            }
            publishConfig();
        }

        void SprockletLED5V::detectDouble(bool detect)
        {
            if (detect)
            {
                _switchConfig |= DLED5V_SWITCH_DETECT_DOUBLE_PRESS;
            }
            else
            {
                _switchConfig &= ~DLED5V_SWITCH_DETECT_DOUBLE_PRESS;
            }
            publishConfig();
        }

        void SprockletLED5V::detectTriple(bool detect)
        {
            if (detect)
            {
                _switchConfig |= DLED5V_SWITCH_DETECT_TRIPLE_PRESS;
            }
            else
            {
                _switchConfig &= ~DLED5V_SWITCH_DETECT_TRIPLE_PRESS;
            }
            publishConfig();
        }

        void SprockletLED5V::publishBrightness()
        {

            if (address() != SPROCKET_UNADDRESSED)
            {
                ESP_LOGD("SprockletLED5VLight", "Brightness %d to %d", _brightness, address());
                // set the brightness
                Wire.beginTransmission(address());
                Wire.write(DLED5V_LED_BRIGHTNESS_REGISTER);
                Wire.write((uint8_t)_brightness);
                auto error = Wire.endTransmission();
                ESP_LOGD("SprockletLED5VLight", "Brightness error %d from %d", error, address());
                delay(1);
                if (error == 0)
                {
                    _brightnessDirty = false;
                }
                else
                {
                    _brightnessDirty = true;
                }
            }
            else
            {
                // flag for update loop
                _brightnessDirty = true;
            }
        }

        void SprockletLED5V::publishEffect()
        {
            if (address() != SPROCKET_UNADDRESSED)
            {
                ESP_LOGD("SprockletLED5VLight", "Effect %d to %d", _effect, address());
                Wire.beginTransmission(address());
                Wire.write(DLED5V_LED_EFFECT_REGISTER);
                Wire.write((uint8_t)_effect);
                Wire.endTransmission();
                delay(1);
                _effectDirty = false;
            }
            else
            {
                // flag for update loop
                _effectDirty = true;
            }
        }

        void SprockletLED5V::publishConfig()
        {
            if (address() != SPROCKET_UNADDRESSED)
            {
                ESP_LOGD("SprockletLED5VLight", "Detect Config %d on %d", _switchConfig, address());
                Wire.beginTransmission(address());
                Wire.write(DLED5V_SW_DETECT_REGISTER);
                Wire.write((uint8_t)_switchConfig);
                Wire.endTransmission();
                delay(1);
                _configDirty = false;
            }
            else
            {
                // flag for update loop
                _configDirty = true;
            }
        }

    }
}