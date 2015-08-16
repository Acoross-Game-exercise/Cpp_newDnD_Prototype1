#ifndef _BATTLE_EVENT_HANDLER_
#define _BATTLE_EVENT_HANDLER_

#include "Battle.h"

class BattleCharacter;

namespace BattleEventHandler
{
	bool END_BATTLE(CBattle* battle);	// end battle

	CBattle::OnBattleEvent Set_Enemy_ToHitBonus(int nToHitBonus);

	CBattle::OnBattleEvent Run_Script(int nScriptID);

	///////////////////////////////////////////////////////////
	// Conds
	CBattle::OnBattleEvent COND_ROUND_AT(int nRound, 
		const CBattle::OnBattleEvent& Handler);

	///////////////////////////////////////////////////////////
	// HandlerOP
	CBattle::OnBattleEvent OP_Concat(const CBattle::OnBattleEvent& handler1, const CBattle::OnBattleEvent& handler2);

	CBattle::OnBattleEvent operator+(const CBattle::OnBattleEvent& lhs, const CBattle::OnBattleEvent& rhs);
}
#endif
