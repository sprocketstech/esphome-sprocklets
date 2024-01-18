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
			class SprockletSwitchOnDoublePressTrigger : public Trigger<>
			{
			public:
				SprockletSwitchOnDoublePressTrigger(SprockletSwitch *sw)
				{
					sw->addOnDoublePressCallback([this]()
												{
												this->stop_action(); // stop any previous running actions
												this->trigger(); });
				}
			};
		}
	}
}