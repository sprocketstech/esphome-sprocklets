#pragma once
#include <stdint.h>
#include <string>
#include <vector>

#include <sprocklets/sprocklets.h>

#include "Bus.h"

namespace esphome
{
    namespace sprocklet
    {
        class Sprocklet
        {
        public:
            Sprocklet(const char *id, int position) : _address(SPROCKET_UNADDRESSED), _position(position)
            {
                _id = id;
            }

            void address(uint8_t address)
            {
                _address = address;
                onAddressProgrammed(address);
            }

            uint8_t address() const { return _address; }

            uint8_t position() const { return _position; }
            const char *id() const { return _id.c_str(); }

            void fail() { _failed = true; }
            bool failed() { return _failed; }

            virtual uint16_t deviceId() = 0;
        protected:
            virtual void onAddressProgrammed(uint8_t address) { }
        private:
            bool _failed {false};
            std::string _id;
            uint8_t _address;
            uint8_t _position;
        };
        
        // Callback which will provide textual information on the current status
        // of the programAddresses operation
        typedef void (*programAddressesLogCallback)(const char *);

        class SprockletBoard
        {
        public:
            virtual void programAddresses(programAddressesLogCallback cb, std::vector<Sprocklet *> &sprocklets) = 0;
        };

    }
}