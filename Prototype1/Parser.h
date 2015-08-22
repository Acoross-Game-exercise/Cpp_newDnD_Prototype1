#ifndef _MY_PARSER_
#define _MY_PARSER_

#include <fstream>
#include <locale>
#include <codecvt>

#include <functional>
#include <string>
#include <list>
#include <unordered_map>

#include "Util.h"

namespace Parser
{
	class Token
	{
	public:
		Token(const wchar_t* token, int nLen, const wchar_t* next) : wcsToken(token), nLength(nLen), nextInput(next)
		{}

		const wchar_t* wcsToken;
		const wchar_t* nextInput;
		int nLength;
	};

	Token GetToken(const wchar_t* input);

	std::wstring ParseStr(Token& token);

	int ParseInt(Token& token);


	// 고정 column size 의 데이터를 읽어들이는 용도. 
	// 각 column 의 용도는 정해져 있다.
	// 각 row 는 unique 하게 DB 에 저장된다. 
	template<typename T>
	class CParser
	{
	public:
		typedef std::function<void(T&, Token&)> ParserFunc;
		typedef std::list<ParserFunc> funcList;
		typedef std::unordered_map<int, T*> TargetMap;
		
		// 앞 공백을 제외, 콤마(,) 로 구분되는 token 을 얻는다.
		// input 은 nullptr 일 수도 있지만, 일단 정상적인 str 인 것을 가정... null char 가 나오면 끝.
		
		bool Load(const wchar_t* const filename, funcList fList, TargetMap& targetMap)
		{
			funcList parserFunc = fList;

			std::wifstream wis(filename, std::ifstream::binary);
			if (false == wis.is_open())
			{
				return false;
			}
			// apply BOM-sensitive UTF-16 facet
			wis.imbue(std::locale(wis.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));

			int nScriptLine = 0;
			std::wstring wline;
			while (std::getline(wis, wline))	// 한 줄 읽어들인다.
			{
				++nScriptLine;

				T data;

				wline = Script::RemoveReturnChar(wline);
				const wchar_t* line = wline.c_str();

				bool bParsedAll = true;
				for (auto it = parserFunc.begin(); it != parserFunc.end(); ++it)
				{
					// token 을 읽는다.
					Token token = GetToken(line);
					line = token.nextInput;

					if (token.nLength == -1)	 // 다 읽고 더 읽으려고 했을 경우 == 정해진 길이보다 토큰 수가 적었을 때
					{
						wprintf_s(L"\nCParser::Load error in file(%s). too small item in line(%d)\n", filename, nScriptLine);
						bParsedAll = false;
						break;
					}

					// 제대로 토큰을 얻어냈을 경우
					ParserFunc f = *it;
					f(data, token);
				}

				if (bParsedAll)
				{
					T* pData = new T(data);

					auto ret = targetMap.insert(TargetMap::value_type(pData->m_nID, pData));
					if (ret.second == false)
					{
						printf("\nparser insert failed, file(%s), line(%d)\n", filename, nScriptLine);
						delete pData;
						return false;
					}
				}
			}

			return true;
		}
	};

	template<typename T>
	class CMultilineParser
	{
	public:
		//typedef std::function<void(T&, Token&)> ParserFunc;
		//typedef std::list<ParserFunc> funcList;
		typedef std::function<void(T&, std::wstring)> ParserFunc;
		typedef std::unordered_map<int, T*> TargetMap;

		// Script 파일을 읽어들인다.
		// 시작, 끝 위치가 있고, 그 사이의 row 는 모두 해당 object 에 포함된다.
		bool Load(const wchar_t* const filename, TargetMap& targetMap, ParserFunc funcParseAndAddData)
		{
			std::wifstream wis(filename, std::ifstream::binary);
			if (wis.is_open())
			{
				// apply BOM-sensitive UTF-16 facet
				wis.imbue(std::locale(wis.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));

				int nLine = 0;	// 읽고 있는 줄
				int nStart = -1;	// 마지막 읽은 @s x 의 위치
				int nEnd = -1;	// 마지막 읽은 @send 의 위치

				std::wstring TStart = L"@s ";
				std::wstring TEnd = L"@send";

				T data;

				std::wstring wline;
				while (std::getline(wis, wline))	// 한 줄 읽어들인다.
				{
					// @s 가 나타났다면 조건을 비교하여 처리
					if (wcsncmp(wline.c_str(), TStart.c_str(), TStart.length()) == 0)		// 시작 위치
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
						data.m_nID = std::wcstol(&wline[idx + TStart.length()], nullptr, 10);
					}
					else if (wcsncmp(wline.c_str(), L"@send", 5) == 0)
					{
						// 이전 start 가 존재해야 한다.
						if (nStart == -1)
						{
							printf("@send ocurred without @s x, last @s[%d], last @send[%d], now[%d]\n", nStart, nEnd, nLine);
							return false;
						}

						T* pData = new T();
						pData->SetData(data);

						auto ret = targetMap.insert(TargetMap::value_type(pData->m_nID, pData));
						if (ret.second == false)	// 실패
						{
							printf("data insert failed, last @s[%d], last @send[%d], now[%d]\n", nStart, nEnd, nLine);

							delete pData;
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
							funcParseAndAddData(data, wline);
							
							//// remove '\r'
							//wline = Script::RemoveReturnChar(wline);

							//// replace "//n" -> '/n'
							//int idx = wline.find(L"\\n");
							//while (idx != std::wstring::npos)
							//{
							//	wline.replace(idx, 2, L"\n");
							//	idx = wline.find(L"\\n");
							//}

							//data.m_Script.push_back(wline);
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
	};
}

#endif