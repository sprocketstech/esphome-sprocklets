#pragma once

#include "esphome/core/component.h"
#include "esphome/core/helpers.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/sprocklet/DirtyValue.h"

#include <sprocklets/sprocklets.h>
#include <sprocklets/switch.h>

namespace esphome
{
	namespace sprocklet
	{
        namespace switches
        {
            class SprockletSwitch : public binary_sensor::BinarySensor, 
								            public PollingComponent
            {
            public:
                SprockletSwitch(): PollingComponent(500)
                {
                }

                DSPROCKLET_SWITCH_TYPE getSwitchType() { return _switchType.value(); }
                void setSwitchType(DSPROCKLET_SWITCH_TYPE switchType) { _switchType = switchType; }

                uint16_t getSwitchAge() const { return _switchAge.value(); }
                void setSwitchAge(uint16_t age) { _switchAge = age; }

                uint32_t getLongPressThreshold() const { return _longPressThreshold; }
                void setLongPressThreshold(uint32_t thresh) { _longPressThreshold = thresh; }

                uint32_t getVeryLongPressThreshold() const { return _veryLongPressThreshold; }
                void setVeryLongPressThreshold(uint32_t thresh) { _veryLongPressThreshold = thresh; }
                
                void set_click_count_sensor(sensor::Sensor *clickCountSensor)
                {
                    this->_clickCountSensor = clickCountSensor;
                    this->_clickCountSensor->publish_state(_lastClickCount.value());
                }

                void set_press_duration_sensor(sensor::Sensor *pressDurationSensor)
                {
                    this->_pressDurationSensor = pressDurationSensor;
                    this->_pressDurationSensor->publish_state(_lastPressDuration.value());
                }

                void addWhenOnCallback(std::function<void()> &&callback) { this->_whenOnCallbacks.add(std::move(callback)); }
                void addWhenOffCallback(std::function<void()> &&callback) { this->_whenOffCallbacks.add(std::move(callback)); }
                void addOnPressCallback(std::function<void()> &&callback) { this->_onPressCallbacks.add(std::move(callback)); }
                void addOnDoublePressCallback(std::function<void()> &&callback) { this->_onDoublePressCallbacks.add(std::move(callback)); }
                void addOnTriplePressCallback(std::function<void()> &&callback) { this->_onTriplePressCallbacks.add(std::move(callback)); }
                void addOnLongPressCallback(std::function<void()> &&callback) { this->_onLongPressCallbacks.add(std::move(callback)); }
                void addOnVeryLongPressCallback(std::function<void()> &&callback) { this->_onVeryLongPressCallbacks.add(std::move(callback)); }

				void update() override;

                void configure(uint8_t address,
                                    uint8_t typeRegister,
                                    uint8_t ageRegister,
                                    uint8_t stateRegister,
                                    uint8_t clickCountRegister,
                                    uint8_t pressDurationRegister);
            protected:

            private:
                DirtyValue<bool>                    _lastState{false};
                DirtyValue<uint8_t>                 _lastClickCount{0};
                DirtyValue<uint32_t>                _lastPressDuration{0};

                void publishType();
                void publishAge();
                void processState();
                void processClickCount();
                void processPressDuration();

                sensor::Sensor *                    _clickCountSensor{nullptr};
                sensor::Sensor *                    _pressDurationSensor{nullptr};
                
                DirtyValue<DSPROCKLET_SWITCH_TYPE>  _switchType{DSPROCKLET_SWITCH_NONE};
                DirtyValue<uint16_t>                _switchAge{1000};

                uint32_t                            _longPressThreshold{1000};
                uint32_t                            _veryLongPressThreshold{3000};
                
                uint8_t                             _address{SPROCKET_UNADDRESSED};
                uint8_t                             _typeRegister{0};
                uint8_t                             _ageRegister{0};
                uint8_t                             _stateRegister{0};
                uint8_t                             _clickCountRegister{0};
                uint8_t                             _pressDurationRegister{0};

                CallbackManager<void()>             _whenOnCallbacks{};
                CallbackManager<void()>             _whenOffCallbacks{};
                CallbackManager<void()>             _onPressCallbacks{};
                CallbackManager<void()>             _onDoublePressCallbacks{};
                CallbackManager<void()>             _onTriplePressCallbacks{};
                CallbackManager<void()>             _onLongPressCallbacks{};
                CallbackManager<void()>             _onVeryLongPressCallbacks{};
            };
        }
    }
}