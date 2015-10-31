#ifndef _SCRIPT_DB_
#define _SCRIPT_DB_

#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

#include "Util.h"

#include "../RecurrentDescentParser/Parser/RDParser.h"

namespace Script
{
	// Scene begin ///////////////
	typedef std::vector<std::wstring> ScriptData;

	class CScene
	{
	public:
		int m_nID;
		ScriptData m_Script;

		// SetData from data, and clear data.
		void SetData(CScene& data)
		{
			m_nID = data.m_nID;
			data.m_nID = 0;

			m_Script.swap(data.m_Script);
		}
	};
	// Scene end /////////////////
	

	// ScriptDB begin ////////////
	typedef std::unordered_map<int, CScene*> SceneMap;

	class ScriptDB
	{
	public:
		bool Load(const wchar_t* const filename);
		bool Load2(const wchar_t* const filename);
		bool Load3(const wchar_t* const filename);

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


	class CScriptParser
	{
	public:
		///////////////////////////////
		// IMPL 
		SCANNERDEF_BEGIN(ScannerDefine)
		{
			/*add_token(TK_NULL, nullptr), \
			*/
#define token_list  \
	add_token(COMMENT, L"//(.*)"),	\
	add_token(LINEEND, L"[\r\n]+"),	\
	add_token(SE, L"@send"),	\
	add_token(SB, L"@s[ \t]+"),	\
	add_token(DIGIT, L"(-)?[1-9]([0-9]*)([ \t]*)"), \
	add_token(ANYWORD, L"([^\r\n]+)"), \
	add_token(TK_MAX, nullptr)

#include "../RecurrentDescentParser/Scanner/ScannerImplMacro.inc"

#undef token_list
		}
		SCANNERDEF_END;

		using TokenType = ScannerDefine::TokenType;
		using Scanner = Scanner<ScannerDefine>;
		using MyParserType = CRDParser<Scanner>;

	public:
		CScriptParser() = default;
		~CScriptParser() = default;
		NO_COPY(CScriptParser);

	public:
		bool Parse(wchar_t* buf)
		{
			m_RDParser.input = buf;
			m_RDParser.input_token = Scanner::Scan(m_RDParser.input);

			return scriptdata();
		}

		bool scriptdata();
		bool sbegin();
		bool line();
		bool send();

	private:
		MyParserType m_RDParser;
		CScene m_scene;
	};
}

#endif