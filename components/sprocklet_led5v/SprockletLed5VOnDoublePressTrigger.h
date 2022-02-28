#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "SprockletLED5V.h"

namespace esphome
{
	namespace sprocklet
	{
		class SprockletLed5VOnDoublePressTrigger : public Trigger<>
		{
		public:
			SprockletLed5VOnDoublePressTrigger(SprockletLED5V *led)
			{
				led->addOnDoublePressCallback([this]()
											  {
											this->stop_action(); // stop any previous running actions
											this->trigger(); });
			}
		};
	}
}