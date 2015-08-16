#pragma once

#include <functional>

class CCreature;

class CBattle
{
public:
	int m_nRound;

	int m_nEnemyID;
	CCreature* m_pEnemy;

	typedef std::function<bool(CBattle*)> OnBattleEvent;
		
	OnBattleEvent OnBattleStart;
	OnBattleEvent OnBattleEnd;
	OnBattleEvent OnEnemyGotDamage;
	OnBattleEvent OnRoundEnd;

	CBattle()
		: m_pEnemy(nullptr), 
		OnBattleStart(DefaultHandler),
		OnBattleEnd(DefaultHandler),
		OnEnemyGotDamage(DefaultHandler),
		OnRoundEnd(DefaultHandler)
	{
		;
	}

	bool RunBattle();//CCreature* pEnemy);

	static bool DefaultHandler(CBattle* battle)
	{
		return true;
	}
};