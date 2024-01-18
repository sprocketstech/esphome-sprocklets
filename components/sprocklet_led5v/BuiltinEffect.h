#pragma once
#include "esphome/components/light/light_effect.h"
namespace esphome
{
    namespace sprocklet
    {
        namespace led5v
        {
			class BuiltinEffect : public light::LightEffect
			{
            public:
                BuiltinEffect(std::string name, const std::function<void()>& cb) : light::LightEffect(name), _cb(cb)
                {
                }

                virtual void apply()
                {
                    _cb();
                }
            private:
                const std::function<void()> _cb;
            };
        }
    }
}

