#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "SprockletLED5V.h"

namespace esphome
{
	namespace sprocklet
	{
		class SprockletLed5VOnLongPressTrigger : public Trigger<>
		{
		public:
			SprockletLed5VOnLongPressTrigger(SprockletLED5V *led)
			{
				led->addOnLongPressCallback([this]()
											{
											this->stop_action(); // stop any previous running actions
											this->trigger(); });
			}
		};
	}
}