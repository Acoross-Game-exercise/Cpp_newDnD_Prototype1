// ScannerDefine �� �����ϱ� ���� ����ϴ� macro
// ���� ���Ͽ����� #define token_list ��ũ�θ� �����Ѵ�.
// �����Ϸ��� ScannerDefine struct �� ���ο� �� ������ include �Ѵ�.
	// #include "..\ScannerImplMacro.inc"

#define add_token(type, rex) type
	enum TokenType
	{
		token_list
	};
#undef add_token
	typedef TokenDefine<TokenType> _TkDef;

	// ��� ������ Token�� regex �� ����.
#define add_token(type, rex) {type, rex}
	static const _TkDef& GetTokenDefine(TokenType type) 
	{
		static const _TkDef TokenDefines[] = 
		{ 
			token_list
		};
		return TokenDefines[type];
	}
#undef add_token

#define add_token(type, rex) L#type
	static const wchar_t* TokenToName(TokenType type) {
		static const wchar_t* nameMap[] = 
		{ 
			token_list 
		};
		return nameMap[type];
	}
#undef add_token