//������Ӧֲ���ս��ʬ�������ܿ�ݼ�

#include<Windows.h>

//��Ӧ����еĺ�
#define ID_CD		  1					//��ȴ
#define ID_SUN		  2					//����
#define ID_MONEY	  3					//���
#define ID_PLANT	  10				//��ֲ��
#define ID_AUTO		  12				//�Զ��ռ�
#define ID_BOOM		  13				//ȫ��ӣ��ը��
#define ID_SHUPAI	  20				//������ֲ
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
		//�����������ڲ�����Ϸ���ڣ������ذ�����Ϣ
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
	//����Ϣ������һ�����ӣ�������Ϣ����ԭ���Ĵ��ڣ�û����һ����󴰿��ղ���������Ϣ�����°������޷�Ӧ
	return CallNextHookEx(hook, code, wParam, lParam);
	//MessageBox(NULL, TEXT("����Ϣ"), TEXT("��ʾ"), MB_OK);
}