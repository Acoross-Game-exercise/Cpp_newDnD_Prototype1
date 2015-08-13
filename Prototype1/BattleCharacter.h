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

// <능력치>
	int STR;	//힘
	int AGL;	//민첩성
	int INT;	//지능
	int CON;	//건강
// </능력치>

// <내성치>
	int toPoison;
// </내성치>

// <임시>
	int toHit;
// </임시>

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