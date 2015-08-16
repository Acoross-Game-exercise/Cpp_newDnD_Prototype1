#ifndef _MY_CHARACTER_
#define _MY_CHARACTER_

#include "CCreature.h"

class PlayerCharacter : public CCreature
{
public:

	PlayerCharacter() : CCreature(L"´ç½Å") { ; }
	
	virtual bool CheckResistance(ResistanceType RT);

	virtual bool DoAttack(CBattle* pBattle, CCreature* pEnemy);
};

#endif //_MY_CHARACTER_
