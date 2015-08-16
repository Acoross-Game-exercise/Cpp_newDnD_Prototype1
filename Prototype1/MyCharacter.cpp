#include "MyCharacter.h"

#include <iostream>
#include <conio.h>

#include "Util.h"

bool PlayerCharacter::CheckResistance(ResistanceType RT) 
{
	Script::RunFormattedScript(L"\n내성굴림: %s\n", strRegistance[RT]);

	Script::Pause(L"(roll d20 to evade poison... ToEvade:%d)", nRegistance[RT]);

	// 주사위를 굴린다.
	int d20 = Dice::D20();

	// 중독 되었는지 체크한다. -> 내성굴림
	if (d20 > nRegistance[RT])	// 회피함
	{
		const wchar_t* strings[] =
		{
			L"내성굴림 성공!\n",
			L"\0"
		};

		Script::RunScript(strings);

		return true;
	}
	else	// 독 피해
	{
		const wchar_t* strings[] =
		{
			L"내성굴림 실패!\n",

			L"\0"
		};

		Script::RunScript(strings);

		return false;
	}
};

bool PlayerCharacter::DoAttack(CBattle* pBattle, CCreature* pEnemy)
{
	int toHitEnemy = ToHitEnemy(this, pEnemy);

	// 내 행동
	Script::Pause(L"(roll d20 to attack... ToHit:%d)", toHitEnemy);

	int d20 = Dice::D20();
	if (d20 >= toHitEnemy)	// 명중
	{
		OnHitMessage();
		//Script::RunFormattedScript(L"%s에게 당신의 공격이 명중했다!\n", pEnemy->Name);

		pEnemy->OnDamaged(1);

		return true;
	}
	else // 실패
	{
		const wchar_t* strings[] =
		{
			L"당신의 공격이 빗나갔다.\n",
			L"\0"
		};

		Script::RunScript(strings);

		return false;
	}
}