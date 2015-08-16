#include "scenes.h"

#include <iostream>
#include <functional>

#include "Util.h"

#include "MyCharacter.h"
#include "BattleCharacter.h"
#include "Battle.h"

#include "ScriptDB.h"

extern PlayerCharacter g_PC;

namespace Scene
{
	class Goblin_2 : public BattleCharacter
	{
	public:
		Goblin_2() : BattleCharacter(L"고블린") { ; }

		virtual void DoAttack(CBattle* battle, BattleCharacter* pEnemy)
		{
			Script::RunFormattedScript(L"%s이 %s을 공격한다!\n", Name, pEnemy->Name);

			if (battle->m_nRound == 1 || battle->m_nRound == 3)
			{
				OnHit();
				g_PC.OnDamaged(2);
			}
			else
			{
				OnMiss();
			}
		}
	};

	bool __stdcall RunScene4()
	{
		Script::Pause();

		Script::CScene* pScene = Script::g_ScriptDB.m_sceneMap[4];
		Script::RunScript(pScene->m_Script, 100);

		// Scene1 이랑 로직이 다른 고블린.
		Goblin_2 goblin;
		goblin.HP = 2;
		goblin.toHit = 12;

		CBattle Battle;
		Battle.OnRoundEnd = [](CBattle* battle)->bool
		{
			if (battle->m_nRound == 1)	// 첫 라운드가 끝나면 다음을 출력한다.
			{
				const wchar_t* strings[] =
				{
					L"\1",

					L" 당신이 고블린과 싸우고 있는 동안 알리나는 철퇴를 허공에서 앞뒤로 휘두르며 무서운 기세로 눈에 보이지 않는 마법사를 찾고 있다. ",
					L"무언가를 때린 것 같다. ",
					L"그리고 무거운 신음소리가 들린다. ",
					L"알리나는 철퇴를 휘두르고 있지만 더 이상 아무 것도 맞지 않는다. ",
					L"그래서 그녀는 철퇴로 공격하는 것을 그만두고 마법을 건다. ",
					L"당신은 싸움에 정신을 쏟고 있기 때문에 그녀의 마법이 어떻게 되어가고 있는지 보지 못한다. ",
					L"\1",

					L"\0"
				};

				Script::RunScript(strings);
			}
			else if (battle->m_nRound == 2)	// 둘째 라운드가 끝나도록 고블린을 못 죽였다면 다음을 출력한다.
			{
				const wchar_t* strings[] =
				{
					L"\1",

					L" 알리나는 바글을 찾아내지 못해서 초조해하기 시작한다. ",
					L"갑자기 방의 먼 구석 쪽에서 주문을 외우는 소리가 들린다! ",
					L"성직자는 방향을 바꿔 철퇴를 휘두르고 고함을 지르면서 그 쪽으로 달려간다. ",
					L"검은 로브의 마법사는 주문 소리가 들려오던 바로 그 구석자리에 나타난다. ",
					L"빛나는 화살이 그의 옆 공중에 둥실 떠 있다. ",
					L"그가 알리나를 가리키자마자 화살이 날아가서 그녀의 몸에 꽂힌다! ",
					L"\1",

					L"그녀는 비명을 지르고 한숨을 토하며 방 한가운데에 털썩 쓰러진다. ",
					L"빛나는 화살이 사라진다. ",
					L"\1",

					L"\0"
				};

				Script::RunScript(strings);
			}
			else if (battle->m_nRound == 3)
			{
				const wchar_t* strings[] =
				{
					L"\1",

					L" 마법사는 구석으로 물러나, 다음에는 어떤 마법을 쓸까 생각하고 있다.",
					L"\1",

					L"\0"
				};

				Script::RunScript(strings);
			}

			return true;
		};
		Battle.RunBattle(&goblin);

		{
			const wchar_t* strings[] =
			{
				L" 고블린이 쓰러졌을 때부터 마법사에게 걱정하는 기색이 보인다. ",
				L"당신을 주의해서 살피며 그는 다른 마법의 주문을 외며 손을 흔든다. ",
				L"그가 당신에게 마법을 걸고 있다.",
				L"\1",

				L"당신은 그의 마법이 완성되기 전에 검을 휘두를 기회를 잡을 수 있을까 하고 마법사에게 달려간다. ",
				L"그러나 너무 늦었다 - 마법의 힘이 당신을 사로잡는다. ",
				L"\1",

				L"\0"
			};

			Script::RunScript(strings);
		}

		// 내성굴림 - 마법
		if (false == g_PC.CheckResistance(RT_MAGIC))	// 실패
		{
			return RunScene5();	// 마법에 걸림.		끝 장면 #1
		}
		else //성공
		{
			return RunScene6();	// 마법을 견뎌냄.	끝 장면 #2
		}
	}

	bool __stdcall RunScene5()	// 끝 장면 #1
	{
		return true;
	}

	bool __stdcall RunScene6()	// 끝 장면 #2
	{
		return true;
	}
}