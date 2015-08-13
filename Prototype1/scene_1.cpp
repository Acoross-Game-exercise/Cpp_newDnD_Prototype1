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
		Goblin() : BattleCharacter(L"���") { ; }

		virtual void DoAttack(Battle& battle, BattleCharacter* pEnemy)
		{
			Script::RunFormattedScript(L"%s�� %s�� �����Ѵ�!\n", Name, pEnemy->Name);
			
			OnMiss();
		}

		virtual void OnDamaged(int nDamage)
		{
			const wchar_t* strings[] =
			{
				L"������� ������ �����ߴ�!\n",
				L"����� ����� ġ�� ����� �Ҹ��� ������ ��θ� ���� ���� ������ �޾Ƴ� ������. ",
				L"(������� ��ο� �������� �� �� �ִ�). ",

				L"\0"
			};

			Script::RunScript(strings);

			HP = 0;
		}
	};

	bool __stdcall RunScene1()
	{
		// ����. ��Ȳ ����.
		{
			const wchar_t* strings[] =
			{
				L" ���� ���� ��Ӱ� ������ ���� �׿� �ִ�. ",
				L"���� �Ա����� �������� �̾��� ��θ� ���ϸ� ����� ���Ϸ� �� ���� �� �� �ֵ��� �Ǿ� �ִ�. ",
				L"�� �� �ִ� ���� �װ� �ϳ����� �� ���Ƽ� ����� �� �������� ���ϸ� ���㳪 �ٸ� ���Ͱ� �ִ��� ���� ��� ���ǰ� �ִ�.\n",
				L"\1",

				L" ���ڱ� ����� �� ���� ���δ�! ",
				L"����� ��ź��� Ű�� �۰�, ȸ�� �찯�� ���� ���� ������ó�� �����. ����� ����� ���� �Ҹ��� ������ Į�� �ֵѷ� �����ؿ´�! ",
				L"����� �� ������ ���ϰ� Į�� ��� �ֵθ���.\n",
				L"\1",

				L" ���� �� ����� �ٷ� �������� �ʾҴ���� ����� �׿� �̾߱⸦ �غ����� �� ���� �־��� ���̴�. ",
				L"������ ������ ��¿ �� ����. ",
				L"����� ��Ű�� ���ؼ� �ο� �� �ۿ� ����. \n",
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
		Snake() : BattleCharacter(L"��") { ; }

		virtual void DoAttack(Battle& battle, BattleCharacter* pEnemy)
		{
			Script::RunFormattedScript(L"%s�� %s�� �����Ѵ�!\n", Name, pEnemy->Name);

			if (battle.nRound == 1)	// ù ���忡�� ���� ������ �����Ѵ�.
			{
				OnHit();

				g_PC.OnDamaged(1);

				// �ߵ� �Ǿ����� üũ�Ѵ�. -> ��������
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

		// ��2
		{
			const wchar_t* strings[] = 
			{
				L"[[��2]]\n",
				L" ����� ��� ���缭 �� ���¸� �� �� Ȯ���� �Ŀ� �ٽ� ���� ��θ� ���� ���ư���. ",
				L"�����̳� �ٸ� ���� ����. \n",
				L"\1",
				
				L" ��δ� ������ �� ���� ������ ���� �ִ�. ",
				L"�̷� ���� \"��\"�̶�� �θ���. ",
				L"����� ������ �ֳ� ���Ƿ��� ������ ���߸鼭 ���� ��� �� ������ ����. ",
				L"����� ���� �� �������� \"����\"�ϴ� �Ҹ��� �鸰��. ",
				L"�׸��� �ű⿡�� ���̰� ���� 3���ͳ� �Ǵ� �Ŵ��� ������ �ִ�! ",
				L"�� ������, �ٴڿ��� ���� ���� ��ȭ�� ��ȭ�� �׿� �ִ�.\n\n",
				L"������ �տ� �������� �ο� �� �ۿ� ����!!\n",
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