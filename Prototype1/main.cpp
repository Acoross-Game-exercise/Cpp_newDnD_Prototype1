#include <iostream>
#include "locale.h"
#include <time.h>

#include "scenes.h"
#include "MyCharacter.h"

#include "ScriptDB.h"

#include <algorithm>
#include <string>

extern PlayerCharacter g_PC;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");

	srand(time(nullptr));

	// InitCharacter
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

	Script::g_ScriptDB.Load(L"script.txt");

	//Scene::RunScene1();
	//Scene::RunScene2();
	//Scene::RunScene3();
	Scene::RunScene4();

	system("pause");

	return 0;
}