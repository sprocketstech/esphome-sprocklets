#pragma once

#include "esphome/core/component.h"
#include "esphome/core/helpers.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/output/float_output.h"
#include <Sprocklets.h>

namespace esphome
{
	namespace sprocklet
	{
		class SprockletLED5V : public binary_sensor::BinarySensor,
							   public output::FloatOutput,
							   public PollingComponent,
							   public Sprocklet
		{
		public:
			SprockletLED5V(const char *id, DLED5V_SWITCH_TYPE switchType) : PollingComponent(1000),
																			Sprocklet(id)

			{
				_switchConfig = DLED5V_SWITCH_DETECT_NONE;
				_lastState = DLED5V_SWITCH_OFF;
				_switchType = switchType;
			}

			void write_state(float val) override;

			void setup() override;
			void update() override;
			void dump_config() override;

			void setEffect(DLED5V_EFFECTS effect);
			void detectLong(bool detect);
			void detectVeryLong(bool detect);
			void detectDouble(bool detect);
			void detectTriple(bool detect);

			uint16_t deviceId() override { return DLED5V_DEVICE_ID; }

			void addWhenOnCallback(std::function<void()> &&callback) { this->_whenOnCallbacks.add(std::move(callback)); }
			void addWhenOffCallback(std::function<void()> &&callback) { this->_whenOffCallbacks.add(std::move(callback)); }

			void addOnPressCallback(std::function<void()> &&callback) { this->_onPressCallbacks.add(std::move(callback)); }
			void addOnDoublePressCallback(std::function<void()> &&callback) { this->_onDoublePressCallbacks.add(std::move(callback)); }
			void addOnTriplePressCallback(std::function<void()> &&callback) { this->_onTriplePressCallbacks.add(std::move(callback)); }
			void addOnLongPressCallback(std::function<void()> &&callback) { this->_onLongPressCallbacks.add(std::move(callback)); }
			void addOnVeryLongPressCallback(std::function<void()> &&callback) { this->_onVeryLongPressCallbacks.add(std::move(callback)); }

		private:
			void publishEffect();
			void publishConfig();
			void publishBrightness();

			DLED5V_SWITCH_STATE _lastState;

			uint32_t _brightness;
			bool _brightnessDirty = false;

			DLED5V_SWITCH_TYPE _switchType;
			DLED5V_EFFECTS _effect = DLED5V_EFFECT_STATIC;
			bool _effectDirty = false;
			uint8_t _switchConfig;
			bool _configDirty = false;
			uint32_t min_value = 0;
			uint32_t max_value = 255;

			CallbackManager<void()> _whenOnCallbacks{};
			CallbackManager<void()> _whenOffCallbacks{};
			CallbackManager<void()> _onPressCallbacks{};
			CallbackManager<void()> _onDoublePressCallbacks{};
			CallbackManager<void()> _onTriplePressCallbacks{};
			CallbackManager<void()> _onLongPressCallbacks{};
			CallbackManager<void()> _onVeryLongPressCallbacks{};
		};
	}
}