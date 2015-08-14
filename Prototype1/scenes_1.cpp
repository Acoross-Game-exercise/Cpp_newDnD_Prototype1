#include "scenes_1.h"

#include <iostream>
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
		Goblin() : BattleCharacter(L"������") { ; }

		virtual void DoAttack(CBattle* battle, BattleCharacter* pEnemy)
		{
			Script::RunFormattedScript(L"%s�� %s�� �����Ѵ�!\n", Name, pEnemy->Name);
			
			OnMiss();
		}

		virtual void OnDamaged(int nDamage)
		{
			const wchar_t* strings[] =
			{
				//L"����� �������� ġ�� "
				L"�������� �Ҹ��� ������ ��θ� ���� ���� ������ �޾Ƴ� ������. \n",
				L"(���������� ��ο� �������� �� �� �ִ�). ",

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
				L"[[��1]]\n",
				L" ����� ������ ���������� ���� �� �ִ� ���� �����̴�. ",
				L"����� ��ħ�� ����ؼ� ������ ���� ����� �ö󰣴�. ",
				L"�� ������� ������ � �ִµ�, ���������� ������ �߰��� ���� �ְ� ���Ͱ� ���� ���� �ִ�. ",
				L"����� '�ٱ�'�̶�� ����� �� ���� ���� �ϳ��� �������� �𸥴ٴ� ���� �����. ",
				L"�ٱ��� ���� ��ġ�� ������� ��ġ�� �� ����� ������ ������ ���� �ϴ� �����̴�. ",
				L"����� �� �Ǵ��� ���� �� �ִٸ� ������ �Ǵ� ���̴�! ",
				L"\1",

				L"\n �Ա��� �ٰ����鼭 ����� ������ �ѷ�����. ",
				L"������ ���� ��� ���� ��ȭ�Ӱ� ���δ�. ",
				L"����� ���Ͱ� ��� �ִ� ���� ���� ���� ��ȭ���� ���ϸ� įį�ϰ� ��Ӵٴ� ���� �˰� �ִ�. ",
				L"����� ������ �ν˵� ���ڸ� ������",
				L"(������ ���� �߸����� �ʾҴ�. ���� �ȿ��� �ν˵��� �������� ��� �ִ�.) ",
				L"���ɽ����� ������ ���� ����. ",
				L"Į�� ���� �غ� �ϰ� ���� ������ ���� �鿩���´�.",
				L"\1",

				L"\n ���� ���� ��Ӱ� ������ ���� �׿� �ִ�. ",
				L"���� �Ա����� �������� �̾��� ��θ� ���ϸ� ����� ���Ϸ� �� ���� �� �� �ֵ��� �Ǿ� �ִ�. ",
				L"�� �� �ִ� ���� �װ� �ϳ����� �� ���Ƽ� ����� �� �������� ���ϸ� ���㳪 �ٸ� ���Ͱ� �ִ��� ���� ���� ���ǰ� �ִ�.\n",
				L"\1",

				L"\n ���ڱ� �������� �� ���� ���δ�! ",
				L"�������� ��ź��� Ű�� �۰�, ȸ�� �찯�� ���� ���� ������ó�� �����. �������� ����� ���� �Ҹ��� ������ Į�� �ֵѷ� �����ؿ´�! ",
				L"����� �� ������ ���ϰ� Į�� ��� �ֵθ���.\n",
				L"\1",

				L"\n ���� �� �������� �ٷ� �������� �ʾҴ���� ����� �׿� �̾߱⸦ �غ����� �� ���� �־��� ���̴�. ",
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
				L"����� ������ �ֳ� ���Ƿ��� ������ ���߸鼭 ���� ���� �� ������ ����. ",
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
		
		CBattle Battle;
		if (Battle.RunBattle(&snake))
		{
			return RunScene3();
		}
		
		return true;
	}

	bool __stdcall RunScene3()
	{
		Console::Wait(1000);
		system("cls");

		{
			const wchar_t* strings[] =
			{
				L"[[��3]]\n",
				L" ����� �λ���ߴ�. ",
				L"�׷����� ���� ������ ��� �� ���� ����. ",
				L"����� ���簡 ���� ���ش� ��ĥ ���� ����� ġ��ȴ�. ",
				L"���� ���� �������� �ʴ�. ",
				L"�׷��Ƿ� ����� �ؾ� �� ���� ����Ѵ�.",
				L"\1",

				L" ����� ���� ��ȭ�� ��ȭ�� �ֿ��� ������ �ִ� �ָӴϿ� �ִ´�. ",
				L"�̷��� ���ȿ� ����� ��ȭ ������ �� ���� ������ ������ �ִٴ� ���� �˾�������. ",
				L"��κ��� �׳� ��������, �� �߿��� �� ������ ȣ�ڱ�ȭ�� ���ȭ�� �ִ�! ",
				L"\1",

				L" �̷� �͵��� ���� �����̴�. ",
				L"����� �밳 �ƹ��͵� ������ ���� �ʴ�. ",
				L"�� ������ �Ƹ� ���� ���̷��ٰ� ������ � ����� ������ �־��� �Ͱ���.",
				L"\1",

				L" � ��쿡�� ������ ������ �ֱ⵵ �ϴ�. ",
				L"����� ���� ���� ���� ���캸�ٰ� ���� ������ ã�Ƴ���. ",
				L"���ְ� �� �� ������ �ִ�. ",
				L"�̰��� �Ƹ� ��ȭ 100���� ��ġ�� ���� �� ����!",
				L"\1",

				L" ���� ���鼭 ���� ������, ����� �ٽ� ������ ������ ������. ",
				L"�׸��� ��� �ӿ� �Ǵٸ� ��ΰ� �ִ� ���� ���δ�. ",
				L"����� ������ ���� �ڵ��ƺ��� �ָ� ���� �Ա����� ���� �޺��� ������ ������ ���� ���δ�.",
				L"\1",

				L" �� ���� �޺��� �̲����ٰ���, ����� �ڽ��� �밨�� ������ ���� �ǻ����. ",
				L"�̷� ���� �ο� ������ �޾Ƴ� ���� ���� ����.",
				L"\1",

				L" �λ��� �Ծ��ٴ� ���� ����ϰ� ��� ���ư� �� ��������! �ٸ� ���� ���ų� � ������ ���� ������ �������� �Ѵ�. ",
				L"������ ���ؼ� �ȵȴ�! �Ǵٸ� ���� �ο��� ���ؼ� ��Ƴ��ƶ�. ",
				L"������ ����� ��ٸ��� �ִ�.",
				L"\1",

				L"\2",

				L" ����� ���� ���ϴ� ���� ���� �ִ� ��θ� ���ɽ����� ���� ��������.",
				L"\1",

				L" ������ ���� ��� Į�� ���� �غ� �ϰ� �ִ�.",
				L"\1",

				L" ��δ� �Ǵٸ� ���� ������ ���� �ִ�. ",
				L"�������� �ٰ����� � ��Ҹ��� ������� ���� ���δ�.",
				L"\1",

				L" ����� ������ �Ѳ��� ��� �� �� ���� �� ���� �� �ֵ��� �ϰ� ���ɽ����� ������ ������ ���캻��. ",
				L"�����ʿ� ����� ���ʰ� ���� ������ ���� �Ƹ��ٿ� ������ ���� ���� ���� �ɾ� �ִ�. ",
				L"�׳�� ���� ������ ������ ������ ���� ���� �ݼ����� ���� ���� �پ� �ִ� ���븦 ������ �ִ�. ",
				L"�װ��� ö��(��� ����� �߼� ����)��� �����̴�. ",
				L"���� ������ ������ �׳� ���� �ٴڿ� ���� �ִ�.",
				L"�׳�� ������ �ϰ� �ְų� �⵵�ϰ� �ִ� �� ����.",
				L"\1",

				// �ϸ���
				L" ����� �׳ฦ �������� �ʰ� ��������� ���� �Դ´�.",
				L" �׷����� ����� ��ݻ�� �������� ���ȿ� �׳�� ���� �÷��ٺ��� ���Ѵ�.",
				L"\1",

				L"  \"�ȳ��ϼ���, ģ����!",
				L" �������� ã�� ��Ű���?",
				L" - ����!",
				L" ��ġ�̱���!",
				L" ���͵帱���?\" ",
				L"�׳�� ����� Ȥ�� ������ ����� �ƴұ� ���ɽ����� ���캸����, �����ְ� �;��ϴ� �Ͱ���.",
				L"\1",

				L"  ����� �����ؼ� �̾��ϴٰ� ����ϰ�, �׳డ �������� ���ؼ� � ���� �˰� �ִ��� �ñ����Ѵ�.",
				L" �׸��� - �������ٵ� - �׳డ ��� ����� ������ �� ������.",
				L" �׷����� ��ٷ���.",
				L" �׳�� ���� ���� �ִ�.",
				L" ��� ���� ���� �غ� �ϸ� ����� �� �� ������ �ٰ�����.",
				L"\1",

				L"  �׳�� �Ͼ�� �̷��� ���Ѵ�.",
				L"\1",

				L"  \"�� �̸��� �˸��� �Դϴ�.",
				L" ���� �������̰� ���ó�� ������ �ϴ� ����Դϴ�.",
				L" ���� ����� ���� �ִ� ������ ��µ�, ���͵�� ������ ã������ �̰��� �Դ�ϴ�.",
				L" �����ڿ� ���ؼ� �ƽó���?\"",
				L"\1",

				L"  ��� ����� ĳ���Ͱ� � ���� �� ���ΰ� ����� ���ƶ�.",
				L" �������� �׳�� ����� �̿��� ����� ���� ������ ����� �� �������� �ʴ´�.",
				L" �׸��� ����� �����ڿ� ���ؼ� �𸣰� �ִ�.",
				L"\1",

				L"  ����� ���� ��� ���� �˸����� ���Ѵ�.",
				L" \"��, �������� �������� �����ϴ�.\"",
				L" �׸��� �� �ٱ������� ������ ��θ� ����Ų��.",
				L" \"�������� �ʹ� ���� �����ļ� ���� ����� ���� ���߽��ϴ�.",
				L" ����� �� �������� �����߳���?",
				L"\1",

				L"  �� �ϼ̱���!",
				L" �������� ���� ���������.",
				L"\1",

				L"  ����� �����ڿ� ���ؼ� �𸣽Ŵٰ� �Ͻô�, ���� ������ �� �帮�ھ��.",
				L" �����ڵ��� ���ó�� ������ �ϵ��� �Ʒ��� �޽��ϴ�.",
				L" �׷����� �츮�� ������ �� �� ������.",
				L" ���� ������ �ϰ��������� ������ ������ �����ϴ�.",
				L" ���� ���� �� �� �ִ� ������ ġ���� �����Դϴ�.",
				L" ��Ų��� ġ�ᰡ �ʿ��� �� ������.\"",
				L"\1",

				L" ������ �Ǵ�! ",
				L"����� �׷� �Ϳ� ���� �� ���� ������, �ű⿡ ���ؼ��� �ƹ� �͵� �𸥴�. ",
				L"����� ������ �����ϸ鼭 �� �����ڰ� ���� ���� �߾�Ÿ��� ����� ���� ������ ������ ���� ����. ",
				L"�ź񽺷��Ե� ����� ��ó�� ġ��Ǿ���!",
				L"\1",

				L"\0"
			};

			Script::RunScript(strings);
		}
				
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