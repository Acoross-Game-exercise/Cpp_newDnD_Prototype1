#pragma once

#include <list>
#include <functional>

namespace Scene
{
	typedef std::function<bool(void)> SceneFunc;

	class CScene
	{
	public:
		int m_nID;
		std::list<SceneFunc> m_SceneFuncList;

		CScene();
		virtual ~CScene();

		void Run();
	};
}