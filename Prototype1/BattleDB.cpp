#include "BattleDB.h"

#include "Battle.h"
#include "BattleEventHandler.h"

#include "Parser.h"

#include "BattleParser.h"

BattleDB g_BattleDB;

BattleDB::BattleDB()
{
}

BattleDB::~BattleDB()
{
}

bool BattleDB::Load(const wchar_t* const filename)
{
	setlocale(LC_ALL, "");

	std::wifstream wis(filename, std::ifstream::binary);
	if (false == wis.is_open())
		return false;

	// apply BOM-sensitive UTF-16 facet
	wis.imbue(std::locale(wis.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));

	int nScriptLine = 0;
	std::wstring wline;

	wchar_t buf[2000];

	BattleParser parser;

	bool ret = true;
	while (std::getline(wis, wline))	// �� �� �о���δ�.
	{
		memset(buf, 0, sizeof(buf));
		wline._Copy_s(buf, 2000, wline.size(), 0);

		ret = parser.Parse(buf);
	}
	wis.close();

	return true;
}

//bool BattleDB::Load(const wchar_t* const filename)
//{
//	using namespace Parser;
//
//	CParser<CBattle>::funcList fList =
//	{
//		[](CBattle& battle, Token& token)
//	{
//		battle.m_nID = ParseInt(token);
//	},
//		[](CBattle& battle, Token& token)
//	{
//		battle.m_nEnemyID = ParseInt(token);
//	}
//	};
//
//	CParser<CBattle> parser;
//
//	return parser.Load(filename, fList, m_BattleMap);
//}

void InitBattleDB_test()
{
	//{
	//	CBattle* Battle = new CBattle();
	//	Battle->m_nID = 1;
	//	Battle->m_nEnemyID = 1; //goblin 1
	//	Battle->OnEnemyGotDamage = BattleEventHandler::END_BATTLE;	// �Ѵ�� ������ battle end;
	//	//RunSceneFunc(Func_RunBattle(Battle));
	//	g_BattleDB.m_BattleMap.insert(BattleMap::value_type(Battle->m_nID, Battle));
	//}

	//{
	//	CBattle* Battle = new CBattle();
	//	Battle->m_nID = 2;
	//	Battle->m_nEnemyID = 2;	// snake
	//	Battle->OnRoundEnd = BattleEventHandler::Set_Enemy_ToHitBonus(-20);
	//	//RunSceneFunc(Func_RunBattle(Battle));
	//	g_BattleDB.m_BattleMap.insert(BattleMap::value_type(Battle->m_nID, Battle));
	//}

	//{
	//	using namespace BattleEventHandler;
	//	CBattle* Battle = new CBattle();
	//	Battle->m_nID = 3;
	//	Battle->m_nEnemyID = 1; //goblin

	//	Battle->OnBattleStart = Set_Enemy_ToHitBonus(20);	// ù�� ����.

	//	CBattle::OnBattleEvent op1, op2, op3, ev;

	//	op1 = COND_ROUND_AT(1,
	//		Run_Script(8) + Set_Enemy_ToHitBonus(-20));		// 2���� ���
	//	op2 = COND_ROUND_AT(2,
	//		Run_Script(9) + Set_Enemy_ToHitBonus(20));		// 3���� ����
	//	op3 = COND_ROUND_AT(3,
	//		Run_Script(10) + Set_Enemy_ToHitBonus(-20));		// 4���� ���� ���

	//	ev = op1 + op2 + op3;
	//	Battle->OnRoundEnd = ev;
	//	//RunSceneFunc(Func_RunBattle(Battle));
	//	g_BattleDB.m_BattleMap.insert(BattleMap::value_type(Battle->m_nID, Battle));
	//}
}