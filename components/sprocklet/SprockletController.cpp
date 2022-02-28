#include "SprockletController.h"

namespace esphome
{
	namespace sprocklet
	{
		static const char *const TAG = "sprocklet_esp12";

		void debuglog(const char *msg)
		{
			esp_log_printf_(ESPHOME_LOG_LEVEL_DEBUG, TAG, __LINE__, msg);
		}

		void SprockletController::setup()
		{
			// build a vector of sprocklets in the proper order
			// based on the childids
			std::vector<Sprocklet *> sprocklets;
			for (auto it = _childIds.begin(); it != _childIds.end(); ++it)
			{
				std::string searchId = *it;
				auto sp = std::find_if(_sprocklets.begin(), _sprocklets.end(), [&searchId](const Sprocklet *obj)
									   { return obj->id() == searchId; });
				if (sp != _sprocklets.end())
				{
					sprocklets.push_back(*sp);
				}
			}
			_board.programAddresses(debuglog, sprocklets);
		}

		void SprockletController::loop()
		{
		}
	}
}