#include "BattleCharacter.h"

#include "Util.h"

BattleCharacter::~BattleCharacter()
{
}

void BattleCharacter::OnHealed(int nHealed)
{
	HP += nHealed;

	Script::RunFormattedScript(L"%s의 생명력이 %d 회복되었다!!\n", Name, nHealed);
}

void BattleCharacter::OnDamaged(int nDamage)	// 내가 맞음
{
	HP -= nDamage;

	Script::RunFormattedScript(L"%d점의 피해!!\n", nDamage);
	
	if (HP <= 0)
	{
		Script::Pause();
		Script::RunFormattedScript(L"%s은 죽었다.\n", Name);
	}
}

void BattleCharacter::OnHit()	// 내가 때림
{
	Script::RunFormattedScript(L"%s의 공격이 명중했다!!\n", Name);
}

void BattleCharacter::OnMiss()	// 내 공격이 빗나감
{
	Script::RunFormattedScript(L"그러나 %s의 공격은 빗나갔다.\n", Name);
}


int ToHitEnemy(BattleCharacter* pAttacker, BattleCharacter* pTarget)
{
	if (nullptr == pAttacker)
		return 0;

	if (nullptr == pTarget)
		return 0;

	// 임시...
	return pTarget->toHit;
}