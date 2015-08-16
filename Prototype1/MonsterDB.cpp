#include "MonsterDB.h"

#include "CCreature.h"

#include "SkillData.h"

MonsterDB g_monsterDB;

void InitMonsterDB_test()
{
	CCreature* goblin = new CCreature(L"고블린");
	{
		goblin->m_nID = 1;
		goblin->HP = 3;
		goblin->toHitMe = 12;
		goblin->toHitBonus = -20; // 명중 불가
		goblin->m_AttackPower = 2;
	}

	g_monsterDB.m_CreatureMap.insert(CreatureMap::value_type(1, goblin));

	CCreature* snake = new CCreature(L"뱀");
	{
		snake->m_nID = 2;
		snake->HP = 3;
		snake->toHitMe = 11;
		snake->toHitBonus = 20;	// 반드시 명중
		snake->m_AttackPower = 1;
		
		CSkill_PoisonAttack* sp = new CSkill_PoisonAttack();
		
		sp->m_nDamage = 2;
		snake->m_pAttackSkill = sp;
	}

	g_monsterDB.m_CreatureMap.insert(CreatureMap::value_type(2, snake));
}
