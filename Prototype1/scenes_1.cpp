#include "scenes.h"

#include <iostream>
#include <functional>

#include "Util.h"
#include "BattleCharacter.h"
#include "MyCharacter.h"
#include "Battle.h"
#include "ScriptDB.h"

extern PlayerCharacter g_PC;

namespace Scene
{
	class Goblin : public BattleCharacter
	{
	public:
		Goblin() : BattleCharacter(L"고블린") { ; }

		virtual void DoAttack(CBattle* battle, BattleCharacter* pEnemy)
		{
			Script::RunFormattedScript(L"%s이 %s을 공격한다!\n", Name, pEnemy->Name);
			
			OnMiss();
		}

		virtual void OnDamaged(int nDamage)
		{
			const wchar_t* strings[] =
			{
				//L"당신이 고블린을 치면 "
				L"고블린은 소리를 지르며 통로를 따라 여둠 속으로 달아나 버린다. \n",
				L"(고블린들은 어두운 곳에서도 볼 수 있다). ",

				L"\0"
			};

			Script::RunScript(strings);

			HP = 0;
		}
	};

	bool __stdcall RunScene1()
	{
		Script::CScene* pScene = Script::g_ScriptDB.m_sceneMap[1];
		Script::RunScript(pScene->m_Script, 100);
		
		Goblin goblin;
		goblin.HP = 3;
		goblin.toHit = 12;
		
		CBattle Battle;
		Battle.RunBattle(&goblin);
		
		Script::Pause();

		return RunScene2();
	}
	

	class Snake : public BattleCharacter
	{
	public:
		Snake() : BattleCharacter(L"뱀") { ; }

		virtual void DoAttack(CBattle* battle, BattleCharacter* pEnemy)
		{
			Script::RunFormattedScript(L"%s이 %s을 공격한다!\n", Name, pEnemy->Name);

			if (battle->m_nRound == 1)	// 첫 라운드에만 뱀의 공격이 명중한다.
			{
				OnHit();

				g_PC.OnDamaged(1);

				// 중독 되었는지 체크한다. -> 내성굴림
				if (false == g_PC.CheckResistance(ResistanceType::RT_POISON))
				{ 
					Script::RunFormattedScript(L"중독되었다!\n");
					g_PC.OnDamaged(2);
				}
				else
				{
					// 내성굴림 성공
					Script::RunFormattedScript(L"중독되기 전에 뱀의 이빨에서 벗어날 수 있었다.\n");
				}
			}
			else
			{
				OnMiss();
			}
		}
	};
	
	bool __stdcall RunScene2()
	{
		Script::Pause();
		system("cls");

		Script::CScene* pScene = Script::g_ScriptDB.m_sceneMap[2];
		Script::RunScript(pScene->m_Script, 100);

		Snake snake;
		snake.HP = 3;
		snake.toHit = 11;
		
		CBattle Battle;
		if (Battle.RunBattle(&snake))
		{
			return RunScene3();
		}
		
		return true;
	}

	bool __stdcall RunScene3()
	{
		Script::Pause();
		system("cls");
		
		Script::CScene* pScene = Script::g_ScriptDB.m_sceneMap[3];
		Script::RunScript(pScene->m_Script, 100);
				
		g_PC.OnHealed(g_PC.HPMax - g_PC.HP);

		{
			const wchar_t* strings[] =
			{
				L"\1",
				L"\n\n 일리나가 이런 저런 설명을 한다...\n",
				L"\1",

				L"일리나와 동료가 되었다!\n",
				L"\1",
				L"\0"
			};

			Script::RunScript(strings);
		}

		return RunScene4();
	}
}