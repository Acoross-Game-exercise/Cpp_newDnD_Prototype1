#ifndef _SCRIPT_DB_
#define _SCRIPT_DB_

#include <vector>
#include <string>
#include <unordered_map>

#include "Util.h"

namespace Script
{
	// Scene begin ///////////////
	typedef std::vector<std::wstring> ScriptData;

	class CScene
	{
	public:
		int m_nID;
		ScriptData m_Script;
	};
	// Scene end /////////////////
	

	// ScriptDB begin ////////////
	typedef std::unordered_map<int, CScene*> SceneMap;

	class ScriptDB
	{
	public:
		bool Load(wchar_t* filename);
		SceneMap m_sceneMap;

		virtual ~ScriptDB()
		{
			for (auto it = m_sceneMap.begin(); it != m_sceneMap.end(); ++it)
			{
				delete it->second;
			}
		}
	};

	extern ScriptDB g_ScriptDB;

	// ScriptDB end /////////////
	
	bool __stdcall RunScript(int nNum);
	bool __stdcall RunScript(ScriptData& sd, unsigned long dwMilliSeconds = DEFAULT_WAIT);
}

#endif