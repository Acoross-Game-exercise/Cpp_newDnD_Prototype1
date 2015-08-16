#ifndef _MY_UTIL_
#define _MY_UTIL_

#include <Windows.h>

#include "default.h"

namespace Console
{
	void Wait(unsigned long dwMilliSeconds = DEFAULT_WAIT);
}

namespace Script
{
	void Pause();
	void Pause(wchar_t const* const _Format, ...);
	bool RunFormattedScript(wchar_t const* const _Format, ...);
	bool __stdcall RunScript(const wchar_t* Script[], unsigned long dwMilliSeconds = DEFAULT_WAIT);
}

namespace Dice
{
	int D20(bool bPause = true);
}

#endif