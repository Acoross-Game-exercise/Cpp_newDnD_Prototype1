#ifndef _MONSTER_DB_
#define _MONSTER_DB_

#include <unordered_map>

class CCreature;

typedef std::unordered_map<int, CCreature*> CreatureMap;

class MonsterDB
{
public:
	CreatureMap m_CreatureMap;
};

extern MonsterDB g_monsterDB;

void InitMonsterDB_test();

#endif
