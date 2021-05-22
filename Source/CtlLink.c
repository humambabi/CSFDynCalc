//
// CSF Dynamic CALC v1.0
// (CtlLink.c) CtlLink Custom Control
//

#include "Build.h"
#include "GdipFlatC.h"
#include <WindowsX.h>
#include "AppDefs.h"


// External global variables
extern HINSTANCE			g_hInstApp;


// Local Object's definitions
typedef struct LINKDATA {
	GpFont		*pFont;
	BOOL			bStateHot;
	BOOL			bTracking;
	BOOL			bMouseDown;
	RECT			rcActive;
	COLORREF		clrBackground;
} LINKDATA;


// External function prototypes
GpFont *APIENTRY CreateGdipFont(int iPointSize, int iWeight, BOOL bItalic, BOOL bUnderline);
GpGraphics *APIENTRY CreateGdipGraphics(HDC hDC, GpUnit Unit, CompositingQuality CmQua, TextRenderingHint TxtRnHint);
void APIENTRY ClearDC(HDC hDC, COLORREF clrBrush, int iLeft, int iTop, int iRight, int iBottom);
TCHAR *APIENTRY GetCtlTextAlloc(HWND hWnd);
GpStringFormat *APIENTRY CreateGdipStringFormat(StringAlignment saHorz, StringAlignment saVert);
int APIENTRY Float2IntComplete(float fVal);
int APIENTRY DPIScaleY(int iY);


///////////////////////////////////////////////////////////////////////////////////////////////////
static void APIENTRY CtlLink_Clicked(HWND hWndLink) {
	if (IsWindowEnabled(hWndLink) == FALSE) return;
	FORWARD_WM_COMMAND(GetParent(hWndLink), GetWindowID(hWndLink), hWndLink, BN_CLICKED, PostMessage);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
static void APIENTRY MeasureActiveRect(HWND hWnd) {
	HDC				hDCWnd = GetDC(hWnd);
	GpGraphics		*pGr = CreateGdipGraphics(hDCWnd, UnitPixel, CompositingQualityAssumeLinear, TextRenderingHintAntiAlias);
	GpStringFormat	*pStrFmt = CreateGdipStringFormat(StringAlignmentNear, StringAlignmentNear);
	RectF				RcIn, RcOut;
	LINKDATA			*pLinkData = (LINKDATA *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	WCHAR				*pwsText = (WCHAR *)GetCtlTextAlloc(hWnd);
	RECT				rcCli;
	UINT				uWText, uHText;


	GetClientRect(hWnd, &rcCli);
	RcIn.X = 0.0f; RcIn.Y = 0.0f; RcIn.Width = 1000.0f, RcIn.Height = 500.0f;
	GdipMeasureString(pGr, pwsText, lstrlen(pwsText), pLinkData->pFont, &RcIn, pStrFmt, &RcOut, NULL, NULL);
	GdipDeleteStringFormat(pStrFmt);
	GdipDeleteGraphics(pGr);
	ReleaseDC(hWnd, hDCWnd);
	HeapFree(GetProcessHeap(), 0, pwsText);

	uWText = Float2IntComplete(RcOut.Width);
	uHText = Float2IntComplete(RcOut.Height);
	pLinkData->rcActive.left = 0;
	pLinkData->rcActive.right = pLinkData->rcActive.left + uWText;

	pLinkData->rcActive.top = 0;
	pLinkData->rcActive.bottom = pLinkData->rcActive.top + uHText;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
static void APIENTRY DrawCtlLink(HWND hWnd, HDC hDC) {
	RECT				rcCli;
	LINKDATA			*pLinkData = (LINKDATA *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	TCHAR				*ptsText = (TCHAR *)GetCtlTextAlloc(hWnd);
	HDC				hDCMem;
	HBITMAP			hBmpMem, hBmpMemOrig;
	GpGraphics		*pGr;
	GpStringFormat	*pStrFmt = CreateGdipStringFormat(StringAlignmentNear, StringAlignmentNear);
	GpBrush			*pBrush;
	RectF				RcText;
	COLORREF			clrBrush;


	// Initialize
	GetClientRect(hWnd, &rcCli);
	hDCMem = CreateCompatibleDC(hDC);
	hBmpMem = CreateCompatibleBitmap(hDC, rcCli.right, rcCli.bottom);
	hBmpMemOrig = SelectBitmap(hDCMem, hBmpMem);
	pGr = CreateGdipGraphics(hDCMem, UnitPixel, CompositingQualityAssumeLinear, TextRenderingHintAntiAlias);

	// Clear the background
	ClearDC(hDCMem, pLinkData->clrBackground, 0, 0, rcCli.right, rcCli.bottom);

	// Draw the text
	if (ptsText != NULL) {
		clrBrush = (pLinkData->bStateHot) ? RGB(70, 163, 255) : RGB(0, 83, 166);
		GdipCreateSolidFill(RGB2ARGB(255, clrBrush), &pBrush);

		RcText.X = (REAL)pLinkData->rcActive.left;
		RcText.Y = (REAL)pLinkData->rcActive.top;
		RcText.Width = (REAL)pLinkData->rcActive.right;
		RcText.Height = (REAL)pLinkData->rcActive.bottom;
		GdipDrawString(pGr, ptsText, lstrlen(ptsText), pLinkData->pFont, &RcText, pStrFmt, pBrush);

		GdipDeleteBrush(pBrush);
		HeapFree(GetProcessHeap(), 0, ptsText);

		if (pLinkData->bStateHot) {
			GpPen	*pPen;
			
			GdipCreatePen1(MAKEARGB(255, 70, 163, 255), 1.0f, UnitPixel, &pPen);
			GdipDrawLine(pGr, pPen, (float)pLinkData->rcActive.left, (float)pLinkData->rcActive.bottom - 1.0f,
				(float)pLinkData->rcActive.right, (float)pLinkData->rcActive.bottom - 1.0f);
			GdipDeletePen(pPen);
		}
		if (GetFocus() == hWnd) {
			RECT	rcFocus = { pLinkData->rcActive.left, pLinkData->rcActive.top, pLinkData->rcActive.right, pLinkData->rcActive.bottom + DPIScaleY(2) };

			SetBkColor(hDCMem, RGB(0, 0, 0));
			SetTextColor(hDCMem, RGB(100, 100, 100));
			DrawFocusRect(hDCMem, &rcFocus);
		}
	}

	BitBlt(hDC, 0, 0, rcCli.right, rcCli.bottom, hDCMem, 0, 0, SRCCOPY);

	GdipDeleteStringFormat(pStrFmt);
	GdipDeleteGraphics(pGr);
	SelectBitmap(hDCMem, hBmpMemOrig);
	DeleteBitmap(hBmpMem);
	DeleteDC(hDCMem);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
static BOOL APIENTRY CtlLink_OnCreate(HWND hWnd, CREATESTRUCT *pCS) {
	LINKDATA	*pData = (LINKDATA *)pCS->lpCreateParams;

	// Save the window's private data
	SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pData);

	MeasureActiveRect(hWnd);
	return TRUE; // Means OK
}


///////////////////////////////////////////////////////////////////////////////////////////////////
static void APIENTRY CtlLink_OnPaint(HWND hWnd) {
	PAINTSTRUCT	Ps;
	
	BeginPaint(hWnd, &Ps);
	DrawCtlLink(hWnd, Ps.hdc);
	EndPaint(hWnd, &Ps);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
static void APIENTRY CtlLink_OnMouseMove(HWND hWnd, int iX, int iY, UINT uKeyFlags) {
	LINKDATA	*pLinkData = (LINKDATA *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	
	UNUSED(uKeyFlags);

	if ((iX < pLinkData->rcActive.left) || (iX > pLinkData->rcActive.right) || (iY < pLinkData->rcActive.top) ||
			(iY > pLinkData->rcActive.bottom)) {
		if (pLinkData->bTracking != FALSE) {
			TRACKMOUSEEVENT	tme;

			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE | TME_CANCEL;
			tme.hwndTrack = hWnd;
			tme.dwHoverTime = HOVER_DEFAULT;
			TrackMouseEvent(&tme);

			pLinkData->bTracking = FALSE;
		}

		pLinkData->bMouseDown = FALSE;
		pLinkData->bStateHot = FALSE;
		InvalidateRect(hWnd, NULL, FALSE);
		SetCursor(LoadCursor(NULL, IDC_ARROW));
	} else {
		pLinkData->bStateHot = TRUE;
		InvalidateRect(hWnd, NULL, FALSE);
		SetCursor(LoadCursor(NULL, IDC_HAND));
		if (pLinkData->bTracking == FALSE) {
			TRACKMOUSEEVENT	tme;

			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = hWnd;
			tme.dwHoverTime = HOVER_DEFAULT;
			TrackMouseEvent(&tme);

			pLinkData->bTracking = TRUE;
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY CtlLink_OnMouseLeave(HWND hWnd) {
	LINKDATA	*pLinkData = (LINKDATA *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	pLinkData->bTracking = FALSE;
	pLinkData->bMouseDown = FALSE;
	pLinkData->bStateHot = FALSE;
	InvalidateRect(hWnd, NULL, FALSE);
	SetCursor(LoadCursor(NULL, IDC_ARROW));
}


///////////////////////////////////////////////////////////////////////////////////////////////////
static void APIENTRY CtlLink_OnSetFocus(HWND hWnd, HWND hWndOldFocus) {
	HDC			hDCWnd = GetDC(hWnd);
	LINKDATA	*pLinkData = (LINKDATA *)GetWindowLongPtr(hWnd, GWLP_USERDATA);


	UNUSED(hWndOldFocus);

	pLinkData->bStateHot = TRUE;
	DrawCtlLink(hWnd, hDCWnd);
	ReleaseDC(hWnd, hDCWnd);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
static void APIENTRY CtlLink_OnKillFocus(HWND hWnd, HWND hWndNewFocus) {
	HDC			hDCWnd = GetDC(hWnd);
	LINKDATA	*pLinkData = (LINKDATA *)GetWindowLongPtr(hWnd, GWLP_USERDATA);


	UNUSED(hWndNewFocus);

	pLinkData->bStateHot = FALSE;
	DrawCtlLink(hWnd, hDCWnd);
	ReleaseDC(hWnd, hDCWnd);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
static void APIENTRY CtlLink_OnLButtonDown(HWND hWnd, BOOL bDoubleClick, int iX, int iY, UINT uKeyFlags) {
	UNUSED(bDoubleClick);
	UNUSED(iX);
	UNUSED(iY);
	UNUSED(uKeyFlags);

	SetCapture(hWnd);
	SetFocus(hWnd);
	((LINKDATA *)GetWindowLongPtr(hWnd, GWLP_USERDATA))->bMouseDown = TRUE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
static void APIENTRY CtlLink_OnLButtonUp(HWND hWnd, int iX, int iY, UINT uKeyFlags) {
	LINKDATA	*pLinkData = (LINKDATA *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	BOOL		bWasDown = pLinkData->bMouseDown;
	RECT		rcCli;


	UNUSED(uKeyFlags);

	ReleaseCapture();
	pLinkData->bMouseDown = FALSE;
	GetClientRect(hWnd, &rcCli);
	if ((iX >= 0) && (iX <= rcCli.right) && (iY >= 0) && (iY <= rcCli.bottom)) {
		if (bWasDown != FALSE) CtlLink_Clicked(hWnd);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
static void APIENTRY CtlLink_OnKey(HWND hWnd, UINT uVK, BOOL bDown, int iRepeat, UINT uFlags) {
	UNUSED(bDown);
	UNUSED(iRepeat);
	UNUSED(uFlags);

	if ((uVK == VK_SPACE) || (uVK == VK_RETURN)) CtlLink_Clicked(hWnd);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
static void APIENTRY CtlLink_OnDestroy(HWND hWnd) {
	LINKDATA	*pLinkData = (LINKDATA *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	GdipDeleteFont(pLinkData->pFont);
	HeapFree(GetProcessHeap(), 0, pLinkData);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
static LRESULT CALLBACK LinkCtl_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		HANDLE_MSG(hWnd, WM_CREATE, CtlLink_OnCreate);
		HANDLE_MSG(hWnd, WM_PAINT, CtlLink_OnPaint);
		HANDLE_MSG(hWnd, WM_MOUSEMOVE, CtlLink_OnMouseMove);
		HANDLE_MSG(hWnd, WM_MOUSELEAVE, CtlLink_OnMouseLeave);
		HANDLE_MSG(hWnd, WM_SETFOCUS, CtlLink_OnSetFocus);
		HANDLE_MSG(hWnd, WM_KILLFOCUS, CtlLink_OnKillFocus);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, CtlLink_OnLButtonDown);
		HANDLE_MSG(hWnd, WM_LBUTTONUP, CtlLink_OnLButtonUp);
		HANDLE_MSG(hWnd, WM_KEYUP, CtlLink_OnKey);
		HANDLE_MSG(hWnd, WM_DESTROY, CtlLink_OnDestroy);
		default: return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
HWND APIENTRY CreateCtlLink(TCHAR *ptsText, int iX, int iY, UINT uW, UINT uH, HWND hWndParent, UINT uCtlID, COLORREF clrBkgnd) {
	WNDCLASS	WndCls;
	HWND		hWndLink;
	LINKDATA	*pLinkData = (LINKDATA *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY | HEAP_GENERATE_EXCEPTIONS, sizeof(LINKDATA));


	// Register the class only once
	if (GetClassInfo(g_hInstApp, WC_CTLLINK, &WndCls) == FALSE) {
		ZeroMemory(&WndCls, sizeof(WNDCLASS));
		WndCls.hbrBackground = NULL;	// To prevent the system from drawing a background
		WndCls.hCursor = NULL;			// To set the icon explicitly
		WndCls.hIcon = NULL;				// The system provides a default icon
		WndCls.hInstance = g_hInstApp;
		WndCls.lpfnWndProc = (WNDPROC)LinkCtl_WndProc;
		WndCls.lpszClassName = WC_CTLLINK;
		WndCls.style = CS_OWNDC;
		RegisterClass(&WndCls);
	}

	// Initialize the CtlLink window data here because we need the parameters (all other un-initialized members are actually zeroed)
	pLinkData->pFont = CreateGdipFont(11, FW_NORMAL, FALSE, FALSE);
	pLinkData->clrBackground = clrBkgnd;

	// Create a new Link Control window (invisible initially), and save pLinkData)
#pragma warning(disable: 4312) // Only for x64 systems: Warning of converting UINT to HMENU (Bigger data type)
	hWndLink = CreateWindow(WC_CTLLINK, ptsText, WS_CHILD | WS_TABSTOP, iX, iY, uW, uH, hWndParent, (HMENU)uCtlID, g_hInstApp, pLinkData);
#pragma warning(default: 4312) // Re-enable it
	if (hWndLink == NULL) {
		GdipDeleteFont(pLinkData->pFont);
		HeapFree(GetProcessHeap(), 0, pLinkData);
		return NULL;
	}

	ShowWindow(hWndLink, SW_SHOW);
	return hWndLink;
}
