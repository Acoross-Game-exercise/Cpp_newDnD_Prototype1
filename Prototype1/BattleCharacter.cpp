#include "BattleCharacter.h"

#include "Util.h"

BattleCharacter::~BattleCharacter()
{
}

void BattleCharacter::OnHealed(int nHealed)
{
	HP += nHealed;

	Script::RunFormattedScript(L"%s�� ������� %d ȸ���Ǿ���!!\n", Name, nHealed);
}

void BattleCharacter::OnDamaged(int nDamage)	// ���� ����
{
	HP -= nDamage;

	Script::RunFormattedScript(L"%d���� ����!!\n", nDamage);
	
	if (HP <= 0)
	{
		Script::Pause();
		Script::RunFormattedScript(L"%s�� �׾���.\n", Name);
	}
}

void BattleCharacter::OnHit()	// ���� ����
{
	Script::RunFormattedScript(L"%s�� ������ �����ߴ�!!\n", Name);
}

void BattleCharacter::OnMiss()	// �� ������ ������
{
	Script::RunFormattedScript(L"�׷��� %s�� ������ ��������.\n", Name);
}


int ToHitEnemy(BattleCharacter* pAttacker, BattleCharacter* pTarget)
{
	if (nullptr == pAttacker)
		return 0;

	if (nullptr == pTarget)
		return 0;

	// �ӽ�...
	return pTarget->toHit;
}