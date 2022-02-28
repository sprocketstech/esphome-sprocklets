#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "SprockletLED5V.h"

namespace esphome
{
	namespace sprocklet
	{
		class SprockletLed5VOnPressTrigger : public Trigger<>
		{
		public:
			SprockletLed5VOnPressTrigger(SprockletLED5V *led)
			{
				led->addOnPressCallback([this]()
										{
											this->stop_action(); // stop any previous running actions
											this->trigger(); });
			}
		};
	}
}