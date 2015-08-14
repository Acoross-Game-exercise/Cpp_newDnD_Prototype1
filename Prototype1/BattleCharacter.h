#ifndef _BATTLE_CHARACTER_
#define _BATTLE_CHARACTER_

enum ResistanceType
{
	RT_POISON,
	RT_MAGIC,
	RT_MAX
};

class CBattle;

class BattleCharacter
{
public:
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
	int toHit;
// </�ӽ�>

	BattleCharacter(const wchar_t* name) : Name(name) 
	{
		; 
	}

	virtual ~BattleCharacter();

	virtual void OnHealed(int nHealed);

	virtual void OnDamaged(int nDamage);

	virtual void OnHit();

	virtual void OnMiss();
	
	virtual bool CheckResistance(ResistanceType RT) { return true; };

	virtual void DoAttack(CBattle* pBattle, BattleCharacter* pEnemy) = 0;
};

int ToHitEnemy(BattleCharacter* pAttacker, BattleCharacter* pTarget);

#endif