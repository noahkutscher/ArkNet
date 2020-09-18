#pragma once
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ToDo: For now all the values are doubles (input output and matrix values), in the future we may want to do generic types
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef BUILD_LIB
#define ARKNET_EXPORT _declspec(dllexport)
#else
#define ARKNET_EXPORT _declspec(dllimport)
#endif

#define ARKNET_ERROR(x) { printf("[ERROR] %s:%d - %s\n", __FILE__, __LINE__, x); }

#ifdef ARKNET_DEBUG
#define ARKNET_ASSERT(x, y) { if(!(x)) { ARKNET_ERROR(y) __debugbreak(); } } 
#else
#define ARKNET_ASSERT(x, y)
#endif

namespace AN {
	ARKNET_EXPORT void TestFunctionality(const char* test);
}