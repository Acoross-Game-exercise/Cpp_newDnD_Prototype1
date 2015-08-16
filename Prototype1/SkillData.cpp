
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
	if (d20 >= toHitEnemy)	// 명중
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

	// 중독 되었는지 체크한다. -> 내성굴림
	if (false == pTarget->CheckResistance(ResistanceType::RT_POISON))
	{
		Script::RunFormattedScript(L"중독되었다!\n");
		pTarget->OnDamaged(m_nDamage);
	}
	else
	{
		// 내성굴림 성공
		Script::RunFormattedScript(L"중독되기 전에 뱀의 이빨에서 벗어날 수 있었다.\n");
	}

	return true;	// 중독 안되더라도 명중은 했음.
}