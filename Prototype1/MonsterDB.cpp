#include "MonsterDB.h"

#include <string>
#include <iostream>
#include <functional>

#include "CCreature.h"
#include "SkillData.h"
#include "Util.h"

#include "Parser.h"

#include "MonsterParser.h"

MonsterDB g_monsterDB;

bool MonsterDB::Load2(const wchar_t* const filename)
{
	setlocale(LC_ALL, "");

	std::wifstream wis(L"monster.csv", std::ifstream::binary);
	if (false == wis.is_open())
		return false;

	// apply BOM-sensitive UTF-16 facet
	wis.imbue(std::locale(wis.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));

	int nScriptLine = 0;
	std::wstring wline;

	wchar_t buf[2000];

	MonsterParser parser;

	bool ret = true;
	while (std::getline(wis, wline))	// 한 줄 읽어들인다.
	{
		memset(buf, 0, sizeof(buf));
		wline._Copy_s(buf, 2000, wline.size(), 0);
		//wchar_t* input = buf;

		ret = parser.Parse(buf);
		
		std::cout << "ret=" << ret << std::endl;
	}

	return true;
}

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
