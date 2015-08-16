#include "scenes.h"

#include <iostream>
#include <functional>

#include "Util.h"

#include "MyCharacter.h"
#include "BattleCharacter.h"
#include "Battle.h"

#include "ScriptDB.h"

extern PlayerCharacter g_PC;

namespace Scene
{
	class Goblin_2 : public BattleCharacter
	{
	public:
		Goblin_2() : BattleCharacter(L"���") { ; }

		virtual void DoAttack(CBattle* battle, BattleCharacter* pEnemy)
		{
			Script::RunFormattedScript(L"%s�� %s�� �����Ѵ�!\n", Name, pEnemy->Name);

			if (battle->m_nRound == 1 || battle->m_nRound == 3)
			{
				OnHit();
				g_PC.OnDamaged(2);
			}
			else
			{
				OnMiss();
			}
		}
	};

	bool __stdcall RunScene4()
	{
		Script::Pause();

		Script::CScene* pScene = Script::g_ScriptDB.m_sceneMap[4];
		Script::RunScript(pScene->m_Script, 100);

		// Scene1 �̶� ������ �ٸ� ���.
		Goblin_2 goblin;
		goblin.HP = 2;
		goblin.toHit = 12;

		CBattle Battle;
		Battle.OnRoundEnd = [](CBattle* battle)->bool
		{
			if (battle->m_nRound == 1)	// ù ���尡 ������ ������ ����Ѵ�.
			{
				const wchar_t* strings[] =
				{
					L"\1",

					L" ����� ����� �ο�� �ִ� ���� �˸����� ö�� ������� �յڷ� �ֵθ��� ������ �⼼�� ���� ������ �ʴ� �����縦 ã�� �ִ�. ",
					L"���𰡸� ���� �� ����. ",
					L"�׸��� ���ſ� �����Ҹ��� �鸰��. ",
					L"�˸����� ö�� �ֵθ��� ������ �� �̻� �ƹ� �͵� ���� �ʴ´�. ",
					L"�׷��� �׳�� ö��� �����ϴ� ���� �׸��ΰ� ������ �Ǵ�. ",
					L"����� �ο� ������ ��� �ֱ� ������ �׳��� ������ ��� �Ǿ�� �ִ��� ���� ���Ѵ�. ",
					L"\1",

					L"\0"
				};

				Script::RunScript(strings);
			}
			else if (battle->m_nRound == 2)	// ��° ���尡 �������� ����� �� �׿��ٸ� ������ ����Ѵ�.
			{
				const wchar_t* strings[] =
				{
					L"\1",

					L" �˸����� �ٱ��� ã�Ƴ��� ���ؼ� �������ϱ� �����Ѵ�. ",
					L"���ڱ� ���� �� ���� �ʿ��� �ֹ��� �ܿ�� �Ҹ��� �鸰��! ",
					L"�����ڴ� ������ �ٲ� ö�� �ֵθ��� ������ �����鼭 �� ������ �޷�����. ",
					L"���� �κ��� ������� �ֹ� �Ҹ��� ������� �ٷ� �� �����ڸ��� ��Ÿ����. ",
					L"������ ȭ���� ���� �� ���߿� �ս� �� �ִ�. ",
					L"�װ� �˸����� ����Ű�ڸ��� ȭ���� ���ư��� �׳��� ���� ������! ",
					L"\1",

					L"�׳�� ����� ������ �Ѽ��� ���ϸ� �� �Ѱ���� �н� ��������. ",
					L"������ ȭ���� �������. ",
					L"\1",

					L"\0"
				};

				Script::RunScript(strings);
			}
			else if (battle->m_nRound == 3)
			{
				const wchar_t* strings[] =
				{
					L"\1",

					L" ������� �������� ������, �������� � ������ ���� �����ϰ� �ִ�.",
					L"\1",

					L"\0"
				};

				Script::RunScript(strings);
			}

			return true;
		};
		Battle.RunBattle(&goblin);

		{
			const wchar_t* strings[] =
			{
				L" ����� �������� ������ �����翡�� �����ϴ� ����� ���δ�. ",
				L"����� �����ؼ� ���Ǹ� �״� �ٸ� ������ �ֹ��� �ܸ� ���� ����. ",
				L"�װ� ��ſ��� ������ �ɰ� �ִ�.",
				L"\1",

				L"����� ���� ������ �ϼ��Ǳ� ���� ���� �ֵθ� ��ȸ�� ���� �� ������ �ϰ� �����翡�� �޷�����. ",
				L"�׷��� �ʹ� �ʾ��� - ������ ���� ����� �����´�. ",
				L"\1",

				L"\0"
			};

			Script::RunScript(strings);
		}

		// �������� - ����
		if (false == g_PC.CheckResistance(RT_MAGIC))	// ����
		{
			return RunScene5();	// ������ �ɸ�.		�� ��� #1
		}
		else //����
		{
			return RunScene6();	// ������ �ߵ���.	�� ��� #2
		}
	}

	bool __stdcall RunScene5()	// �� ��� #1
	{
		return true;
	}

	bool __stdcall RunScene6()	// �� ��� #2
	{
		return true;
	}
}