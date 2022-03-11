#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "SprockletLED5V.h"

namespace esphome
{
	namespace sprocklet
	{
		template <typename... Ts>
		class SprockletLed5VSetEffectAction : public Action<Ts...>, public Parented<SprockletLED5V>
		{
		public:
			SprockletLed5VSetEffectAction(DLED5V_EFFECTS effect)
			{
				_effect = effect;
			}

			void play(Ts... x) override { this->parent_->setEffect(this->_effect); }

		private:
			DLED5V_EFFECTS _effect;
		};
	}
}