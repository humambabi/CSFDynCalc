//
// CSF Dynamic CALC
// (Functions.c) Contains various helper functions
//

#include "Build.h"
#include <CommCtrl.h>
#include <Shlwapi.h>
#include <Richedit.h>
#include <math.h>
#include <tchar.h>
#define STRSAFE_NO_DEPRECATE
#include <strsafe.h>
#include "AppDefs.h"
#include "Resources.h"


// External global variables
extern HINSTANCE			g_hInstApp;
extern HANDLE				g_hMtxAppInstance;
extern int					g_iCurPage;
extern HWND					g_hWndDialog;


// External function prototypes
int APIENTRY DPIScaleX(int iX);
int APIENTRY DPIScaleY(int iY);
INT_PTR CALLBACK PageEvans_DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK PageMarmarou_DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK PageKatzman_DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY GetMainWndPos(POINT *pptWnd) {
	RECT	rcWorkArea;

	// Get the work area dimention, and devide it by a fraction
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0);

	// Assign the new size/position to the passed RECT structure
	pptWnd->x = (LONG)(((rcWorkArea.right - rcWorkArea.left) / 2.0f) - (MAINWND_DEFWIDTH / 2.0f));
	pptWnd->y = (LONG)(((rcWorkArea.bottom - rcWorkArea.top) / 2.0f) - (MAINWND_DEFHEIGHT / 2.0f));
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY ForceSetForegroundWindow(HWND hWnd) {
	DWORD	dwFGThreadId, dwFGProcessId, dwThisThreadId;
	HWND	hWndForeground = GetForegroundWindow();


	dwFGThreadId = GetWindowThreadProcessId(hWndForeground, &dwFGProcessId);
	dwThisThreadId = GetCurrentThreadId();

	AttachThreadInput(dwThisThreadId, dwFGThreadId, TRUE);

	SetForegroundWindow(hWnd);
	BringWindowToTop(hWnd);
	SetFocus(hWnd);

	AttachThreadInput(dwThisThreadId, dwFGThreadId, FALSE);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL APIENTRY IsWinXPOrLater(void) {
	OSVERSIONINFOEX	osvi;
	DWORDLONG			dwlConditionMask = 0;
	BYTE					yOp = VER_GREATER_EQUAL;


	// Initialize the OSVERSIONINFOEX structure.
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	osvi.dwMajorVersion = 5;
	osvi.dwMinorVersion = 1;

	// Initialize the condition mask.
	VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, yOp);
	VER_SET_CONDITION(dwlConditionMask, VER_MINORVERSION, yOp);

	// Perform the test.
	return VerifyVersionInfo(&osvi, VER_MAJORVERSION | VER_MINORVERSION, dwlConditionMask);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL APIENTRY IsOSWin8OrLater(void) {
	OSVERSIONINFOEX	osvi;
	DWORDLONG		dwlConditionMask = 0;
	BYTE			yOp = VER_GREATER_EQUAL;


	// Initialize the OSVERSIONINFOEX structure. Windows 8 Version = 6.2
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	osvi.dwMajorVersion = 6;
	osvi.dwMinorVersion = 2;

	// Initialize the condition mask.
	VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, yOp);
	VER_SET_CONDITION(dwlConditionMask, VER_MINORVERSION, yOp);

	// Perform the test.
	return VerifyVersionInfo(&osvi, VER_MAJORVERSION | VER_MINORVERSION, dwlConditionMask);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL APIENTRY PrimaryCheck(void) {
	DWORD		dwLastErr;

	// Check for another instance of the application
	g_hMtxAppInstance = CreateMutex(NULL, TRUE, STR_APPNAME);
	dwLastErr = GetLastError();

	if ((g_hMtxAppInstance == NULL) || (dwLastErr == ERROR_INVALID_HANDLE) || (dwLastErr == ERROR_ALREADY_EXISTS)) {
		HWND	hWndFound;

		if (g_hMtxAppInstance != NULL) CloseHandle(g_hMtxAppInstance);
		MessageBox(HWND_DESKTOP, TEXT("The program is already running!"), STR_APPNAME, MB_ICONINFORMATION);

		// Search for the other instance (if any), bring it to the foreground, and flash it
		hWndFound = FindWindowEx(HWND_DESKTOP, NULL, WC_MAINWND, NULL);
		if (hWndFound != NULL) {
			FLASHWINFO	fwx;

			if (IsIconic(hWndFound) != FALSE) ShowWindow(hWndFound, SW_RESTORE);
			ForceSetForegroundWindow(hWndFound);

			fwx.cbSize = sizeof(FLASHWINFO);
			fwx.hwnd = hWndFound;
			fwx.dwFlags = FLASHW_ALL;
			fwx.uCount = 5;
			fwx.dwTimeout = 0;
			FlashWindowEx(&fwx);
		}

		return FALSE;
	}

	// Check OS version (Minimum: Windows XP)
	if (IsWinXPOrLater() == FALSE) {
		MessageBox(HWND_DESKTOP, TEXT("Sorry! This program needs Windows XP or later to work."), STR_APPNAME, MB_ICONINFORMATION);
		CloseHandle(g_hMtxAppInstance);
		return FALSE;
	}

	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
int APIENTRY PointOnTabbtn(POINT Pt) {
	int	iC, iTop1stbtn = TABS_OUTER_MARGIN_Y + TABS_ITEM_CURVE_MARGIN_Y + TABS_TITLE_HEIGHT;
	RECT	rcTest;

	/*
	Return value: either a page index (0, 1, ...) or -1 if the point is not on a tab button
	*/

	rcTest.right = TABS_OUTER_MARGIN_X + TABS_ITEM_CURVE_MARGIN_X + TABS_LABELAREA_WIDTH;

	for (iC = 0; iC < PAGE_COUNT; iC++) {
		// Adjust the test rectangle
		rcTest.top = iTop1stbtn + (iC * TABS_ITEM_HEIGHT);
		rcTest.left = TABS_OUTER_MARGIN_Y + ((g_iCurPage != iC) ? TABS_ITEM_CURVE_MARGIN_X : 0); // Non-selected tab buttons are smaller
		rcTest.bottom = rcTest.top + TABS_ITEM_HEIGHT;

		// Test the point
		if (PtInRect(&rcTest, Pt)) return iC;
	}

	return -1; // Point is not on anyone of the tab buttons
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY LoadTabPage(HWND hWndParent, int iPage) {
	HWND	hWndDlgOld = g_hWndDialog;

	// Load the new page
	switch (iPage) {
		case PAGE_EVANS:
			g_hWndDialog = CreateDialog(g_hInstApp, MAKEINTRESOURCE(IDD_PAGE_EVANS), hWndParent, PageEvans_DlgProc);
			break;

		case PAGE_MARMAROU:
			g_hWndDialog = CreateDialog(g_hInstApp, MAKEINTRESOURCE(IDD_PAGE_MARMAROU), hWndParent, PageMarmarou_DlgProc);
			break;

		case PAGE_KATZMAN:
			g_hWndDialog = CreateDialog(g_hInstApp, MAKEINTRESOURCE(IDD_PAGE_KATZMAN), hWndParent, PageKatzman_DlgProc);
			break;
	}
	
	// Unload the old page (on the 1st call there will not be an old page yet)
	if (IsWindow(hWndDlgOld)) DestroyWindow(hWndDlgOld);

	// Update the global variable
	g_iCurPage = iPage;

	// Redraw the parent window (MainWnd) to redraw the tabs
	InvalidateRect(hWndParent, NULL, FALSE);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY SetDlgItemPosSize(HWND hDlg, UINT uItemID, int iX, int iY, UINT uWidth, UINT uHeight) {
	SetWindowPos(GetDlgItem(hDlg, uItemID), NULL, iX, iY, uWidth, uHeight, SWP_NOOWNERZORDER | SWP_NOZORDER);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY InvalidField(HWND hDlg, UINT uCtlID, TCHAR *ptsText) {
	EDITBALLOONTIP	ebt;

	ebt.cbStruct = sizeof(EDITBALLOONTIP);
	ebt.pszTitle = TEXT("Invalid Field");
	ebt.pszText = ptsText;
	ebt.ttiIcon = TTI_WARNING;
	SendDlgItemMessage(hDlg, uCtlID, EM_SHOWBALLOONTIP, 0, (LPARAM)&ebt);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
int APIENTRY Float2IntComplete(float fVal) {
	int	iVal = (int)fVal;

	if (fVal != iVal) {
		if (fVal > 0) iVal++;
		if (fVal < 0) iVal--;
	}

	return iVal;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
TCHAR *APIENTRY GetCtlTextAlloc(HWND hWnd) {
	int	iLen = (int)SendMessage(hWnd, WM_GETTEXTLENGTH, 0, 0);
	TCHAR	*ptsText;


	if (iLen < 1) return NULL;
	ptsText = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY | HEAP_GENERATE_EXCEPTIONS, (iLen + 1) * sizeof(TCHAR));
	if (GetWindowText(hWnd, ptsText, iLen + 1) != iLen) {
		HeapFree(GetProcessHeap(), 0, ptsText);
		return NULL;
	}

	return ptsText;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL APIENTRY ValidateEditEmpty(HWND hDlg, UINT uItemID) {
	TCHAR	*ptsText = GetCtlTextAlloc(GetDlgItem(hDlg, uItemID));
	BOOL	bRet;


	if (ptsText == NULL) return TRUE;
	StrTrim(ptsText, TEXT(" "));

	if (lstrlen(ptsText) > 0) bRet = FALSE; else bRet = TRUE;
	HeapFree(GetProcessHeap(), 0, ptsText);

	return bRet;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL APIENTRY ValidateEditNumberRange(HWND hDlg, UINT uItemID, int iMin, int iMax) {
	TCHAR	*ptsText = GetCtlTextAlloc(GetDlgItem(hDlg, uItemID));
	int	iVal;
	BOOL	bRet;


	if (ptsText == NULL) return FALSE;
	iVal = StrToInt(ptsText);
	if ((iVal < iMin) || (iVal > iMax)) bRet = FALSE; else bRet = TRUE;
	HeapFree(GetProcessHeap(), 0, ptsText);

	return bRet;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY LoadCheckDpiAwareBitmap(HWND hDlg, UINT uCtlID) {
	int		cX = DPIScaleX(32), idRes; // Selection is based on the X-axis DPI
	HBITMAP	hBmp;
	HGDIOBJ	hObjOld;


	if (cX <= 32) idRes = IDB_CHECK32;
	else if ((cX > 32) && (cX <= 40)) idRes = IDB_CHECK40;
	else if ((cX > 40) && (cX <= 48)) idRes = IDB_CHECK48;
	else if ((cX > 48) && (cX <= 56)) idRes = IDB_CHECK56;
	else if ((cX > 56) && (cX <= 64)) idRes = IDB_CHECK64;
	else if ((cX > 64) && (cX <= 72)) idRes = IDB_CHECK72;
	else idRes = IDB_CHECK80; // (cX > 72)

	hBmp = (HBITMAP)LoadImage(g_hInstApp, MAKEINTRESOURCE(idRes), IMAGE_BITMAP, 0, 0, LR_SHARED);
	hObjOld = (HGDIOBJ)SendDlgItemMessage(hDlg, uCtlID, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp);
	if (hObjOld) DeleteObject(hObjOld);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
TCHAR *APIENTRY CreateResultsFileNameAlloc(TCHAR *ptsTestName) {
	TCHAR			tsDate[250], tsFile[350], tsExt[] = TEXT(".txt"), tsAppPath[500], tsFullPath[750], *ptsOut;
	SYSTEMTIME	stmNow;
	UINT			uC = 0;


	GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, NULL, NULL, tsDate, sizeof(tsDate) / sizeof(TCHAR));
	GetLocalTime(&stmNow);

	GetModuleFileName(g_hInstApp, tsAppPath, sizeof(tsAppPath) / sizeof(TCHAR));
	PathRemoveFileSpec(tsAppPath);
	if (tsAppPath[lstrlen(tsAppPath) - 1] != TEXT('\\')) lstrcat(tsAppPath, TEXT("\\"));

	do {
		uC++;

		if (uC == 1) {
			wsprintf(tsFile, TEXT("%s - %s (%02u.%02u.%02u)%s"), ptsTestName, tsDate, stmNow.wHour, stmNow.wMinute, stmNow.wSecond, tsExt);
		} else {
			wsprintf(tsFile, TEXT("%s - %s (%02u.%02u.%02u) %u%s"), ptsTestName, tsDate, stmNow.wHour, stmNow.wMinute, stmNow.wSecond, uC, tsExt);
		}

		// Construct a full path for the file
		wsprintf(tsFullPath, TEXT("%s%s"), tsAppPath, tsFile);
	} while (PathFileExists(tsFullPath));

	ptsOut = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY | HEAP_GENERATE_EXCEPTIONS, (lstrlen(tsFullPath) + 1) * sizeof(TCHAR));
	lstrcpy(ptsOut, tsFullPath);
	return ptsOut;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY PageResults_Hide(HWND hDlg) {
	ShowWindow(GetDlgItem(hDlg, IDC_PIC_RESULTS), SW_HIDE);
	ShowWindow(GetDlgItem(hDlg, IDC_STC_RESULTS), SW_HIDE);
	ShowWindow(GetDlgItem(hDlg, IDC_LNK_RESULTS), SW_HIDE);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
DWORD CALLBACK Disclaimer_StreamCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb) {
	BSTORE	*pbsRTF = (BSTORE *)dwCookie;

	CopyMemory(pbBuff, pbsRTF->pyStorage + pbsRTF->uRead, cb);
	pbsRTF->uRead += cb;
	*pcb = cb;
	return 0; // Success
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void APIENTRY LoadDisclaimerText(HWND hDlg, UINT uCtlID) {
	HRSRC			hRsrc = FindResource(g_hInstApp, MAKEINTRESOURCE(ID_RICHTEXT_DISCLAIMER), RT_RCDATA);
	DWORD			dwLen = SizeofResource(g_hInstApp, hRsrc);
	BYTE			*pRsrc = (BYTE *)LoadResource(g_hInstApp, hRsrc);
	EDITSTREAM	EStream;
	BSTORE		bsRTF;


	/* Resources don't need to be freed */

	bsRTF.uResLen = dwLen;
	bsRTF.uRead = 0;
	bsRTF.pyStorage = pRsrc;

	EStream.pfnCallback = Disclaimer_StreamCallback;
	EStream.dwError = 0;
	EStream.dwCookie = (DWORD_PTR)&bsRTF;

	SendDlgItemMessage(hDlg, uCtlID, EM_AUTOURLDETECT, TRUE, 0);
	SendDlgItemMessage(hDlg, uCtlID, EM_SETEVENTMASK, 0, ENM_LINK);
	SendDlgItemMessage(hDlg, uCtlID, EM_STREAMIN, SF_RTF, (LPARAM)&EStream);
	PostMessage(GetDlgItem(hDlg, uCtlID), EM_SETSEL, 0, 0);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK SignedIntegerSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData) {
	switch (uMsg) {
		case WM_NCDESTROY: {
			RemoveWindowSubclass(hWnd, SignedIntegerSubclassProc, uIdSubclass);
			break;
		}


		case WM_CHAR: {
			TCHAR				tcCh = (TCHAR)wParam;
			EDITBALLOONTIP	ebt;


			if (tcCh < TEXT(' ')) break;											// Let control character through
			else if ((tcCh >= TEXT('0')) && (tcCh <= TEXT('9'))) break;	// Let digit through
			else if ((tcCh == TEXT('-')) || (tcCh == TEXT('\x2212'))) {	// Let hyphen-minus and Unicode minus sign through
				TCHAR	tsText[250];

				// (only once, and only if it's the 1st character)
				GetWindowText(hWnd, tsText, sizeof(tsText) / sizeof(TCHAR));
				if (lstrlen(tsText) == 0) break;
			}
			else if (tcCh == TEXT('.')) {											// Let floating point (only once)
				TCHAR	tsText[250];

				GetWindowText(hWnd, tsText, sizeof(tsText) / sizeof(TCHAR));
				if (StrStr(tsText, TEXT(".")) == NULL) break;
			}
			
			// Otherwise invalid
			MessageBeep(0);
			
			ebt.cbStruct = sizeof(EDITBALLOONTIP);
			ebt.pszTitle = TEXT("Unacceptable Character");
			ebt.pszText = TEXT("You can only type a number here.");
			ebt.ttiIcon = TTI_ERROR;
			SendMessage(hWnd, EM_SHOWBALLOONTIP, 0, (LPARAM)&ebt);

			return 0;
		}
	}

	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL APIENTRY EnforceSignedIntegerEdit(HWND hCtl) {
	return SetWindowSubclass(hCtl, SignedIntegerSubclassProc, 0, 0);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL APIENTRY CreateResults_Evans(HWND hDlg) {
	int		iFrontalHornsMaxWidth, iMaxInternalSkullDiameter;
	BOOL		bTranslated;
	float		fResult;
	TCHAR		tsResult[250], *ptsFilePath, tsTestName[] = TEXT("Evan's index"), tsLine[250], tsTemp[150];
	HANDLE	hFile;


	/*
	This procedure MUST only be called AFTER validating the fields
	*/

	// Get the input
	iFrontalHornsMaxWidth = GetDlgItemInt(hDlg, IDC_EVANS_EDT_FRONTALHORNSMAXWIDTH, &bTranslated, FALSE);
	if (!bTranslated) {
		MessageBox(hDlg, TEXT("Sorry, cannot get input values!"), STR_APPNAME, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	iMaxInternalSkullDiameter = GetDlgItemInt(hDlg, IDC_EVANS_EDT_SKULLMAXINNERDIAMETER, &bTranslated, FALSE);
	if (!bTranslated) {
		MessageBox(hDlg, TEXT("Sorry, cannot get input values!"), STR_APPNAME, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Calculate, create a result string, and assign it to the results static control
	if (iMaxInternalSkullDiameter == 0) {
		MessageBox(hDlg, TEXT("Sorry! The entered values caused a division by zero error!"), STR_APPNAME, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	fResult = (float)iFrontalHornsMaxWidth / (float)iMaxInternalSkullDiameter;
	StringCbPrintf(tsResult, sizeof(tsResult), TEXT("%ls: %.2f"), tsTestName, fResult);
	SetDlgItemText(hDlg, IDC_STC_RESULTS, tsResult);

	// Create a text file
	ptsFilePath = CreateResultsFileNameAlloc(tsTestName);
	hFile = CreateFile(ptsFilePath, GENERIC_WRITE, 0x0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		HeapFree(GetProcessHeap(), 0, ptsFilePath);
		MessageBox(hDlg, TEXT("Sorry, the output text file was not created!\r\n\r\n(Cannot create a file in the application's folder)"),
			STR_APPNAME, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Print the results on it
	lstrcpy(tsLine, TEXT("==================================================\r\n"));
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);
	
	GetDlgItemText(hDlg, IDC_EVANS_EDT_EVALUATORNAME, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Evaluator's Name: %s\r\n\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);
	
	GetDlgItemText(hDlg, IDC_EVANS_EDT_PATIENTNAME, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Patient's Name: %s\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);
	
	GetDlgItemText(hDlg, IDC_EVANS_EDT_MEDICALRECORD, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Medical Record: %s\r\n\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);
	
	wsprintf(tsLine, TEXT("Test type: %s\r\n"), tsTestName);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);
	
	lstrcpy(tsLine, TEXT("==================================================\r\n\r\n"));
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	GetDlgItemText(hDlg, IDC_EVANS_EDT_FRONTALHORNSMAXWIDTH, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Maximum width of the frontal horns: %s mm\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);
	
	GetDlgItemText(hDlg, IDC_EVANS_EDT_SKULLMAXINNERDIAMETER, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Maximum internal skull inner diameter: %s mm\r\n\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	wsprintf(tsLine, TEXT("%s\r\n"), tsResult);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	CloseHandle(hFile);
	/* Don't free ptsFilePath's memory, it will be saved for later usage and freed in the DlgProc */

	// Save the file path (in order to open it later)
	SetWindowLongPtr(hDlg, DWLP_USER, (LONG_PTR)ptsFilePath);
	
	// Show the results controls
	ShowWindow(GetDlgItem(hDlg, IDC_PIC_RESULTS), SW_SHOW);
	ShowWindow(GetDlgItem(hDlg, IDC_STC_RESULTS), SW_SHOW);
	ShowWindow(GetDlgItem(hDlg, IDC_LNK_RESULTS), SW_SHOW);

	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL APIENTRY CreateResults_MarmarouBolus(HWND hDlg) {
	float		fDeltaVol, fBasePressure, fMaxPressure, fPressureTmin, fTime4Pt;
	float		fPpDivP0, fTemp, fPVI, fCompliance, fT2P0, fRLogArgument, fRout, fCout;
	TCHAR		tsText[250], tsResult[500], *ptsFilePath, tsTestName[] = TEXT("Marmarou's test"), tsLine[250], tsTemp[150];
	HANDLE	hFile;


	/*
	This procedure MUST only be called AFTER validating the fields
	*/

	// Get the input 
	GetDlgItemText(hDlg, IDC_MARMAROU_EDT_ADDEDVOLUME, tsText, sizeof(tsText) / sizeof(TCHAR));
	fDeltaVol = _tcstof(tsText, NULL);

	GetDlgItemText(hDlg, IDC_MARMAROU_EDT_BASELINEPRESSURE, tsText, sizeof(tsText) / sizeof(TCHAR));
	fBasePressure = _tcstof(tsText, NULL);

	GetDlgItemText(hDlg, IDC_MARMAROU_EDT_MAXIMUMPRESSURE, tsText, sizeof(tsText) / sizeof(TCHAR));
	fMaxPressure = _tcstof(tsText, NULL);

	GetDlgItemText(hDlg, IDC_MARMAROU_EDT_PRESSUREAFTERTMINS, tsText, sizeof(tsText) / sizeof(TCHAR));
	fPressureTmin = _tcstof(tsText, NULL);

	GetDlgItemText(hDlg, IDC_MARMAROU_EDT_TIMEFORPT, tsText, sizeof(tsText) / sizeof(TCHAR));
	fTime4Pt = _tcstof(tsText, NULL);

	// Calculate
	if (fBasePressure == 0.0f) {
		MessageBox(hDlg, TEXT("Sorry! The entered values caused a division by zero error!"), STR_APPNAME, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	fPpDivP0 = fMaxPressure / fBasePressure;
	if (fPpDivP0 <= 0) { // Logarithms' argument cannot be 0 or less
		MessageBox(hDlg, TEXT("Sorry! The entered values caused a logarithm error!\r\n\r\nPlease, check the values and try again."), STR_APPNAME, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	fTemp = log10f(fPpDivP0);
	if (fTemp == 0.0f) {
		MessageBox(hDlg, TEXT("Sorry! The entered values caused a division by zero error!"), STR_APPNAME, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	fPVI = fDeltaVol / fTemp;

	/* P is P0 */
	// fBasePressure is checked before (not to be 0)
	fCompliance = (0.4343f * fPVI) / fBasePressure;
	
	fT2P0 = fTime4Pt * fBasePressure;
	if ((fMaxPressure == 0.0f) || ((fPressureTmin - fBasePressure) == 0.0f)) {
		MessageBox(hDlg, TEXT("Sorry! The entered values caused a division by zero error!"), STR_APPNAME, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	fRLogArgument = (fPressureTmin / fMaxPressure) * ((fMaxPressure - fBasePressure) / (fPressureTmin - fBasePressure));
	if (fRLogArgument <= 0) { // Logarithms' argument cannot be 0 or less
		MessageBox(hDlg, TEXT("Sorry! The entered values caused a logarithm error!\r\n\r\nPlease, check the values and try again."), STR_APPNAME, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	fTemp = fPVI * log10f(fRLogArgument);
	if (fTemp == 0.0f) {
		MessageBox(hDlg, TEXT("Sorry! The entered values caused a division by zero error!"), STR_APPNAME, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	fRout = fT2P0 / fTemp;

	fCout = 1.0f / fRout;

	// Create a result string, and assign it to the results static control
	StringCbPrintf(tsResult, sizeof(tsResult), TEXT("PVI = %.3f mL\r\nCompliance = %.3f mL/mmHg\r\nRout = %.3f mmHg/mL/min\r\nCout = %.3f mmHg/mL/min"),
		fPVI, fCompliance, fRout, fCout);
	SetDlgItemText(hDlg, IDC_STC_RESULTS, tsResult);

	// Create a text file
	ptsFilePath = CreateResultsFileNameAlloc(tsTestName);
	hFile = CreateFile(ptsFilePath, GENERIC_WRITE, 0x0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		HeapFree(GetProcessHeap(), 0, ptsFilePath);
		MessageBox(hDlg, TEXT("Sorry, the output text file was not created!\r\n\r\n(Cannot create a file in the application's folder)"),
			STR_APPNAME, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Print the results on it
	lstrcpy(tsLine, TEXT("==================================================\r\n"));
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	GetDlgItemText(hDlg, IDC_MARMAROU_EDT_EVALUATORNAME, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Evaluator's Name: %s\r\n\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	GetDlgItemText(hDlg, IDC_MARMAROU_EDT_PATIENTNAME, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Patient's Name: %s\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	GetDlgItemText(hDlg, IDC_MARMAROU_EDT_MEDICALRECORD, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Medical Record: %s\r\n\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	wsprintf(tsLine, TEXT("Test type: %s\r\n"), tsTestName);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	lstrcpy(tsLine, TEXT("==================================================\r\n\r\n"));
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	GetDlgItemText(hDlg, IDC_MARMAROU_EDT_ADDEDVOLUME, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Added Volume (ΔV): %s mL\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	GetDlgItemText(hDlg, IDC_MARMAROU_EDT_BASELINEPRESSURE, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Baseline Pressure (P0): %s mmHg\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	GetDlgItemText(hDlg, IDC_MARMAROU_EDT_MAXIMUMPRESSURE, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Maximum Pressure (Pp): %s mmHg\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	GetDlgItemText(hDlg, IDC_MARMAROU_EDT_PRESSUREAFTERTMINS, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Pressure after 't' minutes (Pt): %s mmHg\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	GetDlgItemText(hDlg, IDC_MARMAROU_EDT_TIMEFORPT, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Time at Pt: %s (minutes after bolus)\r\n\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	wsprintf(tsLine, TEXT("%s\r\n"), tsResult);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	CloseHandle(hFile);
	/* Don't free ptsFilePath's memory, it will be saved for later usage and freed in the DlgProc */

	// Save the file path (in order to open it later)
	SetWindowLongPtr(hDlg, DWLP_USER, (LONG_PTR)ptsFilePath);

	// Show the results controls
	ShowWindow(GetDlgItem(hDlg, IDC_PIC_RESULTS), SW_SHOW);
	ShowWindow(GetDlgItem(hDlg, IDC_STC_RESULTS), SW_SHOW);
	ShowWindow(GetDlgItem(hDlg, IDC_LNK_RESULTS), SW_SHOW);

	return TRUE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL APIENTRY CreateResults_Katzman(HWND hDlg) {
	float		fInfusionRate, fBasePressure, fPlateauPressure, fTimeAtPlateau, fRout, fCout;
	TCHAR		tsText[250], tsResult[300], *ptsFilePath, tsTestName[] = TEXT("Katzman's test"), tsLine[250], tsTemp[150];
	HANDLE	hFile;


	/*
	This procedure MUST only be called AFTER validating the fields
	*/

	// Get the input
	GetDlgItemText(hDlg, IDC_KATZMAN_EDT_INFUSIONRATE, tsText, sizeof(tsText) / sizeof(TCHAR));
	fInfusionRate = _tcstof(tsText, NULL);

	GetDlgItemText(hDlg, IDC_KATZMAN_EDT_BASELINEPRESSURE, tsText, sizeof(tsText) / sizeof(TCHAR));
	fBasePressure = _tcstof(tsText, NULL);

	GetDlgItemText(hDlg, IDC_KATZMAN_EDT_PLATEAUPRESSURE, tsText, sizeof(tsText) / sizeof(TCHAR));
	fPlateauPressure = _tcstof(tsText, NULL);

	GetDlgItemText(hDlg, IDC_KATZMAN_EDT_TIMEPLATEAU, tsText, sizeof(tsText) / sizeof(TCHAR));
	fTimeAtPlateau = _tcstof(tsText, NULL);

	// Calculate
	if (fInfusionRate == 0.0f) {
		MessageBox(hDlg, TEXT("Sorry! The entered values caused a division by zero error!"), STR_APPNAME, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	fRout = (fPlateauPressure - fBasePressure) / fInfusionRate;

	if (fRout == 0.0f) {
		MessageBox(hDlg, TEXT("Sorry! The entered values caused a division by zero error!"), STR_APPNAME, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	fCout = 1 / fRout;

	// Create a result string, and assign it to the results static control
	StringCbPrintf(tsResult, sizeof(tsResult), TEXT("Rout = %.3f mmHg/mL/min\r\nCout = %.3f mmHg/mL/min\r\nTime at plateau = %.1f min"),
		fRout, fCout, fTimeAtPlateau);
	SetDlgItemText(hDlg, IDC_STC_RESULTS, tsResult);

	// Create a text file
	ptsFilePath = CreateResultsFileNameAlloc(tsTestName);
	hFile = CreateFile(ptsFilePath, GENERIC_WRITE, 0x0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		HeapFree(GetProcessHeap(), 0, ptsFilePath);
		MessageBox(hDlg, TEXT("Sorry, the output text file was not created!\r\n\r\n(Cannot create a file in the application's folder)"),
			STR_APPNAME, MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Print the results on it
	lstrcpy(tsLine, TEXT("==================================================\r\n"));
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	GetDlgItemText(hDlg, IDC_KATZMAN_EDT_EVALUATORNAME, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Evaluator's Name: %s\r\n\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	GetDlgItemText(hDlg, IDC_KATZMAN_EDT_PATIENTNAME, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Patient's Name: %s\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	GetDlgItemText(hDlg, IDC_KATZMAN_EDT_MEDICALRECORD, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Medical Record: %s\r\n\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	wsprintf(tsLine, TEXT("Test type: %s\r\n"), tsTestName);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	lstrcpy(tsLine, TEXT("==================================================\r\n\r\n"));
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	GetDlgItemText(hDlg, IDC_KATZMAN_EDT_INFUSIONRATE, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Infusion Rate: %s mL/min\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	GetDlgItemText(hDlg, IDC_KATZMAN_EDT_BASELINEPRESSURE, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Baseline Pressure (P0): %s mmHg\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	GetDlgItemText(hDlg, IDC_KATZMAN_EDT_PLATEAUPRESSURE, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Plateau Pressure (Pp): %s mmHg\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	GetDlgItemText(hDlg, IDC_KATZMAN_EDT_TIMEPLATEAU, tsTemp, sizeof(tsTemp) / sizeof(TCHAR));
	wsprintf(tsLine, TEXT("Time at plateau: %s min\r\n\r\n"), tsTemp);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);
	
	wsprintf(tsLine, TEXT("%s\r\n"), tsResult);
	WriteFile(hFile, tsLine, lstrlen(tsLine) * sizeof(TCHAR), NULL, NULL);

	CloseHandle(hFile);
	/* Don't free ptsFilePath's memory, it will be saved for later usage and freed in the DlgProc */

	// Save the file path (in order to open it later)
	SetWindowLongPtr(hDlg, DWLP_USER, (LONG_PTR)ptsFilePath);

	// Show the results controls
	ShowWindow(GetDlgItem(hDlg, IDC_PIC_RESULTS), SW_SHOW);
	ShowWindow(GetDlgItem(hDlg, IDC_STC_RESULTS), SW_SHOW);
	ShowWindow(GetDlgItem(hDlg, IDC_LNK_RESULTS), SW_SHOW);

	return TRUE;
}
