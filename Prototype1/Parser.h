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

					pData->Print();

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
}

#endif