//
// CSF Dynamic CALC
// (PagesWnd.c) Pages' dialog event procedures
//

#include "Build.h"
#include <ShellAPI.h>
#include <Richedit.h>
#include <WindowsX.h>
#include "AppDefs.h"
#include "Resources.h"


// External global variables
extern HINSTANCE			g_hInstApp;
extern HWND					g_hWndDialog;


// External function prototypes
int APIENTRY DPIScaleX(int iX);
int APIENTRY DPIScaleY(int iY);
void APIENTRY ClearDC(HDC hDC, COLORREF clrBrush, int iLeft, int iTop, int iRight, int iBottom);
void APIENTRY SetDlgItemPosSize(HWND hDlg, UINT uItemID, int iX, int iY, UINT uWidth, UINT uHeight);
void APIENTRY InvalidField(HWND hDlg, UINT uCtlID, TCHAR* ptsText);
BOOL APIENTRY ValidateEditEmpty(HWND hDlg, UINT uItemID);
BOOL APIENTRY ValidateEditNumberRange(HWND hDlg, UINT uItemID, int iMin, int iMax);
void APIENTRY LoadCheckDpiAwareBitmap(HWND hDlg, UINT uCtlID);
HWND APIENTRY CreateCtlLink(TCHAR* ptsText, int iX, int iY, UINT uW, UINT uH, HWND hWndParent, UINT uCtlID, COLORREF clrBkgnd, BOOL bTypeRed);
void APIENTRY PageResults_Hide(HWND hDlg);
void APIENTRY LoadDisclaimerText(HWND hDlg, UINT uCtlID);
BOOL APIENTRY EnforceSignedIntegerEdit(HWND hCtl);
BOOL APIENTRY CreateResults_Evans(HWND hDlg);
BOOL APIENTRY CreateResults_MarmarouBolus(HWND hDlg);
BOOL APIENTRY CreateResults_Katzman(HWND hDlg);
HFONT APIENTRY CreateGdiFont(int iPointSize, int iWeight);


///////////////////////////////////////////////////////////////////////////////////////////////////
INT_PTR CALLBACK Disclaimer_DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_INITDIALOG: {
		SetWindowText(hDlg, STR_APPNAME);
		LoadDisclaimerText(hDlg, IDC_RTF_DISCLAIMER);
		break;
	}

	case WM_COMMAND: {
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
		}
		break;
	}

	case WM_NOTIFY: {
		NMHDR* pNmHdr = (NMHDR*)lParam;

		if (pNmHdr->idFrom == IDC_RTF_DISCLAIMER) {
			ENLINK* pEnLink = (ENLINK*)lParam;

			if (pEnLink->msg == WM_LBUTTONUP) {
				TCHAR			tsURL[500];
				TEXTRANGE	TRange;


				TRange.chrg = pEnLink->chrg;
				TRange.lpstrText = tsURL;
				SendMessage(pNmHdr->hwndFrom, EM_GETTEXTRANGE, 0, (LPARAM)&TRange);
				ShellExecute(hDlg, TEXT("open"), tsURL, NULL, NULL, SW_SHOW);
			}
		}
		break;
	}
	}

	return FALSE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
INT_PTR CALLBACK About_DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_INITDIALOG: {
		CreateCtlLink(TEXT("License"), DPIScaleX(71), DPIScaleY(313), ABOUTWND_LNKLICENSE_WIDTH, DPIScaleY(21),
			hDlg, IDC_ABOUT_LNK_LICENSE, GetSysColor(COLOR_3DFACE), FALSE);
		CreateCtlLink(TEXT("Disclaimer"), DPIScaleX(71), DPIScaleY(335), DPIScaleX(75), DPIScaleY(21),
			hDlg, IDC_ABOUT_LNK_DISCLAIMER, GetSysColor(COLOR_3DFACE), FALSE);
		CreateCtlLink(TEXT("Source code on github.com"), DPIScaleX(71), DPIScaleY(357), DPIScaleX(190), DPIScaleY(21),
			hDlg, IDC_ABOUT_LNK_SOURCE, GetSysColor(COLOR_3DFACE), FALSE);
		break;
	}


	case WM_PAINT: {
		PAINTSTRUCT	Ps;
		RECT			rcCli, rcText;
		HICON			hIcon;
		HFONT			hFont, hFontOrig;
		int			iX, iY;
		TCHAR			tsText[250];


		GetClientRect(hDlg, &rcCli);
		BeginPaint(hDlg, &Ps);

		SetBkColor(Ps.hdc, GetSysColor(COLOR_3DFACE));

		// No need to free when using LR_SHARED resources
		hIcon = LoadImage(g_hInstApp, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, DPIScaleX(48), DPIScaleY(48), LR_SHARED);
		DrawIconEx(Ps.hdc, DPIScaleX(15), DPIScaleY(15), hIcon, DPIScaleX(48), DPIScaleY(48), 0, NULL, DI_NORMAL);

		iX = DPIScaleX(71);
		iY = DPIScaleY(30);
		hFont = CreateGdiFont(14, FW_BOLD);
		hFontOrig = SelectFont(Ps.hdc, hFont);
		TextOut(Ps.hdc, iX, iY, STR_APPNAME, lstrlen(STR_APPNAME));
		SelectFont(Ps.hdc, hFontOrig);
		DeleteFont(hFont);

		iY += DPIScaleY(28);
		hFont = CreateGdiFont(10, FW_NORMAL);
		hFontOrig = SelectFont(Ps.hdc, hFont);
		lstrcpy(tsText, TEXT("Copyright © 2021, Naurotraumatology and Neurosurgery Research Unit, ")
			TEXT("Vall d'Hebron Research Institute, Barcelona, Spain."));
		SetRect(&rcText, iX, iY, rcCli.right - DPIScaleX(25), rcCli.bottom);
		DrawText(Ps.hdc, tsText, -1, &rcText, DT_WORDBREAK);
		SelectFont(Ps.hdc, hFontOrig);
		DeleteFont(hFont);

		iY += DPIScaleY(50);
		hFont = CreateGdiFont(10, FW_BOLD);
		hFontOrig = SelectFont(Ps.hdc, hFont);
		lstrcpy(tsText, TEXT("An open-source program to calculate cerebrospinal fluid (CSF) variables in ")
			TEXT("patients or animal experiments based on the following papers:"));
		SetRect(&rcText, iX, iY, rcCli.right - DPIScaleX(25), rcCli.bottom);
		DrawText(Ps.hdc, tsText, -1, &rcText, DT_WORDBREAK);
		DrawText(Ps.hdc, tsText, -1, &rcText, DT_WORDBREAK | DT_CALCRECT);
		SelectFont(Ps.hdc, hFontOrig);
		DeleteFont(hFont);

		iY += (rcText.bottom - rcText.top) + DPIScaleY(13);
		hFont = CreateGdiFont(10, FW_NORMAL);
		hFontOrig = SelectFont(Ps.hdc, hFont);
		lstrcpy(tsText, TEXT("1. Marmarou A, Shulman K, LaMorgese J. Compartmental analysis of compliance ")
			TEXT("and outflow resistance of the cerebrospinal fluid system. J Neurosurgery 43:523-534, 1975"));
		SetRect(&rcText, iX, iY, rcCli.right - DPIScaleX(25), rcCli.bottom);
		DrawText(Ps.hdc, tsText, -1, &rcText, DT_WORDBREAK);
		DrawText(Ps.hdc, tsText, -1, &rcText, DT_WORDBREAK | DT_CALCRECT);

		iY += (rcText.bottom - rcText.top) + DPIScaleY(13);
		lstrcpy(tsText, TEXT("2. Marmarou A, Shulman K, Rosende RM. A nonlinear analysis of the ")
			TEXT("cerebrospinal fluid system and intracranial pressure dynamics. J Neurosurgery ")
			TEXT("48:332-344, 1978"));
		SetRect(&rcText, iX, iY, rcCli.right - DPIScaleX(25), rcCli.bottom);
		DrawText(Ps.hdc, tsText, -1, &rcText, DT_WORDBREAK);
		SelectFont(Ps.hdc, hFontOrig);
		DeleteFont(hFont);

		hFont = CreateGdiFont(11, FW_NORMAL);
		hFontOrig = SelectFont(Ps.hdc, hFont);
		lstrcpy(tsText, TEXT("(GNU GPLv3)"));
		GetWindowRect(GetDlgItem(hDlg, IDC_ABOUT_LNK_LICENSE), &rcText);
		MapWindowPoints(HWND_DESKTOP, hDlg, (POINT*)&rcText, 2);
		rcText.left += ABOUTWND_LNKLICENSE_WIDTH;
		rcText.right = rcCli.right;
		DrawText(Ps.hdc, tsText, -1, &rcText, DT_SINGLELINE);
		SelectFont(Ps.hdc, hFontOrig);
		DeleteFont(hFont);

		EndPaint(hDlg, &Ps);

		return TRUE;
		break;
	}


	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			break;

		case IDC_ABOUT_LNK_LICENSE:
			ShellExecute(hDlg, TEXT("open"), TEXT("https://github.com/humambabi/CSFDynCalc/blob/master/LICENSE"), NULL, NULL, SW_SHOW);
			break;

		case IDC_ABOUT_LNK_DISCLAIMER:
			if (DialogBox(g_hInstApp, MAKEINTRESOURCE(IDD_DISCLAIMER), hDlg, Disclaimer_DlgProc) == IDCANCEL) {
				// Close the app if the user "disagree"d to the disclaimer
				DestroyWindow(GetParent(hDlg)); // Destroy the main window
			}
			break;

		case IDC_ABOUT_LNK_SOURCE:
			ShellExecute(hDlg, TEXT("open"), TEXT("https://github.com/humambabi/CSFDynCalc"), NULL, NULL, SW_SHOW);
			break;
		}
		break;
	}
	}

	return FALSE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
INT_PTR CALLBACK PageEvans_DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_INITDIALOG: {
		HWND			hWndMain = GetParent(hDlg);
		RECT			rcMainWndCli, rcCli;
		POINT			ptDlg;
		SIZE			zeDlg;
		MAINWNDDATA* pMainData = (MAINWNDDATA*)GetWindowLongPtr(hWndMain, GWLP_USERDATA);


		// Resize and move the dialog to fill the page area
		GetClientRect(hWndMain, &rcMainWndCli);
		ptDlg.x = TABS_OUTER_MARGIN_X + TABS_ITEM_CURVE_MARGIN_X + TABS_LABELAREA_WIDTH + DPIScaleX(2);
		ptDlg.y = TABS_OUTER_MARGIN_Y + TABS_ITEM_CURVE_MARGIN_Y + DPIScaleY(2);
		zeDlg.cx = rcMainWndCli.right - (TABS_OUTER_MARGIN_X + TABS_ITEM_CURVE_MARGIN_X) - ptDlg.x - DPIScaleX(1);
		zeDlg.cy = rcMainWndCli.bottom - (TABS_OUTER_MARGIN_X + TABS_ITEM_CURVE_MARGIN_X) - ptDlg.y - DPIScaleY(1);
		SetWindowPos(hDlg, NULL, ptDlg.x, ptDlg.y, zeDlg.cx, zeDlg.cy, SWP_NOZORDER);

		// Set child controls properties
		SendDlgItemMessage(hDlg, IDC_EVANS_STC_TITLE, WM_SETFONT, (WPARAM)pMainData->hFontPageTitle, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_EVANS_EDT_FRONTALHORNSMAXWIDTH, EM_SETLIMITTEXT, 3, 0);
		SendDlgItemMessage(hDlg, IDC_EVANS_EDT_SKULLMAXINNERDIAMETER, EM_SETLIMITTEXT, 3, 0);

		SendDlgItemMessage(hDlg, IDC_EVANS_STC_EVALUATORNAME, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_EVANS_STC_PATIENTNAME, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_EVANS_STC_MEDICALRECORD, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_EVANS_STC_FRONTALHORNSMAXWIDTH, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_EVANS_STC_SKULLINNERDIAMETER, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));

		LoadCheckDpiAwareBitmap(hDlg, IDC_PIC_RESULTS);
		SendDlgItemMessage(hDlg, IDC_STC_RESULTS, WM_SETFONT, (WPARAM)pMainData->hFontResults, MAKELPARAM(TRUE, 0));
		CreateCtlLink(TEXT("(Open output file)"), 10, 20, 150, 30, hDlg, IDC_LNK_RESULTS, CLR_BACKGROUND, FALSE);
		PageResults_Hide(hDlg);

		// Should send a WM_SIZE message after adding any control
		GetClientRect(hDlg, &rcCli);
		SendMessage(hDlg, WM_SIZE, SIZE_RESTORED, MAKELPARAM(rcCli.right, rcCli.bottom));

		// Set the keyboard focus
		SetFocus(GetDlgItem(hDlg, IDC_EVANS_EDT_EVALUATORNAME));
		return FALSE; // Don't change the focus owner
		break;
	}


	case WM_COMMAND: {
		if (LOWORD(wParam) == IDC_EVANS_CMD_CALCULATE) {
			// Validate the fields
			if (ValidateEditEmpty(hDlg, IDC_EVANS_EDT_EVALUATORNAME)) {
				InvalidField(hDlg, IDC_EVANS_EDT_EVALUATORNAME, TEXT("You should type a name here"));
				return TRUE;
			}

			if (ValidateEditEmpty(hDlg, IDC_EVANS_EDT_PATIENTNAME)) {
				InvalidField(hDlg, IDC_EVANS_EDT_PATIENTNAME, TEXT("You should type a name here"));
				return TRUE;
			}

			if (ValidateEditEmpty(hDlg, IDC_EVANS_EDT_MEDICALRECORD)) {
				InvalidField(hDlg, IDC_EVANS_EDT_MEDICALRECORD, TEXT("You should type a medical record here"));
				return TRUE;
			}

			if (ValidateEditEmpty(hDlg, IDC_EVANS_EDT_FRONTALHORNSMAXWIDTH)) {
				InvalidField(hDlg, IDC_EVANS_EDT_FRONTALHORNSMAXWIDTH, TEXT("You should type a number here"));
				return TRUE;
			}
			if (ValidateEditNumberRange(hDlg, IDC_EVANS_EDT_FRONTALHORNSMAXWIDTH, 10, 200) == FALSE) {
				InvalidField(hDlg, IDC_EVANS_EDT_FRONTALHORNSMAXWIDTH, TEXT("Should be a number in the range (10 - 200)"));
				return TRUE;
			}

			if (ValidateEditEmpty(hDlg, IDC_EVANS_EDT_SKULLMAXINNERDIAMETER)) {
				InvalidField(hDlg, IDC_EVANS_EDT_SKULLMAXINNERDIAMETER, TEXT("You should type a number here"));
				return TRUE;
			}
			if (ValidateEditNumberRange(hDlg, IDC_EVANS_EDT_SKULLMAXINNERDIAMETER, 50, 200) == FALSE) {
				InvalidField(hDlg, IDC_EVANS_EDT_SKULLMAXINNERDIAMETER, TEXT("Should be a number in the range (50 - 200)"));
				return TRUE;
			}

			// Calculate the results
			if (CreateResults_Evans(hDlg)) {
				EnableWindow(GetDlgItem(hDlg, IDC_EVANS_CMD_CALCULATE), FALSE);
			}
		}

		// "Open output file" link
		if (LOWORD(wParam) == IDC_LNK_RESULTS) {
			TCHAR* ptsFilePath = (TCHAR*)GetWindowLongPtr(hDlg, DWLP_USER);

			if (ptsFilePath == NULL) {
				MessageBox(hDlg, TEXT("Sorry, file not found!"), STR_APPNAME, MB_ICONEXCLAMATION | MB_OK);
				break;
			}

			ShellExecute(hDlg, TEXT("open"), ptsFilePath, NULL, NULL, SW_SHOW);
		}

		// Any one of the edit controls has been changed
		if (HIWORD(wParam) == EN_CHANGE) {
			TCHAR* ptsFilePath = (TCHAR*)GetWindowLongPtr(hDlg, DWLP_USER);

			if (ptsFilePath) {
				HeapFree(GetProcessHeap(), 0, ptsFilePath);
				SetWindowLongPtr(hDlg, DWLP_USER, (LONG_PTR)0);
			}
			PageResults_Hide(hDlg);
			EnableWindow(GetDlgItem(hDlg, IDC_EVANS_CMD_CALCULATE), TRUE);
		}
		break;
	}


	case WM_PAINT: {
		PAINTSTRUCT	Ps;
		RECT			rcCli;


		GetClientRect(hDlg, &rcCli);
		BeginPaint(hDlg, &Ps);
		ClearDC(Ps.hdc, CLR_BACKGROUND, 0, 0, rcCli.right, rcCli.bottom);
		EndPaint(hDlg, &Ps);

		return TRUE;
		break;
	}


	case WM_CTLCOLORSTATIC:
	case WM_CTLCOLORBTN:
	case WM_CTLCOLOREDIT: // Useful only for disabled or read-only Edit controls
	{
		MAINWNDDATA* pMainData = (MAINWNDDATA*)GetWindowLongPtr(GetParent(hDlg), GWLP_USERDATA);

		SetBkColor((HDC)wParam, CLR_BACKGROUND);
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (INT_PTR)pMainData->hBrushCtlBkgnd;
		break;
	}


	case WM_SIZE: {
		UINT	uY, uX, uCliWidth = LOWORD(lParam), uCliHeight = HIWORD(lParam);
		UINT	uFullWidth = uCliWidth - (PAGES_MARGIN_LEFT + PAGES_MARGIN_RIGHT);
		UINT	uColWidth = (UINT)((uFullWidth - PAGES_HSPACE_MD) / 2.0f);


		uY = PAGES_MARGIN_TOP;
		SetDlgItemPosSize(hDlg, IDC_EVANS_STC_TITLE, PAGES_MARGIN_LEFT, uY, uFullWidth, PAGES_TITLE_HEIGHT);
		uY += PAGES_TITLE_HEIGHT;

		uY += PAGES_VSPACE_LG;
		SetDlgItemPosSize(hDlg, IDC_EVANS_STC_EVALUATORNAME, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_STATIC_HEIGHT);
		uY += PAGES_STATIC_HEIGHT;

		uY += PAGES_VSPACE_SM;
		SetDlgItemPosSize(hDlg, IDC_EVANS_EDT_EVALUATORNAME, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_EDIT_HEIGHT);
		uY += PAGES_EDIT_HEIGHT;

		uY += PAGES_VSPACE_MD;
		SetDlgItemPosSize(hDlg, IDC_EVANS_STC_PATIENTNAME, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_STATIC_HEIGHT);
		SetDlgItemPosSize(hDlg, IDC_EVANS_STC_MEDICALRECORD, PAGES_MARGIN_LEFT + uColWidth + PAGES_HSPACE_MD, uY, uColWidth, PAGES_STATIC_HEIGHT);
		uY += PAGES_STATIC_HEIGHT;

		uY += PAGES_VSPACE_SM;
		SetDlgItemPosSize(hDlg, IDC_EVANS_EDT_PATIENTNAME, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_EDIT_HEIGHT);
		SetDlgItemPosSize(hDlg, IDC_EVANS_EDT_MEDICALRECORD, PAGES_MARGIN_LEFT + uColWidth + PAGES_HSPACE_MD, uY, uColWidth, PAGES_EDIT_HEIGHT);
		uY += PAGES_EDIT_HEIGHT;

		uY += PAGES_VSPACE_LG;
		SetDlgItemPosSize(hDlg, IDC_EVANS_STC_FRONTALHORNSMAXWIDTH, PAGES_MARGIN_LEFT, uY, uFullWidth, PAGES_STATIC_HEIGHT);
		uY += PAGES_STATIC_HEIGHT;

		uY += PAGES_VSPACE_SM;
		SetDlgItemPosSize(hDlg, IDC_EVANS_EDT_FRONTALHORNSMAXWIDTH, PAGES_MARGIN_LEFT, uY, uFullWidth, PAGES_EDIT_HEIGHT);
		uY += PAGES_EDIT_HEIGHT;

		uY += PAGES_VSPACE_MD;
		SetDlgItemPosSize(hDlg, IDC_EVANS_STC_SKULLINNERDIAMETER, PAGES_MARGIN_LEFT, uY, uFullWidth, PAGES_STATIC_HEIGHT);
		uY += PAGES_STATIC_HEIGHT;

		uY += PAGES_VSPACE_SM;
		SetDlgItemPosSize(hDlg, IDC_EVANS_EDT_SKULLMAXINNERDIAMETER, PAGES_MARGIN_LEFT, uY, uFullWidth, PAGES_EDIT_HEIGHT);

		// The "Calculate" button
		SetDlgItemPosSize(hDlg, IDC_EVANS_CMD_CALCULATE,
			uCliWidth - (PAGES_MARGIN_RIGHT + PAGES_CALCBTN_WIDTH),
			uCliHeight - (PAGES_MARGIN_BOTTOM + PAGES_CALCBTN_HEIGHT),
			PAGES_CALCBTN_WIDTH, PAGES_CALCBTN_HEIGHT);

		// The "Results" section
		uX = PAGES_MARGIN_LEFT;
		uY = uCliHeight - (PAGES_MARGIN_BOTTOM + PAGES_CALCBTN_HEIGHT);
		SetDlgItemPosSize(hDlg, IDC_PIC_RESULTS, uX, uY, PAGES_RESULT_PIC_WIDTH, PAGES_RESULT_PIC_HEIGHT);
		uX += PAGES_RESULT_PIC_WIDTH + PAGES_RESULT_HSPC_PICSTC;
		SetDlgItemPosSize(hDlg, IDC_STC_RESULTS, uX, uY + PAGES_EVANS_RESSTC_SPCTOP, PAGES_EVANS_RESSTC_WIDTH, PAGES_EVANS_RESSTC_HEIGHT);
		uX += PAGES_EVANS_RESSTC_WIDTH + PAGES_RESULT_HSPC_STCLNK;
		SetDlgItemPosSize(hDlg, IDC_LNK_RESULTS, uX, uY + PAGES_RESULT_VSPC_LNKTOP, PAGES_RESULT_LNK_WIDTH, PAGES_RESULT_LNK_HEIGHT);

		InvalidateRect(hDlg, NULL, FALSE);
		break;
	}


	case WM_DESTROY: {
		HGDIOBJ	hObjOld = (HGDIOBJ)SendDlgItemMessage(hDlg, IDC_PIC_RESULTS, STM_GETIMAGE, IMAGE_BITMAP, 0);
		TCHAR* ptsFilePath = (TCHAR*)GetWindowLongPtr(hDlg, DWLP_USER);


		if (hObjOld) DeleteObject(hObjOld);
		if (ptsFilePath) HeapFree(GetProcessHeap(), 0, ptsFilePath);
		break;
	}
	}

	return FALSE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
INT_PTR CALLBACK PageMarmarou_DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_INITDIALOG: {
		HWND			hWndMain = GetParent(hDlg);
		RECT			rcMainWndCli, rcCli;
		POINT			ptDlg;
		SIZE			zeDlg;
		MAINWNDDATA* pMainData = (MAINWNDDATA*)GetWindowLongPtr(hWndMain, GWLP_USERDATA);


		// Resize and move the dialog to fill the page area
		GetClientRect(hWndMain, &rcMainWndCli);
		ptDlg.x = TABS_OUTER_MARGIN_X + TABS_ITEM_CURVE_MARGIN_X + TABS_LABELAREA_WIDTH + DPIScaleX(2);
		ptDlg.y = TABS_OUTER_MARGIN_Y + TABS_ITEM_CURVE_MARGIN_Y + DPIScaleY(2);
		zeDlg.cx = rcMainWndCli.right - (TABS_OUTER_MARGIN_X + TABS_ITEM_CURVE_MARGIN_X) - ptDlg.x - DPIScaleX(1);
		zeDlg.cy = rcMainWndCli.bottom - (TABS_OUTER_MARGIN_X + TABS_ITEM_CURVE_MARGIN_X) - ptDlg.y - DPIScaleY(1);
		SetWindowPos(hDlg, NULL, ptDlg.x, ptDlg.y, zeDlg.cx, zeDlg.cy, SWP_NOZORDER);

		// Set child controls properties
		SendDlgItemMessage(hDlg, IDC_MARMAROU_STC_TITLE, WM_SETFONT, (WPARAM)pMainData->hFontPageTitle, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_MARMAROU_STC_EVALUATORNAME, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_MARMAROU_STC_PATIENTNAME, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_MARMAROU_STC_MEDICALRECORD, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_MARMAROU_STC_ADDEDVOLUME, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_MARMAROU_STC_BASELINEPRESSURE, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_MARMAROU_STC_MAXIMUMPRESSURE, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_MARMAROU_STC_PRESSUREAFTERTMINS, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_MARMAROU_STC_TIMEFORPT, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));

		LoadCheckDpiAwareBitmap(hDlg, IDC_PIC_RESULTS);
		SendDlgItemMessage(hDlg, IDC_STC_RESULTS, WM_SETFONT, (WPARAM)pMainData->hFontResults, MAKELPARAM(TRUE, 0));
		CreateCtlLink(TEXT("(Open output file)"), 10, 20, 150, 30, hDlg, IDC_LNK_RESULTS, CLR_BACKGROUND, FALSE);
		PageResults_Hide(hDlg);

		EnforceSignedIntegerEdit(GetDlgItem(hDlg, IDC_MARMAROU_EDT_ADDEDVOLUME));
		EnforceSignedIntegerEdit(GetDlgItem(hDlg, IDC_MARMAROU_EDT_BASELINEPRESSURE));
		EnforceSignedIntegerEdit(GetDlgItem(hDlg, IDC_MARMAROU_EDT_MAXIMUMPRESSURE));
		EnforceSignedIntegerEdit(GetDlgItem(hDlg, IDC_MARMAROU_EDT_PRESSUREAFTERTMINS));
		EnforceSignedIntegerEdit(GetDlgItem(hDlg, IDC_MARMAROU_EDT_TIMEFORPT));

		// Should send a WM_SIZE message after adding any control
		GetClientRect(hDlg, &rcCli);
		SendMessage(hDlg, WM_SIZE, SIZE_RESTORED, MAKELPARAM(rcCli.right, rcCli.bottom));

		// Set the keyboard focus
		SetFocus(GetDlgItem(hDlg, IDC_MARMAROU_EDT_EVALUATORNAME));
		return FALSE; // Don't change the focus owner
		break;
	}


	case WM_COMMAND: {
		if (LOWORD(wParam) == IDC_MARMAROU_CMD_CALCULATE) {
			// Validate the fields
			if (ValidateEditEmpty(hDlg, IDC_MARMAROU_EDT_EVALUATORNAME)) {
				InvalidField(hDlg, IDC_MARMAROU_EDT_EVALUATORNAME, TEXT("You should type a name here"));
				return TRUE;
			}

			if (ValidateEditEmpty(hDlg, IDC_MARMAROU_EDT_PATIENTNAME)) {
				InvalidField(hDlg, IDC_MARMAROU_EDT_PATIENTNAME, TEXT("You should type a name here"));
				return TRUE;
			}

			if (ValidateEditEmpty(hDlg, IDC_MARMAROU_EDT_MEDICALRECORD)) {
				InvalidField(hDlg, IDC_MARMAROU_EDT_MEDICALRECORD, TEXT("You should type a medical record here"));
				return TRUE;
			}

			if (ValidateEditEmpty(hDlg, IDC_MARMAROU_EDT_ADDEDVOLUME)) {
				InvalidField(hDlg, IDC_MARMAROU_EDT_ADDEDVOLUME, TEXT("You should type a number here"));
				return TRUE;
			}

			if (ValidateEditEmpty(hDlg, IDC_MARMAROU_EDT_BASELINEPRESSURE)) {
				InvalidField(hDlg, IDC_MARMAROU_EDT_BASELINEPRESSURE, TEXT("You should type a number here"));
				return TRUE;
			}

			if (ValidateEditEmpty(hDlg, IDC_MARMAROU_EDT_MAXIMUMPRESSURE)) {
				InvalidField(hDlg, IDC_MARMAROU_EDT_MAXIMUMPRESSURE, TEXT("You should type a number here"));
				return TRUE;
			}

			if (ValidateEditEmpty(hDlg, IDC_MARMAROU_EDT_PRESSUREAFTERTMINS)) {
				InvalidField(hDlg, IDC_MARMAROU_EDT_PRESSUREAFTERTMINS, TEXT("You should type a number here"));
				return TRUE;
			}

			if (ValidateEditEmpty(hDlg, IDC_MARMAROU_EDT_TIMEFORPT)) {
				InvalidField(hDlg, IDC_MARMAROU_EDT_TIMEFORPT, TEXT("You should type a number here"));
				return TRUE;
			}

			// Calculate the results
			if (CreateResults_MarmarouBolus(hDlg)) {
				EnableWindow(GetDlgItem(hDlg, IDC_MARMAROU_CMD_CALCULATE), FALSE);
			}
		}

		// "Open output file" link
		if (LOWORD(wParam) == IDC_LNK_RESULTS) {
			TCHAR* ptsFilePath = (TCHAR*)GetWindowLongPtr(hDlg, DWLP_USER);

			if (ptsFilePath == NULL) {
				MessageBox(hDlg, TEXT("Sorry, file not found!"), STR_APPNAME, MB_ICONEXCLAMATION | MB_OK);
				break;
			}

			ShellExecute(hDlg, TEXT("open"), ptsFilePath, NULL, NULL, SW_SHOW);
		}

		// Any one of the edit controls has been changed
		if (HIWORD(wParam) == EN_CHANGE) {
			TCHAR* ptsFilePath = (TCHAR*)GetWindowLongPtr(hDlg, DWLP_USER);

			if (ptsFilePath) {
				HeapFree(GetProcessHeap(), 0, ptsFilePath);
				SetWindowLongPtr(hDlg, DWLP_USER, (LONG_PTR)0);
			}
			PageResults_Hide(hDlg);
			EnableWindow(GetDlgItem(hDlg, IDC_MARMAROU_CMD_CALCULATE), TRUE);
		}
		break;
	}


	case WM_PAINT: {
		PAINTSTRUCT	Ps;
		RECT			rcCli;


		GetClientRect(hDlg, &rcCli);
		BeginPaint(hDlg, &Ps);
		ClearDC(Ps.hdc, CLR_BACKGROUND, 0, 0, rcCli.right, rcCli.bottom);
		EndPaint(hDlg, &Ps);

		return TRUE;
		break;
	}


	case WM_CTLCOLORSTATIC:
	case WM_CTLCOLORBTN:
	case WM_CTLCOLOREDIT: // Useful only for disabled or read-only Edit controls
	{
		MAINWNDDATA* pMainData = (MAINWNDDATA*)GetWindowLongPtr(GetParent(hDlg), GWLP_USERDATA);

		SetBkColor((HDC)wParam, CLR_BACKGROUND);
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (INT_PTR)pMainData->hBrushCtlBkgnd;
		break;
	}


	case WM_SIZE: {
		UINT	uY, uX, uCliWidth = LOWORD(lParam), uCliHeight = HIWORD(lParam);
		UINT	uFullWidth = uCliWidth - (PAGES_MARGIN_LEFT + PAGES_MARGIN_RIGHT);
		UINT	uColWidth = (UINT)((uFullWidth - PAGES_HSPACE_MD) / 2.0f);


		uY = PAGES_MARGIN_TOP;
		SetDlgItemPosSize(hDlg, IDC_MARMAROU_STC_TITLE, PAGES_MARGIN_LEFT, uY, uFullWidth, PAGES_TITLE_HEIGHT);
		uY += PAGES_TITLE_HEIGHT;

		uY += PAGES_VSPACE_LG;
		SetDlgItemPosSize(hDlg, IDC_MARMAROU_STC_EVALUATORNAME, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_STATIC_HEIGHT);
		uY += PAGES_STATIC_HEIGHT;

		uY += PAGES_VSPACE_SM;
		SetDlgItemPosSize(hDlg, IDC_MARMAROU_EDT_EVALUATORNAME, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_EDIT_HEIGHT);
		uY += PAGES_EDIT_HEIGHT;

		uY += PAGES_VSPACE_MD;
		SetDlgItemPosSize(hDlg, IDC_MARMAROU_STC_PATIENTNAME, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_STATIC_HEIGHT);
		SetDlgItemPosSize(hDlg, IDC_MARMAROU_STC_MEDICALRECORD, PAGES_MARGIN_LEFT + uColWidth + PAGES_HSPACE_MD, uY, uColWidth, PAGES_STATIC_HEIGHT);
		uY += PAGES_STATIC_HEIGHT;

		uY += PAGES_VSPACE_SM;
		SetDlgItemPosSize(hDlg, IDC_MARMAROU_EDT_PATIENTNAME, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_EDIT_HEIGHT);
		SetDlgItemPosSize(hDlg, IDC_MARMAROU_EDT_MEDICALRECORD, PAGES_MARGIN_LEFT + uColWidth + PAGES_HSPACE_MD, uY, uColWidth, PAGES_EDIT_HEIGHT);
		uY += PAGES_EDIT_HEIGHT;

		uY += PAGES_VSPACE_LG;
		SetDlgItemPosSize(hDlg, IDC_MARMAROU_STC_ADDEDVOLUME, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_STATIC_HEIGHT);
		SetDlgItemPosSize(hDlg, IDC_MARMAROU_STC_BASELINEPRESSURE, PAGES_MARGIN_LEFT + uColWidth + PAGES_HSPACE_MD, uY, uColWidth, PAGES_STATIC_HEIGHT);
		uY += PAGES_STATIC_HEIGHT;

		uY += PAGES_VSPACE_SM;
		SetDlgItemPosSize(hDlg, IDC_MARMAROU_EDT_ADDEDVOLUME, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_EDIT_HEIGHT);
		SetDlgItemPosSize(hDlg, IDC_MARMAROU_EDT_BASELINEPRESSURE, PAGES_MARGIN_LEFT + uColWidth + PAGES_HSPACE_MD, uY, uColWidth, PAGES_EDIT_HEIGHT);
		uY += PAGES_EDIT_HEIGHT;

		uY += PAGES_VSPACE_MD;
		SetDlgItemPosSize(hDlg, IDC_MARMAROU_STC_MAXIMUMPRESSURE, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_STATIC_HEIGHT);
		SetDlgItemPosSize(hDlg, IDC_MARMAROU_STC_PRESSUREAFTERTMINS, PAGES_MARGIN_LEFT + uColWidth + PAGES_HSPACE_MD, uY, uColWidth, PAGES_STATIC_HEIGHT);
		uY += PAGES_STATIC_HEIGHT;

		uY += PAGES_VSPACE_SM;
		SetDlgItemPosSize(hDlg, IDC_MARMAROU_EDT_MAXIMUMPRESSURE, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_EDIT_HEIGHT);
		SetDlgItemPosSize(hDlg, IDC_MARMAROU_EDT_PRESSUREAFTERTMINS, PAGES_MARGIN_LEFT + uColWidth + PAGES_HSPACE_MD, uY, uColWidth, PAGES_EDIT_HEIGHT);
		uY += PAGES_EDIT_HEIGHT;

		uY += PAGES_VSPACE_MD;
		SetDlgItemPosSize(hDlg, IDC_MARMAROU_STC_TIMEFORPT, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_STATIC_HEIGHT);
		uY += PAGES_STATIC_HEIGHT;

		uY += PAGES_VSPACE_SM;
		SetDlgItemPosSize(hDlg, IDC_MARMAROU_EDT_TIMEFORPT, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_EDIT_HEIGHT);

		// The "Calculate" button
		SetDlgItemPosSize(hDlg, IDC_MARMAROU_CMD_CALCULATE,
			uCliWidth - (PAGES_MARGIN_RIGHT + PAGES_CALCBTN_WIDTH),
			uCliHeight - (PAGES_MARGIN_BOTTOM + PAGES_CALCBTN_HEIGHT),
			PAGES_CALCBTN_WIDTH, PAGES_CALCBTN_HEIGHT);

		// The "Results" section
		uX = PAGES_MARGIN_LEFT;
		uY = uCliHeight - (PAGES_MARGIN_BOTTOM + PAGES_CALCBTN_HEIGHT);
		SetDlgItemPosSize(hDlg, IDC_PIC_RESULTS, uX, uY, PAGES_RESULT_PIC_WIDTH, PAGES_RESULT_PIC_HEIGHT);
		uX += PAGES_RESULT_PIC_WIDTH + PAGES_RESULT_HSPC_PICSTC;
		SetDlgItemPosSize(hDlg, IDC_STC_RESULTS, uX, uY + PAGES_MARMAROU_RESSTC_SPCTOP, PAGES_MARMAROU_RESSTC_WIDTH, PAGES_MARMAROU_RESSTC_HEIGHT);
		uX += PAGES_MARMAROU_RESSTC_WIDTH + PAGES_RESULT_HSPC_STCLNK;
		SetDlgItemPosSize(hDlg, IDC_LNK_RESULTS, uX, uY + PAGES_RESULT_VSPC_LNKTOP, PAGES_RESULT_LNK_WIDTH, PAGES_RESULT_LNK_HEIGHT);

		InvalidateRect(hDlg, NULL, FALSE);
		break;
	}


	case WM_DESTROY: {
		HGDIOBJ	hObjOld = (HGDIOBJ)SendDlgItemMessage(hDlg, IDC_PIC_RESULTS, STM_GETIMAGE, IMAGE_BITMAP, 0);
		TCHAR* ptsFilePath = (TCHAR*)GetWindowLongPtr(hDlg, DWLP_USER);


		if (hObjOld) DeleteObject(hObjOld);
		if (ptsFilePath) HeapFree(GetProcessHeap(), 0, ptsFilePath);
		break;
	}
	}

	return FALSE;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
INT_PTR CALLBACK PageKatzman_DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_INITDIALOG: {
		HWND			hWndMain = GetParent(hDlg);
		RECT			rcMainWndCli, rcCli;
		POINT			ptDlg;
		SIZE			zeDlg;
		MAINWNDDATA* pMainData = (MAINWNDDATA*)GetWindowLongPtr(hWndMain, GWLP_USERDATA);


		// Resize and move the dialog to fill the page area
		GetClientRect(hWndMain, &rcMainWndCli);
		ptDlg.x = TABS_OUTER_MARGIN_X + TABS_ITEM_CURVE_MARGIN_X + TABS_LABELAREA_WIDTH + DPIScaleX(2);
		ptDlg.y = TABS_OUTER_MARGIN_Y + TABS_ITEM_CURVE_MARGIN_Y + DPIScaleY(2);
		zeDlg.cx = rcMainWndCli.right - (TABS_OUTER_MARGIN_X + TABS_ITEM_CURVE_MARGIN_X) - ptDlg.x - DPIScaleX(1);
		zeDlg.cy = rcMainWndCli.bottom - (TABS_OUTER_MARGIN_X + TABS_ITEM_CURVE_MARGIN_X) - ptDlg.y - DPIScaleY(1);
		SetWindowPos(hDlg, NULL, ptDlg.x, ptDlg.y, zeDlg.cx, zeDlg.cy, SWP_NOZORDER);

		// Set child controls properties
		SendDlgItemMessage(hDlg, IDC_KATZMAN_STC_TITLE, WM_SETFONT, (WPARAM)pMainData->hFontPageTitle, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_KATZMAN_STC_EVALUATORNAME, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_KATZMAN_STC_PATIENTNAME, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_KATZMAN_STC_MEDICALRECORD, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_KATZMAN_STC_INFUSIONRATE, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_KATZMAN_STC_BASELINEPRESSURE, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_KATZMAN_STC_PLATEAUPRESSURE, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_KATZMAN_STC_TIMEPLATEAU, WM_SETFONT, (WPARAM)pMainData->hFontInput, MAKELPARAM(TRUE, 0));

		LoadCheckDpiAwareBitmap(hDlg, IDC_PIC_RESULTS);
		SendDlgItemMessage(hDlg, IDC_STC_RESULTS, WM_SETFONT, (WPARAM)pMainData->hFontResults, MAKELPARAM(TRUE, 0));
		CreateCtlLink(TEXT("(Open output file)"), 10, 20, 150, 30, hDlg, IDC_LNK_RESULTS, CLR_BACKGROUND, FALSE);

		EnforceSignedIntegerEdit(GetDlgItem(hDlg, IDC_KATZMAN_EDT_INFUSIONRATE));
		EnforceSignedIntegerEdit(GetDlgItem(hDlg, IDC_KATZMAN_EDT_BASELINEPRESSURE));
		EnforceSignedIntegerEdit(GetDlgItem(hDlg, IDC_KATZMAN_EDT_PLATEAUPRESSURE));
		EnforceSignedIntegerEdit(GetDlgItem(hDlg, IDC_KATZMAN_EDT_TIMEPLATEAU));
		PageResults_Hide(hDlg);

		// Should send a WM_SIZE message after adding any control
		GetClientRect(hDlg, &rcCli);
		SendMessage(hDlg, WM_SIZE, SIZE_RESTORED, MAKELPARAM(rcCli.right, rcCli.bottom));

		// Set the keyboard focus
		SetFocus(GetDlgItem(hDlg, IDC_KATZMAN_EDT_EVALUATORNAME));
		return FALSE; // Don't change the focus owner
		break;
	}


	case WM_COMMAND: {
		if (LOWORD(wParam) == IDC_KATZMAN_CMD_CALCULATE) {
			// Validate the fields
			if (ValidateEditEmpty(hDlg, IDC_KATZMAN_EDT_EVALUATORNAME)) {
				InvalidField(hDlg, IDC_KATZMAN_EDT_EVALUATORNAME, TEXT("You should type a name here"));
				return TRUE;
			}

			if (ValidateEditEmpty(hDlg, IDC_KATZMAN_EDT_PATIENTNAME)) {
				InvalidField(hDlg, IDC_KATZMAN_EDT_PATIENTNAME, TEXT("You should type a name here"));
				return TRUE;
			}

			if (ValidateEditEmpty(hDlg, IDC_KATZMAN_EDT_MEDICALRECORD)) {
				InvalidField(hDlg, IDC_KATZMAN_EDT_MEDICALRECORD, TEXT("You should type a medical record here"));
				return TRUE;
			}

			if (ValidateEditEmpty(hDlg, IDC_KATZMAN_EDT_INFUSIONRATE)) {
				InvalidField(hDlg, IDC_KATZMAN_EDT_INFUSIONRATE, TEXT("You should type a number here"));
				return TRUE;
			}

			if (ValidateEditEmpty(hDlg, IDC_KATZMAN_EDT_BASELINEPRESSURE)) {
				InvalidField(hDlg, IDC_KATZMAN_EDT_BASELINEPRESSURE, TEXT("You should type a number here"));
				return TRUE;
			}

			if (ValidateEditEmpty(hDlg, IDC_KATZMAN_EDT_PLATEAUPRESSURE)) {
				InvalidField(hDlg, IDC_KATZMAN_EDT_PLATEAUPRESSURE, TEXT("You should type a number here"));
				return TRUE;
			}

			if (ValidateEditEmpty(hDlg, IDC_KATZMAN_EDT_TIMEPLATEAU)) {
				InvalidField(hDlg, IDC_KATZMAN_EDT_TIMEPLATEAU, TEXT("You should type a number here"));
				return TRUE;
			}

			// Calculate the results
			if (CreateResults_Katzman(hDlg)) {
				EnableWindow(GetDlgItem(hDlg, IDC_KATZMAN_CMD_CALCULATE), FALSE);
			}
		}

		// "Open output file" link
		if (LOWORD(wParam) == IDC_LNK_RESULTS) {
			TCHAR* ptsFilePath = (TCHAR*)GetWindowLongPtr(hDlg, DWLP_USER);

			if (ptsFilePath == NULL) {
				MessageBox(hDlg, TEXT("Sorry, file not found!"), STR_APPNAME, MB_ICONEXCLAMATION | MB_OK);
				break;
			}

			ShellExecute(hDlg, TEXT("open"), ptsFilePath, NULL, NULL, SW_SHOW);
		}

		// Any one of the edit controls has been changed
		if (HIWORD(wParam) == EN_CHANGE) {
			TCHAR* ptsFilePath = (TCHAR*)GetWindowLongPtr(hDlg, DWLP_USER);

			if (ptsFilePath) {
				HeapFree(GetProcessHeap(), 0, ptsFilePath);
				SetWindowLongPtr(hDlg, DWLP_USER, (LONG_PTR)0);
			}
			PageResults_Hide(hDlg);
			EnableWindow(GetDlgItem(hDlg, IDC_KATZMAN_CMD_CALCULATE), TRUE);
		}
		break;
	}


	case WM_PAINT: {
		PAINTSTRUCT	Ps;
		RECT			rcCli;


		GetClientRect(hDlg, &rcCli);
		BeginPaint(hDlg, &Ps);
		ClearDC(Ps.hdc, CLR_BACKGROUND, 0, 0, rcCli.right, rcCli.bottom);
		EndPaint(hDlg, &Ps);

		return TRUE;
		break;
	}


	case WM_CTLCOLORSTATIC:
	case WM_CTLCOLORBTN:
	case WM_CTLCOLOREDIT: // Useful only for disabled or read-only Edit controls
	{
		MAINWNDDATA* pMainData = (MAINWNDDATA*)GetWindowLongPtr(GetParent(hDlg), GWLP_USERDATA);

		SetBkColor((HDC)wParam, CLR_BACKGROUND);
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (INT_PTR)pMainData->hBrushCtlBkgnd;
		break;
	}


	case WM_SIZE: {
		UINT	uY, uX, uCliWidth = LOWORD(lParam), uCliHeight = HIWORD(lParam);
		UINT	uFullWidth = uCliWidth - (PAGES_MARGIN_LEFT + PAGES_MARGIN_RIGHT);
		UINT	uColWidth = (UINT)((uFullWidth - PAGES_HSPACE_MD) / 2.0f);


		uY = PAGES_MARGIN_TOP;
		SetDlgItemPosSize(hDlg, IDC_KATZMAN_STC_TITLE, PAGES_MARGIN_LEFT, uY, uFullWidth, PAGES_TITLE_HEIGHT);
		uY += PAGES_TITLE_HEIGHT;

		uY += PAGES_VSPACE_LG;
		SetDlgItemPosSize(hDlg, IDC_KATZMAN_STC_EVALUATORNAME, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_STATIC_HEIGHT);
		uY += PAGES_STATIC_HEIGHT;

		uY += PAGES_VSPACE_SM;
		SetDlgItemPosSize(hDlg, IDC_KATZMAN_EDT_EVALUATORNAME, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_EDIT_HEIGHT);
		uY += PAGES_EDIT_HEIGHT;

		uY += PAGES_VSPACE_MD;
		SetDlgItemPosSize(hDlg, IDC_KATZMAN_STC_PATIENTNAME, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_STATIC_HEIGHT);
		SetDlgItemPosSize(hDlg, IDC_KATZMAN_STC_MEDICALRECORD, PAGES_MARGIN_LEFT + uColWidth + PAGES_HSPACE_MD, uY, uColWidth, PAGES_STATIC_HEIGHT);
		uY += PAGES_STATIC_HEIGHT;

		uY += PAGES_VSPACE_SM;
		SetDlgItemPosSize(hDlg, IDC_KATZMAN_EDT_PATIENTNAME, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_EDIT_HEIGHT);
		SetDlgItemPosSize(hDlg, IDC_KATZMAN_EDT_MEDICALRECORD, PAGES_MARGIN_LEFT + uColWidth + PAGES_HSPACE_MD, uY, uColWidth, PAGES_EDIT_HEIGHT);
		uY += PAGES_EDIT_HEIGHT;

		uY += PAGES_VSPACE_LG;
		SetDlgItemPosSize(hDlg, IDC_KATZMAN_STC_INFUSIONRATE, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_STATIC_HEIGHT);
		SetDlgItemPosSize(hDlg, IDC_KATZMAN_STC_BASELINEPRESSURE, PAGES_MARGIN_LEFT + uColWidth + PAGES_HSPACE_MD, uY, uColWidth, PAGES_STATIC_HEIGHT);
		uY += PAGES_STATIC_HEIGHT;

		uY += PAGES_VSPACE_SM;
		SetDlgItemPosSize(hDlg, IDC_KATZMAN_EDT_INFUSIONRATE, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_EDIT_HEIGHT);
		SetDlgItemPosSize(hDlg, IDC_KATZMAN_EDT_BASELINEPRESSURE, PAGES_MARGIN_LEFT + uColWidth + PAGES_HSPACE_MD, uY, uColWidth, PAGES_EDIT_HEIGHT);
		uY += PAGES_EDIT_HEIGHT;

		uY += PAGES_VSPACE_MD;
		SetDlgItemPosSize(hDlg, IDC_KATZMAN_STC_PLATEAUPRESSURE, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_STATIC_HEIGHT);
		SetDlgItemPosSize(hDlg, IDC_KATZMAN_STC_TIMEPLATEAU, PAGES_MARGIN_LEFT + uColWidth + PAGES_HSPACE_MD, uY, uColWidth, PAGES_STATIC_HEIGHT);
		uY += PAGES_STATIC_HEIGHT;

		uY += PAGES_VSPACE_SM;
		SetDlgItemPosSize(hDlg, IDC_KATZMAN_EDT_PLATEAUPRESSURE, PAGES_MARGIN_LEFT, uY, uColWidth, PAGES_EDIT_HEIGHT);
		SetDlgItemPosSize(hDlg, IDC_KATZMAN_EDT_TIMEPLATEAU, PAGES_MARGIN_LEFT + uColWidth + PAGES_HSPACE_MD, uY, uColWidth, PAGES_EDIT_HEIGHT);
		uY += PAGES_EDIT_HEIGHT;


		// The "Calculate" button
		SetDlgItemPosSize(hDlg, IDC_KATZMAN_CMD_CALCULATE,
			uCliWidth - (PAGES_MARGIN_RIGHT + PAGES_CALCBTN_WIDTH),
			uCliHeight - (PAGES_MARGIN_BOTTOM + PAGES_CALCBTN_HEIGHT),
			PAGES_CALCBTN_WIDTH, PAGES_CALCBTN_HEIGHT);

		// The "Results" section
		uX = PAGES_MARGIN_LEFT;
		uY = uCliHeight - (PAGES_MARGIN_BOTTOM + PAGES_CALCBTN_HEIGHT);
		SetDlgItemPosSize(hDlg, IDC_PIC_RESULTS, uX, uY, PAGES_RESULT_PIC_WIDTH, PAGES_RESULT_PIC_HEIGHT);
		uX += PAGES_RESULT_PIC_WIDTH + PAGES_RESULT_HSPC_PICSTC;
		SetDlgItemPosSize(hDlg, IDC_STC_RESULTS, uX, uY + PAGES_KATZMAN_RESSTC_SPCTOP, PAGES_KATZMAN_RESSTC_WIDTH, PAGES_KATZMAN_RESSTC_HEIGHT);
		uX += PAGES_KATZMAN_RESSTC_WIDTH + PAGES_RESULT_HSPC_STCLNK;
		SetDlgItemPosSize(hDlg, IDC_LNK_RESULTS, uX, uY + PAGES_RESULT_VSPC_LNKTOP, PAGES_RESULT_LNK_WIDTH, PAGES_RESULT_LNK_HEIGHT);

		InvalidateRect(hDlg, NULL, FALSE);
		break;
	}


	case WM_DESTROY: {
		HGDIOBJ	hObjOld = (HGDIOBJ)SendDlgItemMessage(hDlg, IDC_PIC_RESULTS, STM_GETIMAGE, IMAGE_BITMAP, 0);
		TCHAR* ptsFilePath = (TCHAR*)GetWindowLongPtr(hDlg, DWLP_USER);


		if (hObjOld) DeleteObject(hObjOld);
		if (ptsFilePath) HeapFree(GetProcessHeap(), 0, ptsFilePath);
		break;
	}
	}

	return FALSE;
}
