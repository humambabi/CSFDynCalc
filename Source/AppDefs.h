//
// CSF Dynamic CALC v1.0
// (AppDefs.h) Main Application's Definitions
//


// Main window related definitions
#define STR_APPNAME							TEXT("CSF Dynamic CALC v1.0")
#define WC_MAINWND							TEXT("CSFDCMain_WndCls")
#define WC_CTLLINK					      TEXT("CtlLink")

#define MAINWND_DEFWIDTH					DPIScaleX(825)
#define MAINWND_DEFHEIGHT					DPIScaleY(550)
#define MAINWND_MINWIDTH					DPIScaleX(805)
#define MAINWND_MINHEIGHT					DPIScaleY(521)

#define CLR_BACKGROUND                 0xFFFFFF          // White background

#define CM_SHOWDISCLAIMER              (WM_APP + 0x101)
#define HANDLE_CM_SHOWDISCLAIMER(hWnd, wParam, lParam, fn)  ((fn)(hWnd), 0L)

#define MAINWND_LNK_ABOUT_WIDTH        DPIScaleX(43)
#define MAINWND_LNK_HEIGHT             DPIScaleY(23)
#define MAINWND_LNK_MARGINBOTTOM       DPIScaleY(15)

// Tabs-related definitions
#define CLR_TABAREA                    RGB(245, 250, 255)

#define TABS_LABELAREA_WIDTH           DPIScaleX(150)
#define TABS_OUTER_MARGIN_X            DPIScaleX(7)
#define TABS_OUTER_MARGIN_Y            DPIScaleY(7)
#define TABS_TITLE_HEIGHT              DPIScaleY(45)
#define TABS_ITEM_HEIGHT               DPIScaleY(75)
#define TABS_INNER_MARGIN_X            DPIScaleX(9)
#define TABS_INNER_MARGIN_Y            DPIScaleY(9)
#define TABS_ITEM_CURVE_MARGIN_X       DPIScaleX(6)
#define TABS_ITEM_CURVE_MARGIN_Y       DPIScaleY(6)

// Pages (the 1st page's value should be kept 0)
#define PAGE_EVANS                     0
#define PAGE_MARMAROU                  1
#define PAGE_KATZMAN                   2

// Must be se accordingly
#define PAGE_COUNT                     3

// Page names MUST be consistent with the pages' indices above
#define PAGE_NAMES                                 \
{                                                  \
   TEXT("Evans' index"),                           \
   TEXT("Marmarou's Bolus test"),                  \
   TEXT("Katzman's constant volume infusion test") \
}

// Pages-related definitions
#define PAGES_MARGIN_TOP               DPIScaleY(15)
#define PAGES_MARGIN_LEFT              DPIScaleX(25)
#define PAGES_MARGIN_RIGHT             DPIScaleX(25)
#define PAGES_MARGIN_BOTTOM            DPIScaleY(24)

#define PAGES_TITLE_HEIGHT             DPIScaleY(30)
#define PAGES_STATIC_HEIGHT            DPIScaleY(17)
#define PAGES_EDIT_HEIGHT              DPIScaleY(21)
#define PAGES_CALCBTN_WIDTH            DPIScaleX(95)
#define PAGES_CALCBTN_HEIGHT           DPIScaleY(35)

#define PAGES_VSPACE_LG                DPIScaleY(37)     // Between the title and other controls
#define PAGES_VSPACE_MD                DPIScaleY(15)     // Between row of controls
#define PAGES_VSPACE_SM                DPIScaleY(2)      // Between the static and edit controls
#define PAGES_HSPACE_MD                DPIScaleX(50)     // Between columns of controls

#define PAGES_RESULT_PIC_WIDTH         DPIScaleX(35)
#define PAGES_RESULT_PIC_HEIGHT        DPIScaleY(35)     // Should be the same as Calc button's height
#define PAGES_RESULT_LNK_WIDTH         DPIScaleX(125)
#define PAGES_RESULT_LNK_HEIGHT        DPIScaleY(25)

#define PAGES_EVANS_RESSTC_WIDTH       DPIScaleX(126)
#define PAGES_EVANS_RESSTC_HEIGHT      DPIScaleY(20)
#define PAGES_EVANS_RESSTC_SPCTOP      DPIScaleY(6)
#define PAGES_MARMAROU_RESSTC_WIDTH    DPIScaleX(215)
#define PAGES_MARMAROU_RESSTC_HEIGHT   DPIScaleY(88)
#define PAGES_MARMAROU_RESSTC_SPCTOP   DPIScaleY(-26)
#define PAGES_KATZMAN_RESSTC_WIDTH     DPIScaleX(215)
#define PAGES_KATZMAN_RESSTC_HEIGHT    DPIScaleY(45)
#define PAGES_KATZMAN_RESSTC_SPCTOP    DPIScaleY(-3)

#define PAGES_RESULT_HSPC_PICSTC       DPIScaleX(3)      // Horizontal space between the pic & stc controls
#define PAGES_RESULT_HSPC_STCLNK       DPIScaleX(3)      // Horizontal space between the stc & lnk controls
#define PAGES_RESULT_VSPC_LNKTOP       DPIScaleY(6)      // A space above the lnk control

// Some missing definitions
#if !defined(WM_DPICHANGED)
#define WM_DPICHANGED 0x02E0
#endif
#define HANDLE_WM_DPICHANGED(hWnd, wParam, lParam, fn) \
    ((fn)((hWnd), (int)(short)LOWORD(wParam), (int)(short)HIWORD(wParam), (RECT *)(lParam)), 0L)

#define HANDLE_WM_MOUSELEAVE(hWnd, wParam, lParam, fn)	((fn)(hWnd), 0L)

// Helper macros
#define UNUSED(Param)						(void)Param

// Private data structure for the main window
typedef struct {
   HFONT		hFontPageTitle;
   HFONT    hFontResults;
   HBRUSH   hBrushCtlBkgnd;
} MAINWNDDATA;

// Byte Storage structure. Used for getting the text from a RichEdit stream callback
typedef struct BSTORE {
	UINT	uResLen;
   UINT  uRead;
	BYTE	*pyStorage;
} BSTORE;
