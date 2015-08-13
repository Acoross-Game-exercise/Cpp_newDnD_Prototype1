#include "MyCharacter.h"

#include <iostream>
#include <conio.h>
#include "Util.h"

void PlayerCharacter::CheckAndDealPoison()
{
	{
		const wchar_t* strings[] =
		{
			L"\n��������: ��\n",
			L"\0"
		};

		Script::RunScript(strings);
	}

	Script::Pause(L"(roll d20 to evade poison... ToEvade:%d)", toPoison);	

	// �ֻ����� ������.
	int d20 = Dice::D20();

	// �ߵ� �Ǿ����� üũ�Ѵ�. -> ��������
	if (d20 > toPoison)	// ȸ����
	{
		const wchar_t* strings[] =
		{
			L"�������� ����!\n",
			L"\0"
		};

		Script::RunScript(strings);
	}
	else	// �� ����
	{
		const wchar_t* strings[] =
		{
			L"�������� ����!\n",
			L"�ߵ��Ǿ���!\n",

			L"\0"
		};
		
		Script::RunScript(strings);

		OnDamaged(2);
	}
}

void PlayerCharacter::DoAttack(Battle& battle, BattleCharacter* pEnemy)
{
	int toHitEnemy = ToHitEnemy(this, pEnemy);

	// �� �ൿ
	Script::Pause(L"(roll d20 to attack... ToHit:%d)", toHitEnemy);

	int d20 = Dice::D20();
	if (d20 >= toHitEnemy)	// ����
	{
		Script::RunFormattedScript(L"%s���� ����� ������ �����ߴ�!\n", pEnemy->Name);

		pEnemy->OnDamaged(1);
	}
	else // ����
	{
		const wchar_t* strings[] =
		{
			L"����� ������ ��������.\n",
			L"\0"
		};

		Script::RunScript(strings);
	}
}