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

template <class _ScannerT, class _ParserSymbolType>
class CRDParser
{
public:
	using TokenType = typename _ScannerT::TokenType;
	using TokenStruct = typename _ScannerT::Token;
	using DeriveFuncSig = bool(typename _ParserSymbolType, typename CRDParser*);
	using DeriveFuncType = typename std::function<DeriveFuncSig>;

#define new_MATCH(eType) if (!parser->match(eType)) return false;
#define DERIVE(symbol) if (!parser->Derive(symbol)) return false;
#define EXPECT(eType) if (!parser->expect(eType)) return false;

	CRDParser(DeriveFuncSig* deriveF)
		: m_DeriveFunc(deriveF)
	{
	}

	~CRDParser() = default;
	
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

	int parseInt(const wchar_t* str)
	{
		return std::wcstol(str, nullptr, 10);
	}

	bool expect(const TokenType eType)
	{
		return input_token.type == eType;
	}

	// api: general, 
	// contents: specific
	bool Derive(const _ParserSymbolType eSymbol)
	{
		return m_DeriveFunc(eSymbol, this);
	}

	class IParserSymbolBase
	{
	public:
		using TokenType = typename _ScannerT::TokenType;
		using TokenStruct = typename _ScannerT::Token;

		IParserSymbolBase() = default;
		virtual ~IParserSymbolBase() = default;

		bool DoDerive(CRDParser* parser)
		{
			if (Derive(parser))
			{
				OnDerived();
				return true;
			}
			return false;
		}

		virtual bool Derive(CRDParser* parser) = 0;
		virtual void OnDerived() = 0;
	};

private:
	DeriveFuncType m_DeriveFunc;

private:
	NO_COPY(CRDParser);
};