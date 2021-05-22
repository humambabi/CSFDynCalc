//
// CSF Dynamic CALC v1.0
// (Graphics.c) Contains graphics functions
//

#include "Build.h"
#include <WindowsX.h>
#include "GdipFlatC.h"
#include "AppDefs.h"


// External global variables
extern int				g_iDpiX, g_iDpiY, g_iCurPage;


// Local (Object's) definitions
ULONG_PTR				o_ulpGpToken;


// External Function prototypes
BOOL APIENTRY IsOSWin8OrLater(void);


///////////////////////////////////////////////////////////////////////////////////////////////////
int APIENTRY DPIScaleX(int iX) {
	if (!g_iDpiX) {
		HDC	hDC = GetDC(NULL);

		g_iDpiX = GetDeviceCaps(hDC, LOGPIXELSX);
		ReleaseDC(NULL, hDC);
	}
	
	return MulDiv(iX, g_iDpiX, 96);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
int APIENTRY DPIScaleY(int iY) {
	if (!g_iDpiY) {
		HDC	hDC = GetDC(NULL);

		g_iDpiY = GetDeviceCaps(hDC, LOGPIXELSY);
		ReleaseDC(NULL, hDC);
	}
	
	return MulDiv(iY, g_iDpiY, 96);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL APIENTRY InitLibs(void) {
	GdiplusStartupInput	GpInput;


	// Initialize the COM library
	if (CoInitializeEx(NULL, COINIT_MULTITHREADED | COINIT_SPEED_OVER_MEMORY | COINIT_DISABLE_OLE1DDE) != S_OK) {
		CoUninitialize(); // Even if CoInitializeEx() returned S_FALSE
		return FALSE;
	}

	// Initialize the GDI+ library
	GpInput.GdiplusVersion = 1;
	GpInput.DebugEventCallback = NULL;
	GpInput.SuppressBackgroundThread = FALSE;
	GpInput.SuppressExternalCodecs = TRUE;

	if (GdiplusStartup(&o_ulpGpToken, &GpInput, NULL) != Ok) {
		CoUninitialize();
		return FALSE;
	}

	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY FreeLibs(void) {
	// Shutdown the GDI+ library
	GdiplusShutdown(o_ulpGpToken);

	// Shutdown the COM library
	CoUninitialize();
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY ClearDC(HDC hDC, COLORREF clrBrush, int iLeft, int iTop, int iRight, int iBottom) {
	HBRUSH	hBrush = CreateSolidBrush(clrBrush);
	RECT	rcFill;


	rcFill.top = iTop;
	rcFill.left = iLeft;
	rcFill.right = iRight;
	rcFill.bottom = iBottom;
	FillRect(hDC, &rcFill, hBrush);
	DeleteBrush(hBrush);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
GpGraphics *APIENTRY CreateGdipGraphics(HDC hDC, GpUnit Unit, CompositingQuality CmQua, TextRenderingHint TxtRnHint) {
	GpGraphics	*pGr;
	int			iStatus;


	GdipCreateFromHDC(hDC, &pGr);

	// Set grahics paramenters
	GdipSetPageUnit(pGr, Unit);

	iStatus = GdipSetSmoothingMode(pGr, SmoothingModeAntiAlias8x8);			// GDI+ 1.1
	if (iStatus != Ok) GdipSetSmoothingMode(pGr, SmoothingModeHighQuality);	// GDI+ 1.0

	GdipSetCompositingQuality(pGr, CmQua);
	GdipSetTextRenderingHint(pGr, TxtRnHint);

	// Return the created graphics object
	return pGr;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY SuggestFontFace(TCHAR *ptsOut) {
	lstrcpy(ptsOut, IsOSWin8OrLater() ? TEXT("Segoe UI") : TEXT("Tahoma"));
}


///////////////////////////////////////////////////////////////////////////////////////////////////
GpFont *APIENTRY CreateGdipFont(int iPointSize, int iWeight, BOOL bItalic, BOOL bUnderline) {
	int		iHeight, iStatus;
	WCHAR		wsFaceName[LF_FACESIZE]; // MSDN: Must not exceed 32 characters, including the terminating null character.
	LOGFONTW	LogFont;
	GpFont	*pFont = NULL;
	HDC		hDCDesktop = GetDC(HWND_DESKTOP);


	if (!g_iDpiY) g_iDpiY = GetDeviceCaps(hDCDesktop, LOGPIXELSY);
	iHeight = -MulDiv(iPointSize, g_iDpiY, 72); // One inch contains 72 points vertically

	SuggestFontFace(wsFaceName);

	LogFont.lfHeight = iHeight;
	LogFont.lfWidth = 0L;
	LogFont.lfEscapement = 0L;
	LogFont.lfOrientation = 0L;
	LogFont.lfWeight = iWeight;
	LogFont.lfItalic = (BYTE)bItalic;
	LogFont.lfUnderline = (BYTE)bUnderline;
	LogFont.lfStrikeOut = FALSE;
	LogFont.lfCharSet = DEFAULT_CHARSET;
	LogFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	LogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	LogFont.lfQuality = CLEARTYPE_QUALITY; // Instead of DEFAULT_QUALITY
	LogFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	lstrcpy(LogFont.lfFaceName, wsFaceName);

	iStatus = GdipCreateFontFromLogfontW(hDCDesktop, &LogFont, &pFont);
	ReleaseDC(HWND_DESKTOP, hDCDesktop);

	if (iStatus == Ok) return pFont; else return NULL;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
HFONT APIENTRY CreateGdiFont(int iPointSize, int iWeight) {
	WCHAR		wsFaceName[LF_FACESIZE];
	HDC		hDCDesktop = GetDC(HWND_DESKTOP);


	if (!g_iDpiY) g_iDpiY = GetDeviceCaps(hDCDesktop, LOGPIXELSY);
	SuggestFontFace(wsFaceName);

	return CreateFont(-MulDiv(iPointSize, g_iDpiY, 72), 0, 0, 0, iWeight, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, wsFaceName);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
GpStringFormat *APIENTRY CreateGdipStringFormat(StringAlignment saHorz, StringAlignment saVert) {
	GpStringFormat* pSF, * pSFTemp;
	REAL				rTabStops[] = { 33.0f };


	GdipStringFormatGetGenericTypographic(&pSFTemp);
	GdipCloneStringFormat(pSFTemp, &pSF);
	GdipDeleteStringFormat(pSFTemp);

	GdipSetStringFormatTabStops(pSF, 0.0f, 1, rTabStops);

	GdipSetStringFormatAlign(pSF, saHorz);
	GdipSetStringFormatLineAlign(pSF, saVert);
	return pSF;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY DrawTabs(GpGraphics *pGr, RECT *prcCli) {
	GpPen				*pPen;
	GpBrush			*pBrush, *pBrushTabSelected, *pBrushTextNoSel, *pBrushTextSelected;
	TCHAR				tsText[100], *ptsPageTitles[] = PAGE_NAMES;
	GpFont			*pFont;
	RectF				RcText;
	GpStringFormat	*pStrFmt = CreateGdipStringFormat(StringAlignmentCenter, StringAlignmentCenter);
	int				iC, iY;
	int				iMarginFullX = TABS_OUTER_MARGIN_X + TABS_ITEM_CURVE_MARGIN_X;
	int				iMarginFullY = TABS_OUTER_MARGIN_Y + TABS_ITEM_CURVE_MARGIN_Y;


	// Paint tabs (label area) background
	GdipCreateSolidFill(RGB2ARGB(255, CLR_TABAREA), &pBrush);
	GdipFillRectangleI(pGr, pBrush, iMarginFullX, iMarginFullY, TABS_LABELAREA_WIDTH,
		prcCli->bottom - (2 * iMarginFullY));
	GdipDeleteBrush(pBrush);
	
	// Draw the tabs' general title
	lstrcpy(tsText, TEXT("Select an option"));
	RcText.X = (REAL)iMarginFullX;
	RcText.Y = (REAL)iMarginFullY;
	RcText.Width = (REAL)TABS_LABELAREA_WIDTH;
	RcText.Height = (REAL)TABS_TITLE_HEIGHT;
	pFont = CreateGdipFont(10, FW_NORMAL, FALSE, FALSE);
	GdipCreateSolidFill(MAKEARGB(200, 0, 0, 0), &pBrush);
	GdipDrawString(pGr, tsText, lstrlen(tsText), pFont, &RcText, pStrFmt, pBrush);
	GdipDeleteBrush(pBrush);
	GdipDeleteFont(pFont);

	// Draw the tabs (taking into account their individual state)
	GdipCreateSolidFill(RGB2ARGB(255, CLR_BACKGROUND), &pBrushTabSelected);
	GdipCreateSolidFill(MAKEARGB(150, 0, 128, 192), &pBrushTextNoSel);
	GdipCreateSolidFill(MAKEARGB(255, 0, 128, 192), &pBrushTextSelected);
	pFont = CreateGdipFont(12, FW_BOLD, FALSE, FALSE);

	for (iC = 0; iC < PAGE_COUNT; iC++) {
		iY = iMarginFullY + TABS_TITLE_HEIGHT + (iC * TABS_ITEM_HEIGHT);

		RcText.X = (REAL)(iMarginFullX + TABS_INNER_MARGIN_X);
		RcText.Y = (REAL)iY;
		RcText.Width = (REAL)(TABS_LABELAREA_WIDTH - (2 * TABS_INNER_MARGIN_X));
		RcText.Height = (REAL)TABS_ITEM_HEIGHT;

		// Paint the "selected" tab background 
		if (g_iCurPage == iC) {
			GdipFillRectangleI(pGr, pBrushTabSelected, iMarginFullX, iY, TABS_LABELAREA_WIDTH, TABS_ITEM_HEIGHT);
		}

		// Draw the tab's title
		GdipDrawString(pGr, ptsPageTitles[iC], lstrlen(ptsPageTitles[iC]), pFont, &RcText, pStrFmt,
			(g_iCurPage == iC) ? pBrushTextSelected : pBrushTextNoSel);
	}

	GdipDeleteFont(pFont);
	GdipDeleteBrush(pBrushTextNoSel);
	GdipDeleteBrush(pBrushTextSelected);
	GdipDeleteBrush(pBrushTabSelected);
	GdipDeleteStringFormat(pStrFmt);

	// Draw the outline
	GdipCreatePen1(MAKEARGB(125, 0, 128, 192), 1.0f, UnitPixel, &pPen);

	// Draw the outline: Upper side
	GdipDrawLineI(pGr, pPen,
		iMarginFullX, iMarginFullY, iMarginFullX + TABS_LABELAREA_WIDTH, iMarginFullY);
	
	// Draw the outline: Right side (above the selected tab)
	iY = iMarginFullY + TABS_TITLE_HEIGHT + (g_iCurPage * TABS_ITEM_HEIGHT);
	GdipDrawLineI(pGr, pPen,
		iMarginFullX + TABS_LABELAREA_WIDTH, iMarginFullY, iMarginFullX + TABS_LABELAREA_WIDTH, iY);

	// Draw the outline: Selected tab's upper side
	GdipDrawLineI(pGr, pPen,
		iMarginFullX + TABS_LABELAREA_WIDTH, iY, iMarginFullX, iY);

	// Draw the outline: Selected tab's upper curved corner
	GdipDrawArcI(pGr, pPen,
		TABS_OUTER_MARGIN_X, iY, TABS_ITEM_CURVE_MARGIN_X * 2, TABS_ITEM_CURVE_MARGIN_Y * 2, 180.0f, 90.0f);

	// Draw the outline: Selected tab's left side
	GdipDrawLineI(pGr, pPen,
		TABS_OUTER_MARGIN_X, iY + TABS_ITEM_CURVE_MARGIN_Y, TABS_OUTER_MARGIN_X,
		iY + TABS_ITEM_HEIGHT - TABS_ITEM_CURVE_MARGIN_Y);

	// Draw the outline: Selected tab's lower curved corner
	iY += TABS_ITEM_HEIGHT;
	GdipDrawArcI(pGr, pPen,
		TABS_OUTER_MARGIN_X, iY - (2 * TABS_ITEM_CURVE_MARGIN_Y),
		TABS_ITEM_CURVE_MARGIN_X * 2, TABS_ITEM_CURVE_MARGIN_Y * 2, 90.0f, 90.0f);

	// Draw the outline: Selected tab's lower side
	GdipDrawLineI(pGr, pPen,
		iMarginFullX, iY, iMarginFullX + TABS_LABELAREA_WIDTH, iY);

	// Draw the outline: Right side (below the selected tab)
	GdipDrawLineI(pGr, pPen,
		iMarginFullX + TABS_LABELAREA_WIDTH, iY,
		iMarginFullX + TABS_LABELAREA_WIDTH, prcCli->bottom - iMarginFullY);

	// Draw the outline: Lower side
	GdipDrawLineI(pGr, pPen,
		iMarginFullX + TABS_LABELAREA_WIDTH, prcCli->bottom - iMarginFullY,
		iMarginFullX, prcCli->bottom - iMarginFullY);

	// Draw the outline: Left side (below the selected tab)
	GdipDrawLineI(pGr, pPen,
		iMarginFullX, prcCli->bottom - iMarginFullY, iMarginFullX, iY);

	// Draw the outline: Left side (above the selected tab)
	iY -= TABS_ITEM_HEIGHT;
	GdipDrawLineI(pGr, pPen,
		iMarginFullX, iY, iMarginFullX, iMarginFullY);

	GdipDeletePen(pPen);

	// Draw item separators
	GdipCreatePen1(MAKEARGB(32, 0, 128, 192), 1.0f, UnitPixel, &pPen);

	for (iC = 0; iC < PAGE_COUNT; iC++) {
		if ((g_iCurPage == iC) || ((g_iCurPage + 1) == iC)) continue;

		iY = iMarginFullY + TABS_TITLE_HEIGHT + (iC * TABS_ITEM_HEIGHT);
		GdipDrawLineI(pGr, pPen,
			iMarginFullX + TABS_INNER_MARGIN_X, iY,
			iMarginFullX + TABS_LABELAREA_WIDTH - TABS_INNER_MARGIN_X, iY);
	}

	// Draw the page's outline
	GdipDrawLineI(pGr, pPen,
		iMarginFullX + TABS_LABELAREA_WIDTH, iMarginFullY, prcCli->right - iMarginFullX, iMarginFullY);
	GdipDrawLineI(pGr, pPen,
		prcCli->right - iMarginFullX, iMarginFullY, prcCli->right - iMarginFullX, prcCli->bottom - iMarginFullY);
	GdipDrawLineI(pGr, pPen,
		prcCli->right - iMarginFullX, prcCli->bottom - iMarginFullY, iMarginFullX + TABS_LABELAREA_WIDTH, prcCli->bottom - iMarginFullY);

	GdipDeletePen(pPen);
}
