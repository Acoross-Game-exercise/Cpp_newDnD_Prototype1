#include <iostream>
#include <locale.h>
#include <time.h>
#include <algorithm>
#include <string>

// for init
#include "ScriptDB.h"
#include "MonsterDB.h"
#include "MyCharacter.h"
#include "BattleDB.h"
#include "SceneDB.h"
//

#include "scenes.h"

extern PlayerCharacter g_PC;

// test
#include "Scene.h"
//#include "Battle.h"
//#include "BattleEventHandler.h"
//test

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	srand(time(nullptr));
	
	// InitCharacter
	{
		g_PC.STR = 17;
		g_PC.AGL = 11;
		g_PC.INT = 9;
		g_PC.CON = 16;
		g_PC.WIS = 8;
		g_PC.CHA = 14;

		g_PC.nRegistance[RT_POISON] = 12;
		g_PC.nRegistance[RT_MAGIC] = 17;

		g_PC.HPMax = 8;
		g_PC.HP = 8;
		g_PC.toHitMe = 10;
		g_PC.m_AttackPower = 1;
	}
		
#ifdef _DEBUG
	Script::g_ScriptDB.Load(L"script_test.txt");
#else
	Script::g_ScriptDB.Load(L"script.txt");
#endif
	InitMonsterDB_test();
	InitBattleDB_test();
	Scene::InitSceneDB_test();

	Scene::CScene* pScene = Scene::g_SceneDB.m_SceneMap[1];
	if (pScene)
	{
		pScene->Run();
	}

	//Scene::RunScenes();
	
	system("pause");

	return 0;
}