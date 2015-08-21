#include "MonsterDB.h"

#include <string>
#include "CCreature.h"
#include "SkillData.h"
#include <iostream>
#include "Util.h"
#include <functional>

#include "Parser.h"

MonsterDB g_monsterDB;

bool MonsterDB::Load(const wchar_t* const filename)
{
	using namespace Parser;	
	
	CParser<CCreature>::funcList fList = 
	{
		[](CCreature& creature, Token& token)
		{
			creature.m_nID = ParseInt(token);
		},
			[](CCreature& creature, Token& token)
		{
			creature.NameInternal = ParseStr(token);
		},
			[](CCreature& creature, Token& token)
		{
			creature.Name = ParseStr(token);
		},
			[](CCreature& creature, Token& token)
		{
			creature.HP = ParseInt(token);
		},
			[](CCreature& creature, Token& token)
		{
			creature.toHitMe = ParseInt(token);
		},
			[](CCreature& creature, Token& token)
		{
			creature.toHitBonus = ParseInt(token);
		},
			[](CCreature& creature, Token& token)
		{
			creature.m_AttackPower = ParseInt(token);
		}
	};

	CParser<CCreature> parser;

	return parser.Load(filename, fList, m_CreatureMap);
}

void InitMonsterDB_test()
{
	//CCreature* goblin = new CCreature(L"고블린");
	//{
	//	goblin->m_nID = 1;
	//	goblin->HP = 3;
	//	goblin->toHitMe = 12;
	//	goblin->toHitBonus = -20; // 명중 불가
	//	goblin->m_AttackPower = 2;
	//}

	//g_monsterDB.m_CreatureMap.insert(CreatureMap::value_type(1, goblin));

	//CCreature* snake = new CCreature(L"뱀");
	//{
	//	snake->m_nID = 2;
	//	snake->HP = 3;
	//	snake->toHitMe = 11;
	//	snake->toHitBonus = 20;	// 반드시 명중
	//	snake->m_AttackPower = 1;
	//	
	//	snake->m_pAttackSkill = new CSkill_PoisonAttack(2);
	//}

	//g_monsterDB.m_CreatureMap.insert(CreatureMap::value_type(2, snake));
}
