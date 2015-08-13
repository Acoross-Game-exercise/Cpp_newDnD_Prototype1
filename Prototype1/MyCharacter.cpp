#include "MyCharacter.h"

#include <iostream>
#include <conio.h>
#include "Util.h"

void PlayerCharacter::CheckAndDealPoison()
{
	{
		const wchar_t* strings[] =
		{
			L"\n내성굴림: 독\n",
			L"\0"
		};

		Script::RunScript(strings);
	}

	Script::Pause(L"(roll d20 to evade poison... ToEvade:%d)", toPoison);	

	// 주사위를 굴린다.
	int d20 = Dice::D20();

	// 중독 되었는지 체크한다. -> 내성굴림
	if (d20 > toPoison)	// 회피함
	{
		const wchar_t* strings[] =
		{
			L"내성굴림 성공!\n",
			L"\0"
		};

		Script::RunScript(strings);
	}
	else	// 독 피해
	{
		const wchar_t* strings[] =
		{
			L"내성굴림 실패!\n",
			L"중독되었다!\n",

			L"\0"
		};
		
		Script::RunScript(strings);

		OnDamaged(2);
	}
}

void PlayerCharacter::DoAttack(Battle& battle, BattleCharacter* pEnemy)
{
	int toHitEnemy = ToHitEnemy(this, pEnemy);

	// 내 행동
	Script::Pause(L"(roll d20 to attack... ToHit:%d)", toHitEnemy);

	int d20 = Dice::D20();
	if (d20 >= toHitEnemy)	// 명중
	{
		Script::RunFormattedScript(L"%s에게 당신의 공격이 명중했다!\n", pEnemy->Name);

		pEnemy->OnDamaged(1);
	}
	else // 실패
	{
		const wchar_t* strings[] =
		{
			L"당신의 공격이 빗나갔다.\n",
			L"\0"
		};

		Script::RunScript(strings);
	}
}