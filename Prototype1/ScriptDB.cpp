#include "ScriptDB.h"

#include <iostream>

#include <fstream>
#include <locale>
#include <codecvt>

#include <functional>

#include "Util.h"

namespace Script
{
	ScriptDB g_ScriptDB;

	bool __stdcall RunScript(int nNum)
	{
		Script::CScene* pScene = Script::g_ScriptDB.m_sceneMap[nNum];
		if (pScene)
		{
			return Script::RunScript(pScene->m_Script);
		}

		return false;
	}

	bool __stdcall RunScript(ScriptData& sd, unsigned long dwMilliSeconds)
	{
		bool ret = true;
		for (auto it = sd.begin(); it != sd.end(); ++it)
		{
			std::wstring& tmpStr = (*it);

			if (tmpStr.size() >= 2 && tmpStr[0] == L'@')
			{
				if (tmpStr[1] == L'0')
				{
					break;
				}
				else if (tmpStr[1] == L'1')
				{
					Script::Pause();
				}
				else if (tmpStr[1] == L'2')
				{
					system("cls");
				}
			}
			else
			{
				wprintf(tmpStr.c_str());
				Console::Wait(dwMilliSeconds);
			}
		}

		return ret;
	}

	bool ScriptDB::Load(wchar_t* filename)
	{
		std::wifstream wis(filename, std::ifstream::binary);
		if (wis.is_open())
		{
			// apply BOM-sensitive UTF-16 facet
			wis.imbue(std::locale(wis.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));

			int nLine = 0;	// 읽고 있는 줄
			int nStart = -1;	// 마지막 읽은 @s x 의 위치
			int nEnd = -1;	// 마지막 읽은 @send 의 위치

			CScene scene;
			std::wstring wline;
			while (std::getline(wis, wline))	// 한 줄 읽어들인다.
			{
				// @s 가 나타났다면 조건을 비교하여 처리
				if (wcsncmp(wline.c_str(), L"@s ", 3) == 0)		// 시작 위치
				{
					// @s 를 찾고 있었으며 이전 end 보다 line 수가 커야한다.
					if (nStart != -1 || nLine <= nEnd)
					{
						printf("@s ocurred before @send, last @s[%d], last @send[%d], now[%d]\n", nStart, nEnd, nLine);
						return false;
					}

					int idx = wline.find(L"@s ");
					if (idx == std::wstring::npos)
					{
						printf("@s x: couldn't parse index, last @s[%d], last @send[%d], now[%d]\n", nStart, nEnd, nLine);
						return false;
					}

					nStart = nLine;
					scene.m_nID = std::wcstol(&wline[idx + 3], nullptr, 10);
					//scene.m_Script.push_back(wline);
					
				}
				else if (wcsncmp(wline.c_str(), L"@send", 5) == 0)
				{
					// 이전 start 가 존재해야 한다.
					if (nStart == -1)
					{
						printf("@send ocurred without @s x, last @s[%d], last @send[%d], now[%d]\n", nStart, nEnd, nLine);
						return false;
					}
					
					CScene* pScene = new CScene();
					pScene->m_nID = scene.m_nID;
					pScene->m_Script.swap(scene.m_Script);
					scene.m_nID = 0;

					auto ret = m_sceneMap.insert(SceneMap::value_type(pScene->m_nID, pScene));
					if (ret.second == false)	// 실패
					{
						printf("pScene insert failed, last @s[%d], last @send[%d], now[%d]\n", nStart, nEnd, nLine);
						
						delete pScene;
						return false;
					}
					
					// scene 읽기 성공, 다음 scene 을 위해 정리
					nEnd = nLine;
					nStart = -1;
				}
				else
				{
					// @s 찾고 @send 찾기 전 까지 scene 에 줄 삽입
					if (nStart != -1)
					{
						// remove '\r'
						if (!wline.empty() && wline[wline.size() - 1] == '\r')
							wline.erase(wline.size() - 1);

						// replace "//n" -> '/n'
						int idx = wline.find(L"\\n");
						while (idx != std::wstring::npos)
						{
							wline.replace(idx, 2, L"\n");
							idx = wline.find(L"\\n");
						}

						scene.m_Script.push_back(wline);
					}
				}

				++nLine;
			}

			if (nStart != -1)
			{
				printf("there was @s x without @send, last @s[%d], last @send[%d], now[%d]\n", nStart, nEnd, nLine);
				return false;
			}
		}

		return true;
	}
}