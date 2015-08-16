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
		Goblin() : BattleCharacter(L"���") { ; }

		virtual void DoAttack(CBattle* battle, BattleCharacter* pEnemy)
		{
			Script::RunFormattedScript(L"%s�� %s�� �����Ѵ�!\n", Name, pEnemy->Name);
			
			OnMiss();
		}

		virtual void OnDamaged(int nDamage)
		{
			const wchar_t* strings[] =
			{
				//L"����� ����� ġ�� "
				L"����� �Ҹ��� ������ ��θ� ���� ���� ������ �޾Ƴ� ������. \n",
				L"(������� ��ο� �������� �� �� �ִ�). ",

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
		Snake() : BattleCharacter(L"��") { ; }

		virtual void DoAttack(CBattle* battle, BattleCharacter* pEnemy)
		{
			Script::RunFormattedScript(L"%s�� %s�� �����Ѵ�!\n", Name, pEnemy->Name);

			if (battle->m_nRound == 1)	// ù ���忡�� ���� ������ �����Ѵ�.
			{
				OnHit();

				g_PC.OnDamaged(1);

				// �ߵ� �Ǿ����� üũ�Ѵ�. -> ��������
				if (false == g_PC.CheckResistance(ResistanceType::RT_POISON))
				{ 
					Script::RunFormattedScript(L"�ߵ��Ǿ���!\n");
					g_PC.OnDamaged(2);
				}
				else
				{
					// �������� ����
					Script::RunFormattedScript(L"�ߵ��Ǳ� ���� ���� �̻����� ��� �� �־���.\n");
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
				L"\n\n �ϸ����� �̷� ���� ������ �Ѵ�...\n",
				L"\1",

				L"�ϸ����� ���ᰡ �Ǿ���!\n",
				L"\1",
				L"\0"
			};

			Script::RunScript(strings);
		}

		return RunScene4();
	}
}