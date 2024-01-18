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
			class SprockletSwitchWhenOffTrigger : public Trigger<>
			{
			public:
				SprockletSwitchWhenOffTrigger(SprockletSwitch *sw)
				{
					sw->addWhenOffCallback([this]()
											{
												this->stop_action(); // stop any previous running actions
												this->trigger(); });
				}
			};
		}
	}
}