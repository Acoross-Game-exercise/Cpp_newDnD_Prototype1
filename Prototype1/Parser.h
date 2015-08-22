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


	// ���� column size �� �����͸� �о���̴� �뵵. 
	// �� column �� �뵵�� ������ �ִ�.
	// �� row �� unique �ϰ� DB �� ����ȴ�. 
	template<typename T>
	class CParser
	{
	public:
		typedef std::function<void(T&, Token&)> ParserFunc;
		typedef std::list<ParserFunc> funcList;
		typedef std::unordered_map<int, T*> TargetMap;
		
		// �� ������ ����, �޸�(,) �� ���еǴ� token �� ��´�.
		// input �� nullptr �� ���� ������, �ϴ� �������� str �� ���� ����... null char �� ������ ��.
		
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
			while (std::getline(wis, wline))	// �� �� �о���δ�.
			{
				++nScriptLine;

				T data;

				wline = Script::RemoveReturnChar(wline);
				const wchar_t* line = wline.c_str();

				bool bParsedAll = true;
				for (auto it = parserFunc.begin(); it != parserFunc.end(); ++it)
				{
					// token �� �д´�.
					Token token = GetToken(line);
					line = token.nextInput;

					if (token.nLength == -1)	 // �� �а� �� �������� ���� ��� == ������ ���̺��� ��ū ���� ������ ��
					{
						wprintf_s(L"\nCParser::Load error in file(%s). too small item in line(%d)\n", filename, nScriptLine);
						bParsedAll = false;
						break;
					}

					// ����� ��ū�� ������ ���
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

		// Script ������ �о���δ�.
		// ����, �� ��ġ�� �ְ�, �� ������ row �� ��� �ش� object �� ���Եȴ�.
		bool Load(const wchar_t* const filename, TargetMap& targetMap, ParserFunc funcParseAndAddData)
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

				T data;

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
						// ���� start �� �����ؾ� �Ѵ�.
						if (nStart == -1)
						{
							printf("@send ocurred without @s x, last @s[%d], last @send[%d], now[%d]\n", nStart, nEnd, nLine);
							return false;
						}

						T* pData = new T();
						pData->SetData(data);

						auto ret = targetMap.insert(TargetMap::value_type(pData->m_nID, pData));
						if (ret.second == false)	// ����
						{
							printf("data insert failed, last @s[%d], last @send[%d], now[%d]\n", nStart, nEnd, nLine);

							delete pData;
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