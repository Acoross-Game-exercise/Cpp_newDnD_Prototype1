#include "Scene.h"
#include "SceneFunctions.h"

namespace Scene
{
	CScene::CScene()
	{
	}

	CScene::~CScene()
	{
	}

	void CScene::Run()
	{
		for (auto it = m_SceneFuncList.begin(); it != m_SceneFuncList.end(); ++it)
		{
			RunSceneFunc(*it);
		}
	}
}