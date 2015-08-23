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

		// SetData from data, and clear data.
		void SetData(CScene& data)
		{
			m_nID = data.m_nID;
			data.m_nID = 0;

			m_SceneFuncList.swap(data.m_SceneFuncList);
		}

		CScene();
		virtual ~CScene();

		void Run();
	};
}