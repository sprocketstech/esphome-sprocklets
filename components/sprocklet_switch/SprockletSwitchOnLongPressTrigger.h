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
			class SprockletSwitchOnLongPressTrigger : public Trigger<>
			{
			public:
				SprockletSwitchOnLongPressTrigger(SprockletSwitch *sw)
				{
					sw->addOnLongPressCallback([this]()
												{
												this->stop_action(); // stop any previous running actions
												this->trigger(); });
				}
			};
		}
	}
}