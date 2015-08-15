#include "Util.h"
#include <iostream>
#include <conio.h>
#include <stdarg.h >

#include <fstream>
#include <locale>
#include <codecvt>

#include <vector>
#include <list>

namespace Console
{
	void Wait(unsigned long dwMilliSeconds)
	{
		Sleep(dwMilliSeconds);
	}
}

namespace Script
{
	bool ScriptDB::Load(wchar_t* filename)
	{
		std::wifstream wis(filename, std::ifstream::binary);
		if (wis.is_open())
		{
			// apply BOM-sensitive UTF-16 facet
			wis.imbue(std::locale(wis.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));

			int nLine = 0;
			int nStart = -1;
			int nEnd = -1;

			int sceneID = 0;
			ScriptData myScript;
			std::list<int> sceneStarts;

			std::wstring wline;;
			while (std::getline(wis, wline))
			{
				myScript.push_back(wline);
				if (wcsncmp(wline.c_str(), L"@s ", 3) == 0)
				{
					// 이전 end 보다 line 수가 커야한다.
					if (nLine > nEnd)
					{
						nStart = nLine;

						// id 를 얻는다.
						int idx = wline.find(L'@s ') + 3;
						int id = std::wcstol(&wline[idx], nullptr, 10);

						sceneID = id;
					}
					else
					{
						// error
						std::cout << "couldn't found @send" << std::endl;
						break;
					}
					//sceneStarts.push_back(nLine);
				}
				else if (wcsncmp(wline.c_str(), L"@send", 5) == 0)
				{
					// 이전 start 가 존재해야 한다.
					if (nStart == -1)
					{
						std::cout << "@send occured without @s x" << std::endl;
						return false;
					}

					std::cout << "found @s ~ @send" << std::endl;
					nEnd = nLine;

					// Scene 을 만든다.
					{
						Scene* pScene = new Scene;
						pScene->m_Script = myScript;

						ScriptData empty;
						myScript.swap(empty);

						pScene->m_nID = sceneID;
						
						auto ret = m_sceneMap.insert(SceneMap::value_type(sceneID, pScene));
						if (ret.second == false)
						{
							std::cout << "sceneID is duplicated" << std::endl;
							return false;
						}
					}
					
					nStart = -1;	// 초기화
				}
								
				++nLine;
			}

			if (nStart != -1)
			{
				std::cout << "there was @s x without @send" << std::endl;
			}
		}

		return true;
	}

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
	int D20()
	{
		// 주사위를 굴린다.
		int d20 = rand() % 20 + 1;

		Script::RunFormattedScript(L"\nd20: ");

		Script::RunFormattedScript(L"%d!!\n", d20);

		return d20;
	}
}
