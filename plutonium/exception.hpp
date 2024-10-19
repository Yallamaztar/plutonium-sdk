#pragma once

namespace plutonium
{
    namespace sdk
    {
        class exception : public std::exception
        {
        public:
            using std::exception::exception;
        };
    }
}
