#pragma once

#include <memory>

#include "../RecurrentDescentParser/Parser/RDParser.h"
#include "Battle.h"

class BattleParser
{
public:
	///////////////////////////////
	// IMPL 
	SCANNERDEF_BEGIN(FuncScannerDefine)
	{
		/*add_token(TK_NULL, nullptr), \
		*/
#define token_list  \
	add_token(COMMENT, L"//(.*)"),	\
	add_token(SEMICOLON, L";"), \
	add_token(PLUS, L"\\+"),	\
	add_token(COMMA, L","),	\
	add_token(LPAREN, L"\\("),	\
	add_token(RPAREN, L"\\)"),	\
	add_token(STR, L"[a-zA-Z]([a-zA-Z0-9_]*)"),	\
	add_token(ID, L"([0-9]+)([a-zA-z]+)"),	\
	add_token(DIGIT, L"(-)?[1-9]([0-9]*)"), \
	add_token(ANYWORD, L"([^ \t\n\\(\\),])+"), \
	add_token(TK_MAX, nullptr)

#include "../RecurrentDescentParser/Scanner/ScannerImplMacro.inc"

#undef token_list
	}
	SCANNERDEF_END;

	typedef Scanner<FuncScannerDefine> FuncScanner;

	using TokenType = FuncScannerDefine::TokenType;
	using MyParserType = CRDParser<FuncScanner>;

	using OnBattleEvent = CBattle::OnBattleEvent;

	bool battledata(BattleParser::MyParserType* parser);

	OnBattleEvent eventevent(const wchar_t* name, BattleParser::MyParserType* parser);

	OnBattleEvent eventgrammar(BattleParser::MyParserType* parser);

	OnBattleEvent battleevent(BattleParser::MyParserType* parser);
	OnBattleEvent onstart(BattleParser::MyParserType* parser);
	OnBattleEvent onend(BattleParser::MyParserType* parser);
	OnBattleEvent ongotdamage(BattleParser::MyParserType* parser);
	OnBattleEvent onroundend(BattleParser::MyParserType* parser);

public:
	BattleParser() = default;
	NO_COPY(BattleParser);

	bool Parse(wchar_t* buf)
	{
		MyParserType parser;

		parser.input = buf;
		parser.input_token = FuncScanner::Scan(parser.input);

		return battledata(&parser);
	}
};