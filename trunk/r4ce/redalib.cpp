#include "stdafx.h"
#include "aygshell.h"
#include "redalib.h"
#include "graf.h"

const TCHAR wincls[5] = TEXT("reda");

HINSTANCE hInst;
HWND hWnd;

unsigned short mxpos,mypos;
bool mbutton;
int tecla;
int evento=0;
// nuevas interrupciones
int SYSirqlapiz=0;
int SYSirqteclado=0;
int SYSirqsonido=0;
int SYSirqred=0;
int SYSirqjoystick=0;

GXKeyList kl;				// Hardware buttons

#define MENU_HEIGHT 26

//------------------------------------------------------------------------------
void taskbar(bool show)
{
RECT rc;
GetWindowRect(hWnd,&rc);
HWND hWndTB=FindWindow(TEXT("HHTaskbar"),NULL);
if (show)
	{
	SHFullScreen(hWnd,SHFS_SHOWTASKBAR | SHFS_SHOWSIPBUTTON + SHFS_SHOWSTARTICON);
	ShowWindow(hWndTB,SW_SHOW );
	MoveWindow(hWnd,rc.left,rc.top + MENU_HEIGHT,rc.right,rc.bottom - 2 * MENU_HEIGHT,TRUE);
	}
else
	{
	SHFullScreen(hWnd, SHFS_HIDETASKBAR | SHFS_HIDESIPBUTTON + SHFS_HIDESTARTICON);
	ShowWindow(hWndTB, SW_HIDE );
	MoveWindow(hWnd,rc.left,rc.top - MENU_HEIGHT,rc.right,rc.bottom + MENU_HEIGHT,TRUE);
	}
}

// rutina de loop boludeador
//------------------------------------------------------------
void update()
{
MSG msg;
while (PeekMessage(&msg,0,0,0,PM_NOREMOVE)==TRUE) {
	GetMessage(&msg,0,0,0);
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	}
}


//------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
switch (message) 
	{
	case WM_MOUSEMOVE:
		mxpos=LOWORD(lParam);mypos=HIWORD(lParam);
		evento=SYSirqlapiz;break;
	case WM_LBUTTONDOWN:
		mxpos=LOWORD(lParam);mypos=HIWORD(lParam);mbutton=true;
		evento=SYSirqlapiz;break;
	case WM_LBUTTONUP:
		mbutton=false;evento=SYSirqlapiz;break;
	case WM_KEYUP:
		tecla|=wParam;evento=SYSirqteclado;break;
	case WM_KEYDOWN:
		tecla&=~wParam;evento=SYSirqteclado;break;
    case WM_DESTROY:
        GXCloseInput();GXCloseDisplay();//taskbar(true);
        PostQuitMessage(0);break;
    case WM_KILLFOCUS:
        GXSuspend();break;
    case WM_SETFOCUS:
        GXResume();break;
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE) GXSuspend(); else GXResume();
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
   }
return 0;
}
//------------------------------------------------------------------------------
ATOM MyRegisterClass(HINSTANCE hInstance)
{
WNDCLASS wcls;
wcls.style			= 0;
wcls.lpfnWndProc	= (WNDPROC)WndProc;
wcls.cbClsExtra		= 0;
wcls.cbWndExtra		= 0;
wcls.hInstance		= hInstance;
wcls.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(1));
wcls.hCursor		= 0;
wcls.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
wcls.lpszMenuName	= 0;
wcls.lpszClassName	= wincls;
return RegisterClass(&wcls);
}
//------------------------------------------------------------------------------
BOOL InitInstance(HINSTANCE hi,int nCmdShow)
{
hInst=hi;
hWnd=CreateWindowEx(WS_EX_TOPMOST,wincls,wincls,WS_VISIBLE,0,0,240,320,NULL,NULL,hi,NULL);
if (!hWnd) return FALSE;
ShowWindow(hWnd, nCmdShow);
UpdateWindow(hWnd);
return TRUE;
}

//*****************************************************************************************
extern void __cdecl main(void);
//*****************************************************************************************
//------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow)
{
//taskbar(false);
if (!MyRegisterClass(hInstance)) return FALSE;
if (!InitInstance(hInstance, nCmdShow)) return FALSE;
GXOpenDisplay(hWnd,GX_FULLSCREEN);
GXOpenInput();
kl=GXGetDefaultKeys(GX_NORMALKEYS);
mbutton=false;
//srand(clock());
gr_init();
//---------------------------------------------------------------------
main();
//---------------------------------------------------------------------
gr_fin();
GXCloseInput();
GXCloseDisplay();
//taskbar(true);
DestroyWindow(hWnd);
return 0;
}
