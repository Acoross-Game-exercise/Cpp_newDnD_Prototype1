#ifndef _SKILLDATA_
#define _SKILLDATA_

class CCreature;

class CSkill
{
public:
	virtual bool Instant(CCreature* pAttacker, CCreature* pTarget) = 0;
};

class CSkill_NormalAttack : public CSkill
{
public:
	virtual bool Instant(CCreature* pAttacker, CCreature* pTarget);
};

class CSkill_PoisonAttack : public CSkill
{
public:
	int m_nDamage;
	virtual bool Instant(CCreature* pAttacker, CCreature* pTarget);
};

#endif
