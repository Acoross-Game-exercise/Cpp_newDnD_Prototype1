#ifndef _MONSTER_DB_
#define _MONSTER_DB_

#include <unordered_map>
#include "CCreature.h"

#include "../RecurrentDescentParser/Parser/RDParser.h"

typedef std::unordered_map<int, CCreature*> CreatureMap;

class MonsterDB
{
public:
	bool Load2(const wchar_t* const filename);
	bool Load(const wchar_t* const filename);
	CreatureMap m_CreatureMap;

	virtual ~MonsterDB()
	{
		for (auto it = m_CreatureMap.begin(); it != m_CreatureMap.end(); ++it)
		{
			delete it->second;
		}
	}
};

extern MonsterDB g_monsterDB;

void InitMonsterDB_test();

#endif
