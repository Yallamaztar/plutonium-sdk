#pragma once

#ifndef PLUTONIUM_SDK_H
#define PLUTONIUM_SDK_H

#pragma warning(push)
#pragma warning(disable: 4229)
#define PLUTONIUM_CALLBACK __cdecl

#ifdef PLUTONIUM_LIB
#define PLUTONIUM_API extern "C" __declspec(dllimport)
#else
#define PLUTONIUM_API extern "C" __declspec(dllexport)
#endif

#include <memory>
#include <string>
#include <cstdint>
#include <exception>
#include <functional>

#ifndef PLUTONIUM_SDK_VERSION
#define PLUTONIUM_SDK_VERSION 1u
#endif

#include "plutonium/exception.hpp"
#include "plutonium/unique_ptr.hpp"

// Ensure the interface header is included correctly
#if PLUTONIUM_SDK_VERSION == 1u
#include "plutonium/v1/interface.hpp"  // Ensure this file defines the iinterface class

namespace plutonium
{
    namespace sdk
    {
        namespace v1
        {
            using iinterface = plutonium::sdk::v1::iinterface;  // Adjusted to use the correct namespace
        }

    }

}
#else
#error Unknown SDK version specified!
#endif

namespace plutonium
{
    namespace sdk
    {
        using iinterface = plutonium::sdk::v1::iinterface;

        enum class game
        {
            IW5,  // Use uppercase for better readability
            T4,
            T5,
            T6,
        };

        class plugin
        {
        public:
            virtual ~plugin() = default;

            // Plugin information
            virtual std::uint32_t plugin_version() const  // Added const correctness
            {
                return PLUTONIUM_SDK_VERSION;
            }

            virtual const char* plugin_name() = 0;

            virtual bool is_game_supported(game) const  // Added const correctness
            {
                return true;  // Consider implementing game-specific checks
            }

            // Plugin initialization & shutdown
            virtual void on_startup(iinterface* interface_ptr, game game) = 0;
            virtual void on_shutdown() = 0;
        };
    }
}

#pragma warning(pop)

#endif // PLUTONIUM_SDK_H
