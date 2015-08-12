#include "scenes_1.h"

#include <iostream>
#include <conio.h>
#include <stdlib.h>

#include "Util.h"
#include "MyCharacter.h"

PlayerCharacter g_PC;

namespace Scene
{
	bool __stdcall RunScript(const wchar_t* Script[], unsigned long dwMilliSeconds = 1000);

	// '\0' ���� �����ϴ� ���ڿ��� ���� �� ���� ���ڿ��� ����Ѵ�.	
	bool __stdcall RunScript(const wchar_t* Script[], unsigned long dwMilliSeconds)
	{
		int iStr = 0;

		bool ret = true;

		try
		{
			while (true)
			{
				const wchar_t* tmpStr = Script[iStr++];

				if (tmpStr[0] == L'\0')
				{
					break;
				}
				if (tmpStr[0] == L'\1')
				{
					wprintf(L"(enter...)\n");
					_getch();

				}
				else
				{
					wprintf(tmpStr);
					Console::Wait(dwMilliSeconds);
				}
			}
		}
		catch (const std::exception&)
		{
			ret = false;
		}

		return ret;
	}

	bool __stdcall RunScene1()
	{
		// InitCharacter
		g_PC.STR = 17;
		g_PC.AGL = 11;
		g_PC.INT = 9;
		g_PC.CON = 16;

		g_PC.HP = 8;

		// ����. ��Ȳ ����.
		{
			const wchar_t* strings[] =
			{
				L" ���� ���� ��Ӱ� ������ ���� �׿� �ִ�. ",
				L"���� �Ա����� �������� �̾��� ��θ� ���ϸ� ����� ���Ϸ� �� ���� �� �� �ֵ��� �Ǿ� �ִ�. ",
				L"�� �� �ִ� ���� �װ� �ϳ����� �� ���Ƽ� ����� �� �������� ���ϸ� ���㳪 �ٸ� ���Ͱ� �ִ��� ���� ��� ���ǰ� �ִ�.\n",
				L"\1",

				L" ���ڱ� ����� �� ���� ���δ�! ",
				L"����� ��ź��� Ű�� �۰�, ȸ�� �찯�� ���� ���� ������ó�� �����. ����� ����� ���� �Ҹ��� ������ Į�� �ֵѷ� �����ؿ´�! ",
				L"����� �� ������ ���ϰ� Į�� ��� �ֵθ���.\n",
				L"\1",

				L" ���� �� ����� �ٷ� �������� �ʾҴ���� ����� �׿� �̾߱⸦ �غ����� �� ���� �־��� ���̴�. ",
				L"������ ������ ��¿ �� ����. ",
				L"����� ��Ű�� ���ؼ� �ο� �� �ۿ� ����. \n",
				L"\1",
				L"\0"	// string end
			};

			if (false == RunScript(strings))
			{
				wprintf(L"error! RunScript error. [%s][%d]", TEXT(__FILE__), __LINE__);
				_getch();
			}
		}
		
		system("cls");
		wprintf(L"������� ����\n\n");

		// ������� ����
		while (true)
		{
			wprintf(L"(enter...)\n");

			_getch();

			// �ֻ����� ������.
			int d20 = rand() % 20 + 1;
			wprintf(L"\nd20: ");
			Console::Wait(1000);

			wprintf(L"%d!!\n", d20);
			Console::Wait(1000);

			if (d20 > 11)	// ����
			{
				const wchar_t* strings[] =
				{
					L"������� ������ �����ߴ�!\n",
					L"����� ����� ġ�� ����� �Ҹ��� ������ ��θ� ���� ���� ������ �޾Ƴ� ������. ",
					L"(������� ��ο� �������� �� �� �ִ�). ",
					L"\1",

					L"\0"
				};

				RunScript(strings);
				break;
			}
			else // ����
			{
				const wchar_t* strings[] =
				{
					L"����� ������ ��������.\n",
					L"����� ����� �����Ѵ�!\n",
					L"�׷��� ����� ������ ��������. ",

					L"\0"
				};

				RunScript(strings);
			}
		}
				
		return RunScene2();
	}

	bool __stdcall RunScene2()
	{
		Console::Wait(1000);
		system("cls");

		// ��2
		{
			const wchar_t* strings[] = 
			{
				L"[[��2]]\n",
				L" ����� ��� ���缭 �� ���¸� �� �� Ȯ���� �Ŀ� �ٽ� ���� ��θ� ���� ���ư���. ",
				L"�����̳� �ٸ� ���� ����. \n",
				L"\1",
				
				L" ��δ� ������ �� ���� ������ ���� �ִ�. ",
				L"�̷� ���� \"��\"�̶�� �θ���. ",
				L"����� ������ �ֳ� ���Ƿ��� ������ ���߸鼭 ���� ��� �� ������ ����. ",
				L"����� ���� �� �������� \"����\"�ϴ� �Ҹ��� �鸰��. ",
				L"�׸��� �ű⿡�� ���̰� ���� 3���ͳ� �Ǵ� �Ŵ��� ������ �ִ�! ",
				L"�� ������, �ٴڿ��� ���� ���� ��ȭ�� ��ȭ�� �׿� �ִ�.\n",
				L"\1",

				L"\0"
			};

			RunScript(strings);
		}

		system("cls");

		wprintf(L"����� ����!!!\n\n");

		// ����� ����
		int snake_HP = 3;
		bool bFirstRound = true;
		while (true)
		{
			wprintf(L"(enter...)\n");

			_getch();

			// �ֻ����� ������.
			int d20 = rand() % 20 + 1;
			wprintf(L"\nd20: ");
			Console::Wait(1000);

			wprintf(L"%d!!\n", d20);
			Console::Wait(1000);

			// �� �ൿ
			if (d20 >= 11)	// ����
			{
				const wchar_t* strings[] =
				{
					L"�쿡�� ����� ������ �����ߴ�!\n",
					L"���� 1�� ���ظ� �Ծ���!\n",
					L"\1",

					L"\0"
				};

				RunScript(strings);

				snake_HP -= 1;

				if (snake_HP <= 0)
				{
					break;
				}
			}
			else // ����
			{
				const wchar_t* strings[] =
				{
					L"����� ������ ��������.\n",
					L"\0"
				};

				RunScript(strings);
			}

			// ���� �ൿ
			if (bFirstRound)	// ù ���忡�� ���� ������ �����Ѵ�.
			{
				bFirstRound = false;

				const wchar_t* strings[] =
				{
					L"���� ����� �����Ѵ�!\n",
					L"���� ������ �����ߴ�!!",
					L"\0"
				};

				RunScript(strings);

				// �ߵ� �Ǿ����� üũ�Ѵ�.

			}
			else
			{
				const wchar_t* strings[] =
				{
					L"���� ����� �����Ѵ�!\n",
					L"�׷��� ���� ������ ��������. ",
					L"\0"
				};

				RunScript(strings);
			}
		}
		

		printf("\n");
		printf("\n");
		system("pause");

		return true;
	}
}