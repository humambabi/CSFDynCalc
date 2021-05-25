//
// CSF Dynamic CALC
// By Humam A. Babi (humam_babi@yahoo.com), 2021 
//
// (MainWnd.c) Application's main window event procedures
//

#include "Build.h"
#include <CommCtrl.h>
#include <WindowsX.h>
#include "AppDefs.h"
#include "Resources.h"


// Global variables
HINSTANCE				g_hInstApp;
HANDLE					g_hMtxAppInstance;
HWND						g_hWndDialog = NULL;
int						g_iDpiX = 0, g_iDpiY = 0, g_iCurPage = PAGE_EVANS;


// External function prototypes
BOOL APIENTRY InitLibs(void);
void APIENTRY FreeLibs(void);
int APIENTRY DPIScaleX(int iX);
int APIENTRY DPIScaleY(int iY);
BOOL APIENTRY PrimaryCheck(void);
void APIENTRY GetMainWndPos(POINT *pptWnd);
BOOL APIENTRY MainWnd_OnCreate(HWND hWnd, CREATESTRUCT *pCreateStruct);
void APIENTRY MainWnd_OnCustomShowDisclaimer(HWND hWnd);
int APIENTRY MainWnd_OnDpiChanged(HWND hWnd, WORD wDpiX, WORD wDpiY, RECT *pRectWnd);
void APIENTRY MainWnd_OnCommand(HWND hWnd, int iID, HWND hWndCtl, UINT uCodeNotify);
BOOL APIENTRY MainWnd_OnEraseBkgnd(HWND hWnd, HDC hDC);
void APIENTRY MainWnd_OnPaint(HWND hWnd);
void APIENTRY MainWnd_OnMouseMove(HWND hWnd, int iX, int iY, UINT uKeyFlags);
void APIENTRY MainWnd_OnLButtonDown(HWND hWnd, BOOL bDoubleClick, int iX, int iY, UINT uKeyFlags);
void APIENTRY MainWnd_OnLButtonUp(HWND hWnd, int iX, int iY, UINT uKeyFlags);
void APIENTRY MainWnd_OnSize(HWND hWnd, UINT uState, int iCliWidth, int iCliHeight);
void APIENTRY MainWnd_OnGetMinMaxInfo(HWND hWnd, MINMAXINFO* pMinMaxInfo);
void APIENTRY MainWnd_OnDestroy(HWND hWnd);


///////////////////////////////////////////////////////////////////////////////////////////////////
static LRESULT CALLBACK MainWnd_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		HANDLE_MSG(hWnd, WM_CREATE, MainWnd_OnCreate);
		HANDLE_MSG(hWnd, CM_SHOWDISCLAIMER, MainWnd_OnCustomShowDisclaimer);
		HANDLE_MSG(hWnd, WM_COMMAND, MainWnd_OnCommand);
		HANDLE_MSG(hWnd, WM_SIZE, MainWnd_OnSize);
		HANDLE_MSG(hWnd, WM_GETMINMAXINFO, MainWnd_OnGetMinMaxInfo);
		HANDLE_MSG(hWnd, WM_MOUSEMOVE, MainWnd_OnMouseMove);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, MainWnd_OnLButtonDown);
		HANDLE_MSG(hWnd, WM_LBUTTONUP, MainWnd_OnLButtonUp);
		HANDLE_MSG(hWnd, WM_DPICHANGED, MainWnd_OnDpiChanged);
		HANDLE_MSG(hWnd, WM_ERASEBKGND, MainWnd_OnEraseBkgnd);
		HANDLE_MSG(hWnd, WM_PAINT, MainWnd_OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, MainWnd_OnDestroy);
	}
	
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
static HWND APIENTRY CreateMainWindow(int nShowCmd) {
	WNDCLASSEX	WndClsEx;
	HWND			hWndMain;
	POINT			ptPosition;


	// Register the main window's window class, then create the main window
	ZeroMemory(&WndClsEx, sizeof(WNDCLASSEX));
	WndClsEx.cbSize = sizeof(WNDCLASSEX);
	WndClsEx.hbrBackground = NULL; // Don't allow erasing of the background
	WndClsEx.hCursor = NULL; // Don't set the cursor. We will set it explicitly
	WndClsEx.hIcon = LoadIcon(g_hInstApp, MAKEINTRESOURCE(IDI_APPICON));
	WndClsEx.hIconSm = NULL; // Use an appropriate size of .hIcon
	WndClsEx.hInstance = g_hInstApp;
	WndClsEx.lpfnWndProc = MainWnd_WndProc;
	WndClsEx.lpszClassName = WC_MAINWND;

	if (RegisterClassEx(&WndClsEx) == 0) return NULL;

	// Calculate the position of the main window to be centered in the desktop area (according toits size)
	GetMainWndPos(&ptPosition);
	hWndMain = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_CONTROLPARENT, WC_MAINWND, STR_APPNAME, WS_POPUP | WS_OVERLAPPEDWINDOW |
		WS_CLIPCHILDREN | WS_CLIPSIBLINGS, ptPosition.x, ptPosition.y, MAINWND_DEFWIDTH, MAINWND_DEFHEIGHT, HWND_DESKTOP, NULL,
		g_hInstApp, NULL);
	if (hWndMain == NULL) return FALSE;

	ShowWindow(hWndMain, nShowCmd);
	UpdateWindow(hWndMain);

	return hWndMain; // Creation OK
}


///////////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) {
	INITCOMMONCONTROLSEX	ICCEx;
	MSG						Msg = { 0 };
	HWND						hWndMain;


	UNUSED(lpCmdLine);
	UNUSED(hPrevInstance);

	// Initialize the global variables
	g_hInstApp = hInstance;
	g_hMtxAppInstance = NULL;

	// Initialize the Common Controls library (and indirectly enable Windows Visual Styles)
	ICCEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	ICCEx.dwICC = ICC_WIN95_CLASSES | ICC_STANDARD_CLASSES;
	InitCommonControlsEx(&ICCEx);

	// Initialize some libraries
	if (InitLibs() == FALSE) {
		MessageBox(HWND_DESKTOP, TEXT("Can not load some libraries.\r\nThe program with quit now."), STR_APPNAME, MB_ICONEXCLAMATION);
		return 0;
	}

	// Check for multi-instancing and the OS version
	if (PrimaryCheck() == FALSE) {
		FreeLibs();
		return 0;
	}

	// Create the application's main window
	hWndMain = CreateMainWindow(nShowCmd);
	if (hWndMain == NULL) {
		FreeLibs();
		return 0;
	}

	// The application's main loop
	while (IsWindow(hWndMain) && GetMessage(&Msg, NULL, 0, 0) > 0) {
		// Process child dialog's (page dialog's) messages
		if (IsDialogMessage(g_hWndDialog, &Msg)) continue;

		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	// Clean-up
	FreeLibs();
	return (int)Msg.wParam;
}
