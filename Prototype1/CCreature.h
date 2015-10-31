#ifndef _BATTLE_CHARACTER_
#define _BATTLE_CHARACTER_

#include <list>
#include <memory>

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
	int m_nID{ 0 };

	int HPMax{ 1 };
	int HP{ 1 };

	std::wstring Name{ L"" };
	std::wstring NameInternal{ L"" };

// <능력치>
	int STR{ 0 };	//힘
	int AGL{ 0 };	//민첩성
	int INT{ 0 };	//지능
	int CON{ 0 };	//건강
	int WIS{ 0 };	//지혜
	int CHA{ 0 };	//매력
// </능력치>

// <내성치>
	int nRegistance[RT_MAX]{ 0, };
	const wchar_t* const strRegistance[RT_MAX] = {
		L"독",
		L"마법"
	};
// </내성치>

// <임시>
	int toHitMe{ 0 };
	int toHitBonus{ 0 };
	int m_AttackPower{ 1 };
	//CSkill* m_pAttackSkill{ nullptr };
	std::unique_ptr<CSkill> m_pAttackSkill{ nullptr };
// </임시>

	CCreature() { ; }
	CCreature(const wchar_t* name) : Name(name)
	{
	}

	void Print()
	{
		wprintf_s(L"\nId(%d), Name(%s, %s), HP(%d), toHitMe(%d), toHitBonus(%d), Attack(%d)\n", m_nID, Name.c_str(), NameInternal.c_str(), HP, toHitMe, toHitBonus, m_AttackPower);
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