#ifndef _MY_UTIL_
#define _MY_UTIL_

#include <Windows.h>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>

#ifdef _DEBUG
#define DEFAULT_WAIT 100
#else
#define DEFAULT_WAIT 800
#endif

namespace Console
{
	void Wait(unsigned long dwMilliSeconds = DEFAULT_WAIT);
}

namespace Script
{
	typedef std::vector<std::wstring> ScriptData;

	class Scene
	{
	public:
		int m_nID;
		ScriptData m_Script;
	};

	typedef std::unordered_map<int, Scene*> SceneMap;

	class ScriptDB
	{
	public:
		bool Load(wchar_t* filename);
		SceneMap m_sceneMap;

	};

	void Pause();
	void Pause(wchar_t const* const _Format, ...);
	bool RunFormattedScript(wchar_t const* const _Format, ...);
	bool __stdcall RunScript(const wchar_t* Script[], unsigned long dwMilliSeconds = DEFAULT_WAIT);
}

namespace Dice
{
	int D20();
}

#endif