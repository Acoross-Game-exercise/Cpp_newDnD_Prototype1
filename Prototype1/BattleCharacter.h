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
	int toHit;
// </임시>

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