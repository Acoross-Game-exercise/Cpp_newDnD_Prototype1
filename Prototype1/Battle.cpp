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
		// 적, 아군 상태 표시
		wprintf(L"\n나\t%s\n", pEnemy->Name);
		wprintf(L"HP: %d\tHP: %d\n", g_PC.HP, pEnemy->HP);
	};

	while (true)
	{
		++battle.nRound;

		// 전투 소개 문구
		system("cls");
		Script::RunFormattedScript(L"%s과의 전투!!!\n", pEnemy->Name);

		printBattleState();

		// 내 행동
		g_PC.DoAttack(battle, pEnemy);
		if (pEnemy->HP <= 0)
		{
			Script::RunFormattedScript(L"당신은 %s에게 승리했다..", pEnemy->Name);
			break;
		}

		printBattleState();

		// 적의 행동
		pEnemy->DoAttack(battle, &g_PC);
		if (g_PC.HP <= 0)
		{
			break;
		}

		Script::Pause();
	}

	return true;
}