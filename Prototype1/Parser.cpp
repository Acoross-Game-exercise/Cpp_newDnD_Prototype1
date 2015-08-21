#include "Parser.h"

namespace Parser
{
	Token GetToken(const wchar_t* input)
	{
		if (input == nullptr)
		{
			return Token(nullptr, -1, nullptr);
		}

		int nPos = 0;
		while (true)
		{
			if (input[nPos] == L' ' || input[nPos] == L'\t')
			{
				++nPos;
			}
			else
			{
				break;	// L'\0' ����
			}
		}

		int nStartPos = nPos;
		const wchar_t* next = nullptr;
		while (true)
		{
			if (input[nPos] == L'\0')
			{
				break;
			}
			if (input[nPos] == L'/')
			{
				break;
			}
			else if (input[nPos] == L',')
			{
				next = &input[nPos + 1];
				break;
			}

			++nPos;
		}

		return Token(&input[nStartPos], nPos, next);	// L'\0' ���� ������ next = nullptr;
	}

	std::wstring ParseStr(Token& token)
	{
		return std::wstring(token.wcsToken, token.nLength);
	}

	int ParseInt(Token& token)
	{
		return std::wcstol(token.wcsToken, nullptr, 10);
	}
}