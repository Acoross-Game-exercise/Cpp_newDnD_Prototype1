#pragma once

#include "../RecurrentDescentParser/Parser/RDParser.h"

class MonsterParser
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

	enum ParserSymbolEnums
	{
		monsterdata,
		id,
		nameInternal,
		name,
		hp,
		toHitMe,
		toHitBonus,
		attackPower,
		func,
		args,
		argtail,
		arg
	};

	using MyParserType = CRDParser<FuncScanner, ParserSymbolEnums>;

	struct Derivation
	{
		ParserSymbolEnums eType;
		MyParserType::IParserSymbolBase* derive;
	};

	static const Derivation DerivationTable[];

	class CMonsterData : public MyParserType::IParserSymbolBase
	{
	public:
		DEF_CON(CMonsterData);
		bool Derive(MyParserType* parser) final
		{
			DERIVE(id);
			new_MATCH(TokenType::COMMA);
			DERIVE(nameInternal);
			new_MATCH(TokenType::COMMA);
			DERIVE(name);
			new_MATCH(TokenType::COMMA);
			DERIVE(hp);
			new_MATCH(TokenType::COMMA);
			DERIVE(toHitMe);
			new_MATCH(TokenType::COMMA);
			DERIVE(toHitBonus);
			new_MATCH(TokenType::COMMA);
			DERIVE(attackPower);
			new_MATCH(TokenType::COMMA);

			DERIVE(func);

			return true;
		}
		void OnDerived() final
		{
			return;
		}
	};

	class CId : public MyParserType::IParserSymbolBase
	{
	public:
		DEF_CON(CId);
		bool Derive(MyParserType* parser) final
		{
			EXPECT(TokenType::DIGIT);
			m_ID = parser->parseInt(parser->input_token.data.c_str());
			new_MATCH(TokenType::DIGIT);
			return true;
		}
		void OnDerived() final
		{
		}
		int m_ID{ 0 };
	};

	//{nameInternal, new CNameInternal},
	class CNameInternal : public MyParserType::IParserSymbolBase
	{
	public:
		DEF_CON(CNameInternal);
		bool Derive(MyParserType* parser) final
		{
			EXPECT(TokenType::STR);
			m_NameInternal = parser->input_token.data;
			new_MATCH(TokenType::STR);
			return true;
		}
		void OnDerived() final
		{
		}
		wstring m_NameInternal;
	};

	class CName : public MyParserType::IParserSymbolBase
	{
	public:
		DEF_CON(CName);
		bool Derive(MyParserType* parser) final
		{
			EXPECT(TokenType::ANYWORD);
			m_Name = parser->input_token.data;
			new_MATCH(TokenType::ANYWORD);
			return true;
		}
		void OnDerived() final
		{
		}
		wstring m_Name;
	};

	class CHp : public MyParserType::IParserSymbolBase
	{
	public:
		DEF_CON(CHp);
		bool Derive(MyParserType* parser) final
		{
			EXPECT(TokenType::DIGIT);
			m_nHP = parser->parseInt(parser->input_token.data.c_str());
			new_MATCH(TokenType::DIGIT);
			return true;
		}
		void OnDerived() final
		{
		}
		int m_nHP;
	};

	class CToHitMe : public MyParserType::IParserSymbolBase
	{
	public:
		DEF_CON(CToHitMe);
		bool Derive(MyParserType* parser) final
		{
			EXPECT(TokenType::DIGIT);
			m_nToHitMe = parser->parseInt(parser->input_token.data.c_str());
			new_MATCH(TokenType::DIGIT);
			return true;
		}
		void OnDerived() final
		{
		}
		int m_nToHitMe;
	};
	
	class CToHitBonus : public MyParserType::IParserSymbolBase
	{
	public:
		DEF_CON(CToHitBonus);
		bool Derive(MyParserType* parser) final
		{
			EXPECT(TokenType::DIGIT);
			m_nToHitBonus = parser->parseInt(parser->input_token.data.c_str());
			new_MATCH(TokenType::DIGIT);
			return true;
		}
		void OnDerived() final
		{
		}
		int m_nToHitBonus;
	};

	class CAttackPower : public MyParserType::IParserSymbolBase
	{
	public:
		DEF_CON(CAttackPower);
		bool Derive(MyParserType* parser) final
		{
			EXPECT(TokenType::DIGIT);
			m_nAttackPower = parser->parseInt(parser->input_token.data.c_str());
			new_MATCH(TokenType::DIGIT);
			return true;
		}
		void OnDerived() final
		{
		}
		int m_nAttackPower;
	};

	class CFunc : public MyParserType::IParserSymbolBase
	{
	public:
		DEF_CON(CFunc);

	public:
		bool Derive(MyParserType* parser) final
		{
			// func -> funcname ( args )

			EXPECT(TokenType::STR);
			m_FuncName = parser->input_token.data;
			new_MATCH(TokenType::STR);
			new_MATCH(TokenType::LPAREN);
			DERIVE(args);
			new_MATCH(TokenType::RPAREN);

			return true;
		}
		void OnDerived() final
		{
			std::wcout << "func parsed: " << m_FuncName.c_str() << std::endl;
		}

	private:
		wstring m_FuncName;
	};

	class CArgs : public MyParserType::IParserSymbolBase
	{
	public:
		DEF_CON(CArgs);
	public:
		bool Derive(MyParserType* parser) final
		{
			// args -> arg argtail | e
			if (parser->expect(TokenType::RPAREN))
			{
				// epsilon production
				return true;
			}
			else
			{
				DERIVE(arg);
				DERIVE(argtail);
				return true;
			}

			return false;
		}
		void OnDerived() final
		{

		}
	};

	class CArgtail : public MyParserType::IParserSymbolBase
	{
	public:
		DEF_CON(CArgtail);
		bool Derive(MyParserType* parser) final
		{
			// argtail -> , args | e
			if (parser->expect(TokenType::RPAREN))
			{
				// epsilon production
				return true;
			}
			else
			{
				new_MATCH(TokenType::COMMA);
				DERIVE(args);
				return true;
			}
			return false;
		}
		void OnDerived() final
		{

		}
	};

	class CArg : public MyParserType::IParserSymbolBase
	{
	public:
		DEF_CON(CArg);
		bool Derive(MyParserType* parser) final
		{
			// arg -> func | STR | DIGIT
			if (parser->expect(TokenType::DIGIT))
			{
				new_MATCH(TokenType::DIGIT);
				return true;
			}
			else if (parser->expect(TokenType::STR))
			{
				wchar_t* bak_input = parser->input;
				TokenStruct bak_input_TK = parser->input_token;

				if (parser->Derive(func))
				{
					return true;
				}
				else
				{
					parser->input = bak_input;
					parser->input_token = bak_input_TK;
					new_MATCH(TokenType::STR);
					return true;
				}
			}

			return false;
		}
		void OnDerived() final
		{

		}
	};

	static bool DerivationRull(ParserSymbolEnums eSymbol, MyParserType* parser)
	{
		static const Derivation DerivationTable[] = {
			{ monsterdata, new CMonsterData },
			{ id, new CId },
			{ nameInternal, new CNameInternal },
			{ name, new CName },
			{ hp, new CHp },
			{ toHitMe,new CToHitMe },
			{ toHitBonus, new CToHitBonus },
			{ attackPower, new CAttackPower },
			{ func, new CFunc },
			{ args, new CArgs },
			{ argtail, new CArgtail },
			{ arg, new CArg },
		};

		if (eSymbol < 0 || eSymbol >= _countof(DerivationTable))
			return false;

		DerivationTable[eSymbol].derive->DoDerive(parser);
	}

public:
	MonsterParser() = default;

	bool Parse(wchar_t* buf)
	{
		MyParserType parser(DerivationRull);

		parser.input = buf;
		parser.input_token = FuncScanner::Scan(parser.input);

		return parser.Derive(monsterdata);
	}

private:
	NO_COPY(MonsterParser);
};