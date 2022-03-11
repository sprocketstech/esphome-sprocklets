#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "SprockletLED5V.h"

namespace esphome
{
	namespace sprocklet
	{
		class SprockletLed5VWhenOffTrigger : public Trigger<>
		{
		public:
			SprockletLed5VWhenOffTrigger(SprockletLED5V *led)
			{
				led->addWhenOffCallback([this]()
										{
											this->stop_action(); // stop any previous running actions
											this->trigger(); });
			}
		};
	}
}