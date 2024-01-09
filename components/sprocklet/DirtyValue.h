#pragma once
#include <stdint.h>

namespace esphome
{
    namespace sprocklet
    {
        template<typename T>
        class DirtyValue
        {
        public:
            DirtyValue(const T & initial) : _value(initial), _isDirty(true)
            {
            }
            
            T value() const { return _value; }
            bool dirty() const { return _isDirty; }
            void clean() { _isDirty = false; }

            T& operator =(const T& v)
            {
                _isDirty = _value != v;
                _value = v;
                return _value;
            }
            
            bool operator<(const T& v) const
            {
                return _value < v;
            }

            bool operator>(const T& v) const
            {
                return _value > v;
            }
            
        private:
            T _value;
            bool _isDirty;
        };
    }
}