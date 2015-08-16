#include "Battle.h"

#include <functional>

#include "Util.h"
#include "CCreature.h"
#include "MyCharacter.h"
#include "MonsterDB.h"

PlayerCharacter g_PC;

// return: true (pc win), false (enemy win)
bool CBattle::RunBattle()
{
	CCreature* pEnemy = g_monsterDB.m_CreatureMap[m_nEnemyID];
	if (nullptr == pEnemy)
	{
		return false;
	}
	m_pEnemy = pEnemy;

	if (false == OnBattleStart(this))
	{
		return false;
	}
	
	std::function<void(void)> printBattleState = [&pEnemy]()
	{
		// 적, 아군 상태 표시
		wprintf(L"\n===================================\n");
		wprintf(L"나\t%s\n", pEnemy->Name);
		wprintf(L"HP: %d\tHP: %d\n", g_PC.HP, pEnemy->HP);
		wprintf(L"===================================\n");
	};
	
	m_nRound = 0;
	bool bRet = false;
	while (true)
	{
		++m_nRound;

		// 전투 소개 문구
		system("cls");
		Script::RunFormattedScript(L"%s과의 전투!!!: Round %d\n", pEnemy->Name, m_nRound);

		printBattleState();

		// 내 행동
		if (g_PC.DoAttack(this, pEnemy))
		{
			if (false == OnEnemyGotDamage(this))
			{
				bRet = true;
				break;
			}
		}

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
			Script::RunFormattedScript(L"당신은 %s에게 승리했다..\n", pEnemy->Name);
			bRet = true;
			break;
		}

		Script::Pause();
	}

	OnBattleEnd(this);

	return bRet;
}