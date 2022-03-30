
#include"head.h"


//自制专用全局键盘钩子
#pragma comment(lib,"keyHook.lib")
HHOOK SetKeyHook();
int DeleteHook();


//按钮控件ID
#define ID_CD		  1					//冷却
#define ID_SUN		  2					//阳光
#define ID_MONEY	  3					//金币
#define ID_WISDOMTREE 5					//智慧树
#define ID_TREEGO     6					//修改
#define ID_LEVEL	  7					//选关
#define ID_JUMP		  8					//跳
#define ID_CLEAR      9					//钱清零
#define ID_PLANT	  10				//叠植物
#define ID_BACKSTAGE  11				//免暂停
#define ID_AUTO		  12				//自动收集
#define ID_BOOM		  13				//全屏樱桃炸弹
#define ID_POTATOMINE 14				//土豆地雷
#define ID_CHOMPER    15				//大嘴花
#define ID_DOOMSHROOM 16				//毁灭菇
#define ID_SUNSHROOM  17				//阳光菇
#define ID_MAGSHROOM  18				//磁力菇
#define ID_COBCANNON  19				//玉米加农炮
#define ID_SHUPAI	  20				//竖排种植
#define ID_ZKWXZ	  30				//紫卡
#define ID_DPWX		  31				//钉耙
#define ID_NOSLEEP	  32				//蘑菇免唤醒
#define ID_TALLNUT	  33				//高建国窝瓜
#define ID_NUT		  34				//小坚果核弹

#define IDE_PX		  21
#define IDE_PY		  22
#define IDC_PID		  23
#define IDE_ZX		  24
#define IDE_ZY		  25
#define IDC_ZID		  26
#define IDC_TYPE	  27
#define ID_CALLP	  28
#define ID_CALLZ	  29


//定时器ID
#define ID_TIMER      1					//用来检测游戏是否关闭

//游戏句柄
HWND hGame = NULL;

TCHAR *PlantStr[] = { TEXT("豌豆射手"), TEXT("向日葵"), TEXT("樱桃炸弹"), TEXT("坚果墙"), TEXT("土豆雷"),
TEXT("寒冰射手"), TEXT("大嘴花"), TEXT("双发射手"), TEXT("小喷菇"), TEXT("阳光菇"), TEXT("大喷菇"), TEXT("墓碑吞噬者"),
TEXT("魅惑菇"), TEXT("胆小菇"), TEXT("寒冰菇"), TEXT("毁灭菇"), TEXT("睡莲"), TEXT("窝瓜"), TEXT("三线射手"), TEXT("缠绕海藻"),
TEXT("火爆辣椒"), TEXT("地刺"), TEXT("火炬树桩"), TEXT("高坚果"), TEXT("海蘑菇"), TEXT("路灯花"), TEXT("仙人掌"),
TEXT("三叶草"), TEXT("裂荚射手"), TEXT("杨桃"), TEXT("南瓜头"), TEXT("磁力菇"), TEXT("卷心菜投手"), TEXT("花盆"),
TEXT("玉米投手"), TEXT("咖啡豆"), TEXT("大蒜"), TEXT("叶子保护伞"), TEXT("金盏花"), TEXT("西瓜投手"), TEXT("机枪射手"),
TEXT("双子向日葵"), TEXT("忧郁菇"), TEXT("香蒲"), TEXT("冰瓜"), TEXT("吸金磁"), TEXT("地刺王"), TEXT("玉米加农炮"),
TEXT("左向双发射手"), TEXT("爆炸坚果"), TEXT("巨大坚果") };

TCHAR *ZombieStr[] = { TEXT("普通"), TEXT("摇旗"), TEXT("路障"), TEXT("撑杆"), TEXT("铁桶"),
TEXT("读报"), TEXT("铁栅门"), TEXT("橄榄球"), TEXT("舞王"), TEXT("伴舞"), TEXT("鸭子"), TEXT("潜水"), TEXT("冰车"),
TEXT("雪橇"), TEXT("海豚"), TEXT("小丑"), TEXT("气球"), TEXT("矿工"), TEXT("跳跳"), TEXT("雪人"), TEXT("蹦极"),
TEXT("扶梯"), TEXT("篮球"), TEXT("白眼"), TEXT("小鬼"), TEXT("僵博"), TEXT("豌豆"), TEXT("坚果"),
TEXT("辣椒"), TEXT("机枪"), TEXT("窝瓜"), TEXT("高坚果"), TEXT("红眼") };

LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

struct AddrAndFree
{
	LPVOID addr;
	int needWrite;
}plant = { NULL, 0 }, zombie = { NULL, 0 }, tallNut = { NULL, 0 }, nut = { NULL, 0 }, allNut = { NULL, 1 };




//游戏进程句柄，同时用该变量判断游戏是否打开
HANDLE hGameP = NULL;


//检测游戏进程是否打开成功,成功返回进程句柄，否则返回NULL
HANDLE CheckProcessOn();

//修改冷却
void WuLengQu(HWND);

//修改阳光
int Sun();

//修改金币
int Money();

//智慧树高度
int WisdomTree(HWND hwnd);

//跳关
int Jump(HWND hwnd);

//钱清零
int ClearMoney();

//叠植物
void Plant(HWND);

//免暂停
void Backstage(HWND);

//自定义字符数组比较函数
int StrCmp(char str1[], char str2[], int num);

//程序关闭前的处理函数
void End(HWND);

//自动收集
void Auto(HWND);

//全屏樱桃炸弹
int Boom();

//土豆地雷
void PotatoMine(HWND);

//大嘴花
void Chomper(HWND);

//毁灭菇
void DoomShroom(HWND);

//阳光菇
void SunShroom(HWND);

//磁力菇
void MagShroom(HWND);

//玉米加农炮
void CobCannon(HWND);

//竖排种种植
void ShuPai(HWND);

//种植物
void CallP(HWND);

//种僵尸
void CallZ(HWND);

//紫卡
void ZKWXZ(HWND);

//钉耙
void DPWX(HWND);

//蘑菇免唤醒
void NoSleep(HWND);

//高建国窝瓜
void TallNut(HWND);

//小建国核弹
void Nut(HWND);

//写入坚果变其他植物的代码
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
		MessageBox(NULL, TEXT("这个程序需要在 Windows NT 才能运行！"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName,
		TEXT("植物大战僵尸中文版外挂"),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		4*1080/11,		//窗口宽
		4*1220/11,		//窗口高
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	hGameP = CheckProcessOn();
	if (hGameP == NULL)
	{
		MessageBox(hwnd, TEXT("游戏未打开"), TEXT("提醒"), MB_OK | MB_ICONEXCLAMATION);
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

		//设置键盘钩子用于快捷键
		SetKeyHook();

		SetTimer(hwnd, ID_TIMER, 500, NULL);

		x = LOWORD(GetDialogBaseUnits());		//本机x=8
		
		RECT rcWindow, rcClinet;
		int winX, winY;
		GetWindowRect(hwnd, &rcWindow);
		GetClientRect(hwnd, &rcClinet);
		winX = rcWindow.right - rcWindow.left - (rcClinet.right - rcClinet.left) + 72*x;
		winY = rcWindow.bottom - rcWindow.top - (rcClinet.bottom - rcClinet.top) + 53*x;
		MoveWindow(hwnd, (GetSystemMetrics(SM_CXSCREEN) - winX) / 2, (GetSystemMetrics(SM_CYSCREEN) - winY) / 2, winX, winY, TRUE);


		CreateWindow(TEXT("button"), TEXT("开启无冷却(Q)"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				x, x, 20 * x, 4*x,
				hwnd, (HMENU)ID_CD,
				((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("+1000阳光(W)"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			25 * x, x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_SUN,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("+50,000金币(S)"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			25 * x, 6*x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_MONEY,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("Edit"), NULL,
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			x, 13 * x, 12 * x, (int)(2.8*x),
			hwnd, (HMENU)ID_WISDOMTREE,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("修改"),
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

		CreateWindow(TEXT("button"), TEXT("太无聊了？我帮你把钱给清空吧"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			6 * x, 48*x, 35 * x, 4 * x,
			hwnd, (HMENU)ID_CLEAR,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("开启后台免暂停"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			6 * x, 43*x, 35 * x, 4 * x,
			hwnd, (HMENU)ID_BACKSTAGE,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("开启叠种植物(A)"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			x, 6 * x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_PLANT,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("开启自动收集(D)"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			25 * x, 17 * x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_AUTO,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("秘技：BOOM(B)"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			25 * x, 22 * x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_BOOM,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("开启竖排种植(X)"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			25 * x, 27 * x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_SHUPAI,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("土豆地雷"),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			2*x, 18 * x, 15 * x, 3 * x,
			hwnd, (HMENU)ID_POTATOMINE,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("大嘴花"),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			2 * x, 21 * x, 15 * x, 3 * x,
			hwnd, (HMENU)ID_CHOMPER,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("毁灭菇"),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			2 * x, 24 * x, 15 * x, 3 * x,
			hwnd, (HMENU)ID_DOOMSHROOM,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("阳光菇"),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			2 * x, 27 * x, 15 * x, 3 * x,
			hwnd, (HMENU)ID_SUNSHROOM,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("磁力菇"),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			2 * x, 30 * x, 15 * x, 3 * x,
			hwnd, (HMENU)ID_MAGSHROOM,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("玉米加农炮"),
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
		
		CreateWindow(TEXT("button"), TEXT("种植物"),
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

		CreateWindow(TEXT("button"), TEXT("种僵尸"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			62 * x, 36 * x, 6 * x, 3 * x,
			hwnd, (HMENU)ID_CALLZ,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("开启紫卡无限制(E)"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			49 * x, x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_ZKWXZ,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("开启无限钉耙"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			49 * x, 6*x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_DPWX,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("开启蘑菇免唤醒"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			49 * x, 11 * x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_NOSLEEP,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("高坚果窝瓜"),
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			49 * x, 17 * x, 20 * x, 4 * x,
			hwnd, (HMENU)ID_TALLNUT,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);

		CreateWindow(TEXT("button"), TEXT("小坚果核弹"),
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
			MessageBox(hwnd, TEXT("技术问题，目前就这么点功能。\n你可以尝试在游戏窗口按下Ctrl+7，这也是一个小彩蛋，但是这个彩蛋只是有声音，游戏失去焦点是不会有声音的，所以就没有做这个按钮。"), TEXT("我这也太菜了吧"), MB_OK);
			return 0;
		case IDM_GY:
			//嘿嘿
			MessageBox(hwnd, TEXT("本程序受美国法律保护，仅供C语言初学者交流使用，\n使用本程序产生的一切法律责任与本程序无关。"), TEXT("警告"), MB_OK | MB_ICONEXCLAMATION);
			return 0;
		case IDM_TS:
			MessageBox(hwnd, TEXT("1.当阳光值超过9990时，收集阳光会使阳光变为最大值（9990）。\n2.当金币超过999,990时，花费或者获得金币会使金币变为最大值（999,990）。\n3.开启时间缩短后，食人花、阳光菇、土豆地雷等需要时间准备/长大的植物都会瞬间完成，但窝瓜，地刺会失效（没有伤害）。\n4.括号里面的字符是快捷键，在游戏窗口中按下ctrl+括号里面的字符即可。\n5.过度使用辅助会使游戏失去乐趣，自己斟酌。\n6.背景图片来源于微信公众号roco攻略玩家自制的“泳装毒王”，严禁商用。"), TEXT("提示"), MB_OK);
			return 0;
		}

		if (CheckProcessOn() == NULL)
		{
			MessageBox(hwnd, TEXT("游戏未打开，请打开游戏后再重试"), TEXT("温馨提示"), MB_OK | MB_ICONEXCLAMATION);
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
		//贴背景
		mdc = CreateCompatibleDC(hdc);
		bmp = LoadBitmap((HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDB_BITMAP1));
		SelectObject(mdc, bmp);
		BitBlt(hdc, 0, 0, 47 * x, 53 * x, mdc, 0, 0, SRCCOPY);

		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, x, 11 * x, TEXT("修改智慧树高度"), 7);
		TextOut(hdc, 25 * x, 11 * x, TEXT("冒险模式跳关（1-50）"), 12);

		TextOut(hdc, 33 * x, (int)(32.5 * x), TEXT("列"), 1);
		TextOut(hdc, 44 * x, (int)(32.5 * x), TEXT("行"), 1);
		TextOut(hdc, 33 * x, (int)(36.5 * x), TEXT("列"), 1);
		TextOut(hdc, 44 * x, (int)(36.5 * x), TEXT("行"), 1);

		//时间缩短类
		HBRUSH hBrush, oldHBrush;
		hBrush = (HBRUSH)CreateSolidBrush(RGB(0xf0, 0xf0, 0xf0));
		oldHBrush = SelectObject(hdc, hBrush);
		HPEN hPen, oldHPen;
		hPen = CreatePen(PS_SOLID, 1, RGB(0xf0, 0xf0, 0xf0));
		oldHPen = SelectObject(hdc, hPen);
		Rectangle(hdc, x, 17 * x, 20 * x, 36 * x);

		DeleteObject(SelectObject(hdc, oldHBrush));
		DeleteObject(SelectObject(hdc, oldHPen));

		TextOut(hdc, 5 * x, 16 * x, TEXT("时间缩短类"), 5);

		DeleteObject(bmp);
		DeleteDC(mdc);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:

		//进行最后的处理
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

//修改冷却
void WuLengQu(HWND hwnd)
{
	
	HWND hChildnd = GetDlgItem(hwnd, ID_CD);
	char cd = '0';
	ReadProcessMemory(hGameP, (LPVOID)0x00487296, &cd, 1, NULL);
	if (cd == 0x7e)
	{
		cd = 0x70;
		WriteProcessMemory(hGameP, (LPVOID)0x00487296, &cd, 1, NULL);
		SetWindowText(hChildnd, TEXT("关闭无冷却(Q)"));
	}
	else
	{
		cd = 0x7e;
		WriteProcessMemory(hGameP, (LPVOID)0x00487296, &cd, 1, NULL);
		SetWindowText(hChildnd, TEXT("开启无冷却(Q)"));
	}
	
}



int Sun()
{
	//当前阳光值
	int sunNum = 0;

	DWORD buff1 = 0x6A9EC0;			//基址
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
	//当前的金币值
	int money = 0;
	DWORD buff1 = 0x6A9EC0;			//基址
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
	if (now == str4[0])				//当前已开启功能，要关闭
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
	if (now == str4[0])				//当前已开启功能，要关闭
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
	//智慧树高度
	 int treeHeight = GetDlgItemInt(hwnd, ID_WISDOMTREE, NULL, TRUE);
	if (treeHeight == 0)
	{
		if (MessageBox(hwnd, TEXT("未填入数值或者数值大于2147483647会将智慧树高度修改为0。\n你确定要继续修改？"), TEXT("温馨提示"), MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
			return 0;
	}

	DWORD base = 0x6a9f38;
	DWORD temp = 0;
	ReadProcessMemory(hGameP, (LPVOID)base, &temp, 4, NULL);
	base = temp + 0x82c;
	ReadProcessMemory(hGameP, (LPVOID)base, &temp, 4, NULL);
	//f4有待验证
	base = temp + 0xf4;
	WriteProcessMemory(hGameP, (LPVOID)base, &treeHeight, 4, NULL);

	return 1;

}

int Jump(HWND hwnd)
{
	int level = GetDlgItemInt(hwnd, ID_LEVEL, NULL, TRUE);
	if (level == 0 || level > 50)
	{
		MessageBox(hwnd, TEXT("关数不合法，请检查并重新输入"), TEXT("警告"), MB_YESNO | MB_ICONEXCLAMATION);
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

	DWORD address = 0x6A9EC0;			//基址
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
	//种
	char a = 0x84;		
	char b = 0x81;
	//影子
	char c = 0x74;
	char d = 0xEB;

	char now;
	ReadProcessMemory(hGameP, (LPVOID)0x0040fe30, &now, 1, NULL);
	if (now == a)
	{
		WriteProcessMemory(hGameP, (LPVOID)0x0040fe30, &b, 1, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x00438e40, &d, 1, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_PLANT), TEXT("关闭叠种植物(A)"));
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)0x0040fe30, &a, 1, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x00438e40, &c, 1, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_PLANT), TEXT("开启叠种植物(A)"));
	}
	
}
//相等返回1
int StrCmp(char str1[], char str2[], int num)
{
	//不知道为什么strcmp()有时候会出错，所以自己写了一个符合自己要求的函数
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
		SetWindowText(GetDlgItem(hwnd, ID_BACKSTAGE), TEXT("关闭后台免暂停"));
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)address, &str1, 4, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_BACKSTAGE), TEXT("开启后台免暂停"));
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
		SetWindowText(GetDlgItem(hwnd, ID_AUTO), TEXT("关闭自动收集(D)"));
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)address, &str1, 2, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_AUTO), TEXT("开启自动收集(D)"));
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
	//种植
	char str1[] = { 0x0f, 0x85, 0xe5, 0x00, 0x00, 0x00 };
	char str2[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	//影子
	char str3[] = { 0x0f, 0x85, 0x84, 0x00, 0x00, 0x00 };
	char now[6];
	ReadProcessMemory(hGameP, (LPVOID)0x410ae6, &now, 6, NULL);
	if (StrCmp(now, str1, 6))
	{
		WriteProcessMemory(hGameP, (LPVOID)0x410ae6, &str2, 6, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x43903c, &str2, 6, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_SHUPAI), TEXT("关闭竖排种植(X)"));
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)0x410ae6, &str1, 6, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x43903c, &str3, 6, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_SHUPAI), TEXT("开启竖排种植(X)"));
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
		//防止游戏崩溃
		return 0;
	}

	//将种植函数机器指令写入游戏内存中，并创建远程线程来调用
	//更改参数只需修改特定地址的值即可
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
		//防止游戏崩溃
		return;
	}

	int x = GetDlgItemInt(hwnd, IDE_PX, NULL, TRUE) - 1;
	int y = GetDlgItemInt(hwnd, IDE_PY, NULL, TRUE) - 1;
	int id = SendDlgItemMessage(hwnd, IDC_PID, CB_GETCURSEL, 0, 0);

	int i, j;

	int yMax = 4;

	if (id == -1)
	{
		MessageBox(hwnd, TEXT("植物种类不能为空"), TEXT("错误"), MB_OK);
		return;
	}

	//判断y的最大值（5或4）
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
	if (x == -1 && y == -1)				//全屏
	{
		for (i = 0; i <= 8; i++)
			for (j = 0; j <= yMax; j++)
			{
				CallPlant(i, j, id);
			}
	}
	else if (x == -1)					//整行
	{
		for (i = 0; i <= 8; i++)
		{
			CallPlant(i, y, id);
		}
	}
	else if (y == -1)					//整列
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
		//防止游戏崩溃
		return;
	}

	int x = GetDlgItemInt(hwnd, IDE_ZX, NULL, TRUE) - 1;
	int y = GetDlgItemInt(hwnd, IDE_ZY, NULL, TRUE) - 1;
	int id = SendDlgItemMessage(hwnd, IDC_ZID, CB_GETCURSEL, 0, 0);

	if (id == -1)
	{
		MessageBox(hwnd, TEXT("僵尸种类不能为空"), TEXT("错误"), MB_OK);
		return;
	}

	int i, j;
	int yMax = 4;
	//判断y的最大值（5或4）
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
	if (x == -1 && y == -1)				//全屏
	{
		for (i = 0; i <= 8; i++)
			for (j = 0; j <= yMax; j++)
			{
			CallZombie(i, j, id);
			}
	}
	else if (x == -1)					//整行
	{
		for (i = 0; i <= 8; i++)
		{
			CallZombie(i, y, id);
		}
	}
	else if (y == -1)					//整列
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
		SetWindowText(GetDlgItem(hwnd, ID_ZKWXZ), TEXT("关闭紫卡无限制(E)"));
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)0x0041d7d0, &str1, 3, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x0040e477, &str3, 1, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_ZKWXZ), TEXT("开启紫卡无限制(E)"));
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
		SetWindowText(GetDlgItem(hwnd, ID_DPWX), TEXT("关闭无限钉耙"));
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)0x0040bb25, &str1, 7, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x0040b9e2, &str3, 6, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_DPWX), TEXT("开启无限钉耙"));
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
		SetWindowText(GetDlgItem(hwnd, ID_NOSLEEP), TEXT("关闭蘑菇免唤醒"));
	}
	else
	{
		WriteProcessMemory(hGameP, (LPVOID)0x0045de8e, &str1, 1, NULL);
		SetWindowText(GetDlgItem(hwnd, ID_NOSLEEP), TEXT("开启蘑菇免唤醒"));
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
			MessageBox(NULL, TEXT("申请内存失败"), TEXT("错误"), MB_OK);
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
		MessageBox(NULL, TEXT("创建远程线程失败"), TEXT("错误"), MB_OK);
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
			MessageBox(NULL, TEXT("申请内存失败"), TEXT("错误"), MB_OK);
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
		MessageBox(NULL, TEXT("创建远程线程失败"), TEXT("错误"), MB_OK);
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
		
		//将原函数跳转到写入函数
		temp = (int)((DWORD)allNut.addr - 0x464528);
		WriteProcessMemory(hGameP, (LPVOID)0x464523, &jmp, 1, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x464524, &temp, 4, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x464528, &nop, 1, NULL);

	}
}


void End(HWND hwnd)
{
	//原本的操作码
	char a = 0x84; 
	char c = 0x74;
	char str2[6] = { 0x0f, 0x84, 0x1f, 0x09, 0x00, 0x00 };	//叠植物
	char str3[4] = { 0x55, 0x8b, 0xec, 0x83 };				//免暂停
	char str4[2] = { 0x75, 0x3e };							//自动收集
	char str5	 = 0x7e;									//无cd
	char str6[]  = {0x0f,0x85,0xfa,0x01,0x00,0x00};			//土豆雷
	char str7[]  = { 0x75, 0x5f };							//大嘴花
	char str8[] = { 0x75, 0x05 };							//毁灭菇
	char str9[] = { 0x75, 0x78 };							//阳光菇
	char str10[] = { 0x0f, 0x85, 0x47, 0x05, 0x00, 0x00 };	//磁力菇
	char str11[] = { 0x0f, 0x85, 0x9c, 0x01, 0x00, 0x00 };	//玉米炮
	char str12[] = { 0x0f, 0x85, 0x84, 0x00, 0x00, 0x00 };
	char str13[] = { 0x0f, 0x85, 0xe5, 0x00, 0x00, 0x00 };
	char str14[] = { 0x51, 0x83, 0xf8 };
	char str15[] = { 0x74 };
	char str16[] = { 0x83, 0x80, 0x20, 0x02, 0x00, 0x00, 0xff };
	char str17[] = { 0x0f, 0x84, 0x79, 0x02, 0x00, 0x00 };
	char str18[] = { 0x8B, 0x77, 0x40, 0x8D, 0x0C, 0x40 };


	if (CheckProcessOn() != NULL)
	{
		//若关闭时游戏还在运行，则需要恢复一些已修改的内存

		//叠植物恢复
		WriteProcessMemory(hGameP, (LPVOID)0x0040fe30, &a, 1, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x00438e40, &c, 1, NULL);
		//免暂停恢复
		WriteProcessMemory(hGameP, (LPVOID)0x004502C0, &str3, 4, NULL);
		//竖排种植恢复
		WriteProcessMemory(hGameP, (LPVOID)0x410ae6, &str13, 6, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x43903c, &str12, 6, NULL);
		//关闭无CD
		WriteProcessMemory(hGameP, (LPVOID)0x00487296, &str5, 1, NULL);
		//土豆雷恢复
		WriteProcessMemory(hGameP, (LPVOID)0x45fe53, &str6, 6, NULL);
		//大嘴花
		WriteProcessMemory(hGameP, (LPVOID)0x00461565, &str7, 2, NULL);
		//毁灭菇
		WriteProcessMemory(hGameP, (LPVOID)0x0041d79e, &str8, 2, NULL);
		//阳光菇
		WriteProcessMemory(hGameP, (LPVOID)0x0045fba3, &str9, 2, NULL);
		//磁力菇
		WriteProcessMemory(hGameP, (LPVOID)0x00461e36, &str10, 6, NULL);
		//玉米加农炮
		WriteProcessMemory(hGameP, (LPVOID)0x0046103a, &str11, 6, NULL);
		//紫卡
		WriteProcessMemory(hGameP, (LPVOID)0x0041d7d0, &str14, 3, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x0040e477, &str15, 1, NULL);
		//钉耙
		WriteProcessMemory(hGameP, (LPVOID)0x0040bb25, &str16, 7, NULL);
		WriteProcessMemory(hGameP, (LPVOID)0x0040b9e2, &str17, 6, NULL);
		//蘑菇
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
	

	//删掉键盘钩子
	DeleteHook();
	//删除定时器
	KillTimer(hwnd, ID_TIMER);
}