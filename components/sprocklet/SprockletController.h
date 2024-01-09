#pragma once
#include "esphome.h"

namespace esphome
{
	namespace sprocklet
	{
		enum SprockletBoardType
		{
			SprockletESP12
		};

		class SprockletController : public Component
		{
		public:
			SprockletController(SprockletBoardType boardType);
			void setup() override;
			void loop() override;

			void register_child(Sprocklet *obj) { this->_sprocklets.push_back(obj); }

		private:
			SprockletBoard *_board;
			std::vector<Sprocklet *> _sprocklets;
		};

	}
}