
#include"head.h"


//����ר��ȫ�ּ��̹���
#pragma comment(lib,"keyHook.lib")
HHOOK SetKeyHook();
int DeleteHook();


//��ť�ؼ�ID
#define ID_CD		  1					//��ȴ
#define ID_SUN		  2					//����
#define ID_MONEY	  3					//���
#define ID_WISDOMTREE 5					//�ǻ���
#define ID_TREEGO     6					//�޸�
#define ID_LEVEL	  7					//ѡ��
#define ID_JUMP		  8					//��
#define ID_CLEAR      9					//Ǯ����
#define ID_PLANT	  10				//��ֲ��
#define ID_BACKSTAGE  11				//����ͣ
#define ID_AUTO		  12				//�Զ��ռ�
#define ID_BOOM		  13				//ȫ��ӣ��ը��
#define ID_POTATOMINE 14				//��������
#define ID_CHOMPER    15				//���컨
#define ID_DOOMSHROOM 16				//����
#define ID_SUNSHROOM  17				//���⹽
#define ID_MAGSHROOM  18				//������
#define ID_COBCANNON  19				//���׼�ũ��
#define ID_SHUPAI	  20				//������ֲ
#define ID_ZKWXZ	  30				//�Ͽ�
#define ID_DPWX		  31				//����
#define ID_NOSLEEP	  32				//Ģ���⻽��
#define ID_TALLNUT	  33				//�߽����ѹ�
#define ID_NUT		  34				//С����˵�

#define IDE_PX		  21
#define IDE_PY		  22
#define IDC_PID		  23
#define IDE_ZX		  24
#define IDE_ZY		  25
#define IDC_ZID		  26
#define IDC_TYPE	  27
#define ID_CALLP	  28
#define ID_CALLZ	  29


//��ʱ��ID
#define ID_TIMER      1					//���������Ϸ�Ƿ�ر�

//��Ϸ���
HWND hGame = NULL;

TCHAR *PlantStr[] = { TEXT("�㶹����"), TEXT("���տ�"), TEXT("ӣ��ը��"), TEXT("���ǽ"), TEXT("������"),
TEXT("��������"), TEXT("���컨"), TEXT("˫������"), TEXT("С�繽"), TEXT("���⹽"), TEXT("���繽"), TEXT("Ĺ��������"),
TEXT("�Ȼ�"), TEXT("��С��"), TEXT("������"), TEXT("����"), TEXT("˯��"), TEXT("�ѹ�"), TEXT("��������"), TEXT("���ƺ���"),
TEXT("������"), TEXT("�ش�"), TEXT("�����׮"), TEXT("�߼��"), TEXT("��Ģ��"), TEXT("·�ƻ�"), TEXT("������"),
TEXT("��Ҷ��"), TEXT("�Ѽ�����"), TEXT("����"), TEXT("�Ϲ�ͷ"), TEXT("������"), TEXT("���Ĳ�Ͷ��"), TEXT("����"),
TEXT("����Ͷ��"), TEXT("���ȶ�"), TEXT("����"), TEXT("Ҷ�ӱ���ɡ"), TEXT("��յ��"), TEXT("����Ͷ��"), TEXT("��ǹ����"),
TEXT("˫�����տ�"), TEXT("������"), TEXT("����"), TEXT("����"), TEXT("�����"), TEXT("�ش���"), TEXT("���׼�ũ��"),
TEXT("����˫������"), TEXT("��ը���"), TEXT("�޴���") };

TCHAR *ZombieStr[] = { TEXT("��ͨ"), TEXT("ҡ��"), TEXT("·��"), TEXT("�Ÿ�"), TEXT("��Ͱ"),
TEXT("����"), TEXT("��դ��"), TEXT("�����"), TEXT("����"), TEXT("����"), TEXT("Ѽ��"), TEXT("Ǳˮ"), TEXT("����"),
TEXT("ѩ��"), TEXT("����"), TEXT("С��"), TEXT("����"), TEXT("��"), TEXT("����"), TEXT("ѩ��"), TEXT("�ļ�"),
TEXT("����"), TEXT("����"), TEXT("����"), TEXT("С��"), TEXT("����"), TEXT("�㶹"), TEXT("���"),
TEXT("����"), TEXT("��ǹ"), TEXT("�ѹ�"), TEXT("�߼��"), TEXT("����") };

LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

struct AddrAndFree
{
	LPVOID addr;
	int needWrite;
}plant = { NULL, 0 }, zombie = { NULL, 0 }, tallNut = { NULL, 0 }, nut = { NULL, 0 }, allNut = { NULL, 1 };




//��Ϸ���̾����ͬʱ�øñ����ж���Ϸ�Ƿ��
HANDLE hGameP = NULL;


//�����Ϸ�����Ƿ�򿪳ɹ�,�ɹ����ؽ��̾�������򷵻�NULL
HANDLE CheckProcessOn();

//�޸���ȴ
void WuLengQu(HWND);

//�޸�����
int Sun();

//�޸Ľ��
int Money();

//�ǻ����߶�
int WisdomTree(HWND hwnd);

//����
int Jump(HWND hwnd);

//Ǯ����
int ClearMoney();

//��ֲ��
void Plant(HWND);

//����ͣ
void Backstage(HWND);

//�Զ����ַ�����ȽϺ���
int StrCmp(char str1[], char str2[], int num);

//����ر�ǰ�Ĵ�����
void End(HWND);

//�Զ��ռ�
void Auto(HWND);

//ȫ��ӣ��ը��
int Boom();

//��������
void PotatoMine(HWND);

//���컨
void Chomper(HWND);

//����
void DoomShroom(HWND);

//���⹽
void SunShroom(HWND);

//������
void MagShroom(HWND);

//���׼�ũ��
void CobCannon(HWND);

//��������ֲ
void ShuPai(HWND);

//��ֲ��
void CallP(HWND);

//�ֽ�ʬ
void CallZ(HWND);

//�Ͽ�
void ZKWXZ(HWND);

//����
void DPWX(HWND);

//Ģ���⻽��
void NoSleep(HWND);

//�߽����ѹ�
void TallNut(HWND);

//С�����˵�
void Nut(HWND);

//д����������ֲ��Ĵ���
void WriteNut();

int CallPlant(int x, int y, int id);
int CallZombie(int x, int y, int id);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("PVZKJ");
	HWND hwnd;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WinProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0x9b,0x8f,0xf1));
	wndclass.lpszMenuName = (LPCWSTR)IDR_MENUmain;
	wndclass.lpszClassName = szAppName;
	
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("���������Ҫ�� Windows NT �������У�"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName,
		TEXT("ֲ���ս��ʬ���İ����"),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		4*1080/11,		//���ڿ�
		4*1220/11,		//���ڸ�
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	hGameP = CheckProcessOn();
	if (hGameP == NULL)
	{
		MessageBox(hwnd, TEXT("��Ϸδ��"), TEXT("����"), MB_OK | MB_ICONEXCLAMATION);
	}
	

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return msg.wParam;
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	static int x;
	HDC hdc,mdc;
	PAINTSTRUCT ps;
	HBITMAP bmp;
	int i;


	switch (message)
	{
	case WM_CREATE:

		//���ü��̹������ڿ�ݼ�
		SetKeyHook();

		SetTimer(hwnd, ID_TIMER, 500, NULL);

		x = LOWORD(GetDialogBaseUnits());		//����x=8
		
		RECT rcWindow, rcClinet;
		int winX, winY;
		GetWindowRect(hwnd, &rcWindow);
		GetClientRect(hwnd, &rcClinet);
		winX = rcWindow.right - rcWindow.left - (rcClinet.right - rcClinet.left) + 72*x;
		winY = rcWindow.bottom - rcWindow.top - (rcClinet.bottom - rcClinet.top) + 53*x;
		MoveWindow(hwnd, (GetSystemMetrics(SM_CXSCREEN) - winX) / 2, (GetSystemMetrics(SM_CYSCREEN) - winY) / 2, winX, winY, TRUE);


		CreateWindow(TEXT("button"), TEXT("��������ȴ(Q)"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				x, x, 20 * x, 4*x,
				hwnd, (HMENU)ID_CD,
				((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("+1000����(W)"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			25 * x, x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_SUN,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("+50,000���(S)"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			25 * x, 6*x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_MONEY,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("Edit"), NULL,
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			x, 13 * x, 12 * x, (int)(2.8*x),
			hwnd, (HMENU)ID_WISDOMTREE,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("�޸�"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			14 * x, 13 * x, 6 * x, (int)(2.8*x),
			hwnd, (HMENU)ID_TREEGO,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("Edit"), NULL,
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			25 * x, 13 * x, 10 * x, (int)(2.8*x),
			hwnd, (HMENU)ID_LEVEL,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("GO"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			36 * x, 13 * x, 8 * x, (int)(2.8*x),
			hwnd, (HMENU)ID_JUMP,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("̫�����ˣ��Ұ����Ǯ����հ�"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			6 * x, 48*x, 35 * x, 4 * x,
			hwnd, (HMENU)ID_CLEAR,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("������̨����ͣ"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			6 * x, 43*x, 35 * x, 4 * x,
			hwnd, (HMENU)ID_BACKSTAGE,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("��������ֲ��(A)"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			x, 6 * x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_PLANT,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("�����Զ��ռ�(D)"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			25 * x, 17 * x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_AUTO,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("�ؼ���BOOM(B)"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			25 * x, 22 * x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_BOOM,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("����������ֲ(X)"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			25 * x, 27 * x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_SHUPAI,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("��������"),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			2*x, 18 * x, 15 * x, 3 * x,
			hwnd, (HMENU)ID_POTATOMINE,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("���컨"),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			2 * x, 21 * x, 15 * x, 3 * x,
			hwnd, (HMENU)ID_CHOMPER,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("����"),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			2 * x, 24 * x, 15 * x, 3 * x,
			hwnd, (HMENU)ID_DOOMSHROOM,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("���⹽"),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			2 * x, 27 * x, 15 * x, 3 * x,
			hwnd, (HMENU)ID_SUNSHROOM,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("������"),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			2 * x, 30 * x, 15 * x, 3 * x,
			hwnd, (HMENU)ID_MAGSHROOM,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("���׼�ũ��"),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			2 * x, 33 * x, 15 * x, 3 * x,
			hwnd, (HMENU)ID_COBCANNON,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("Edit"), NULL,
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			25 * x, 32 * x, 7 * x, (int)(2.8*x), hwnd, (HMENU)IDE_PX, ((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		CreateWindow(TEXT("Edit"), NULL,
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			36 * x, 32 * x, 7 * x, (int)(2.8*x), hwnd, (HMENU)IDE_PY, ((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		CreateWindow(TEXT("COMBOBOX"), TEXT("PID"),
			WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL,
			47 * x, 32 * x, 14 * x, 22 * x, hwnd, (HMENU)IDC_PID, ((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		for (i = 0; i < sizeof(PlantStr) / sizeof(PlantStr[0]); i++)
			SendMessage(GetDlgItem(hwnd, IDC_PID), CB_INSERTSTRING, i, PlantStr[i]);
		
		CreateWindow(TEXT("button"), TEXT("��ֲ��"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			62 * x, 32 * x, 6 * x, 3 * x,
			hwnd, (HMENU)ID_CALLP,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("Edit"), NULL,
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			25 * x, 36 * x, 7 * x, (int)(2.8*x), hwnd, (HMENU)IDE_ZX, ((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		CreateWindow(TEXT("Edit"), NULL,
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			36 * x, 36 * x, 7 * x, (int)(2.8*x), hwnd, (HMENU)IDE_ZY, ((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		CreateWindow(TEXT("COMBOBOX"), TEXT("ZID"),
			WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL,
			47 * x, 36 * x, 14 * x, 22 * x, hwnd, (HMENU)IDC_ZID, ((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		for (i = 0; i < sizeof(ZombieStr) / sizeof(ZombieStr[0]); i++)
			SendMessage(GetDlgItem(hwnd, IDC_ZID), CB_INSERTSTRING, i, ZombieStr[i]);

		CreateWindow(TEXT("button"), TEXT("�ֽ�ʬ"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			62 * x, 36 * x, 6 * x, 3 * x,
			hwnd, (HMENU)ID_CALLZ,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("�����Ͽ�������(E)"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			49 * x, x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_ZKWXZ,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("�������޶���"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			49 * x, 6*x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_DPWX,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("����Ģ���⻽��"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			49 * x, 11 * x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_NOSLEEP,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("�߼���ѹ�"),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			49 * x, 17 * x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_TALLNUT,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("С����˵�"),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			49 * x, 23 * x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_NUT,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		return 0;
	case WM_TIMER:
		
		hGameP = CheckProcessOn();

		return 0;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDM_SX:
			MessageBox(hwnd, TEXT("�������⣬Ŀǰ����ô�㹦�ܡ�\n����Գ�������Ϸ���ڰ���Ctrl+7����Ҳ��һ��С�ʵ�����������ʵ�ֻ������������Ϸʧȥ�����ǲ����������ģ����Ծ�û���������ť��"), TEXT("����Ҳ̫���˰�"), MB_OK);
			return 0;
		case IDM_GY:
			//�ٺ�
			MessageBox(hwnd, TEXT("���������������ɱ���������C���Գ�ѧ�߽���ʹ�ã�\nʹ�ñ����������һ�з��������뱾�����޹ء�"), TEXT("����"), MB_OK | MB_ICONEXCLAMATION);
			return 0;
		case IDM_TS:
			MessageBox(hwnd, TEXT("1.������ֵ����9990ʱ���ռ������ʹ�����Ϊ���ֵ��9990����\n2.����ҳ���999,990ʱ�����ѻ��߻�ý�һ�ʹ��ұ�Ϊ���ֵ��999,990����\n3.����ʱ�����̺�ʳ�˻������⹽���������׵���Ҫʱ��׼��/�����ֲ�ﶼ��˲����ɣ����ѹϣ��ش̻�ʧЧ��û���˺�����\n4.����������ַ��ǿ�ݼ�������Ϸ�����а���ctrl+����������ַ����ɡ�\n5.����ʹ�ø�����ʹ��Ϸʧȥ��Ȥ���Լ����á�\n6.����ͼƬ��Դ��΢�Ź��ں�roco����������Ƶġ�Ӿװ���������Ͻ����á�"), TEXT("��ʾ"), MB_OK);
			return 0;
		}

		if (CheckProcessOn() == NULL)
		{
			MessageBox(hwnd, TEXT("��Ϸδ�򿪣������Ϸ��������"), TEXT("��ܰ��ʾ"), MB_OK | MB_ICONEXCLAMATION);
			return 0;
		}

		switch (LOWORD(wParam))
		{
		case ID_FUTURE:
			Future(hGame);
			break;
		case ID_MUSTACHE:
			Mustache(hGame);
			break;
		case ID_TRICKEDOUT:
			Trickedout(hGame);
			break;
		case ID_DAISIES:
			Daisies(hGame);
			break;
		case ID_DANCE:
			Dance(hGame);
			break;
		case ID_PINATA:
			Pinata(hGame);
			break;
		case ID_SOUND:
			Sukhbir(hGame);
			break;

		case ID_CD:
			WuLengQu(hwnd);
			break;
		case ID_SUN:
			Sun();
			break;
		case ID_MONEY:
			Money();
			break;
		case ID_TREEGO:
			WisdomTree(hwnd);
			break;
		case ID_JUMP:
			Jump(hwnd);
		case ID_CLEAR:
			ClearMoney();
			break;
		case ID_PLANT:
			Plant(hwnd);
			break;
		case ID_BACKSTAGE:
			Backstage(hwnd);
			break;
		case ID_AUTO:
			Auto(hwnd);
			break;
		case ID_BOOM:
			Boom();
			break;
		case ID_POTATOMINE:
			PotatoMine(hwnd);
			break;
		case ID_CHOMPER:
			Chomper(hwnd);
			break;
		case ID_DOOMSHROOM:
			DoomShroom(hwnd);
			break;
		case ID_MAGSHROOM:
			MagShroom(hwnd);
			break;
		case ID_COBCANNON:
			CobCannon(hwnd);
			break;
		case ID_SUNSHROOM:
			SunShroom(hwnd);
			break;
		case ID_SHUPAI:
			ShuPai(hwnd);
			break;
		case ID_CALLP:
			CallP(hwnd);
			break;
		case ID_CALLZ:
			CallZ(hwnd);
			break;
		case ID_DPWX:
			DPWX(hwnd);
			break;
		case ID_ZKWXZ:
			ZKWXZ(hwnd);
			break;
		case ID_NOSLEEP:
			NoSleep(hwnd);
			break;
		case ID_TALLNUT:
			TallNut(hwnd);
			break;
		case ID_NUT:
			Nut(hwnd);
			break;
		}

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		//������
		mdc = CreateCompatibleDC(hdc);
		bmp = LoadBitmap((HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDB_BITMAP1));
		SelectObject(mdc, bmp);
		BitBlt(hdc, 0, 0, 47 * x, 53 * x, mdc, 0, 0, SRCCOPY);

		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, x, 11 * x, TEXT("�޸��ǻ����߶�"), 7);
		TextOut(hdc, 25 * x, 11 * x, TEXT("ð��ģʽ���أ�1-50��"), 12);

		TextOut(hdc, 33 * x, (int)(32.5 * x), TEXT("��"), 1);
		TextOut(hdc, 44 * x, (int)(32.5 * x), TEXT("��"), 1);
		TextOut(hdc, 33 * x, (int)(36.5 * x), TEXT("��"), 1);
		TextOut(hdc, 44 * x, (int)(36.5 * x), TEXT("��"), 1);

		//ʱ��������
		HBRUSH hBrush, oldHBrush;
		hBrush = (HBRUSH)CreateSolidBrush(RGB(0xf0, 0xf0, 0xf0));
		oldHBrush = SelectObject(hdc, hBrush);
		HPEN hPen, oldHPen;
		hPen = CreatePen(PS_SOLID, 1, RGB(0xf0, 0xf0, 0xf0));
		oldHPen = SelectObject(hdc, hPen);
		Rectangle(hdc, x, 17 * x, 20 * x, 36 * x);

		DeleteObject(SelectObject(hdc, oldHBrush));
		DeleteObject(SelectObject(hdc, oldHPen));

		TextOut(hdc, 5 * x, 16 * x, TEXT("ʱ��������"), 5);

		DeleteObject(bmp);
		DeleteDC(mdc);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:

		//�������Ĵ���
		End(hwnd);
		
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}


HANDLE CheckProcessOn()
{
	hGame = FindWindow(TEXT("MainWindow"), NULL);
	if (hGame == NULL)
	{
		plant.needWrite = 1;
		zombie.needWrite = 1;
		tallNut.needWrite = 1;
		return NULL;
	}

	DWORD dwPID;
	GetWindowThreadProcessId(hGame, &dwPID);
	if (dwPID == 0)
	{
		return NULL;
	}

	HANDLE handl = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
	if (handl == NULL)
	{
		return NULL;
	}
	return handl;
}

//�޸���ȴ
void WuLengQu(HWND hwnd)
{
	
	HWND hChildnd = GetDlgItem(hwnd, ID_CD);
	char cd = '0';
	ReadProcessMemory(hGameP, (LPVOID)0x00487296, &cd, 1, NULL);
	if (cd == 0x7e)
	{
		cd = 0x70;
		WriteProcessMemory(hGameP, (LPVOID)0x00487296, &cd, 1, NULL);
		SetWindowText(hChildnd, TEXT("�ر�����ȴ(Q)"));
	}
	else
	{
		cd = 0x7e;
		WriteProcessMemory(hGameP, (LPVOID)0x00487296, &cd, 1, NULL);
		SetWindowText(hChildnd, TEXT("��������ȴ(Q)"));
	}
	
}



int Sun()
{
	//��ǰ����ֵ
	int sunNum = 0;

	DWORD buff1 = 0x6A9EC0;			//��ַ
	DWORD buff2;

	ReadProcessMemory(hGameP, (void*)buff1, &buff2, 4, NULL);
	ReadProcessMemory(hGameP, (void*)(buff2 + 0x768), &buff1, 4, NULL);

	if (buff1 == 0 || buff2 == 0)
	{
		return 0;
	}

	ReadProcessMemory(hGameP, (void*)(buff1 + 0x5560), &sunNum, 4, NULL);
	sunNum = sunNum + 1000;
	WriteProcessMemory(hGameP, (void*)(buff1 + 0x5560), &sunNum, 4, NULL);


	return 1;
}


int Money()
{
	//��ǰ�Ľ��ֵ
	int money = 0;
	DWORD buff1 = 0x6A9EC0;			//��ַ
	DWORD buff2;

	ReadProcessMemory(hGameP, (void*)buff1, &buff2, 4, NULL);
	ReadProcessMemory(hGameP, (void*)(buff2 + 0x82c), &buff1, 4, NULL);

	if (buff1 == 0 || buff2 == 0)
	{
		return 0;
	}

	ReadProcessMemory(hGameP, (void*)(buff1 + 0x28), &money, 4, NULL);
	money = money + 5000;
	WriteProcessMemory(hGameP, (void*)(buff1 + 0x28), &money, 4, NULL);

	return 1;
}

#if(0)
void TallNut(HWND hwnd)
{
	char str1[] = { 0x8B, 0x77, 0x40, 0x8D, 0x0C, 0x40, 0x83, 0x7f, 0x24, 0x17, 0x0F, 0x85 };
	char str2[] = { 0x81, 0x7F, 0x40, 0x2C, 0x01, 0x00, 0x00, 0x0F, 0x87 };
	char str3[] = { 0xC7, 0x47, 0x40, 0x40, 0x1F, 0x00, 0x00, 0xC7, 0x47, 0x24, 0x11, 0x00, 0x00, 0x00, 0xE9 };
	char str4[] = { 0xE9, 0x90 };
	char str5[] = { 0x8B, 0x77, 0x40, 0x8D, 0x0C, 0x40 };
	int temp = 0;
	char now = '0';

	if (tallNut.addr == NULL)
	{
		tallNut.needWrite = 1;
	}

	if (tallNut.needWrite)
	{
		tallNut.addr = VirtualAllocEx(hGameP, NULL, 48, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

		WriteProcessMemory(hGameP, tallNut.addr, str1, sizeof(str1), NULL);
		temp = (int)(0x464529 - ((DWORD)tallNut.addr + 0x10));
		WriteProcessMemory(hGameP, (LPVOID)((DWORD)tallNut.addr + 0xC), &temp, 4, NULL);

		WriteProcessMemory(hGameP, ((DWORD)tallNut.addr + 0x10), str2, sizeof(str2), NULL);
		temp = (int)(0x464529 - ((DWORD)tallNut.addr + 0x1D));
		WriteProcessMemory(hGameP, (LPVOID)((DWORD)tallNut.addr + 0x19), &temp, 4, NULL);

		WriteProcessMemory(hGameP, (LPVOID)((DWORD)tallNut.addr + 0x1D), str3, sizeof(str3), NULL);
		temp = (int)(0x464529 - ((DWORD)tallNut.addr + 0x30));
		WriteProcessMemory(hGameP, (LPVOID)((DWORD)tallNut.addr + 0x2C), &temp, 4, NULL);

	}


	ReadProcessMemory(hGameP, (LPVOID)0x464523, &now, 1, NULL);
	if (now == str4[0])				//��ǰ�ѿ������ܣ�Ҫ�ر�
	{
		WriteProcessMemory(hGameP, (LPVOID)0x464523, str5, 6, NULL);
		CheckDlgButton(hwnd, ID_TALLNUT, BST_UNCHECKED);
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)0x464523, &str4[0], 1, NULL);
		temp = (int)((DWORD)tallNut.addr - 0x464528);
		WriteProcessMemory(hGameP, (LPVOID)0x464524, &temp, 4, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x464528, &str4[1], 1, NULL);
		CheckDlgButton(hwnd, ID_TALLNUT, BST_CHECKED);
	}

}


void Nut(HWND hwnd)
{

	char str1[] = { 0x8B, 0x77, 0x40, 0x8D, 0x0C, 0x40, 0x83, 0x7f, 0x24, 0x03, 0x0F, 0x85 };
	char str2[] = { 0x81, 0x7F, 0x40, 0x2C, 0x01, 0x00, 0x00, 0x0F, 0x87 };
	char str3[] = { 0xC7, 0x47, 0x40, 0x40, 0x1F, 0x00, 0x00, 0xC7, 0x47, 0x24, 0x0F, 0x00, 0x00, 0x00, 0xE9 };
	char str4[] = { 0xE9, 0x90 };
	char str5[] = { 0x8B, 0x77, 0x40, 0x8D, 0x0C, 0x40 };
	int temp = 0;
	char now = '0';

	if (tallNut.addr == NULL)
	{
		tallNut.needWrite = 1;
	}

	if (tallNut.needWrite)
	{
		tallNut.addr = VirtualAllocEx(hGameP, NULL, 48, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

		WriteProcessMemory(hGameP, tallNut.addr, str1, sizeof(str1), NULL);
		temp = (int)(0x464529 - ((DWORD)tallNut.addr + 0x10));
		WriteProcessMemory(hGameP, (LPVOID)((DWORD)tallNut.addr + 0xC), &temp, 4, NULL);

		WriteProcessMemory(hGameP, ((DWORD)tallNut.addr + 0x10), str2, sizeof(str2), NULL);
		temp = (int)(0x464529 - ((DWORD)tallNut.addr + 0x1D));
		WriteProcessMemory(hGameP, (LPVOID)((DWORD)tallNut.addr + 0x19), &temp, 4, NULL);

		WriteProcessMemory(hGameP, (LPVOID)((DWORD)tallNut.addr + 0x1D), str3, sizeof(str3), NULL);
		temp = (int)(0x464529 - ((DWORD)tallNut.addr + 0x30));
		WriteProcessMemory(hGameP, (LPVOID)((DWORD)tallNut.addr + 0x2C), &temp, 4, NULL);

	}


	ReadProcessMemory(hGameP, (LPVOID)0x464523, &now, 1, NULL);
	if (now == str4[0])				//��ǰ�ѿ������ܣ�Ҫ�ر�
	{
		WriteProcessMemory(hGameP, (LPVOID)0x464523, str5, 6, NULL);
		CheckDlgButton(hwnd, ID_TALLNUT, BST_UNCHECKED);
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)0x464523, &str4[0], 1, NULL);
		temp = (int)((DWORD)tallNut.addr - 0x464528);
		WriteProcessMemory(hGameP, (LPVOID)0x464524, &temp, 4, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x464528, &str4[1], 1, NULL);
		CheckDlgButton(hwnd, ID_TALLNUT, BST_CHECKED);
	}

}
#endif

void TallNut(HWND hwnd)
{
#define TALL_NUT_ADDR ((DWORD)allNut.addr+0x0B)
	WriteNut();

	char ch[] = { 0x08, 0x3F };		//open	close
	char now = 0;
	ReadProcessMemory(hGameP, TALL_NUT_ADDR, &now, 1, NULL);
	if (now == ch[1])
	{
		//need open
		WriteProcessMemory(hGameP, TALL_NUT_ADDR, &ch[0], 1, NULL);
		CheckDlgButton(hwnd, ID_TALLNUT, BST_CHECKED);
	}
	else
	{
		//need close
		WriteProcessMemory(hGameP, TALL_NUT_ADDR, &ch[1], 1, NULL);
		CheckDlgButton(hwnd, ID_TALLNUT, BST_UNCHECKED);
	}
}

void Nut(HWND hwnd)
{
#define TALL_NUT_ADDR ((DWORD)allNut.addr+0x11)
	WriteNut();

	char ch[] = { 0x1B, 0x39 };		//open	close
	char now = 0;
	ReadProcessMemory(hGameP, TALL_NUT_ADDR, &now, 1, NULL);
	if (now == ch[1])
	{
		//need open
		WriteProcessMemory(hGameP, TALL_NUT_ADDR, &ch[0], 1, NULL);
		CheckDlgButton(hwnd, ID_NUT, BST_CHECKED);
	}
	else
	{
		//need close
		WriteProcessMemory(hGameP, TALL_NUT_ADDR, &ch[1], 1, NULL);
		CheckDlgButton(hwnd, ID_NUT, BST_UNCHECKED);
	}
}

int WisdomTree(HWND hwnd)
{
	//�ǻ����߶�
	 int treeHeight = GetDlgItemInt(hwnd, ID_WISDOMTREE, NULL, TRUE);
	if (treeHeight == 0)
	{
		if (MessageBox(hwnd, TEXT("δ������ֵ������ֵ����2147483647�Ὣ�ǻ����߶��޸�Ϊ0��\n��ȷ��Ҫ�����޸ģ�"), TEXT("��ܰ��ʾ"), MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
			return 0;
	}

	DWORD base = 0x6a9f38;
	DWORD temp = 0;
	ReadProcessMemory(hGameP, (LPVOID)base, &temp, 4, NULL);
	base = temp + 0x82c;
	ReadProcessMemory(hGameP, (LPVOID)base, &temp, 4, NULL);
	//f4�д���֤
	base = temp + 0xf4;
	WriteProcessMemory(hGameP, (LPVOID)base, &treeHeight, 4, NULL);

	return 1;

}

int Jump(HWND hwnd)
{
	int level = GetDlgItemInt(hwnd, ID_LEVEL, NULL, TRUE);
	if (level == 0 || level > 50)
	{
		MessageBox(hwnd, TEXT("�������Ϸ������鲢��������"), TEXT("����"), MB_YESNO | MB_ICONEXCLAMATION);
		return 0;
	}

	DWORD address = 0x6a9ec0;
	DWORD temp = 0;
	ReadProcessMemory(hGameP, (LPVOID)address, &temp, 4, NULL);
	address = temp + 0x82c;
	ReadProcessMemory(hGameP, (LPVOID)address, &temp, 4, NULL);
	address = temp + 0x24;

	WriteProcessMemory(hGameP, (LPVOID)address, &level, 4, NULL);

	return 1;
}

int ClearMoney()
{
	int money = 0;

	DWORD address = 0x6A9EC0;			//��ַ
	DWORD temp;

	ReadProcessMemory(hGameP, (void*)address, &temp, 4, NULL);
	address = temp + 0x82c;
	ReadProcessMemory(hGameP, (void*)address, &temp, 4, NULL);

	if (address == 0 || temp == 0)
	{
		return 0;
	}

	address = temp + 0x28;
	WriteProcessMemory(hGameP, (void*)address, &money, 4, NULL);

	return 1;
}

void Plant(HWND hwnd)
{
	//��
	char a = 0x84;		
	char b = 0x81;
	//Ӱ��
	char c = 0x74;
	char d = 0xEB;

	char now;
	ReadProcessMemory(hGameP, (LPVOID)0x0040fe30, &now, 1, NULL);
	if (now == a)
	{
		WriteProcessMemory(hGameP, (LPVOID)0x0040fe30, &b, 1, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x00438e40, &d, 1, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_PLANT), TEXT("�رյ���ֲ��(A)"));
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)0x0040fe30, &a, 1, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x00438e40, &c, 1, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_PLANT), TEXT("��������ֲ��(A)"));
	}
	
}
//��ȷ���1
int StrCmp(char str1[], char str2[], int num)
{
	//��֪��Ϊʲôstrcmp()��ʱ�����������Լ�д��һ�������Լ�Ҫ��ĺ���
	int i = 0;
	for (i = 0; i < num; i++)
	{
		if (str1[i] != str2[i])
		{
			return 0;
		}
	}
	return 1;
}

void Backstage(HWND hwnd)
{
	char str1[4] = { 0x55, 0x8b, 0xec, 0x83 };
	char str2[4] = { 0xc3, 0x0, 0x0, 0x0 };
	char now[4];
	DWORD address = 0x4502C0;

	ReadProcessMemory(hGameP, (LPVOID)address, &now, 4, NULL);
	if (StrCmp(now, str1, 4))
	{
		WriteProcessMemory(hGameP, (LPVOID)address, &str2, 4, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_BACKSTAGE), TEXT("�رպ�̨����ͣ"));
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)address, &str1, 4, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_BACKSTAGE), TEXT("������̨����ͣ"));
	}
}


void Auto(HWND hwnd)
{
	DWORD address = 0x430ad0;
	char str1[] = { 0x75, 0x3e };
	char str2[] = { 0x90, 0x90 };
	char now[2];
	ReadProcessMemory(hGameP, (LPVOID)address, &now, 2, NULL);
	if (StrCmp(now, str1, 2))
	{
		WriteProcessMemory(hGameP, (LPVOID)address, &str2, 2, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_AUTO), TEXT("�ر��Զ��ռ�(D)"));
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)address, &str1, 2, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_AUTO), TEXT("�����Զ��ռ�(D)"));
	}


}

void PotatoMine(HWND hwnd)
{
	DWORD address = 0x45fe53;
	char str1[] = { 0x0f, 0x85, 0xfa, 0x01, 0x00, 0x00 };
	char str2[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	char now[6];
	ReadProcessMemory(hGameP, (LPVOID)address, &now, 6, NULL);
	if(StrCmp(now,str1,6))
	{
		WriteProcessMemory(hGameP, (LPVOID)address, &str2, 6, NULL);
		CheckDlgButton(hwnd,ID_POTATOMINE,BST_CHECKED);
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)address, &str1, 6, NULL);
		CheckDlgButton(hwnd, ID_POTATOMINE, BST_UNCHECKED);
	}

}

void Chomper(HWND hwnd)
{
	char str1[] = { 0x75, 0x5f };
	char str2[] = { 0x90, 0x90 };
	char now[2];
	ReadProcessMemory(hGameP, (LPVOID)0x00461565, &now, 2, NULL);
	if (StrCmp(now, str1, 2))
	{
		WriteProcessMemory(hGameP, (LPVOID)0x00461565, &str2, 2, NULL);
		CheckDlgButton(hwnd, ID_CHOMPER, BST_CHECKED);
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)0x00461565, &str1, 2, NULL);
		CheckDlgButton(hwnd, ID_CHOMPER, BST_UNCHECKED);
	}

}

void ShuPai(HWND hwnd)
{
	//��ֲ
	char str1[] = { 0x0f, 0x85, 0xe5, 0x00, 0x00, 0x00 };
	char str2[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	//Ӱ��
	char str3[] = { 0x0f, 0x85, 0x84, 0x00, 0x00, 0x00 };
	char now[6];
	ReadProcessMemory(hGameP, (LPVOID)0x410ae6, &now, 6, NULL);
	if (StrCmp(now, str1, 6))
	{
		WriteProcessMemory(hGameP, (LPVOID)0x410ae6, &str2, 6, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x43903c, &str2, 6, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_SHUPAI), TEXT("�ر�������ֲ(X)"));
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)0x410ae6, &str1, 6, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x43903c, &str3, 6, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_SHUPAI), TEXT("����������ֲ(X)"));
	}
}

void DoomShroom(HWND hwnd)
{
	char str1[] = { 0x75, 0x05 };
	char str2[] = { 0x90, 0x90 };
	char now[2];
	ReadProcessMemory(hGameP, (LPVOID)0x0041d79e, &now, 2, NULL);
	if (StrCmp(now, str1, 2))
	{
		WriteProcessMemory(hGameP, (LPVOID)0x0041d79e, &str2, 2, NULL);
		CheckDlgButton(hwnd, ID_DOOMSHROOM, BST_CHECKED);
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)0x0041d79e, &str1, 2, NULL);
		CheckDlgButton(hwnd, ID_DOOMSHROOM, BST_UNCHECKED);
	}
}

void SunShroom(HWND hwnd)
{
	char str1[] = { 0x75, 0x78 };
	char str2[] = { 0x90, 0x90 };
	char now[2];
	ReadProcessMemory(hGameP, (LPVOID)0x0045fba3, &now, 2, NULL);
	if (StrCmp(now, str1, 2))
	{
		WriteProcessMemory(hGameP, (LPVOID)0x0045fba3, &str2, 2, NULL);
		CheckDlgButton(hwnd, ID_SUNSHROOM, BST_CHECKED);
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)0x0045fba3, &str1, 2, NULL);
		CheckDlgButton(hwnd, ID_SUNSHROOM, BST_UNCHECKED);
	}
}

void MagShroom(HWND hwnd)
{
	char str1[] = { 0x0f, 0x85, 0x47, 0x05, 0x00, 0x00 };
	char str2[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	char now[6];
	ReadProcessMemory(hGameP, (LPVOID)0x00461e36, &now, 6, NULL);
	if (StrCmp(now, str1, 6))
	{
		WriteProcessMemory(hGameP, (LPVOID)0x00461e36, &str2, 6, NULL);
		CheckDlgButton(hwnd, ID_MAGSHROOM, BST_CHECKED);
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)0x00461e36, &str1, 6, NULL);
		CheckDlgButton(hwnd, ID_MAGSHROOM, BST_UNCHECKED);
	}

}

void CobCannon(HWND hwnd)
{
	char str1[] = { 0x0f, 0x85, 0x9c, 0x01, 0x00, 0x00 };
	char str2[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	char now[6];

	ReadProcessMemory(hGameP, (LPVOID)0x0046103a, &now, 6, NULL);
	if (StrCmp(now, str1, 6))
	{
		WriteProcessMemory(hGameP, (LPVOID)0x0046103a, &str2, 6, NULL);
		CheckDlgButton(hwnd, ID_COBCANNON, BST_CHECKED);
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)0x0046103a, &str1, 6, NULL);
		CheckDlgButton(hwnd, ID_COBCANNON, BST_UNCHECKED);
	}

}


int Boom()
{
	DWORD addr = 0;
	
	ReadProcessMemory(hGameP, (LPVOID)0x6A9EC0, &addr, 4, NULL);
	ReadProcessMemory(hGameP, (LPVOID)(addr + 0x768), &addr, 4, NULL);

	if (addr == 0)
	{
		//��ֹ��Ϸ����
		return 0;
	}

	//����ֲ��������ָ��д����Ϸ�ڴ��У�������Զ���߳�������
	//���Ĳ���ֻ���޸��ض���ַ��ֵ����
	int i, j;
	int yMax = 4;

	addr = 0x6a9ec0;
	ReadProcessMemory(hGameP, (LPVOID)addr, &addr, 4, NULL);
	ReadProcessMemory(hGameP, (LPVOID)(addr + 0x768), &addr, 4, NULL);
	ReadProcessMemory(hGameP, (LPVOID)(addr + 0x554c), &addr, 4, NULL);
	if (addr == 3 || addr == 2)
	{
		yMax = 5;
	}

	char buff[] = { 0xFE, 0xDB };

	for (i = 0; i <= 8; i++)
		for (j = 0; j <= yMax; j++)
		{
			CallPlant(i, j, 2);
		}
	Sleep(10);
	WriteProcessMemory(hGameP, (LPVOID)0x00552014, &buff[1], 1, NULL);
	return 1;
}

void CallP(HWND hwnd)
{

	DWORD addr = 0;
	char buff[] = { 0xFE, 0xDB };

	ReadProcessMemory(hGameP, (LPVOID)0x6A9EC0, &addr, 4, NULL);
	ReadProcessMemory(hGameP, (LPVOID)(addr + 0x768), &addr, 4, NULL);

	if (addr == 0)
	{
		//��ֹ��Ϸ����
		return;
	}

	int x = GetDlgItemInt(hwnd, IDE_PX, NULL, TRUE) - 1;
	int y = GetDlgItemInt(hwnd, IDE_PY, NULL, TRUE) - 1;
	int id = SendDlgItemMessage(hwnd, IDC_PID, CB_GETCURSEL, 0, 0);

	int i, j;

	int yMax = 4;

	if (id == -1)
	{
		MessageBox(hwnd, TEXT("ֲ�����಻��Ϊ��"), TEXT("����"), MB_OK);
		return;
	}

	//�ж�y�����ֵ��5��4��
	if (y == -1)
	{
		DWORD addr = 0x6a9ec0;
		ReadProcessMemory(hGameP, (LPVOID)addr, &addr, 4, NULL);
		ReadProcessMemory(hGameP, (LPVOID)(addr + 0x768), &addr, 4, NULL);
		ReadProcessMemory(hGameP, (LPVOID)(addr + 0x554c), &addr, 4, NULL);
		if (addr == 3 || addr == 2)
		{
			yMax = 5;
		}
	}

	WriteProcessMemory(hGameP, (LPVOID)0x00552014, &buff[0], 1, NULL);
	if (x == -1 && y == -1)				//ȫ��
	{
		for (i = 0; i <= 8; i++)
			for (j = 0; j <= yMax; j++)
			{
				CallPlant(i, j, id);
			}
	}
	else if (x == -1)					//����
	{
		for (i = 0; i <= 8; i++)
		{
			CallPlant(i, y, id);
		}
	}
	else if (y == -1)					//����
	{
		for (j = 0; j <= yMax; j++)
		{
			CallPlant(x, j, id);
		}
	}
	else
	{
		CallPlant(x, y, id);
	}
	Sleep(10);
	WriteProcessMemory(hGameP, (LPVOID)0x00552014, &buff[1], 1, NULL);
	
}

void CallZ(HWND hwnd)
{
	DWORD addr = 0;

	char buff[] = { 0xFE, 0xDB };
	
	

	ReadProcessMemory(hGameP, (LPVOID)0x6A9EC0, &addr, 4, NULL);
	ReadProcessMemory(hGameP, (LPVOID)(addr + 0x768), &addr, 4, NULL);
	ReadProcessMemory(hGameP, (LPVOID)(addr + 0x160), &addr, 4, NULL);

	if (addr == 0)
	{
		//��ֹ��Ϸ����
		return;
	}

	int x = GetDlgItemInt(hwnd, IDE_ZX, NULL, TRUE) - 1;
	int y = GetDlgItemInt(hwnd, IDE_ZY, NULL, TRUE) - 1;
	int id = SendDlgItemMessage(hwnd, IDC_ZID, CB_GETCURSEL, 0, 0);

	if (id == -1)
	{
		MessageBox(hwnd, TEXT("��ʬ���಻��Ϊ��"), TEXT("����"), MB_OK);
		return;
	}

	int i, j;
	int yMax = 4;
	//�ж�y�����ֵ��5��4��
	if (y == -1)
	{
		DWORD addr = 0x6a9ec0;
		ReadProcessMemory(hGameP, (LPVOID)addr, &addr, 4, NULL);
		ReadProcessMemory(hGameP, (LPVOID)(addr + 0x768), &addr, 4, NULL);
		ReadProcessMemory(hGameP, (LPVOID)(addr + 0x554c), &addr, 4, NULL);
		if (addr == 3 || addr == 2)
		{
			yMax = 5;
		}
	}
	WriteProcessMemory(hGameP, (LPVOID)0x00552014, &buff[0], 1, NULL);
	if (x == -1 && y == -1)				//ȫ��
	{
		for (i = 0; i <= 8; i++)
			for (j = 0; j <= yMax; j++)
			{
			CallZombie(i, j, id);
			}
	}
	else if (x == -1)					//����
	{
		for (i = 0; i <= 8; i++)
		{
			CallZombie(i, y, id);
		}
	}
	else if (y == -1)					//����
	{
		for (j = 0; j <= yMax; j++)
		{
			CallZombie(x, j, id);
		}
	}
	else
	{
		CallZombie(x, y, id);
	}

	Sleep(10);
	WriteProcessMemory(hGameP, (LPVOID)0x00552014, &buff[1], 1, NULL);
}

void ZKWXZ(HWND hwnd)
{
	char str1[] = { 0x51, 0x83, 0xf8 };
	char str2[] = { 0xb0, 0x01, 0xc3 };

	char str3[] = { 0x74 };
	char str4[] = { 0xeb };

	char now[1];
	ReadProcessMemory(hGameP, (LPVOID)0x0040e477, &now, 1, NULL);
	if (StrCmp(now, str3, 1))
	{
		WriteProcessMemory(hGameP, (LPVOID)0x0041d7d0, &str2, 3, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x0040e477, &str4, 1, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_ZKWXZ), TEXT("�ر��Ͽ�������(E)"));
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)0x0041d7d0, &str1, 3, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x0040e477, &str3, 1, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_ZKWXZ), TEXT("�����Ͽ�������(E)"));
	}

}

void DPWX(HWND hwnd)
{
	char str1[] = { 0x83, 0x80, 0x20, 0x02, 0x00, 0x00, 0xff };
	char str2[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

	char str3[] = { 0x0f, 0x84, 0x79, 0x02, 0x00, 0x00 };
	char str4[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

	char now[6];
	ReadProcessMemory(hGameP, (LPVOID)0x0040b9e2, &now, 6, NULL);
	if (StrCmp(now, str3, 6))
	{
		WriteProcessMemory(hGameP, (LPVOID)0x0040bb25, &str2, 7, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x0040b9e2, &str4, 6, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_DPWX), TEXT("�ر����޶���"));
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)0x0040bb25, &str1, 7, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x0040b9e2, &str3, 6, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_DPWX), TEXT("�������޶���"));
	}
}

void NoSleep(HWND hwnd)
{
	char str1[] = { 0x74 };
	char str2[] = { 0xeb };
	char now[1];
	ReadProcessMemory(hGameP, (LPVOID)0x0045de8e, &now, 1, NULL);
	if (StrCmp(now, str1, 1))
	{
		WriteProcessMemory(hGameP, (LPVOID)0x0045de8e, &str2, 1, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_NOSLEEP), TEXT("�ر�Ģ���⻽��"));
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)0x0045de8e, &str1, 1, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_NOSLEEP), TEXT("����Ģ���⻽��"));
	}
}


int CallPlant(int x, int y, int id)
{
	char plantBuff[3];
	
	if (plant.addr == NULL)
	{
		plant.needWrite = 1;
	}
	
	if (plant.needWrite)
	{
		char str[] = { 0x60, 0xB9, 0xC0, 0x9E, 0x6A, 0x00, 0x8B, 0x09, 0x8B, 0x89, 0x68, 0x07, 0x00, 0x00, 0x68, 0xFF, 0xFF, 0xFF, 0xFF, 0x6A, 0x01, 0xB8, 0x01, 0x00, 0x00, 0x00, 0x6A, 0x01, 0x51, 0xBB, 0x20, 0xD1, 0x40, 0x00, 0xFF, 0xD3, 0x61, 0xC3 };
		plant.addr = VirtualAllocEx(hGameP, NULL, sizeof(str), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if (plant.addr == NULL)
		{
			MessageBox(NULL, TEXT("�����ڴ�ʧ��"), TEXT("����"), MB_OK);
			return 0;
		}
		WriteProcessMemory(hGameP, plant.addr, str, sizeof(str), NULL);
		plant.needWrite = 0;
	}

	plantBuff[0] = (char)id;		//20
	plantBuff[1] = (char)y;			//22
	plantBuff[2] = (char)x;			//27

	WriteProcessMemory(hGameP, (LPVOID)((DWORD)plant.addr + 20), &plantBuff[0], 1, NULL);
	WriteProcessMemory(hGameP, (LPVOID)((DWORD)plant.addr + 22), &plantBuff[1], 1, NULL);
	WriteProcessMemory(hGameP, (LPVOID)((DWORD)plant.addr + 27), &plantBuff[2], 1, NULL);

	HANDLE hrt = CreateRemoteThread(hGameP, NULL, 0, (LPTHREAD_START_ROUTINE)plant.addr, NULL, 0, NULL);
	if (hrt == NULL)
	{
		MessageBox(NULL, TEXT("����Զ���߳�ʧ��"), TEXT("����"), MB_OK);
		VirtualFreeEx(hGameP, (LPVOID)plant.addr, 0, MEM_RELEASE);
		plant.needWrite = 1;
		return 0;
	}
	
	WaitForSingleObject(hrt, INFINITE);
	CloseHandle(hrt);
	return 1;
}

int CallZombie(int x, int y, int id)
{
	char zombieBuff[3];
	if (zombie.addr == NULL)
	{
		zombie.needWrite = 1;
	}
	if (zombie.needWrite)
	{
		//char str[] = { 0x60, 0x6A, 0x08, 0x6A, 0x00, 0xB8, 0x03, 0x00, 0x00, 0x00, 0x8B, 0x0D, 0xC0, 0x9E, 0x6A, 0x00, 0x8B, 0x89, 0x68, 0x07, 0x00, 0x00, 0x8B, 0x89, 0x60, 0x01, 0x00, 0x00, 0xBA, 0xF0, 0xA0, 0x42, 0x00, 0xFF, 0xD2, 0x61, 0xC3 };
		char str[] = { 0x68, 0x08, 0x00, 0x00, 0x00, 0x68, 0x1F, 0x00, 0x00, 0x00, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x8B, 0x0D, 0xC0, 0x9E, 0x6A, 0x00, 0x8B, 0x89, 0x68, 0x07, 0x00, 0x00, 0x8B, 0x89, 0x60, 0x01, 0x00, 0x00, 0xE8, 0x02, 0x00, 0x00, 0x00, 0xEB, 0x06, 0x68, 0xF0, 0xA0, 0x42, 0x00, 0xC3, 0xC3 };
		zombie.addr = VirtualAllocEx(hGameP, NULL, sizeof(str), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if (zombie.addr == NULL)
		{
			MessageBox(NULL, TEXT("�����ڴ�ʧ��"), TEXT("����"), MB_OK);
			return 0;
		}
		WriteProcessMemory(hGameP, zombie.addr, str, sizeof(str), NULL);
		zombie.needWrite = 0;
	}
	
	zombieBuff[0] = (char)x;			//2 1
	zombieBuff[1] = (char)id;			//4 6
	zombieBuff[2] = (char)y;			//6 11

	WriteProcessMemory(hGameP, (LPVOID)((DWORD)zombie.addr + 1), &zombieBuff[0], 1, NULL);
	WriteProcessMemory(hGameP, (LPVOID)((DWORD)zombie.addr + 6), &zombieBuff[1], 1, NULL);
	WriteProcessMemory(hGameP, (LPVOID)((DWORD)zombie.addr + 11), &zombieBuff[2], 1, NULL);

	HANDLE hrt = CreateRemoteThread(hGameP, NULL, 0, (LPTHREAD_START_ROUTINE)zombie.addr, NULL, 0, NULL);
	if (hrt == NULL)
	{
		MessageBox(NULL, TEXT("����Զ���߳�ʧ��"), TEXT("����"), MB_OK);
		VirtualFreeEx(hGameP, (LPVOID)zombie.addr, 0, MEM_RELEASE);
		zombie.needWrite = 1;
		return 0;
	}
	
	WaitForSingleObject(hrt, INFINITE);
	CloseHandle(hrt);
	return 1;
}

void WriteNut()
{
	char str[] = { 0x8B, 0x77, 0x40, 0x8D, 0x0C, 0x40, 0x83, 0x7F, 0x24, 0x17, 0x74, 0x3F, 0x83, 0x7F, 0x24, 0x03, 0x74, 0x39, 0x75, 0x37, 0x81, 0x7F, 0x40, 0x2C, 0x01, 0x00, 0x00, 0x77, 0x2E, 0xC7, 0x47, 0x40, 0x40, 0x1F, 0x00, 0x00, 0xC7, 0x47, 0x24, 0x11, 0x00, 0x00, 0x00, 0xEB, 0x1E, 0x81, 0x7F, 0x40, 0x2C, 0x01, 0x00, 0x00, 0x77, 0x15, 0xC7, 0x47, 0x40, 0x40, 0x1F, 0x00, 0x00, 0xC7, 0x47, 0x24, 0x02, 0x00, 0x00, 0x00, 0xC7, 0x47, 0x50, 0x01, 0x00, 0x00, 0x00, 0xE9, 0xD9, 0x44, 0xB3, 0xFF };
	char jmp = 0xE9;
	char nop = 0x90;
	int temp = 0;

	if (allNut.needWrite)
	{
		allNut.addr = VirtualAllocEx(hGameP, NULL, sizeof(str), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		WriteProcessMemory(hGameP, allNut.addr, str, sizeof(str), NULL);
		allNut.needWrite = 0;

		temp = (int)(0x464529 - ((DWORD)allNut.addr + 0x50));
		WriteProcessMemory(hGameP, (LPVOID)((DWORD)allNut.addr + 0x4C), &temp, 4, NULL);
		
		//��ԭ������ת��д�뺯��
		temp = (int)((DWORD)allNut.addr - 0x464528);
		WriteProcessMemory(hGameP, (LPVOID)0x464523, &jmp, 1, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x464524, &temp, 4, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x464528, &nop, 1, NULL);

	}
}


void End(HWND hwnd)
{
	//ԭ���Ĳ�����
	char a = 0x84; 
	char c = 0x74;
	char str2[6] = { 0x0f, 0x84, 0x1f, 0x09, 0x00, 0x00 };	//��ֲ��
	char str3[4] = { 0x55, 0x8b, 0xec, 0x83 };				//����ͣ
	char str4[2] = { 0x75, 0x3e };							//�Զ��ռ�
	char str5	 = 0x7e;									//��cd
	char str6[]  = {0x0f,0x85,0xfa,0x01,0x00,0x00};			//������
	char str7[]  = { 0x75, 0x5f };							//���컨
	char str8[] = { 0x75, 0x05 };							//����
	char str9[] = { 0x75, 0x78 };							//���⹽
	char str10[] = { 0x0f, 0x85, 0x47, 0x05, 0x00, 0x00 };	//������
	char str11[] = { 0x0f, 0x85, 0x9c, 0x01, 0x00, 0x00 };	//������
	char str12[] = { 0x0f, 0x85, 0x84, 0x00, 0x00, 0x00 };
	char str13[] = { 0x0f, 0x85, 0xe5, 0x00, 0x00, 0x00 };
	char str14[] = { 0x51, 0x83, 0xf8 };
	char str15[] = { 0x74 };
	char str16[] = { 0x83, 0x80, 0x20, 0x02, 0x00, 0x00, 0xff };
	char str17[] = { 0x0f, 0x84, 0x79, 0x02, 0x00, 0x00 };
	char str18[] = { 0x8B, 0x77, 0x40, 0x8D, 0x0C, 0x40 };


	if (CheckProcessOn() != NULL)
	{
		//���ر�ʱ��Ϸ�������У�����Ҫ�ָ�һЩ���޸ĵ��ڴ�

		//��ֲ��ָ�
		WriteProcessMemory(hGameP, (LPVOID)0x0040fe30, &a, 1, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x00438e40, &c, 1, NULL);
		//����ͣ�ָ�
		WriteProcessMemory(hGameP, (LPVOID)0x004502C0, &str3, 4, NULL);
		//������ֲ�ָ�
		WriteProcessMemory(hGameP, (LPVOID)0x410ae6, &str13, 6, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x43903c, &str12, 6, NULL);
		//�ر���CD
		WriteProcessMemory(hGameP, (LPVOID)0x00487296, &str5, 1, NULL);
		//�����׻ָ�
		WriteProcessMemory(hGameP, (LPVOID)0x45fe53, &str6, 6, NULL);
		//���컨
		WriteProcessMemory(hGameP, (LPVOID)0x00461565, &str7, 2, NULL);
		//����
		WriteProcessMemory(hGameP, (LPVOID)0x0041d79e, &str8, 2, NULL);
		//���⹽
		WriteProcessMemory(hGameP, (LPVOID)0x0045fba3, &str9, 2, NULL);
		//������
		WriteProcessMemory(hGameP, (LPVOID)0x00461e36, &str10, 6, NULL);
		//���׼�ũ��
		WriteProcessMemory(hGameP, (LPVOID)0x0046103a, &str11, 6, NULL);
		//�Ͽ�
		WriteProcessMemory(hGameP, (LPVOID)0x0041d7d0, &str14, 3, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x0040e477, &str15, 1, NULL);
		//����
		WriteProcessMemory(hGameP, (LPVOID)0x0040bb25, &str16, 7, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x0040b9e2, &str17, 6, NULL);
		//Ģ��
		WriteProcessMemory(hGameP, (LPVOID)0x0045de8e, &str15, 1, NULL);
		//Nut
		WriteProcessMemory(hGameP, (LPVOID)0x464523, str18, 6, NULL);


		if (plant.addr != NULL)
		{
			VirtualFreeEx(hGameP, (LPVOID)plant.addr, 0, MEM_RELEASE);
		}
		if (zombie.addr != NULL)
		{
			VirtualFreeEx(hGameP, (LPVOID)zombie.addr, 0, MEM_RELEASE);
		}
		if (allNut.addr != NULL)
		{
			VirtualFreeEx(hGameP, (LPVOID)allNut.addr, 0, MEM_RELEASE);
		}

	}
	

	//ɾ�����̹���
	DeleteHook();
	//ɾ����ʱ��
	KillTimer(hwnd, ID_TIMER);
}