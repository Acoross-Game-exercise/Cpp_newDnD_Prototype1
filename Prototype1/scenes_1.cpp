#include "scenes.h"

#include <iostream>
#include <functional>

#include "Util.h"
#include "CCreature.h"
#include "MyCharacter.h"
#include "Battle.h"
#include "ScriptDB.h"

extern PlayerCharacter g_PC;

namespace Scene
{
	void __stdcall RunScenes()
	{
		{
			Script::RunScript(1);
			
			{
				CBattle Battle;
				Battle.m_nEnemyID = 1; //goblin 1
				Battle.OnEnemyGotDamage = [](CBattle* battle)->bool
				{
					return false;	// 한대라도 맞으면 battle end;
				};
				Battle.RunBattle();//&goblin);
			}

			Script::RunScript(7);

			Script::Pause();
		}

		// 2 ///////////////////////////
		{
			Script::Pause();
			system("cls");

			Script::RunScript(2);

			{
				CBattle Battle;
				//Battle.m_pEnemy = &snake;
				Battle.m_nEnemyID = 2;	// snake
				Battle.OnRoundEnd = [](CBattle* battle)->bool
				{
					if (battle->m_pEnemy)
					{
						battle->m_pEnemy->toHitBonus = -20;	// 첫 라운드에만 때릴 수 있게
					}

					return true;
				};
				Battle.RunBattle();//&snake);
			}
		}

		// 3 //////////////////////////////////////
		{
			Script::Pause();

			Script::RunScript(4);

			{
				CBattle Battle;
				//Battle.m_pEnemy = &goblin;
				Battle.m_nEnemyID = 3; //goblin 2
				Battle.OnRoundEnd = [](CBattle* battle)->bool
				{
					if (battle->m_nRound == 1)	// 첫 라운드가 끝나면 다음을 출력한다.
					{
						Script::RunScript(8);

						// 첫 라운드가 끝나면 명중률 조정
						battle->m_pEnemy->toHitBonus = -20;	// 안맞게
					}
					else if (battle->m_nRound == 2)	// 둘째 라운드가 끝나도록 고블린을 못 죽였다면 다음을 출력한다.
					{
						Script::RunScript(9);

						battle->m_pEnemy->toHitBonus = 20;	// 필중
					}
					else if (battle->m_nRound == 3)
					{
						Script::RunScript(10);

						battle->m_pEnemy->toHitBonus = -20;	// 안맞게
					}

					return true;
				};
				Battle.RunBattle();//&goblin);
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
}