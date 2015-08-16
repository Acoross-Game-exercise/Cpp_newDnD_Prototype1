#include "scenes.h"

#include <iostream>
#include <functional>

#include "Util.h"
#include "CCreature.h"
#include "MyCharacter.h"
#include "Battle.h"
#include "ScriptDB.h"
#include "BattleEventHandler.h"

#include <functional>

extern PlayerCharacter g_PC;

namespace Scene
{
	typedef std::function<bool(void)> SceneFunc;
	
	bool RunSceneFunc(const SceneFunc& F)
	{
		return F();
	}

	SceneFunc Func_RunBattle(CBattle& battle)
	{
		return [&battle]()->bool
		{
			CBattle newBattle = battle;
			return newBattle.RunBattle();	// battle �� ������ ������ ���� ������ �ִ� prototype �̰�, newBattle �� ������ ������ ������ ���� instance �̴�.
		};
	}

	SceneFunc Func_RunScript(int nScriptID)
	{
		return [nScriptID]()->bool
		{
			return Script::RunScript(nScriptID);
		};
	}

	SceneFunc Cond_CheckPCResistance(ResistanceType RT, SceneFunc F_success, SceneFunc F_fail)
	{
		return [RT, F_success, F_fail]()->bool
		{
			if (g_PC.CheckResistance(RT))
			{
				return F_success();
			}
			else
			{
				return F_fail();
			}
		};
	}


	void __stdcall RunScenes()
	{
		//Script::RunScript(1);
		RunSceneFunc(Func_RunScript(1));

		{
			CBattle Battle;
			Battle.m_nEnemyID = 1; //goblin 1
			Battle.OnEnemyGotDamage = BattleEventHandler::END_BATTLE;	// �Ѵ�� ������ battle end;
			//Battle.RunBattle();
			RunSceneFunc(Func_RunBattle(Battle));
		}

		RunSceneFunc(Func_RunScript(7));
		RunSceneFunc(Func_RunScript(2));
		
		{
			CBattle Battle;
			Battle.m_nEnemyID = 2;	// snake
			Battle.OnRoundEnd = BattleEventHandler::Set_Enemy_ToHitBonus(-20);
			//Battle.RunBattle();
			RunSceneFunc(Func_RunBattle(Battle));
		}
		
		RunSceneFunc(Func_RunScript(4));

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

			//Battle.RunBattle();
			RunSceneFunc(Func_RunBattle(Battle));
		}

		RunSceneFunc(Func_RunScript(11));
		RunSceneFunc(Cond_CheckPCResistance(RT_MAGIC, Func_RunScript(6), Func_RunScript(5)));
	}
}