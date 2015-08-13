#include "Battle.h"

#include <functional>

#include "Util.h"

#include "BattleCharacter.h"
#include "MyCharacter.h"

PlayerCharacter g_PC;

bool RunBattle(BattleCharacter* pEnemy)
{
	if (nullptr == pEnemy)
	{
		return false;
	}

	Battle battle;
	battle.nRound = 0;

	std::function<void(void)> printBattleState = [&pEnemy]()
	{
		// ��, �Ʊ� ���� ǥ��
		wprintf(L"\n��\t%s\n", pEnemy->Name);
		wprintf(L"HP: %d\tHP: %d\n", g_PC.HP, pEnemy->HP);
	};

	while (true)
	{
		++battle.nRound;

		// ���� �Ұ� ����
		system("cls");
		Script::RunFormattedScript(L"%s���� ����!!!\n", pEnemy->Name);

		printBattleState();

		// �� �ൿ
		g_PC.DoAttack(battle, pEnemy);
		if (pEnemy->HP <= 0)
		{
			Script::RunFormattedScript(L"����� %s���� �¸��ߴ�..", pEnemy->Name);
			break;
		}

		printBattleState();

		// ���� �ൿ
		pEnemy->DoAttack(battle, &g_PC);
		if (g_PC.HP <= 0)
		{
			break;
		}

		Script::Pause();
	}

	return true;
}