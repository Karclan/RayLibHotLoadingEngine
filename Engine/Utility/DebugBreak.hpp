#pragma once

#ifdef _DEBUG

#if defined(_MSC_VER)
#define HL_DEBUGBREAK() __debugbreak()
#elif
#include <signal.h>
#define HL_DEBUGBREAK() raise(SIGTRAP)
#else
#error "We haven't supported debugbreak yet!"
#endif

#define HL_ENABLE_ASSERTS

#else
#define HL_DEBUGBREAK()
#endif //_DEBUG