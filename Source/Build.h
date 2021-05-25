//
// CSF Dynamic Calc
//
// (Build.h) Build-related definitions
//


// Support Unicode
#ifndef UNICODE 
#define UNICODE
#endif
#ifndef _UNICODE 
#define _UNICODE
#endif

// Options for standard system include files
#define STRICT
#define WIN32_LEAN_AND_MEAN

// Minimum supported version of Windows (Windows XP)
#ifndef NTDDI_VERSION
#define NTDDI_VERSION			NTDDI_WINXP
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT				0x0501
#endif
#ifndef WINVER
#define WINVER						0x0501
#endif
#ifndef _WIN32_IE
#define _WIN32_IE					0x0501
#endif

// Main Windows include file
#include <windows.h>

