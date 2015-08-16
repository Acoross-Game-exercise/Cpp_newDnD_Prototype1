#include "MyCharacter.h"

#include <iostream>
#include <conio.h>

#include "Util.h"

bool PlayerCharacter::CheckResistance(ResistanceType RT) 
{
	Script::RunFormattedScript(L"\n��������: %s\n", strRegistance[RT]);

	Script::Pause(L"(roll d20 to evade poison... ToEvade:%d)", nRegistance[RT]);

	// �ֻ����� ������.
	int d20 = Dice::D20();

	// �ߵ� �Ǿ����� üũ�Ѵ�. -> ��������
	if (d20 > nRegistance[RT])	// ȸ����
	{
		const wchar_t* strings[] =
		{
			L"�������� ����!\n",
			L"\0"
		};

		Script::RunScript(strings);

		return true;
	}
	else	// �� ����
	{
		const wchar_t* strings[] =
		{
			L"�������� ����!\n",

			L"\0"
		};

		Script::RunScript(strings);

		return false;
	}
};

bool PlayerCharacter::DoAttack(CBattle* pBattle, CCreature* pEnemy)
{
	int toHitEnemy = ToHitEnemy(this, pEnemy);

	// �� �ൿ
	Script::Pause(L"(roll d20 to attack... ToHit:%d)", toHitEnemy);

	int d20 = Dice::D20();
	if (d20 >= toHitEnemy)	// ����
	{
		OnHitMessage();
		//Script::RunFormattedScript(L"%s���� ����� ������ �����ߴ�!\n", pEnemy->Name);

		pEnemy->OnDamaged(1);

		return true;
	}
	else // ����
	{
		const wchar_t* strings[] =
		{
			L"����� ������ ��������.\n",
			L"\0"
		};

		Script::RunScript(strings);

		return false;
	}
}