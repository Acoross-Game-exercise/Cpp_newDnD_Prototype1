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
			Battle.OnEnemyGotDamage = BattleEventHandler::END_BATTLE;	// 한대라도 맞으면 battle end;
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
			
			Battle.OnBattleStart = Set_Enemy_ToHitBonus(20);	// 첫방 필중.

			CBattle::OnBattleEvent op1, op2, op3, ev;

			op1 = COND_ROUND_AT(1, 
				Run_Script(8) + Set_Enemy_ToHitBonus(-20));		// 2라운드 헛방
			op2 = COND_ROUND_AT(2,
				Run_Script(9) + Set_Enemy_ToHitBonus(20));		// 3라운드 필중
			op3 = COND_ROUND_AT(3,
				Run_Script(10) + Set_Enemy_ToHitBonus(-20));		// 4라운드 이후 헛방

			ev = op1 + op2 + op3;
			Battle.OnRoundEnd = ev;

			Battle.RunBattle();
		}

		Script::RunScript(11);

		// 내성굴림 - 마법
		if (false == g_PC.CheckResistance(RT_MAGIC))	// 실패
		{
			Script::RunScript(5);	// 끝 장면 #1
		}
		else //성공
		{
			Script::RunScript(6);	// 끝 장면 #2
		}
	}
}