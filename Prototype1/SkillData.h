#ifndef _SKILLDATA_
#define _SKILLDATA_

class CCreature;

class CSkill
{
public:
	virtual ~CSkill() {};
	virtual bool Instant(CCreature* pAttacker, CCreature* pTarget) = 0;
};

class CSkill_NormalAttack : public CSkill
{
public:
	virtual ~CSkill_NormalAttack() {}
	virtual bool Instant(CCreature* pAttacker, CCreature* pTarget);
};

class CSkill_PoisonAttack : public CSkill
{
public:
	CSkill_PoisonAttack(int nDamage) : m_nDamage(nDamage) {};
	virtual ~CSkill_PoisonAttack() {};
	virtual bool Instant(CCreature* pAttacker, CCreature* pTarget);

private:
	int m_nDamage;
};

#endif
