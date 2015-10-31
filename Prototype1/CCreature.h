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

// <�ɷ�ġ>
	int STR{ 0 };	//��
	int AGL{ 0 };	//��ø��
	int INT{ 0 };	//����
	int CON{ 0 };	//�ǰ�
	int WIS{ 0 };	//����
	int CHA{ 0 };	//�ŷ�
// </�ɷ�ġ>

// <����ġ>
	int nRegistance[RT_MAX]{ 0, };
	const wchar_t* const strRegistance[RT_MAX] = {
		L"��",
		L"����"
	};
// </����ġ>

// <�ӽ�>
	int toHitMe{ 0 };
	int toHitBonus{ 0 };
	int m_AttackPower{ 1 };
	//CSkill* m_pAttackSkill{ nullptr };
	std::unique_ptr<CSkill> m_pAttackSkill{ nullptr };
// </�ӽ�>

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