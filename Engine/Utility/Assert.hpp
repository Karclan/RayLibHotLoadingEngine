#pragma once

#include "../Logging/Logger.hpp"
#include "DebugBreak.hpp"

//Taken from TheCherno's Hazel assert.h and adapted further
#include <filesystem>

#define HL_EXPAND_MACRO(x) x
#define HL_STRINGIFY_MACRO(x) #x

#ifdef HL_ENABLE_ASSERTS

// Alternatively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define HL_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { HL##type##ERROR(msg, __VA_ARGS__); HL_DEBUGBREAK(); } }
#define HL_INTERNAL_ASSERT_WITH_MSG(type, check, ...) HL_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define HL_INTERNAL_ASSERT_NO_MSG(type, check) HL_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", HL_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define HL_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define HL_INTERNAL_ASSERT_GET_MACRO(...) HL_EXPAND_MACRO( HL_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, HL_INTERNAL_ASSERT_WITH_MSG, HL_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define HL_ASSERT(...) HL_EXPAND_MACRO( HL_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define HL_CORE_ASSERT(...) HL_EXPAND_MACRO( HL_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define HL_ASSERT(...)
#define HL_CORE_ASSERT(...)
#endif

