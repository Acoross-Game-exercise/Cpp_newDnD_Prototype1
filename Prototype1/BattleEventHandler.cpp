#include "BattleEventHandler.h"

#include "CCreature.h"
#include "ScriptDB.h"

namespace BattleEventHandler
{
	bool END_BATTLE(CBattle* battle)	// end battle
	{
		return false;
	}

	CBattle::OnBattleEvent Set_Enemy_ToHitBonus(int nToHitBonus)
	{
		return [nToHitBonus](CBattle* bat)->bool
		{
			CCreature* pEnemy = bat->m_pEnemy;
			if (pEnemy)
			{
				pEnemy->toHitBonus = nToHitBonus;
			}

			return true;
		};
	}

	CBattle::OnBattleEvent Run_Script(int nScriptID)
	{
		return [nScriptID](CBattle* battle)->bool
		{
			return Script::RunScript(nScriptID);
		};
	}

	///////////////////////////////////////////////////////////
	// Conds
	CBattle::OnBattleEvent COND_ROUND_AT(int nRound,
		const CBattle::OnBattleEvent& Handler)
	{
		return [nRound, Handler](CBattle* battle)->bool
		{
			if (battle)
			{
				if (battle->m_nRound == nRound)
				{
					return Handler(battle);
				}
			}

			return true;	// battle 속행. false 는 battle 종료.
		};
	}

	///////////////////////////////////////////////////////////
	// HandlerOP
	CBattle::OnBattleEvent OP_Concat(const CBattle::OnBattleEvent& handler1, const CBattle::OnBattleEvent& handler2)
	{
		return [handler1, handler2](CBattle* battle)->bool
		{
			if (battle)
			{
				if (handler1(battle))
					return handler2(battle);
			}

			return false;
		};
	}
}

CBattle::OnBattleEvent operator+(const CBattle::OnBattleEvent& lhs, const CBattle::OnBattleEvent& rhs)
{
	return [lhs, rhs](CBattle* battle)->bool
	{
		if (battle)
		{
			if (lhs(battle))
				return rhs(battle);
		}

		return false;
	};
}