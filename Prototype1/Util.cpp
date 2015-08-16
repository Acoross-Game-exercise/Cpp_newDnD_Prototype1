#include "Util.h"
#include <iostream>
#include <conio.h>
#include <stdarg.h >

namespace Console
{
	void Wait(unsigned long dwMilliSeconds)
	{
		Sleep(dwMilliSeconds);
	}
}

namespace Script
{
	void Pause()
	{
		Pause(L"(...)");
	}

	void Pause(wchar_t const* const _Format, ...)
	{
		va_list _ArgList;
		va_start(_ArgList, _Format);
		vwprintf(_Format, _ArgList);		
		va_end(_ArgList);
		
		std::cout << std::endl;
		_getch();
	}

	bool RunFormattedScript(wchar_t const* const _Format, ...)
	{
		//printf("====================================\n");
		va_list _ArgList;
		va_start(_ArgList, _Format);
		vwprintf(_Format, _ArgList);
		va_end(_ArgList);
		//printf("====================================\n");

		Console::Wait(DEFAULT_WAIT);

		return true;
	}

	// '\0' 으로 시작하는 문자열이 나올 때 까지 문자열을 출력한다.	
	bool __stdcall RunScript(const wchar_t* Script[], unsigned long dwMilliSeconds)
	{
		int iStr = 0;

		bool ret = true;

		try
		{
			while (true)
			{
				const wchar_t* tmpStr = Script[iStr++];

				if (tmpStr[0] == L'\0')
				{
					break;
				}
				else if (tmpStr[0] == L'\1')
				{
					Script::Pause();
				}
				else if (tmpStr[0] == L'\2')
				{
					system("cls");
				}
				else
				{
					wprintf(tmpStr);
					Console::Wait(dwMilliSeconds);
				}
			}
		}
		catch (const std::exception&)
		{
			ret = false;
		}

		return ret;
	}	
}

namespace Dice
{
	int D20(bool bPause)
	{
		// 주사위를 굴린다.
		int d20 = rand() % 20 + 1;
		
		if (bPause)
		{
			Script::RunFormattedScript(L"\nd20: ");
			Script::RunFormattedScript(L"%d!!\n", d20);
		}

		return d20;
	}
}
