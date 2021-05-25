//
// CSF Dynamic CALC
// (MainWnd.c) Application's main window event procedures
//

#include "Build.h"
#include <WindowsX.h>
#include "GdipFlatC.h"
#include "AppDefs.h"
#include "Resources.h"


// External global variables
extern HINSTANCE			g_hInstApp;
extern int					g_iDpiX, g_iDpiY, g_iCurPage;
extern HWND					g_hWndDialog;


// Local (Object's) definitions
int							o_iLastMouseHitpoint;


// External function prototypes
int APIENTRY DPIScaleX(int iX);
int APIENTRY DPIScaleY(int iY);
void APIENTRY ClearDC(HDC hDC, COLORREF clrBrush, int iLeft, int iTop, int iRight, int iBottom);
GpGraphics *APIENTRY CreateGdipGraphics(HDC hDC, GpUnit Unit, CompositingQuality CmQua, TextRenderingHint TxtRnHint);
void APIENTRY DrawTabs(GpGraphics *pGr, RECT *prcCli);
int APIENTRY PointOnTabbtn(POINT Pt);
void APIENTRY LoadTabPage(HWND hWndParent, int iPage);
HFONT APIENTRY CreateGdiFont(int iPointSize, int iWeight);
INT_PTR CALLBACK Disclaimer_DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND APIENTRY CreateCtlLink(TCHAR *ptsText, int iX, int iY, UINT uW, UINT uH, HWND hWndParent, UINT uCtlID, COLORREF clrBkgnd, BOOL bTypeRed);
INT_PTR CALLBACK About_DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);


///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL APIENTRY MainWnd_OnCreate(HWND hWnd, CREATESTRUCT *pCreateStruct) {
	MAINWNDDATA	*pData;
	RECT			rcCli;


	// Create and save the private data structure
	pData = (MAINWNDDATA *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY | HEAP_GENERATE_EXCEPTIONS, sizeof(MAINWNDDATA));
	pData->hFontPageTitle = CreateGdiFont(16, FW_BOLD);
	pData->hFontInput = CreateGdiFont(10, FW_BOLD);
	pData->hFontResults = CreateGdiFont(11, FW_BOLD);
	pData->hBrushCtlBkgnd = CreateSolidBrush(CLR_BACKGROUND);
	SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pData);

	// Create child controls
	GetClientRect(hWnd, &rcCli); // Client rect is not included in CREATESTRUCT members
	CreateCtlLink(TEXT("About"), TABS_OUTER_MARGIN_X + TABS_ITEM_CURVE_MARGIN_X + (TABS_LABELAREA_WIDTH / 2) - (MAINWND_LNK_ABOUT_WIDTH / 2),
		rcCli.bottom - MAINWND_LNK_HEIGHT - MAINWND_LNK_MARGINBOTTOM, MAINWND_LNK_ABOUT_WIDTH, MAINWND_LNK_HEIGHT,
		hWnd, IDC_LNK_ABOUT, CLR_TABAREA, TRUE);

	// Load default page
	LoadTabPage(hWnd, g_iCurPage);

	// Show the disclaimer after showing the main window (but disable the main window)
	LoadLibrary(TEXT("Riched20.dll")); // No need to unload it
	PostMessage(hWnd, CM_SHOWDISCLAIMER, 0, 0);

	return TRUE; // Means OK
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY MainWnd_OnCustomShowDisclaimer(HWND hWnd) {
	INT_PTR iRet = DialogBox(g_hInstApp, MAKEINTRESOURCE(IDD_DISCLAIMER), hWnd, Disclaimer_DlgProc);

	// Close the app if the user "disagree"d to the disclaimer
	if (iRet == IDCANCEL) DestroyWindow(hWnd);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
int APIENTRY MainWnd_OnDpiChanged(HWND hWnd, WORD wDpiX, WORD wDpiY, RECT *pRectWnd) {
	LONG	lWidth = pRectWnd->right - pRectWnd->left, lHeight = pRectWnd->bottom - pRectWnd->top;

	// Update the global DPI settings
	g_iDpiX = wDpiX;
	g_iDpiY = wDpiY;

	// Redraw the entire window on every DPI change
	InvalidateRect(hWnd, NULL, FALSE);

	// Note: Child controls may need update!

	// Use the suggested new window size.
	SetWindowPos(hWnd, NULL, pRectWnd->left, pRectWnd->top, lWidth, lHeight, SWP_NOZORDER | SWP_NOACTIVATE);
	PostMessage(hWnd, WM_SIZE, SIZE_RESTORED, MAKELPARAM(lWidth, lHeight));

	return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY MainWnd_OnCommand(HWND hWnd, int iID, HWND hWndCtl, UINT uCodeNotify) {
	UNUSED(uCodeNotify);
	UNUSED(hWndCtl);

	switch (iID) {
		case IDC_LNK_ABOUT:
			DialogBox(g_hInstApp, MAKEINTRESOURCE(IDD_ABOUT), hWnd, About_DlgProc);
			break;
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL APIENTRY MainWnd_OnEraseBkgnd(HWND hWnd, HDC hDC) {
	UNUSED(hWnd);
	UNUSED(hDC);

	return TRUE; // Non zero => No further erasing required
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY MainWnd_OnPaint(HWND hWnd) {
	PAINTSTRUCT	Ps;
	HDC			hDCMem;
	GpGraphics	*pGr;
	HBITMAP		hBmpMem, hBmpMemOrig;
	RECT			rcCli;


	// Initialization
	GetClientRect(hWnd, &rcCli);
	BeginPaint(hWnd, &Ps);
	hDCMem = CreateCompatibleDC(Ps.hdc);
	hBmpMem = CreateCompatibleBitmap(Ps.hdc, rcCli.right, rcCli.bottom);
	hBmpMemOrig = SelectBitmap(hDCMem, hBmpMem);
	pGr = CreateGdipGraphics(hDCMem, UnitPixel, CompositingQualityAssumeLinear, TextRenderingHintAntiAlias);

	// Paint the background
	ClearDC(hDCMem, CLR_BACKGROUND, 0, 0, rcCli.right, rcCli.bottom);

	// Draw the tabs area
	DrawTabs(pGr, &rcCli);

	// Output the drawing to the window's DC
	BitBlt(Ps.hdc, 0, 0, rcCli.right, rcCli.bottom, hDCMem, 0, 0, SRCCOPY);
	EndPaint(hWnd, &Ps);

	// Clean up
	GdipDeleteGraphics(pGr);
	hBmpMem = SelectBitmap(hDCMem, hBmpMemOrig);
	DeleteBitmap(hBmpMem);
	DeleteDC(hDCMem);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY MainWnd_OnMouseMove(HWND hWnd, int iX, int iY, UINT uKeyFlags) {
	POINT	PtMouse;

	UNUSED(hWnd);
	UNUSED(uKeyFlags);

	// Change the mouse cursor into a "hand" cursor when on a tab button
	PtMouse.x = iX; PtMouse.y = iY;
	SetCursor(LoadCursor(NULL, (PointOnTabbtn(PtMouse) < 0) ? IDC_ARROW : IDC_HAND));
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY MainWnd_OnLButtonDown(HWND hWnd, BOOL bDoubleClick, int iX, int iY, UINT uKeyFlags) {
	POINT	PtMouse;

	UNUSED(uKeyFlags);
	UNUSED(bDoubleClick);

	PtMouse.x = iX; PtMouse.y = iY;
	o_iLastMouseHitpoint = PointOnTabbtn(PtMouse);

	SetCapture(hWnd); // Allow MainWnd to received WM_LBUTTONUP, even if the cursor is outside the window
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY MainWnd_OnLButtonUp(HWND hWnd, int iX, int iY, UINT uKeyFlags) {
	POINT	PtMouse;
	int	iMouseHitpoint;

	UNUSED(hWnd);
	UNUSED(uKeyFlags);

	PtMouse.x = iX; PtMouse.y = iY;
	iMouseHitpoint = PointOnTabbtn(PtMouse);

	// Only if MouseDown and MouseUP events was on the *SAME* tab button
	if ((iMouseHitpoint >= 0) && (iMouseHitpoint == o_iLastMouseHitpoint)) {
		LoadTabPage(hWnd, iMouseHitpoint); // PointOnTabbtn() will return the page index
	}

	ReleaseCapture();
	o_iLastMouseHitpoint = -1;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY MainWnd_OnSize(HWND hWnd, UINT uState, int iCliWidth, int iCliHeight) {
	UNUSED(uState);

	// Resize the child dialog
	if (IsWindow(g_hWndDialog)) {
		POINT	ptDlg;
		SIZE	zeDlg;

		ptDlg.x = TABS_OUTER_MARGIN_X + TABS_ITEM_CURVE_MARGIN_X + TABS_LABELAREA_WIDTH + DPIScaleX(2);
		ptDlg.y = TABS_OUTER_MARGIN_Y + TABS_ITEM_CURVE_MARGIN_Y + DPIScaleY(2);
		zeDlg.cx = iCliWidth - (TABS_OUTER_MARGIN_X + TABS_ITEM_CURVE_MARGIN_X) - ptDlg.x - DPIScaleX(1);
		zeDlg.cy = iCliHeight - (TABS_OUTER_MARGIN_X + TABS_ITEM_CURVE_MARGIN_X) - ptDlg.y - DPIScaleY(1);
		SetWindowPos(g_hWndDialog, NULL, ptDlg.x, ptDlg.y, zeDlg.cx, zeDlg.cy, SWP_NOZORDER);
	}

	// Set the position of "About" link
	SetWindowPos(GetDlgItem(hWnd, IDC_LNK_ABOUT), NULL, TABS_OUTER_MARGIN_X + TABS_ITEM_CURVE_MARGIN_X +
		(TABS_LABELAREA_WIDTH / 2) - (MAINWND_LNK_ABOUT_WIDTH / 2), iCliHeight - MAINWND_LNK_HEIGHT -
		MAINWND_LNK_MARGINBOTTOM, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);	

	// Repaint the main window
	InvalidateRect(hWnd, NULL, FALSE);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY MainWnd_OnGetMinMaxInfo(HWND hWnd, MINMAXINFO *pMinMaxInfo) {
	UNUSED(hWnd);

	pMinMaxInfo->ptMinTrackSize.x = MAINWND_MINWIDTH;
	pMinMaxInfo->ptMinTrackSize.y = MAINWND_MINHEIGHT;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY MainWnd_OnDestroy(HWND hWnd) {
	MAINWNDDATA *pData = (MAINWNDDATA *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (pData) {
		if (pData->hFontPageTitle) DeleteFont(pData->hFontPageTitle);
		if (pData->hFontInput) DeleteFont(pData->hFontInput);
		if (pData->hFontResults) DeleteFont(pData->hFontResults);
		if (pData->hBrushCtlBkgnd) DeleteBrush(pData->hBrushCtlBkgnd);

		HeapFree(GetProcessHeap(), 0, pData);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, 0);
	}

	PostQuitMessage(0);
}
