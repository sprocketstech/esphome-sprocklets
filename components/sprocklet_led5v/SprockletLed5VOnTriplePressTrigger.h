#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "SprockletLED5V.h"

namespace esphome
{
	namespace sprocklet
	{
		class SprockletLed5VOnTriplePressTrigger : public Trigger<>
		{
		public:
			SprockletLed5VOnTriplePressTrigger(SprockletLED5V *led)
			{
				led->addOnTriplePressCallback([this]()
											  {
											this->stop_action(); // stop any previous running actions
											this->trigger(); });
			}
		};
	}
}