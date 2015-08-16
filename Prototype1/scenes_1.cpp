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
					return false;	// �Ѵ�� ������ battle end;
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
						battle->m_pEnemy->toHitBonus = -20;	// ù ���忡�� ���� �� �ְ�
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
					if (battle->m_nRound == 1)	// ù ���尡 ������ ������ ����Ѵ�.
					{
						Script::RunScript(8);

						// ù ���尡 ������ ���߷� ����
						battle->m_pEnemy->toHitBonus = -20;	// �ȸ°�
					}
					else if (battle->m_nRound == 2)	// ��° ���尡 �������� ����� �� �׿��ٸ� ������ ����Ѵ�.
					{
						Script::RunScript(9);

						battle->m_pEnemy->toHitBonus = 20;	// ����
					}
					else if (battle->m_nRound == 3)
					{
						Script::RunScript(10);

						battle->m_pEnemy->toHitBonus = -20;	// �ȸ°�
					}

					return true;
				};
				Battle.RunBattle();//&goblin);
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
}