#pragma once

#include "esphome/core/component.h"
#include "esphome/core/helpers.h"
#include "esphome/components/sprocklet_switch/SprockletSwitch.h"
#include "esphome/components/sprocklet/Sprocklet.h"
#include "esphome/components/light/light_output.h"
#include "esphome/components/sprocklet/DirtyValue.h"

#include <sprocklets/D-LED-5V.h>

namespace esphome
{
	namespace sprocklet
	{
		namespace led5v
		{
			class SprockletLED5V : public light::LightOutput,
								public Component,
								public Sprocklet
			{
			public:
				SprockletLED5V(const char *id, int position);

				uint16_t deviceId() { return DLED5V_DEVICE_ID; }

				light::LightTraits get_traits() override;
				void setup_state(light::LightState *state) override;
				void write_state(light::LightState *state) override;

				void setEffect(DLED5V_EFFECTS effect);
				void setAction(DLED5V_SW_ACTION action);

				void setSwitch(switches::SprockletSwitch *sw);
			protected:
				void onAddressProgrammed(uint8_t address) override;

			private:
				void publishStates();
				void publishEffect();
				void publishBrightness();
				void publishAction();

  				light::LightState *				_state{nullptr};
				switches::SprockletSwitch *		_switch{nullptr};

				DirtyValue<uint32_t> 			_brightness{255};
				DirtyValue<DLED5V_EFFECTS> 		_effect{DLED5V_EFFECT_STATIC};
				DirtyValue<DLED5V_SW_ACTION> 	_switchAction{DLED5V_ACTION_NONE};
				uint32_t 						min_value{0};
				uint32_t 						max_value{255};
			};
		}
	}
}