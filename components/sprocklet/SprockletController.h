#pragma once
#include "esphome.h"
#include <Sprocklets.h>
namespace esphome
{
	namespace sprocklet
	{
		class SprockletController : public Component
		{
		public:
			SprockletController(std::vector<std::string> childIds)
			{
				_childIds = childIds;
			}

			void setup() override;
			void loop() override;

			void register_child(Sprocklet *obj) { this->_sprocklets.push_back(obj); }

		private:
			SprockletESP12Board _board;
			std::vector<Sprocklet *> _sprocklets;
			std::vector<std::string> _childIds;
		};

	}
}