#include "SceneDB.h"

#include "Scene.h"
#include "SceneFunctions.h"

#include "Parser.h"

namespace Scene
{
	SceneDB g_SceneDB;

	SceneDB::SceneDB()
	{
	}

	SceneDB::~SceneDB()
	{
	}

	bool SceneDB::Load(const wchar_t* const filename)
	{
		using namespace Parser;

		CParser<CScene>::funcList fList =
		{
			[](CScene& scene, Token& token)
		{
			scene.m_nID = ParseInt(token);
		}
		};

		CParser<CScene> parser;

		return parser.Load(filename, fList, m_SceneMap);
	}

	void InitSceneDB_test()
	{
		using namespace Scene;
		CScene* pScene = new CScene();

		pScene->m_nID = 1;
		pScene->m_SceneFuncList.push_back(Func_RunScript(1));
		pScene->m_SceneFuncList.push_back(Func_RunBattle(1));
		pScene->m_SceneFuncList.push_back(Func_RunScript(7));
		pScene->m_SceneFuncList.push_back(Func_RunScript(2));
		pScene->m_SceneFuncList.push_back(Func_RunBattle(2));
		pScene->m_SceneFuncList.push_back(Func_RunScript(4));
		pScene->m_SceneFuncList.push_back(Func_RunBattle(3));
		pScene->m_SceneFuncList.push_back(Func_RunScript(11));
		pScene->m_SceneFuncList.push_back(Cond_CheckPCResistance(RT_MAGIC, Func_RunScript(6), Func_RunScript(5)));

		g_SceneDB.m_SceneMap.insert(SceneMap::value_type(pScene->m_nID, pScene));
	}
}