#include "SceneFunctions.h"

#include "Util.h"
#include "ScriptDB.h"
#include "MyCharacter.h"
#include "BattleDB.h"
#include "Battle.h"

extern PlayerCharacter g_PC;

namespace Scene
{
	bool DefaultFunc()
	{
		wprintf_s(L"Scene::DefaultFunc\n");
		return true;
	}

	bool RunSceneFunc(const SceneFunc& F)
	{
		return F();
	}
	
	SceneFunc Func_RunBattle(CBattle& battle)
	{
		return [&battle]()->bool
		{
			CBattle newBattle = battle;
			return newBattle.RunBattle();	// battle 은 전투를 돌리기 위한 정보가 있는 prototype 이고, newBattle 은 실제로 전투를 돌리기 위한 instance 이다.
		};
	}

	SceneFunc Func_RunBattle(int nBattleID)
	{
		return [nBattleID]()->bool
		{
			auto battle = g_BattleDB.m_BattleMap[nBattleID];
			if (battle)
			{
				return battle->RunBattle();
			}
			return false;
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
}