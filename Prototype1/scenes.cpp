#include "scenes.h"

#include <iostream>
#include <functional>

#include "Util.h"
#include "CCreature.h"
#include "MyCharacter.h"
#include "Battle.h"
#include "ScriptDB.h"
#include "BattleEventHandler.h"

extern PlayerCharacter g_PC;

namespace Scene
{
	void __stdcall RunScenes()
	{
		Script::RunScript(1);

		{
			CBattle Battle;
			Battle.m_nEnemyID = 1; //goblin 1
			Battle.OnEnemyGotDamage = BattleEventHandler::END_BATTLE;	// �Ѵ�� ������ battle end;
			Battle.RunBattle();//&goblin);
		}

		Script::RunScript(7);
		
		Script::RunScript(2);
		
		{
			CBattle Battle;
			Battle.m_nEnemyID = 2;	// snake
			Battle.OnRoundEnd = BattleEventHandler::Set_Enemy_ToHitBonus(-20);
			Battle.RunBattle();
		}
		
		Script::RunScript(4);

		{
			using namespace BattleEventHandler;
			CBattle Battle;
			Battle.m_nEnemyID = 1; //goblin
			
			Battle.OnBattleStart = Set_Enemy_ToHitBonus(20);	// ù�� ����.

			CBattle::OnBattleEvent op1, op2, op3, ev;

			op1 = COND_ROUND_AT(1, 
				Run_Script(8) + Set_Enemy_ToHitBonus(-20));		// 2���� ���
			op2 = COND_ROUND_AT(2,
				Run_Script(9) + Set_Enemy_ToHitBonus(20));		// 3���� ����
			op3 = COND_ROUND_AT(3,
				Run_Script(10) + Set_Enemy_ToHitBonus(-20));		// 4���� ���� ���

			ev = op1 + op2 + op3;
			Battle.OnRoundEnd = ev;

			Battle.RunBattle();
		}

		Script::RunScript(11);

		// �������� - ����
		if (false == g_PC.CheckResistance(RT_MAGIC))	// ����
		{
			Script::RunScript(5);	// �� ��� #1
		}
		else //����
		{
			Script::RunScript(6);	// �� ��� #2
		}
	}
}