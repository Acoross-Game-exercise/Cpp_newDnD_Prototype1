#include "scenes_1.h"

#include <iostream>
#include <conio.h>
#include <stdlib.h>

#include <functional>

#include "Util.h"

#include "MyCharacter.h"
#include "BattleCharacter.h"
#include "Battle.h"

extern PlayerCharacter g_PC;

namespace Scene
{
	class Goblin : public BattleCharacter
	{
	public:
		Goblin() : BattleCharacter(L"고블린") { ; }

		virtual void DoAttack(Battle& battle, BattleCharacter* pEnemy)
		{
			Script::RunFormattedScript(L"%s이 %s을 공격한다!\n", Name, pEnemy->Name);
			
			OnMiss();
		}

		virtual void OnDamaged(int nDamage)
		{
			const wchar_t* strings[] =
			{
				L"고블린에게 공격이 명중했다!\n",
				L"당신이 고블린을 치면 고블린은 소리를 지르며 통로를 따라 여둠 속으로 달아나 버린다. ",
				L"(고블린들은 어두운 곳에서도 볼 수 있다). ",

				L"\0"
			};

			Script::RunScript(strings);

			HP = 0;
		}
	};

	bool __stdcall RunScene1()
	{
		// 도입. 상황 설명.
		{
			const wchar_t* strings[] =
			{
				L" 동굴 안은 어둡고 먼지가 많이 쌓여 있다. ",
				L"동굴 입구에서 안쪽으로 이어진 통로를 통하면 언덕의 지하로 더 깊이 들어갈 수 있도록 되어 있다. ",
				L"갈 수 있는 길은 그곳 하나뿐인 것 같아서 당신은 그 방향으로 향하며 박쥐나 다른 몬스터가 있는지 주의 깊게 살피고 있다.\n",
				L"\1",

				L" 갑자기 고블린이 한 마리 보인다! ",
				L"고블린은 당신보다 키가 작고, 회색 살갗의 보기 흉한 난쟁이처럼 생겼다. 고블린은 당신을 보고 소리를 지르며 칼을 휘둘러 공격해온다! ",
				L"당신은 그 공격을 피하고 칼을 들어 휘두른다.\n",
				L"\1",

				L" 만약 그 고블린이 바로 공격하지 않았더라면 당신은 그와 이야기를 해보려고 할 수도 있었을 것이다. ",
				L"하지만 지금은 어쩔 수 없다. ",
				L"목숨을 지키기 위해선 싸울 수 밖에 없다. \n",
				L"\1",
				L"\0"	// string end
			};

			Script::RunScript(strings);
		}
		
		Goblin goblin;
		goblin.HP = 3;
		goblin.toHit = 12;
		
		RunBattle(&goblin);
				
		return RunScene2();
	}
	

	class Snake : public BattleCharacter
	{
	public:
		Snake() : BattleCharacter(L"뱀") { ; }

		virtual void DoAttack(Battle& battle, BattleCharacter* pEnemy)
		{
			Script::RunFormattedScript(L"%s이 %s을 공격한다!\n", Name, pEnemy->Name);

			if (battle.nRound == 1)	// 첫 라운드에만 뱀의 공격이 명중한다.
			{
				OnHit();

				g_PC.OnDamaged(1);

				// 중독 되었는지 체크한다. -> 내성굴림
				g_PC.CheckAndDealPoison();
			}
			else
			{
				OnMiss();
			}
		}
	};
	
	bool __stdcall RunScene2()
	{
		Console::Wait(1000);
		system("cls");

		// 씬2
		{
			const wchar_t* strings[] = 
			{
				L"[[씬2]]\n",
				L" 당신은 잠시 멈춰서 몸 상태를 한 번 확인한 후에 다시 동굴 통로를 따라 나아간다. ",
				L"샛길이나 다른 길은 없다. \n",
				L"\1",
				
				L" 통로는 앞쪽의 더 넓은 곳으로 통해 있다. ",
				L"이런 곳을 \"방\"이라고 부르자. ",
				L"당신은 무엇이 있나 살피려고 램프를 비추면서 주의 깊게 방 쪽으로 간다. ",
				L"당신의 왼쪽 방 구석에서 \"쉿쉿\"하는 소리가 들린다. ",
				L"그리고 거기에는 길이가 거의 3미터나 되는 거대한 방울뱀이 있다! ",
				L"뱀 가까이, 바닥에는 수백 개의 금화와 은화가 쌓여 있다.\n\n",
				L"보물을 손에 넣으려면 싸울 수 밖에 없다!!\n",
				L"\1",

				L"\0"
			};

			Script::RunScript(strings);
		}

		Snake snake;
		snake.HP = 3;
		snake.toHit = 11;

		RunBattle(&snake);

		printf("\n");
		printf("\n");
		system("pause");

		return true;
	}
}