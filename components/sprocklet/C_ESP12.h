#pragma once

#include <stdint.h>
#include "Sprocklet.h"
#include <vector>


namespace esphome
{
    namespace sprocklet
    {
        class SprockletESP12Board : public SprockletBoard
        {
        public:
            SprockletESP12Board();
            SprockletESP12Board(const uint8_t sda,
                                const uint8_t scl,
                                const uint8_t pgm);

            void programAddresses(programAddressesLogCallback cb, std::vector<Sprocklet *> &sprocklets);

        private:
            uint8_t _scl;
            uint8_t _sda;
            uint8_t _pgm;

            uint8_t programUnit(programAddressesLogCallback cb, uint8_t unit);
            void waitForReady(programAddressesLogCallback cb, uint8_t addr);
        };
    }
}