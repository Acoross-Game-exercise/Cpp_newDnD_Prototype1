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
		// ��, �Ʊ� ���� ǥ��
		wprintf(L"\n��\t%s\n", pEnemy->Name);
		wprintf(L"HP: %d\tHP: %d\n", g_PC.HP, pEnemy->HP);
	};

	bool bRet = false;
	while (true)
	{
		++m_nRound;

		// ���� �Ұ� ����
		system("cls");
		Script::RunFormattedScript(L"%s���� ����!!!\n", pEnemy->Name);

		printBattleState();

		// �� �ൿ
		g_PC.DoAttack(this, pEnemy);

		// ���� �ൿ
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
			Script::RunFormattedScript(L"����� %s���� �¸��ߴ�..", pEnemy->Name);
			bRet = true;
			break;
		}

		Script::Pause();
	}

	return bRet;
}