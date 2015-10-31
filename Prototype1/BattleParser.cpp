#include "BattleParser.h"

#include <iostream>

#include "BattleDB.h"
#include "Battle.h"
#include "BattleEventHandler.h"

bool BattleParser::battledata(BattleParser::MyParserType* parser)
{
	if (parser->expect(TokenType::COMMENT))
		return true;

	bool ret = false;
	do
	{
		MATCH2(id, TokenType::DIGIT);
		MATCH1(TokenType::COMMA);
		MATCH2(enemyId, TokenType::DIGIT);
		MATCH1(TokenType::COMMA);
		
		CBattle* battle = new CBattle;
		battle->m_nID = parser->parseInt(id.c_str());
		battle->m_nEnemyID = parser->parseInt(enemyId.c_str());

		battle->OnBattleStart = onstart(parser);
		MATCH1(TokenType::COMMA);
		battle->OnBattleEnd = onend(parser);
		MATCH1(TokenType::COMMA);
		battle->OnEnemyGotDamage = ongotdamage(parser);
		MATCH1(TokenType::COMMA);
		battle->OnRoundEnd = onroundend(parser);

		g_BattleDB.m_BattleMap[battle->m_nID] = battle;
		
		ret = true;

	} while (false);

	return ret;
}

CBattle::OnBattleEvent BattleParser::eventgrammar(BattleParser::MyParserType* parser)
{
	OnBattleEvent retEvent = CBattle::DefaultHandler;

	do
	{
		retEvent = battleevent(parser);
		MATCH1(TokenType::PLUS);
		OnBattleEvent lhs = eventgrammar(parser);
		retEvent = retEvent + lhs;
	} while (false);

	return retEvent;
}

CBattle::OnBattleEvent BattleParser::battleevent(BattleParser::MyParserType* parser)
{
	//CBattle::OnBattleEvent OP_Concat(const CBattle::OnBattleEvent& handler1, const CBattle::OnBattleEvent& handler2);
	//CBattle::OnBattleEvent operator+(const CBattle::OnBattleEvent& lhs, const CBattle::OnBattleEvent& rhs);
	
	OnBattleEvent retEvent = CBattle::DefaultHandler;

	do
	{
		MATCH2(name, TokenType::STR);
		if (name.compare(L"default") == 0)
		{

		}
		else if (name.compare(L"end_battle") == 0)
		{
			DEBUG_OUTPUT("end_battle");
			MATCH1(TokenType::LPAREN);
			MATCH1(TokenType::RPAREN);

			retEvent = BattleEventHandler::END_BATTLE;
		}
		else if (name.compare(L"set_enemy_tohitbonus") == 0)
		{
			DEBUG_OUTPUT("set_enemy_tohitbonus");
			MATCH1(TokenType::LPAREN);
			MATCH2(pow, TokenType::DIGIT);
			MATCH1(TokenType::RPAREN);

			int nPow = parser->parseInt(pow.c_str());
			retEvent = BattleEventHandler::Set_Enemy_ToHitBonus(nPow);
		}
		else if (name.compare(L"run_script") == 0)
		{
			DEBUG_OUTPUT("run_script");
			MATCH1(TokenType::LPAREN);
			MATCH2(scriptId, TokenType::DIGIT);
			MATCH1(TokenType::RPAREN);

			int id = parser->parseInt(scriptId.c_str());
			retEvent = BattleEventHandler::Run_Script(id);
		}
		else if (name.compare(L"cond_round_at") == 0)
		{
			DEBUG_OUTPUT("cond_round_at");
			MATCH1(TokenType::LPAREN);
			MATCH2(roundAt, TokenType::DIGIT);
			MATCH1(TokenType::COMMA);
			OnBattleEvent handler = eventgrammar(parser);
			MATCH1(TokenType::RPAREN);

			int round = parser->parseInt(roundAt.c_str());
			retEvent = BattleEventHandler::COND_ROUND_AT(round, handler);
		}
	} while (false);

	return retEvent;
}

inline
CBattle::OnBattleEvent BattleParser::eventevent(const wchar_t* name, BattleParser::MyParserType* parser)
{
	OnBattleEvent retEvent = CBattle::DefaultHandler;
	do
	{
		MATCH2(name, TokenType::STR);
		if (name.compare(name) != 0) return CBattle::DefaultHandler;
		MATCH1(TokenType::LPAREN);
		retEvent = eventgrammar(parser);
		MATCH1(TokenType::RPAREN);
	} while (false);

	return retEvent;
}

CBattle::OnBattleEvent BattleParser::onstart(BattleParser::MyParserType* parser)
{
	return eventevent(L"onstart", parser);
}

CBattle::OnBattleEvent BattleParser::onend(BattleParser::MyParserType* parser)
{
	return eventevent(L"onend", parser);
}

CBattle::OnBattleEvent BattleParser::ongotdamage(BattleParser::MyParserType* parser)
{
	return eventevent(L"ongotdamage", parser);
}

CBattle::OnBattleEvent BattleParser::onroundend(BattleParser::MyParserType* parser)
{
	return eventevent(L"onroundend", parser);
}