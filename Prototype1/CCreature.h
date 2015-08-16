#ifndef _BATTLE_CHARACTER_
#define _BATTLE_CHARACTER_

#include <list>

#include "SkillData.h"

enum ResistanceType
{
	RT_POISON,
	RT_MAGIC,
	RT_MAX
};

class CBattle;
class CSkill;

class CCreature
{
public:
	int m_nID;

	int HPMax;
	int HP;
	const wchar_t* Name;

// <�ɷ�ġ>
	int STR;	//��
	int AGL;	//��ø��
	int INT;	//����
	int CON;	//�ǰ�
	int WIS;	//����
	int CHA;	//�ŷ�
// </�ɷ�ġ>

// <����ġ>
	int nRegistance[RT_MAX];
	const wchar_t* const strRegistance[RT_MAX] = {
		L"��",
		L"����"
	};
// </����ġ>

// <�ӽ�>
	int toHitMe;
	int toHitBonus;
	int m_AttackPower;
	CSkill* m_pAttackSkill;
// </�ӽ�>

	CCreature(const wchar_t* name) : m_nID(0), HPMax(1), HP(1), Name(name), 
		STR(0), AGL(0), INT(0), CON(0), WIS(0), CHA(0),
		toHitMe(0), toHitBonus(0), m_AttackPower(1), m_pAttackSkill(nullptr)
	{
		memset(nRegistance, 0, sizeof(int) * RT_MAX);
	}

	virtual ~CCreature();

	virtual void OnHealed(int nHealed);

	virtual void OnDamaged(int nDamage);

	virtual void OnHitMessage();

	virtual void OnMissMessage();
	
	virtual bool CheckResistance(ResistanceType RT) { return true; };

	virtual bool DoAttack(CBattle* pBattle, CCreature* pEnemy);
};

int ToHitEnemy(CCreature* pAttacker, CCreature* pTarget);

#endif