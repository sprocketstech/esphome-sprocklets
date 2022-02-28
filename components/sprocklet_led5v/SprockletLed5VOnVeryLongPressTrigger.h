#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "SprockletLED5V.h"

namespace esphome
{
	namespace sprocklet
	{
		class SprockletLed5VOnVeryLongPressTrigger : public Trigger<>
		{
		public:
			SprockletLed5VOnVeryLongPressTrigger(SprockletLED5V *led)
			{
				led->addOnVeryLongPressCallback([this]()
												{
											this->stop_action(); // stop any previous running actions
											this->trigger(); });
			}
		};
	}
}