#ifndef _BATTLE_CHARACTER_
#define _BATTLE_CHARACTER_

struct Battle
{
	int nRound;
};

class BattleCharacter
{
public:
	int HP;
	const wchar_t* Name;

// <�ɷ�ġ>
	int STR;	//��
	int AGL;	//��ø��
	int INT;	//����
	int CON;	//�ǰ�
// </�ɷ�ġ>

// <����ġ>
	int toPoison;
// </����ġ>

// <�ӽ�>
	int toHit;
// </�ӽ�>

	BattleCharacter(const wchar_t* name) : Name(name) 
	{
		; 
	}

	virtual ~BattleCharacter();

	virtual void OnDamaged(int nDamage);

	virtual void OnHit();

	virtual void OnMiss();

	virtual void CheckAndDealPoison() {};

	virtual void DoAttack(Battle& battle, BattleCharacter* pEnemy) = 0;
};

int ToHitEnemy(BattleCharacter* pAttacker, BattleCharacter* pTarget);

#endif