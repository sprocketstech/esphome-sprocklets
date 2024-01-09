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
			class SprockletSwitchOnTriplePressTrigger : public Trigger<>
			{
			public:
				SprockletSwitchOnTriplePressTrigger(SprockletSwitch *sw)
				{
					sw->addOnTriplePressCallback([this]()
												{
												this->stop_action(); // stop any previous running actions
												this->trigger(); });
				}
			};
		}
	}
}