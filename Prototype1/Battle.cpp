#include "Battle.h"

#include <functional>

#include "Util.h"

#include "BattleCharacter.h"
#include "MyCharacter.h"

PlayerCharacter g_PC;

bool CBattle::RunBattle(BattleCharacter* pEnemy)
{
	if (nullptr == pEnemy)
	{
		return false;
	}

	m_nRound = 0;

	std::function<void(void)> printBattleState = [&pEnemy]()
	{
		// 적, 아군 상태 표시
		wprintf(L"\n나\t%s\n", pEnemy->Name);
		wprintf(L"HP: %d\tHP: %d\n", g_PC.HP, pEnemy->HP);
	};

	bool bRet = false;
	while (true)
	{
		++m_nRound;

		// 전투 소개 문구
		system("cls");
		Script::RunFormattedScript(L"%s과의 전투!!!\n", pEnemy->Name);

		printBattleState();

		// 내 행동
		g_PC.DoAttack(this, pEnemy);

		// 적의 행동
		if (pEnemy->HP > 0)
		{
			printBattleState();

			pEnemy->DoAttack(this, &g_PC);
			if (g_PC.HP <= 0)
			{
				bRet = false;
				break;
				//return false;
			}
		}

		if (false == OnRoundEnd(this))
		{
			bRet = true;
			break;
			//return true;
		}

		if (pEnemy->HP <= 0)
		{
			Script::RunFormattedScript(L"당신은 %s에게 승리했다..", pEnemy->Name);
			bRet = true;
			break;
		}

		Script::Pause();
	}

	return bRet;
}