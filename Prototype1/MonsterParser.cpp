#include "MonsterParser.h"

#include <memory>

#include "CCreature.h"
#include "MonsterDB.h"

bool MonsterParser::monsterdata(MonsterParser::MyParserType* parser)
{
	if (parser->expect(TokenType::COMMENT))
		return true;

	bool ret = false;
	do
	{
		MATCH2(id, TokenType::DIGIT);
		MATCH1(TokenType::COMMA);
		MATCH2(nameinternal, TokenType::STR);
		MATCH1(TokenType::COMMA);
		MATCH2(name, TokenType::ANYWORD);
		MATCH1(TokenType::COMMA);
		MATCH2(hp, TokenType::DIGIT);
		MATCH1(TokenType::COMMA);
		MATCH2(toHitMe, TokenType::DIGIT);
		MATCH1(TokenType::COMMA);
		MATCH2(toHitBonus, TokenType::DIGIT);
		MATCH1(TokenType::COMMA);
		MATCH2(attackPower, TokenType::DIGIT);
		MATCH1(TokenType::COMMA);

		std::unique_ptr<CSkill> pSkill = skill(parser);

		CCreature* creature = new CCreature;
		creature->m_nID = parser->parseInt(id.c_str());
		creature->NameInternal = nameinternal;
		creature->Name = name;
		creature->HP = parser->parseInt(hp.c_str());
		creature->toHitMe = parser->parseInt(toHitMe.c_str());
		creature->toHitBonus = parser->parseInt(toHitBonus.c_str());
		creature->m_AttackPower = parser->parseInt(attackPower.c_str());
		creature->m_pAttackSkill = std::move(pSkill);

		g_monsterDB.m_CreatureMap[creature->m_nID] = creature;

		ret = true;

	} while (false);

	return ret;
}

std::unique_ptr<CSkill> MonsterParser::skill(MonsterParser::MyParserType* parser)
{
	// func -> funcname ( args )
	std::unique_ptr<CSkill> pSkill(nullptr);
	do
	{
		MATCH2(skillname, TokenType::STR)

		if (0 == skillname.compare(L"NormalAttack"))
		{
			MATCH1(TokenType::LPAREN)
			MATCH1(TokenType::RPAREN)
			pSkill.reset(new CSkill_NormalAttack());
		}
		else if (0 == skillname.compare(L"PoisonAttack"))
		{
			MATCH1(TokenType::LPAREN)
			MATCH2(pow, TokenType::DIGIT)
			MATCH1(TokenType::RPAREN)
			int nPow = parser->parseInt(pow.c_str());
			pSkill.reset(new CSkill_PoisonAttack(nPow));
		}
	} while (false);

	return pSkill;
}
