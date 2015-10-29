#include "ScriptDB.h"

#include <iostream>

#include <fstream>
#include <locale>
#include <codecvt>
#include <string>

#include <functional>

#include "Util.h"
#include "Parser.h"

namespace Script
{
	ScriptDB g_ScriptDB;

	bool CScriptParser::scriptdata()
	{
		m_scene = CScene();

		if (!sbegin()) return true;
		if (line()) return false;
		if (send()) return false;

		CScene* pScene = new CScene;
		pScene->SetData(m_scene);
		g_ScriptDB.m_sceneMap[pScene->m_nID] = pScene;

		return true;
	}

	bool CScriptParser::sbegin()
	{
		bool bRet = false;
		MyParserType* parser = &m_RDParser;
		do
		{
			MATCH1(TokenType::SB);
			MATCH2(nScriptID, TokenType::DIGIT);

			m_scene.m_nID = parser->parseInt(nScriptID.c_str());

		} while (false);
		return bRet;
	}

	bool CScriptParser::line()
	{
		bool bRet = false;
		MyParserType* parser = &m_RDParser;
		do
		{
			MATCH2(str, TokenType::ANYWORD);
			m_scene.m_Script.push_back(str);
		} while (false);
		return bRet;
	}

	bool CScriptParser::send()
	{
		bool bRet = false;
		MyParserType* parser = &m_RDParser;
		do
		{
			MATCH1(TokenType::SE);
		} while (false);
		return bRet;
	}

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

	bool ScriptDB::Load2(const wchar_t* const filename)
	{
		using namespace Parser;

		CMultilineParser<CScene> parser;
		
		CMultilineParser<CScene>::ParserFunc f = [](CScene& data, std::wstring wline)
		{
			// remove '\r'
			wline = Script::RemoveReturnChar(wline);

			// replace "//n" -> '/n'
			size_t idx = wline.find(L"\\n");
			while (idx != std::wstring::npos)
			{
				wline.replace(idx, 2, L"\n");
				idx = wline.find(L"\\n");
			}

			data.m_Script.push_back(wline);
		};

		return parser.Load(filename, m_sceneMap, f);
	}

	bool ScriptDB::Load3(const wchar_t * const filename)
	{
		setlocale(LC_ALL, "");

		std::wifstream wis(filename, std::ifstream::binary);
		if (false == wis.is_open())
			return false;

		// apply BOM-sensitive UTF-16 facet
		wis.imbue(std::locale(wis.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));

		int nScriptLine = 0;
		std::wstring wline;

		wchar_t buf[2000];

		CScriptParser parser;

		bool ret = true;
		while (std::getline(wis, wline))	// �� �� �о���δ�.
		{
			memset(buf, 0, sizeof(buf));
			wline._Copy_s(buf, 2000, wline.size(), 0);

			ret = parser.Parse(buf);
		}

		return true;
	}

	// Script ������ �о���δ�.
	// ����, �� ��ġ�� �ְ�, �� ������ row �� ��� �ش� object �� ���Եȴ�.
	bool ScriptDB::Load(const wchar_t* const filename)
	{
		std::wifstream wis(filename, std::ifstream::binary);
		if (wis.is_open())
		{
			// apply BOM-sensitive UTF-16 facet
			wis.imbue(std::locale(wis.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));

			int nLine = 0;	// �а� �ִ� ��
			int nStart = -1;	// ������ ���� @s x �� ��ġ
			int nEnd = -1;	// ������ ���� @send �� ��ġ
			
			std::wstring TStart = L"@s ";
			std::wstring TEnd = L"@send";

			CScene scene;
			std::wstring wline;
			while (std::getline(wis, wline))	// �� �� �о���δ�.
			{
				// @s �� ��Ÿ���ٸ� ������ ���Ͽ� ó��
				if (wcsncmp(wline.c_str(), TStart.c_str(), TStart.length()) == 0)		// ���� ��ġ
				{
					// @s �� ã�� �־����� ���� end ���� line ���� Ŀ���Ѵ�.
					if (nStart != -1 || nLine <= nEnd)
					{
						printf("@s ocurred before @send, last @s[%d], last @send[%d], now[%d]\n", nStart, nEnd, nLine);
						return false;
					}

					size_t idx = wline.find(L"@s ");
					if (idx == std::wstring::npos)
					{
						printf("@s x: couldn't parse index, last @s[%d], last @send[%d], now[%d]\n", nStart, nEnd, nLine);
						return false;
					}

					nStart = nLine;
					scene.m_nID = std::wcstol(&wline[idx + TStart.length()], nullptr, 10);
				}
				else if (wcsncmp(wline.c_str(), L"@send", 5) == 0)
				{
					// ���� start �� �����ؾ� �Ѵ�.
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
					if (ret.second == false)	// ����
					{
						printf("pScene insert failed, last @s[%d], last @send[%d], now[%d]\n", nStart, nEnd, nLine);
						
						delete pScene;
						return false;
					}
					
					// scene �б� ����, ���� scene �� ���� ����
					nEnd = nLine;
					nStart = -1;
				}
				else
				{
					// @s ã�� @send ã�� �� ���� scene �� �� ����
					if (nStart != -1)
					{
						// remove '\r'
						wline = Script::RemoveReturnChar(wline);

						// replace "//n" -> '/n'
						size_t idx = wline.find(L"\\n");
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