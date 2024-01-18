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
			class SprockletSwitchWhenOnTrigger : public Trigger<>
			{
			public:
				SprockletSwitchWhenOnTrigger(SprockletSwitch *sw)
				{
					sw->addWhenOnCallback([this]()
										{
												this->stop_action(); // stop any previous running actions
												this->trigger(); });
				}
			};
		}
	}
}