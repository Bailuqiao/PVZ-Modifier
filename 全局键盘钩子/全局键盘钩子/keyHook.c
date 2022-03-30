//用于响应植物大战僵尸辅助功能快捷键

#include<Windows.h>

//对应外挂中的宏
#define ID_CD		  1					//冷却
#define ID_SUN		  2					//阳光
#define ID_MONEY	  3					//金币
#define ID_PLANT	  10				//叠植物
#define ID_AUTO		  12				//自动收集
#define ID_BOOM		  13				//全屏樱桃炸弹
#define ID_SHUPAI	  20				//竖排种植
#define ID_FUTURE                       40007
#define ID_MUSTACHE                     40009
#define ID_TRICKEDOUT                   40010
#define ID_DAISIES                      40013
#define ID_DANCE                        40015
#define ID_PINATA                       40018
#define ID_SOUND                        40019


LRESULT CALLBACK Hookproc(int code, WPARAM wParam, LPARAM lParam);
HHOOK hook;

__declspec(dllexport)
HHOOK SetKeyHook()
{
	hook = SetWindowsHookEx(WH_KEYBOARD, Hookproc, GetModuleHandle(TEXT("keyHook")), NULL);
	return hook;
}

__declspec(dllexport)
int DeleteHook()
{
	return UnhookWindowsHookEx(hook);
}


LRESULT CALLBACK Hookproc(int code, WPARAM wParam, LPARAM lParam)
{
	HWND hwnd;

	if (code < 0 || code == HC_NOREMOVE)
	{
		return CallNextHookEx(hook, code, wParam, lParam);
	}

	hwnd = FindWindow(TEXT("MainWindow"), NULL);
	if (hwnd == NULL || hwnd != GetActiveWindow())
	{
		//若按按键窗口不是游戏窗口，则不拦截按键消息
		return CallNextHookEx(hook, code, wParam, lParam);
	}
	if (lParam & 0x40000000)
	{
		return CallNextHookEx(hook, code, wParam, lParam);
	}

	hwnd = FindWindow(TEXT("PVZKJ"), NULL);
	switch (wParam)
	{
	case 'Q':
		if (GetKeyState(VK_CONTROL) < 0)
			SendMessage(hwnd, WM_COMMAND, ID_CD, 0);
		break;
	case 'W':
		if (GetKeyState(VK_CONTROL) < 0)
			SendMessage(hwnd, WM_COMMAND, ID_SUN, 0);
		break;
	case 'S':
		if (GetKeyState(VK_CONTROL) < 0)
			SendMessage(hwnd, WM_COMMAND, ID_MONEY, 0);
		break;
	case 'A':
		if (GetKeyState(VK_CONTROL) < 0)
			SendMessage(hwnd, WM_COMMAND, ID_PLANT, 0);
		break;
	case 'B':
		if (GetKeyState(VK_CONTROL) < 0)
			SendMessage(hwnd, WM_COMMAND, ID_BOOM, 0);
		break;
	case 'D':
		if (GetKeyState(VK_CONTROL) < 0)
			SendMessage(hwnd, WM_COMMAND, ID_AUTO, 0);
		break;
	case'X':
		if (GetKeyState(VK_CONTROL) < 0)
			SendMessage(hwnd, WM_COMMAND, ID_SHUPAI, 0);
		break;


	case '1':
		if (GetKeyState(VK_CONTROL) < 0)
			SendMessage(hwnd, WM_COMMAND, ID_FUTURE, 0);
		break;
	case '2':
		if (GetKeyState(VK_CONTROL) < 0)
			SendMessage(hwnd, WM_COMMAND, ID_MUSTACHE, 0);
		break;
	case '3':
		if (GetKeyState(VK_CONTROL) < 0)
			SendMessage(hwnd, WM_COMMAND, ID_TRICKEDOUT, 0);
		break;
	case '4':
		if (GetKeyState(VK_CONTROL) < 0)
			SendMessage(hwnd, WM_COMMAND, ID_DAISIES, 0);
		break;
	case '5':
		if (GetKeyState(VK_CONTROL) < 0)
			SendMessage(hwnd, WM_COMMAND, ID_DANCE, 0);
		break;
	case '6':
		if (GetKeyState(VK_CONTROL) < 0)
			SendMessage(hwnd, WM_COMMAND, ID_PINATA, 0);
		break;
	case '7':
		if (GetKeyState(VK_CONTROL) < 0)
			SendMessage(hwnd, WM_COMMAND, ID_SOUND, 0);
		break;
	}
	//将消息传给下一个钩子，即将消息还给原来的窗口，没有这一句最后窗口收不到按键消息，导致按键后无反应
	return CallNextHookEx(hook, code, wParam, lParam);
	//MessageBox(NULL, TEXT("有消息"), TEXT("提示"), MB_OK);
}