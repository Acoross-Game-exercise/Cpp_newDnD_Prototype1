#ifndef _SCENE_FUNCTIONS_
#define _SCENE_FUNCTIONS_

#include <functional>
#include "CCreature.h"

#include "Scene.h"

namespace Scene
{
	bool DefaultFunc();

	bool RunSceneFunc(const SceneFunc& F);

	SceneFunc Func_RunBattle(CBattle& battle);
	SceneFunc Func_RunBattle(int nBattleID);

	SceneFunc Func_RunScript(int nScriptID);

	SceneFunc Cond_CheckPCResistance(ResistanceType RT, SceneFunc F_success, SceneFunc F_fail);
}

#endif
