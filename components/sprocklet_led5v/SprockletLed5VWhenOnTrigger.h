#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "SprockletLED5V.h"

namespace esphome
{
	namespace sprocklet
	{
		class SprockletLed5VWhenOnTrigger : public Trigger<>
		{
		public:
			SprockletLed5VWhenOnTrigger(SprockletLED5V *led)
			{
				led->addWhenOnCallback([this]()
									   {
											this->stop_action(); // stop any previous running actions
											this->trigger(); });
			}
		};
	}
}