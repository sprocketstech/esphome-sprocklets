#if defined(ESP8266)

#include "C_ESP12.h"
#include <Arduino.h>
#include "Bus.h"

namespace esphome
{
    namespace sprocklet
    {
        static const int SPROCKLET_PROGRAM_ADDRESS = 0x00;
        static const int SPROCKLET_PROGRAM_COMMAND = 0x7f;
        static const int SPROCKLET_ADDRESS_OFFSET = 0x10;

        static const uint8_t SPROCKLET_DEFAULT_SDA = 5;
        static const uint8_t SPROCKLET_DEFAULT_SCL = 4;
        static const uint8_t SPROCKLET_DEFAULT_I2C_PGM = 2;
        
        SprockletESP12Board::SprockletESP12Board()
            : _scl(SPROCKLET_DEFAULT_SCL),
            _sda(SPROCKLET_DEFAULT_SDA),
            _pgm(SPROCKLET_DEFAULT_I2C_PGM)
        {
        }

        SprockletESP12Board::SprockletESP12Board(const uint8_t sda,
                                                const uint8_t scl,
                                                const uint8_t pgm)
            : _scl(scl),
            _sda(sda),
            _pgm(pgm)
        {
        }

        #define MAX_LOG_BUFFER_SIZE 72
        static char logBuffer[MAX_LOG_BUFFER_SIZE];

        void SprockletESP12Board::programAddresses(programAddressesLogCallback cb, std::vector<Sprocklet *> &sprocklets)
        {
            cb("Starting address programming");
            // reset the chain
            pinMode(_pgm, OUTPUT);
            // write I2C_PGM low
            digitalWrite(_pgm, LOW);
            delay(100);
            // bring I2C_PGM high to boot the first sprocklet
            digitalWrite(_pgm, HIGH);

            Bus::begin(_sda, _scl);
            delay(500);

            // program the addresses of the sprocklets
            for (uint8_t i = 0; i < sprocklets.size(); ++i)
            {
                uint8_t addr = programUnit(cb, i);
                if (addr > 0)
                {
                    sprocklets[i]->address(addr);
                    waitForReady(cb, addr);

                    uint16_t deviceId = Bus::read16(addr, 0);
                    if (sprocklets[i]->deviceId() != deviceId)
                    {
                        ::snprintf(logBuffer, MAX_LOG_BUFFER_SIZE, "Sprocklet at address %d is expected to be 0x%04x, but is 0x%04x",
                                addr,
                                sprocklets[i]->deviceId(),
                                deviceId);
                        cb(logBuffer);
                    }
                    else
                    {
                        ::snprintf(logBuffer, MAX_LOG_BUFFER_SIZE, "Sprocklet %s is at address %d",
                                sprocklets[i]->id(),
                                addr);
                        cb(logBuffer);
                    }
                    delay(100);
                }
                yield();
            }
        }

        void SprockletESP12Board::waitForReady(programAddressesLogCallback cb, uint8_t addr)
        {
            bool done = false;
            while (!done)
            {
                // query the address which is in register SPROCKLET_PROGRAM_COMMAND
                uint8_t reportedAddr = Bus::read8(addr, SPROCKLET_PROGRAM_COMMAND);

                ::snprintf(logBuffer, MAX_LOG_BUFFER_SIZE, "Sprocklet at address %d reports address %d",
                        addr,
                        reportedAddr);
                cb(logBuffer);

                if (reportedAddr != addr)
                {
                    delay(5);
                }
                else
                {
                    done = true;
                }
            }
        }

        uint8_t SprockletESP12Board::programUnit(programAddressesLogCallback cb, uint8_t unit)
        {
            bool done = false;
            int loopCount = 0;
            int error;
            byte newAddr = unit + SPROCKLET_ADDRESS_OFFSET;
            while (!done)
            {
                // program unit n
                error = Bus::write8(SPROCKLET_PROGRAM_ADDRESS, SPROCKLET_PROGRAM_COMMAND, newAddr);
                if (error == 2)
                {
                    // 2 means address not accepted;
                    // could be one of two conditions:
                    // Next unit is booting
                    // Next unit does not exist.
                    if (loopCount > 10)
                    {
                        // next unit not found
                        ::snprintf(logBuffer, MAX_LOG_BUFFER_SIZE, "No sprocklet found attached at index %d", unit);
                        cb(logBuffer);
                        done = true;
                        newAddr = 0;
                        break;
                    }
                    else
                    {
                        // could be booting, sleep and retry
                        ++loopCount;
                        delay(50);
                    }
                }
                else if (error == 0)
                {
                    // programmed successfully
                    // do the next one
                    ::snprintf(logBuffer, MAX_LOG_BUFFER_SIZE, "Sprocklet %d addressed as %d", unit, newAddr);
                    cb(logBuffer);
                    done = true;
                }
            }
            return newAddr;
        }
    }
}
#endif
