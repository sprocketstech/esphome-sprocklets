#pragma once
#include <stdint.h>

namespace esphome
{
    namespace sprocklet
    {
        class BusWriter
        {
        public:
            BusWriter(uint8_t address, uint8_t registerNum);
            void write(uint8_t value);
            void end() const;
        private:
            uint8_t _address{0};            // address we are writing to
            uint8_t _register{0};           // register number at the start of the buffer
            uint32_t _numWritten{0};        // keeps track of the number written past _register
        };

        class Bus
        {
        public:
            static void begin(uint8_t sda, uint8_t scl);

            static uint8_t read8(uint8_t address, uint8_t registerNum);
            static uint16_t read16(uint8_t address, uint8_t registerNum);
            static uint32_t read32(uint8_t address, uint8_t registerNum);

            static int write8(uint8_t address, uint8_t registerNum, uint8_t value);
            static int write16(uint8_t address, uint8_t registerNum, uint16_t value);
            static int write32(uint8_t address, uint8_t registerNum, uint32_t value);
        };

    }
}