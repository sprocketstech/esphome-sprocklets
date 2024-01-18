#include "Bus.h"
#include <sprocklets/sprocklets.h>
#include <Wire.h>

namespace esphome
{
    namespace sprocklet
    {
        BusWriter::BusWriter(uint8_t address, uint8_t registerNum) : _address(address), _register(registerNum)
        {
            Wire.beginTransmission(address);
            Wire.write(registerNum);
        }

        void BusWriter::write(uint8_t value)
        {
            Wire.write(value);
            ++_numWritten;
            if (_numWritten == SPROCKLET_BUS_BUFFER_SIZE - 1)
            {
                // buffer exceeded, flush
                _register += _numWritten;
                Wire.endTransmission(true);
                delay(1);
                _numWritten = 0;
                Wire.beginTransmission(_address);
                Wire.write(_register);
            }
        }

        void BusWriter::end() const
        {
            Wire.endTransmission(true);
            delay(1);
        }
        
        void Bus::begin(uint8_t sda, uint8_t scl)
        {
            Wire.begin(sda, scl);
        }

        uint8_t Bus::read8(uint8_t address, uint8_t registerNum)
        {
            uint8_t val = 0;
            // read the state
            Wire.beginTransmission(address);
            Wire.write(registerNum);
            Wire.endTransmission(false);
            Wire.requestFrom(address, (size_t)1, true);
            if (Wire.available() >= 1)
            {
                val = Wire.read();
            }
            Wire.endTransmission(true);
            delay(1);
            return val;
        }

        uint16_t Bus::read16(uint8_t address, uint8_t registerNum)
        {
            uint16_t val = 0;
            // read the state
            Wire.beginTransmission(address);
            Wire.write(registerNum);
            Wire.endTransmission(false);

            Wire.requestFrom(address, (size_t)1, true);
            if (Wire.available() >= 1)
            {
                val = Wire.read() << 8;
            }

            Wire.requestFrom(address, (size_t)1, true);
            if (Wire.available() >= 1)
            {
                val |= Wire.read();
            }

            Wire.endTransmission(true);
            return val;
        }

        uint32_t Bus::read32(uint8_t address, uint8_t registerNum)
        {
            uint32_t val = 0;
            // read the state
            Wire.beginTransmission(address);
            Wire.write(registerNum);
            Wire.endTransmission(false);

            Wire.requestFrom(address, (size_t)1, true);
            if (Wire.available() >= 1)
            {
                val = Wire.read() << 24;
            }

            Wire.requestFrom(address, (size_t)1, true);
            if (Wire.available() >= 1)
            {
                val |= Wire.read() << 16;
            }

            Wire.requestFrom(address, (size_t)1, true);
            if (Wire.available() >= 1)
            {
                val |= Wire.read() << 8;
            }

            Wire.requestFrom(address, (size_t)1, true);
            if (Wire.available() >= 1)
            {
                val |= Wire.read();
            }

            Wire.endTransmission(true);
            return val;
        }


        int Bus::write8(uint8_t address, uint8_t registerNum, uint8_t value)
        {
            Wire.beginTransmission(address);
            Wire.write(registerNum);
            Wire.write(value);
            int result = Wire.endTransmission();
            delay(1);
            return result;
        }

        int Bus::write16(uint8_t address, uint8_t registerNum, uint16_t value)
        {
            return 0;
        }

        int Bus::write32(uint8_t address, uint8_t registerNum, uint32_t value)
        {
            return 0;
        }
    }
}