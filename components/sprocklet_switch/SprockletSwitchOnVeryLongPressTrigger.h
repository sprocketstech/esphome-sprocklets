#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "SprockletSwitch.h"

namespace esphome
{
	namespace sprocklet
	{
		namespace switches
		{		
			class SprockletSwitchOnVeryLongPressTrigger : public Trigger<>
			{
			public:
				SprockletSwitchOnVeryLongPressTrigger(SprockletSwitch *sw)
				{
					sw->addOnVeryLongPressCallback([this]()
													{
												this->stop_action(); // stop any previous running actions
												this->trigger(); });
				}
			};
		}
	}
}