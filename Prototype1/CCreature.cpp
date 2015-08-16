#include "CCreature.h"

#include "Util.h"

#include "SkillData.h"

CCreature::~CCreature()
{
}

bool CCreature::DoAttack(CBattle* pBattle, CCreature* pEnemy)
{
	Script::RunFormattedScript(L"%s이 %s을 공격한다!\n", Name, pEnemy->Name);

	if (m_pAttackSkill)
	{
		return m_pAttackSkill->Instant(this, pEnemy);
	}
	else
	{
		CSkill_NormalAttack na;
		na.Instant(this, pEnemy);
	}

	return false;
}

void CCreature::OnHealed(int nHealed)
{
	HP += nHealed;

	Script::RunFormattedScript(L"%s의 생명력이 %d 회복되었다!!\n", Name, nHealed);
}

void CCreature::OnDamaged(int nDamage)	// 내가 맞음
{
	HP -= nDamage;

	Script::RunFormattedScript(L"%d점의 피해!!\n", nDamage);
	
	if (HP <= 0)
	{
		Script::Pause();
		Script::RunFormattedScript(L"%s은 죽었다.\n", Name);
	}
}

void CCreature::OnHitMessage()	// 내가 때림
{
	Script::RunFormattedScript(L"%s의 공격이 명중했다!!\n", Name);
}

void CCreature::OnMissMessage()	// 내 공격이 빗나감
{
	Script::RunFormattedScript(L"그러나 %s의 공격은 빗나갔다.\n", Name);
}


int ToHitEnemy(CCreature* pAttacker, CCreature* pTarget)
{
	if (nullptr == pAttacker)
		return 0;

	if (nullptr == pTarget)
		return 0;
	
	// 임시...
	int ret = (pTarget->toHitMe - pAttacker->toHitBonus);
	return ret > 0 ? ret : 0;
}