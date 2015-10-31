#pragma once

#include <iostream>
//temp
#include <fstream>
#include <locale>
#include <codecvt>
#include <list>
#include <unordered_map>
#include <functional>
//temp

#include "..\default.h"

#include "../Scanner/Scanner.h"

// handwritten parser - for func

// func -> STR ( args )
// args -> arg argtail | e
// argtail -> , args | e
// arg -> func | STR | DIGIT

using namespace AcorossScanner;

template <class _ScannerT>
class CRDParser
{
public:
	using TokenType = typename _ScannerT::TokenType;
	using TokenStruct = typename _ScannerT::Token;

#define MATCH1(eType) if (!parser->match(eType)) break;
#define MATCH2(val, eType)  wstring val = parser->input_token.data;\
							if (!parser->match(eType)) break;

	CRDParser() = default;
	~CRDParser() = default;
	NO_COPY(CRDParser);

	TokenStruct input_token;
	wchar_t* input;

	bool match(const TokenType eType)
	{
		if (input_token.type == eType)
		{
			input_token = _ScannerT::Scan(input);	// consume input_token

			return true;
		}

		return false;
	}

	bool getNextToken()
	{
		input_token = _ScannerT::Scan(input);	// consume input_token

		return true;
	}

	int parseInt(const wchar_t* str)
	{
		return std::wcstol(str, nullptr, 10);
	}

	bool expect(const TokenType eType)
	{
		return input_token.type == eType;
	}
};