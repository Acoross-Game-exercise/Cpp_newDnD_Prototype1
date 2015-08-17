#include "scenes.h"

#include <iostream>

#include "Util.h"
#include "BattleDB.h"
#include "SceneFunctions.h"

#include <list>

#include "SceneDB.h"

namespace Scene
{
	void __stdcall RunScenes()
	{
		CScene* scene_test = g_SceneDB.m_SceneMap[1];
		if (scene_test)
		{
			scene_test->Run();
		}
	}
}