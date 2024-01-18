#include "SprockletSwitch.h"
#include "esphome.h"

#include "esphome/components/sprocklet/Bus.h"

namespace esphome
{
    namespace sprocklet
    {
        namespace switches
        {
            void SprockletSwitch::configure(uint8_t address,
                                                uint8_t typeRegister,
                                                uint8_t ageRegister,
                                                uint8_t stateRegister,
                                                uint8_t clickCountRegister,
                                                uint8_t pressDurationRegister)
            {
                _address = address;
                _typeRegister = typeRegister;
                _ageRegister = ageRegister;
                _stateRegister = stateRegister;
                _clickCountRegister = clickCountRegister;
                _pressDurationRegister = pressDurationRegister;
                update();
            }

            void SprockletSwitch::update()
            {
                publishType();
                publishAge();
                // read the states
                processState();
                processClickCount();
                processPressDuration();
            }

            
            void SprockletSwitch::publishType()
            {
                if (_address != SPROCKET_UNADDRESSED && _switchType.dirty())
                {
                    ESP_LOGD("SprockletSwitch", "Type %d to %d", _switchType.value(), _address);
                    Bus::write8(_address, _typeRegister, _switchType.value());
                    _switchType.clean();
                }
            }

            void SprockletSwitch::publishAge()
            {
                if (_address != SPROCKET_UNADDRESSED && _switchAge.dirty())
                {
                    ESP_LOGD("SprockletSwitch", "Age %d to %d", _switchAge.value(), _address);
                    Bus::write8(_address, _ageRegister, _switchAge.value());
                    _switchAge.clean();
                }
            }

            void SprockletSwitch::processState()
            {
                if (_address != SPROCKET_UNADDRESSED)
                {
                    uint8_t state = Bus::read8(_address, _stateRegister);
                    _lastState = state == 1;
                    publish_state(_lastState.value());
                    if (_lastState.dirty())
                    {
                        ESP_LOGD("SprockletSwitch", "Got state %d from address %d", _lastState.value(), _address);
                        if (_lastState.value())
                        {
                            _whenOnCallbacks.call();
                        }
                        else
                        {
                            _whenOffCallbacks.call();
                        }
                        _lastState.clean();
                    }
                }
            }

            void SprockletSwitch::processClickCount()
            {
                if (_address != SPROCKET_UNADDRESSED)
                {
                    _lastClickCount = Bus::read8(_address, _clickCountRegister);
                    if (_lastClickCount.dirty())
                    {
                        if (this->_clickCountSensor != nullptr)
                        {
                            this->_clickCountSensor->publish_state(_lastClickCount.value());
                        }

                        ESP_LOGD("SprockletSwitch", "Got click count %d from address %d", _lastClickCount.value(), _address);
                        
                        if (_lastClickCount.value() == 1)
                        {
                            _onPressCallbacks.call();
                        }
                        if (_lastClickCount.value() == 2)
                        {
                            _onDoublePressCallbacks.call();
                        }
                        if (_lastClickCount.value() >= 3)
                        {
                            _onTriplePressCallbacks.call();
                        }
                        _lastClickCount.clean();
                    }
                }
            }

            void SprockletSwitch::processPressDuration()
            {
                if (_address != SPROCKET_UNADDRESSED)
                {
                    _lastPressDuration = Bus::read32(_address, _pressDurationRegister);
                    
                    if (_lastPressDuration.dirty())
                    {   
                        if (this->_pressDurationSensor != nullptr)
                        {
                            this->_pressDurationSensor->publish_state(_lastPressDuration.value());
                        }

                        ESP_LOGD("SprockletSwitch", "Got press duration %d from address %d", _lastPressDuration.value(), _address);
                        
                        if (_lastPressDuration.value() >= _longPressThreshold)
                        {
                            _onLongPressCallbacks.call();
                        }
                        if (_lastPressDuration.value() >= _veryLongPressThreshold)
                        {
                            _onVeryLongPressCallbacks.call();
                        }
                        _lastPressDuration.clean();
                    }
                }
            }
        }
    }
}