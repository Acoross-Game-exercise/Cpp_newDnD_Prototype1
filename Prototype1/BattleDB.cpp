#include "BattleDB.h"

#include "Battle.h"
#include "BattleEventHandler.h"

BattleDB g_BattleDB;

BattleDB::BattleDB()
{
}

BattleDB::~BattleDB()
{
}

void InitBattleDB_test()
{
	{
		CBattle* Battle = new CBattle();
		Battle->m_nID = 1;
		Battle->m_nEnemyID = 1; //goblin 1
		Battle->OnEnemyGotDamage = BattleEventHandler::END_BATTLE;	// �Ѵ�� ������ battle end;
		//RunSceneFunc(Func_RunBattle(Battle));
		g_BattleDB.m_BattleMap.insert(BattleMap::value_type(Battle->m_nID, Battle));
	}

	{
		CBattle* Battle = new CBattle();
		Battle->m_nID = 2;
		Battle->m_nEnemyID = 2;	// snake
		Battle->OnRoundEnd = BattleEventHandler::Set_Enemy_ToHitBonus(-20);
		//RunSceneFunc(Func_RunBattle(Battle));
		g_BattleDB.m_BattleMap.insert(BattleMap::value_type(Battle->m_nID, Battle));
	}

	{
		using namespace BattleEventHandler;
		CBattle* Battle = new CBattle();
		Battle->m_nID = 3;
		Battle->m_nEnemyID = 1; //goblin

		Battle->OnBattleStart = Set_Enemy_ToHitBonus(20);	// ù�� ����.

		CBattle::OnBattleEvent op1, op2, op3, ev;

		op1 = COND_ROUND_AT(1,
			Run_Script(8) + Set_Enemy_ToHitBonus(-20));		// 2���� ���
		op2 = COND_ROUND_AT(2,
			Run_Script(9) + Set_Enemy_ToHitBonus(20));		// 3���� ����
		op3 = COND_ROUND_AT(3,
			Run_Script(10) + Set_Enemy_ToHitBonus(-20));		// 4���� ���� ���

		ev = op1 + op2 + op3;
		Battle->OnRoundEnd = ev;
		//RunSceneFunc(Func_RunBattle(Battle));
		g_BattleDB.m_BattleMap.insert(BattleMap::value_type(Battle->m_nID, Battle));
	}
}