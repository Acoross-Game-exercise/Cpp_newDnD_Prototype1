#pragma once

#include <functional>

class CCreature;

//struct Battle
//{
//	int nRound;
//};

//bool RunBattle(CCreature* pEnemy);
//
//typedef std::function<bool(Battle&)> OnBattleEvent;
//
//bool RunBattle(CCreature* pEnemy);
//bool RunBattle(CCreature* pEnemy, OnBattleEvent OnEnd);

class CBattle
{
public:
	int m_nRound;

	int m_nEnemyID;
	CCreature* m_pEnemy;

	typedef std::function<bool(CBattle*)> OnBattleEvent;
	OnBattleEvent OnRoundEnd;
	OnBattleEvent OnBattleEnd;
	OnBattleEvent OnEnemyGotDamage;

	CBattle()
		: m_pEnemy(nullptr)
	{
		OnRoundEnd = [](CBattle* battle)->bool { return true; };
		OnBattleEnd = [](CBattle* battle)->bool { return true; };
		OnEnemyGotDamage = [](CBattle* battle)->bool { return true; };
	}

	bool RunBattle();//CCreature* pEnemy);
};