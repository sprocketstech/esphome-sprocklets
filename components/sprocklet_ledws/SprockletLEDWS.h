#pragma once

#include "esphome/core/component.h"
#include "esphome/core/helpers.h"
#include "esphome/components/sprocklet_switch/SprockletSwitch.h"
#include "esphome/components/sprocklet/Sprocklet.h"
#include "esphome/components/light/addressable_light.h"
#include "esphome/components/sprocklet/DirtyValue.h"

#include <sprocklets/D-LED-WS.h>

namespace esphome
{
	namespace sprocklet
	{
		namespace ledws
		{
			
			struct cRGB
			{
				uint8_t g;
				uint8_t r;
				uint8_t b;
			};
			
			class SprockletLEDWS : public light::AddressableLight,
								public Sprocklet
			{
			public:
				SprockletLEDWS(const char *id, int position);

  				inline int32_t size() const override { return this->_numLeds.value(); }
				uint16_t deviceId() { return DLEDWS_DEVICE_ID; }

				light::LightTraits get_traits() override;
  				void write_state(light::LightState *state) override;
				void clear_effect_data() override;

				void setAction(DLEDWS_SW_ACTION action);
				void setNumLeds(uint8_t numLeds);
                void setSwitch(switches::SprockletSwitch *sw);

            protected:
                void onAddressProgrammed(uint8_t address) override;
				light::ESPColorView get_view_internal(int32_t index) const override;

			private:
				void publishAction();
				void publishNumLeds();
				
                switches::SprockletSwitch *		_switch{nullptr};
				cRGB *							_leds{nullptr};
  				uint8_t *						_effectData{nullptr};
				DirtyValue<uint8_t>         	_numLeds{8};
				DirtyValue<DLEDWS_SW_ACTION>	_switchAction{DLEDWS_ACTION_NONE};
			};
		}
	}
}