#pragma once

#include <unordered_map>

namespace Scene
{
	class CScene;

	typedef std::unordered_map<int, Scene::CScene*> SceneMap;

	class SceneDB
	{
	public:
		std::unordered_map<int, Scene::CScene*> m_SceneMap;
		SceneDB();
		virtual ~SceneDB();
	};

	extern SceneDB g_SceneDB;

	void InitSceneDB_test();
}