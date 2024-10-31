#pragma once

#include <functional>

// ResultsLib.h - Contains declaration of Results functions

#ifdef RESULTSLIB_EXPORTS
#define RESULTSLIB_API __declspec(dllexport)
#else
#define RESULTSLIB_API __declspec(dllimport)
#endif

namespace results {

	extern "C" RESULTSLIB_API void WriteResults(const char* _codeFile, const char* _resultsFile);

	extern "C" RESULTSLIB_API void ReadResults(const char* _resultsFile);

	extern "C" RESULTSLIB_API void TestToggle(char _choice, int& _test);

	extern "C" RESULTSLIB_API void RunLabTest(std::function<void()> _battery, const char* _resultsFile, int _toggle);
}