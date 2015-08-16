
#include "SkillData.h"

#include "CCreature.h"
#include "Util.h"

//CSkill_NormalAttack
bool CSkill_NormalAttack::Instant(CCreature* pAttacker, CCreature* pTarget)
{
	if (!pTarget || !pAttacker)
	{
		return false;
	}

	int toHitEnemy = ToHitEnemy(pAttacker, pTarget);

	int d20 = Dice::D20(false /*pause*/);
	if (d20 >= toHitEnemy)	// ����
	{
		pAttacker->OnHitMessage();
		pTarget->OnDamaged(pAttacker->m_AttackPower);

		return true;
	}
	else
	{
		pAttacker->OnMissMessage();

		return false;
	}
}

//CSkill_PoisonAttack
bool CSkill_PoisonAttack::Instant(CCreature* pAttacker, CCreature* pTarget)
{
	if (!pTarget || !pAttacker)
	{
		return false;
	}

	CSkill_NormalAttack na;
	if (false == na.Instant(pAttacker, pTarget))
	{
		return false;
	}

	// �ߵ� �Ǿ����� üũ�Ѵ�. -> ��������
	if (false == pTarget->CheckResistance(ResistanceType::RT_POISON))
	{
		Script::RunFormattedScript(L"�ߵ��Ǿ���!\n");
		pTarget->OnDamaged(m_nDamage);
	}
	else
	{
		// �������� ����
		Script::RunFormattedScript(L"�ߵ��Ǳ� ���� ���� �̻����� ��� �� �־���.\n");
	}

	return true;	// �ߵ� �ȵǴ��� ������ ����.
}