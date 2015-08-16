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

// <능력치>
	int STR;	//힘
	int AGL;	//민첩성
	int INT;	//지능
	int CON;	//건강
	int WIS;	//지혜
	int CHA;	//매력
// </능력치>

// <내성치>
	int nRegistance[RT_MAX];
	const wchar_t* const strRegistance[RT_MAX] = {
		L"독",
		L"마법"
	};
// </내성치>

// <임시>
	int toHitMe;
	int toHitBonus;
	int m_AttackPower;
	CSkill* m_pAttackSkill;
// </임시>

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