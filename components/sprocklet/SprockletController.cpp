#include "SprockletController.h"
#include "C_ESP12.h"

#include <algorithm>
namespace esphome
{
	namespace sprocklet
	{
		static const char *const TAG = "sprocklet_esp12";

		SprockletController::SprockletController(SprockletBoardType boardType)
		{
			switch (boardType)
			{
				default:
					_board = new SprockletESP12Board();
					break;
			}
		}

		void debuglog(const char *msg)
		{
			esp_log_printf_(ESPHOME_LOG_LEVEL_DEBUG, TAG, __LINE__, msg);
		}

		void SprockletController::setup()
		{
			// sort the vector of sprocklets in the order specified
			std::sort(_sprocklets.begin(), _sprocklets.end(), [](const Sprocklet * a, const Sprocklet * b)
			{
				return a->position() < b->position(); 
			});

			_board->programAddresses(debuglog, _sprocklets);
		}

		void SprockletController::loop()
		{
		}
	}
}