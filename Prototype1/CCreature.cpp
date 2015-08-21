#include "CCreature.h"

#include "Util.h"

#include "SkillData.h"

CCreature::~CCreature()
{
}

bool CCreature::DoAttack(CBattle* pBattle, CCreature* pEnemy)
{
	Script::RunFormattedScript(L"%s�� %s�� �����Ѵ�!\n", Name.c_str(), pEnemy->Name.c_str());

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

	Script::RunFormattedScript(L"%s�� ������� %d ȸ���Ǿ���!!\n", Name.c_str(), nHealed);
}

void CCreature::OnDamaged(int nDamage)	// ���� ����
{
	HP -= nDamage;

	Script::RunFormattedScript(L"%d���� ����!!\n", nDamage);
	
	if (HP <= 0)
	{
		Script::Pause();
		Script::RunFormattedScript(L"%s�� �׾���.\n", Name.c_str());
	}
}

void CCreature::OnHitMessage()	// ���� ����
{
	Script::RunFormattedScript(L"%s�� ������ �����ߴ�!!\n", Name.c_str());
}

void CCreature::OnMissMessage()	// �� ������ ������
{
	Script::RunFormattedScript(L"�׷��� %s�� ������ ��������.\n", Name.c_str());
}


int ToHitEnemy(CCreature* pAttacker, CCreature* pTarget)
{
	if (nullptr == pAttacker)
		return 0;

	if (nullptr == pTarget)
		return 0;
	
	// �ӽ�...
	int ret = (pTarget->toHitMe - pAttacker->toHitBonus);
	return ret > 0 ? ret : 0;
}