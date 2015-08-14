#pragma once

#include <functional>

class BattleCharacter;

//struct Battle
//{
//	int nRound;
//};

//bool RunBattle(BattleCharacter* pEnemy);
//
//typedef std::function<bool(Battle&)> OnBattleEvent;
//
//bool RunBattle(BattleCharacter* pEnemy);
//bool RunBattle(BattleCharacter* pEnemy, OnBattleEvent OnEnd);

class CBattle
{
public:
	int m_nRound;

	typedef std::function<bool(CBattle*)> OnBattleEvent;
	OnBattleEvent OnRoundEnd;

	CBattle()
	{
		OnRoundEnd = [](CBattle* battle)->bool { return true; };
	}

	bool RunBattle(BattleCharacter* pEnemy);
};