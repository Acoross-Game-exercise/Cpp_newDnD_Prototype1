#ifndef _MY_CHARACTER_
#define _MY_CHARACTER_

#include "BattleCharacter.h"

class PlayerCharacter : public BattleCharacter
{
public:
	PlayerCharacter() : BattleCharacter(L"´ç½Å") { ; }
	
	virtual void CheckAndDealPoison();

	virtual void DoAttack(Battle& battle, BattleCharacter* pEnemy);
};

#endif //_MY_CHARACTER_
