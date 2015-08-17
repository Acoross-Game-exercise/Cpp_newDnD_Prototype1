#include "MonsterDB.h"

#include <fstream>
#include <locale>
#include <codecvt>

#include <string>

#include "CCreature.h"
#include "SkillData.h"

#include <iostream>

#include "Util.h"

MonsterDB g_monsterDB;

class Token
{
public:
	Token(const wchar_t* token, int nLen, const wchar_t* next) : wcsToken(token), nLength(nLen), nextInput(next)
	{}

	const wchar_t* wcsToken;
	const wchar_t* nextInput;
	int nLength;
};


// �� ������ ����, �޸�(,) �� ���еǴ� token �� ��´�.
Token GetToken(const wchar_t* input)
{
	int nPos = 0;
	while (true)
	{
		if (input[nPos] == L' ' || input[nPos] == L'\t')
		{
			++nPos;
		}
		else
		{
			break;
		}
	}
	
	int nStartPos = nPos;
	const wchar_t* next = nullptr;
	while (true)
	{
		if (input[nPos] == L'\0')
		{
			break;
		}
		else if (input[nPos] == L',')
		{
			next = &input[nPos + 1];
			break;
		}

		++nPos;
	}

	return Token(&input[nStartPos], nPos, next);
}

bool Load(const wchar_t* const filename)
{
	std::wifstream wis(filename, std::ifstream::binary);
	if (false == wis.is_open())
	{
		return false;
	}
	// apply BOM-sensitive UTF-16 facet
	wis.imbue(std::locale(wis.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));

	std::wstring wline;
	while (std::getline(wis, wline))	// �� �� �о���δ�.
	{
		wline = Script::RemoveReturnChar(wline);

		// token �� �д´�.
		const wchar_t* line = wline.c_str();		
		while (line)
		{
			Token token = GetToken(line);
			line = token.nextInput;
			wprintf_s(L"%.*s,", token.nLength, token.wcsToken);
		}
		std::wcout << std::endl;
	}

	return false;
}

bool MonsterDB::Load(const wchar_t* const filename)
{
	return ::Load(filename);
}

void InitMonsterDB_test()
{
	CCreature* goblin = new CCreature(L"���");
	{
		goblin->m_nID = 1;
		goblin->HP = 3;
		goblin->toHitMe = 12;
		goblin->toHitBonus = -20; // ���� �Ұ�
		goblin->m_AttackPower = 2;
	}

	g_monsterDB.m_CreatureMap.insert(CreatureMap::value_type(1, goblin));

	CCreature* snake = new CCreature(L"��");
	{
		snake->m_nID = 2;
		snake->HP = 3;
		snake->toHitMe = 11;
		snake->toHitBonus = 20;	// �ݵ�� ����
		snake->m_AttackPower = 1;
		
		snake->m_pAttackSkill = new CSkill_PoisonAttack(2);
	}

	g_monsterDB.m_CreatureMap.insert(CreatureMap::value_type(2, snake));
}
