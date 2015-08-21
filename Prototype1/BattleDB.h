#ifndef _BATTLE_DB_
#define _BATTLE_DB_

#include <unordered_map>

class CBattle;

typedef std::unordered_map<int, CBattle*> BattleMap;

class BattleDB
{
public:
	BattleMap m_BattleMap;
	
	bool Load(const wchar_t* const filename);

	BattleDB();
	~BattleDB();
};

extern BattleDB g_BattleDB;

void InitBattleDB_test();

#endif