//´úÌæÊÖÊäÈëÃØ¼®
#include "head.h"

void Future(HWND hwnd)
{
	char ch[6] = { 'F', 'U', 'T', 'U', 'R', 'E' };
	int i = 0;
	for (i = 0; i < 6; i++)
	{
		SendMessage(hwnd, WM_KEYDOWN, ch[i], 0);
		Sleep(1);
	}
}

void Mustache(HWND hwnd)
{
	char ch[8] = { 'M','U','S','T','A','C','H','E' };
	int i = 0;
	for (i = 0; i < 8; i++)
	{
		SendMessage(hwnd, WM_KEYDOWN, ch[i], 0);
		Sleep(1);
	}
}

void Trickedout(HWND hwnd)
{
	char ch[10] = { 'T', 'R', 'I', 'C', 'K', 'E', 'D', 'O','U','T' };
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		SendMessage(hwnd, WM_KEYDOWN, ch[i], 0);
		Sleep(1);
	}

}

void Daisies(HWND hwnd)
{
	//daisies 
	char ch[] = { 'D', 'A', 'I', 'S', 'I', 'E', 'S' };
	int i = 0;
	for (i = 0; i < 7; i++)
	{
		SendMessage(hwnd, WM_KEYDOWN, ch[i], 0);
		Sleep(1);
	}
}

void Dance(HWND hwnd)
{
	char ch[] = { 'D', 'A', 'N', 'C', 'E'};
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		SendMessage(hwnd, WM_KEYDOWN, ch[i], 0);
		Sleep(1);
	}

}

void Pinata(HWND hwnd)
{
	char ch[] = { 'P', 'I', 'N', 'A', 'T', 'A' };
	int i = 0;
	for (i = 0; i < 6; i++)
	{
		SendMessage(hwnd, WM_KEYDOWN, ch[i], 0);
		Sleep(1);
	}

}

void Sukhbir(HWND hwnd)
{

	char ch[] = { 'S', 'U', 'K', 'H', 'B', 'I','R'};
	int i = 0;
	for (i = 0; i < 7; i++)
	{
		SendMessage(hwnd, WM_KEYDOWN, ch[i], 0);
		Sleep(1);
	}
}