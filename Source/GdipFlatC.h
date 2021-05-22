/*
 * GDI+ 
 *
 * This file is collected from the w32api package.
 *
 * Contributors:
 *   Created by Markus Koenig <markus@stber-koenig.de>
 *
 * THIS SOFTWARE IS NOT COPYRIGHTED
 *
 * This source code is offered for use in the public domain. You may
 * use, modify or distribute it freely.
 *
 * This code is distributed in the hope that it will be useful but
 * WITHOUT ANY WARRANTY. ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
 * DISCLAIMED. This includes but is not limited to warranties of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
	Modified By: Humam Babi
	June 29, 2016
*/

#include <ObjIdl.h>				// Necessary for IStream definition

#ifndef _GDIPLUSFLATC_H
#define _GDIPLUSFLATC_H
#pragma once

#if defined(WIN32_DEFAULT_LIBS)
#pragma comment(lib, "GdiPlus.lib")
#endif

typedef float REAL;
#ifndef IStream
typedef struct IStream IStream;
#endif
#ifndef IDirectDrawSurface7
typedef struct IDirectDrawSurface7 IDirectDrawSurface7;
#endif
#ifndef PROPID
typedef unsigned long PROPID;
#endif

// * gdiplusenums.h
#ifndef __GDIPLUS_ENUMS_H
#define __GDIPLUS_ENUMS_H

typedef enum BrushType {
	BrushTypeSolidColor = 0,
	BrushTypeHatchFill = 1,
	BrushTypeTextureFill = 2,
	BrushTypePathGradient = 3,
	BrushTypeLinearGradient = 4
} BrushType;

typedef enum CombineMode {
	CombineModeReplace = 0,
	CombineModeIntersect = 1,
	CombineModeUnion = 2,
	CombineModeXor = 3,
	CombineModeExclude = 4,
	CombineModeComplement = 5
} CombineMode;

typedef enum CompositingMode {
	CompositingModeSourceOver = 0,
	CompositingModeSourceCopy = 1
} CompositingMode;

typedef enum CompositingQuality {
	CompositingQualityDefault = 0,
	CompositingQualityHighSpeed = 1,
	CompositingQualityHighQuality = 2,
	CompositingQualityGammaCorrected = 3,
	CompositingQualityAssumeLinear = 4
} CompositingQuality;

typedef enum CoordinateSpace {
	CoordinateSpaceWorld = 0,
	CoordinateSpacePage = 1,
	CoordinateSpaceDevice = 2
} CoordinateSpace;

typedef enum CustomLineCapType {
	CustomLineCapTypeDefault = 0,
	CustomLineCapTypeAdjustableArrow = 1
} CustomLineCapType;

typedef enum DashCap {
	DashCapFlat = 0,
	DashCapRound = 2,
	DashCapTriangle = 3
} DashCap;

typedef enum DashStyle {
	DashStyleSolid = 0,
	DashStyleDash = 1,
	DashStyleDot = 2,
	DashStyleDashDot = 3,
	DashStyleDashDotDot = 4,
	DashStyleCustom = 5
} DashStyle;

typedef enum DitherType {
	DitherTypeNone = 0,
	DitherTypeSolid = 1,
	DitherTypeOrdered4x4 = 2,
	DitherTypeOrdered8x8 = 3,
	DitherTypeOrdered16x16 = 4,
	DitherTypeOrdered91x91 = 5,
	DitherTypeSpiral4x4 = 6,
	DitherTypeSpiral8x8 = 7,
	DitherTypeDualSpiral4x4 = 8,
	DitherTypeDualSpiral8x8 = 9,
	DitherTypeErrorDiffusion = 10
} DitherType;

typedef enum DriverStringOptions {
	DriverStringOptionsCmapLookup = 1,
	DriverStringOptionsVertical = 2,
	DriverStringOptionsRealizedAdvance = 4,
	DriverStringOptionsLimitSubpixel = 8
} DriverStringOptions;

#define GDIP_WMF_RECORD_TO_EMFPLUS(meta) ((meta) | 0x10000)
#define GDIP_EMFPLUS_RECORD_BASE (0x4000)
typedef enum EmfPlusRecordType {
	WmfRecordTypeSetBkColor                    = GDIP_WMF_RECORD_TO_EMFPLUS(META_SETBKCOLOR),
	WmfRecordTypeSetBkMode                     = GDIP_WMF_RECORD_TO_EMFPLUS(META_SETBKMODE),
	WmfRecordTypeSetMapMode                    = GDIP_WMF_RECORD_TO_EMFPLUS(META_SETMAPMODE),
	WmfRecordTypeSetROP2                       = GDIP_WMF_RECORD_TO_EMFPLUS(META_SETROP2),
	WmfRecordTypeSetRelAbs                     = GDIP_WMF_RECORD_TO_EMFPLUS(META_SETRELABS),
	WmfRecordTypeSetPolyFillMode               = GDIP_WMF_RECORD_TO_EMFPLUS(META_SETPOLYFILLMODE),
	WmfRecordTypeSetStretchBltMode             = GDIP_WMF_RECORD_TO_EMFPLUS(META_SETSTRETCHBLTMODE),
	WmfRecordTypeSetTextCharExtra              = GDIP_WMF_RECORD_TO_EMFPLUS(META_SETTEXTCHAREXTRA),
	WmfRecordTypeSetTextColor                  = GDIP_WMF_RECORD_TO_EMFPLUS(META_SETTEXTCOLOR),
	WmfRecordTypeSetTextJustification          = GDIP_WMF_RECORD_TO_EMFPLUS(META_SETTEXTJUSTIFICATION),
	WmfRecordTypeSetWindowOrg                  = GDIP_WMF_RECORD_TO_EMFPLUS(META_SETWINDOWORG),
	WmfRecordTypeSetWindowExt                  = GDIP_WMF_RECORD_TO_EMFPLUS(META_SETWINDOWEXT),
	WmfRecordTypeSetViewportOrg                = GDIP_WMF_RECORD_TO_EMFPLUS(META_SETVIEWPORTORG),
	WmfRecordTypeSetViewportExt                = GDIP_WMF_RECORD_TO_EMFPLUS(META_SETVIEWPORTEXT),
	WmfRecordTypeOffsetWindowOrg               = GDIP_WMF_RECORD_TO_EMFPLUS(META_OFFSETWINDOWORG),
	WmfRecordTypeScaleWindowExt                = GDIP_WMF_RECORD_TO_EMFPLUS(META_SCALEWINDOWEXT),
	WmfRecordTypeOffsetViewportOrg             = GDIP_WMF_RECORD_TO_EMFPLUS(META_OFFSETVIEWPORTORG),
	WmfRecordTypeScaleViewportExt              = GDIP_WMF_RECORD_TO_EMFPLUS(META_SCALEVIEWPORTEXT),
	WmfRecordTypeLineTo                        = GDIP_WMF_RECORD_TO_EMFPLUS(META_LINETO),
	WmfRecordTypeMoveTo                        = GDIP_WMF_RECORD_TO_EMFPLUS(META_MOVETO),
	WmfRecordTypeExcludeClipRect               = GDIP_WMF_RECORD_TO_EMFPLUS(META_EXCLUDECLIPRECT),
	WmfRecordTypeIntersectClipRect             = GDIP_WMF_RECORD_TO_EMFPLUS(META_INTERSECTCLIPRECT),
	WmfRecordTypeArc                           = GDIP_WMF_RECORD_TO_EMFPLUS(META_ARC),
	WmfRecordTypeEllipse                       = GDIP_WMF_RECORD_TO_EMFPLUS(META_ELLIPSE),
	WmfRecordTypeFloodFill                     = GDIP_WMF_RECORD_TO_EMFPLUS(META_FLOODFILL),
	WmfRecordTypePie                           = GDIP_WMF_RECORD_TO_EMFPLUS(META_PIE),
	WmfRecordTypeRectangle                     = GDIP_WMF_RECORD_TO_EMFPLUS(META_RECTANGLE),
	WmfRecordTypeRoundRect                     = GDIP_WMF_RECORD_TO_EMFPLUS(META_ROUNDRECT),
	WmfRecordTypePatBlt                        = GDIP_WMF_RECORD_TO_EMFPLUS(META_PATBLT),
	WmfRecordTypeSaveDC                        = GDIP_WMF_RECORD_TO_EMFPLUS(META_SAVEDC),
	WmfRecordTypeSetPixel                      = GDIP_WMF_RECORD_TO_EMFPLUS(META_SETPIXEL),
	WmfRecordTypeOffsetClipRgn                 = GDIP_WMF_RECORD_TO_EMFPLUS(META_OFFSETCLIPRGN),
	WmfRecordTypeTextOut                       = GDIP_WMF_RECORD_TO_EMFPLUS(META_TEXTOUT),
	WmfRecordTypeBitBlt                        = GDIP_WMF_RECORD_TO_EMFPLUS(META_BITBLT),
	WmfRecordTypeStretchBlt                    = GDIP_WMF_RECORD_TO_EMFPLUS(META_STRETCHBLT),
	WmfRecordTypePolygon                       = GDIP_WMF_RECORD_TO_EMFPLUS(META_POLYGON),
	WmfRecordTypePolyline                      = GDIP_WMF_RECORD_TO_EMFPLUS(META_POLYLINE),
	WmfRecordTypeEscape                        = GDIP_WMF_RECORD_TO_EMFPLUS(META_ESCAPE),
	WmfRecordTypeRestoreDC                     = GDIP_WMF_RECORD_TO_EMFPLUS(META_RESTOREDC),
	WmfRecordTypeFillRegion                    = GDIP_WMF_RECORD_TO_EMFPLUS(META_FILLREGION),
	WmfRecordTypeFrameRegion                   = GDIP_WMF_RECORD_TO_EMFPLUS(META_FRAMEREGION),
	WmfRecordTypeInvertRegion                  = GDIP_WMF_RECORD_TO_EMFPLUS(META_INVERTREGION),
	WmfRecordTypePaintRegion                   = GDIP_WMF_RECORD_TO_EMFPLUS(META_PAINTREGION),
	WmfRecordTypeSelectClipRegion              = GDIP_WMF_RECORD_TO_EMFPLUS(META_SELECTCLIPREGION),
	WmfRecordTypeSelectObject                  = GDIP_WMF_RECORD_TO_EMFPLUS(META_SELECTOBJECT),
	WmfRecordTypeSetTextAlign                  = GDIP_WMF_RECORD_TO_EMFPLUS(META_SETTEXTALIGN),
	WmfRecordTypeDrawText                      = GDIP_WMF_RECORD_TO_EMFPLUS(0x062F),
	WmfRecordTypeChord                         = GDIP_WMF_RECORD_TO_EMFPLUS(META_CHORD),
	WmfRecordTypeSetMapperFlags                = GDIP_WMF_RECORD_TO_EMFPLUS(META_SETMAPPERFLAGS),
	WmfRecordTypeExtTextOut                    = GDIP_WMF_RECORD_TO_EMFPLUS(META_EXTTEXTOUT),
	WmfRecordTypeSetDIBToDev                   = GDIP_WMF_RECORD_TO_EMFPLUS(META_SETDIBTODEV),
	WmfRecordTypeSelectPalette                 = GDIP_WMF_RECORD_TO_EMFPLUS(META_SELECTPALETTE),
	WmfRecordTypeRealizePalette                = GDIP_WMF_RECORD_TO_EMFPLUS(META_REALIZEPALETTE),
	WmfRecordTypeAnimatePalette                = GDIP_WMF_RECORD_TO_EMFPLUS(META_ANIMATEPALETTE),
	WmfRecordTypeSetPalEntries                 = GDIP_WMF_RECORD_TO_EMFPLUS(META_SETPALENTRIES),
	WmfRecordTypePolyPolygon                   = GDIP_WMF_RECORD_TO_EMFPLUS(META_POLYPOLYGON),
	WmfRecordTypeResizePalette                 = GDIP_WMF_RECORD_TO_EMFPLUS(META_RESIZEPALETTE),
	WmfRecordTypeDIBBitBlt                     = GDIP_WMF_RECORD_TO_EMFPLUS(META_DIBBITBLT),
	WmfRecordTypeDIBStretchBlt                 = GDIP_WMF_RECORD_TO_EMFPLUS(META_DIBSTRETCHBLT),
	WmfRecordTypeDIBCreatePatternBrush         = GDIP_WMF_RECORD_TO_EMFPLUS(META_DIBCREATEPATTERNBRUSH),
	WmfRecordTypeStretchDIB                    = GDIP_WMF_RECORD_TO_EMFPLUS(META_STRETCHDIB),
	WmfRecordTypeExtFloodFill                  = GDIP_WMF_RECORD_TO_EMFPLUS(META_EXTFLOODFILL),
	WmfRecordTypeSetLayout                     = GDIP_WMF_RECORD_TO_EMFPLUS(0x0149),
	WmfRecordTypeResetDC                       = GDIP_WMF_RECORD_TO_EMFPLUS(0x014C),
	WmfRecordTypeStartDoc                      = GDIP_WMF_RECORD_TO_EMFPLUS(0x014D),
	WmfRecordTypeStartPage                     = GDIP_WMF_RECORD_TO_EMFPLUS(0x004F),
	WmfRecordTypeEndPage                       = GDIP_WMF_RECORD_TO_EMFPLUS(0x0050),
	WmfRecordTypeAbortDoc                      = GDIP_WMF_RECORD_TO_EMFPLUS(0x0052),
	WmfRecordTypeEndDoc                        = GDIP_WMF_RECORD_TO_EMFPLUS(0x005E),
	WmfRecordTypeDeleteObject                  = GDIP_WMF_RECORD_TO_EMFPLUS(META_DELETEOBJECT),
	WmfRecordTypeCreatePalette                 = GDIP_WMF_RECORD_TO_EMFPLUS(META_CREATEPALETTE),
	WmfRecordTypeCreateBrush                   = GDIP_WMF_RECORD_TO_EMFPLUS(0x00F8),
	WmfRecordTypeCreatePatternBrush            = GDIP_WMF_RECORD_TO_EMFPLUS(META_CREATEPATTERNBRUSH),
	WmfRecordTypeCreatePenIndirect             = GDIP_WMF_RECORD_TO_EMFPLUS(META_CREATEPENINDIRECT),
	WmfRecordTypeCreateFontIndirect            = GDIP_WMF_RECORD_TO_EMFPLUS(META_CREATEFONTINDIRECT),
	WmfRecordTypeCreateBrushIndirect           = GDIP_WMF_RECORD_TO_EMFPLUS(META_CREATEBRUSHINDIRECT),
	WmfRecordTypeCreateBitmapIndirect          = GDIP_WMF_RECORD_TO_EMFPLUS(0x02FD),
	WmfRecordTypeCreateBitmap                  = GDIP_WMF_RECORD_TO_EMFPLUS(0x06FE),
	WmfRecordTypeCreateRegion                  = GDIP_WMF_RECORD_TO_EMFPLUS(META_CREATEREGION),
	EmfRecordTypeHeader                        = EMR_HEADER,
	EmfRecordTypePolyBezier                    = EMR_POLYBEZIER,
	EmfRecordTypePolygon                       = EMR_POLYGON,
	EmfRecordTypePolyline                      = EMR_POLYLINE,
	EmfRecordTypePolyBezierTo                  = EMR_POLYBEZIERTO,
	EmfRecordTypePolyLineTo                    = EMR_POLYLINETO,
	EmfRecordTypePolyPolyline                  = EMR_POLYPOLYLINE,
	EmfRecordTypePolyPolygon                   = EMR_POLYPOLYGON,
	EmfRecordTypeSetWindowExtEx                = EMR_SETWINDOWEXTEX,
	EmfRecordTypeSetWindowOrgEx                = EMR_SETWINDOWORGEX,
	EmfRecordTypeSetViewportExtEx              = EMR_SETVIEWPORTEXTEX,
	EmfRecordTypeSetViewportOrgEx              = EMR_SETVIEWPORTORGEX,
	EmfRecordTypeSetBrushOrgEx                 = EMR_SETBRUSHORGEX,
	EmfRecordTypeEOF                           = EMR_EOF,
	EmfRecordTypeSetPixelV                     = EMR_SETPIXELV,
	EmfRecordTypeSetMapperFlags                = EMR_SETMAPPERFLAGS,
	EmfRecordTypeSetMapMode                    = EMR_SETMAPMODE,
	EmfRecordTypeSetBkMode                     = EMR_SETBKMODE,
	EmfRecordTypeSetPolyFillMode               = EMR_SETPOLYFILLMODE,
	EmfRecordTypeSetROP2                       = EMR_SETROP2,
	EmfRecordTypeSetStretchBltMode             = EMR_SETSTRETCHBLTMODE,
	EmfRecordTypeSetTextAlign                  = EMR_SETTEXTALIGN,
	EmfRecordTypeSetColorAdjustment            = EMR_SETCOLORADJUSTMENT,
	EmfRecordTypeSetTextColor                  = EMR_SETTEXTCOLOR,
	EmfRecordTypeSetBkColor                    = EMR_SETBKCOLOR,
	EmfRecordTypeOffsetClipRgn                 = EMR_OFFSETCLIPRGN,
	EmfRecordTypeMoveToEx                      = EMR_MOVETOEX,
	EmfRecordTypeSetMetaRgn                    = EMR_SETMETARGN,
	EmfRecordTypeExcludeClipRect               = EMR_EXCLUDECLIPRECT,
	EmfRecordTypeIntersectClipRect             = EMR_INTERSECTCLIPRECT,
	EmfRecordTypeScaleViewportExtEx            = EMR_SCALEVIEWPORTEXTEX,
	EmfRecordTypeScaleWindowExtEx              = EMR_SCALEWINDOWEXTEX,
	EmfRecordTypeSaveDC                        = EMR_SAVEDC,
	EmfRecordTypeRestoreDC                     = EMR_RESTOREDC,
	EmfRecordTypeSetWorldTransform             = EMR_SETWORLDTRANSFORM,
	EmfRecordTypeModifyWorldTransform          = EMR_MODIFYWORLDTRANSFORM,
	EmfRecordTypeSelectObject                  = EMR_SELECTOBJECT,
	EmfRecordTypeCreatePen                     = EMR_CREATEPEN,
	EmfRecordTypeCreateBrushIndirect           = EMR_CREATEBRUSHINDIRECT,
	EmfRecordTypeDeleteObject                  = EMR_DELETEOBJECT,
	EmfRecordTypeAngleArc                      = EMR_ANGLEARC,
	EmfRecordTypeEllipse                       = EMR_ELLIPSE,
	EmfRecordTypeRectangle                     = EMR_RECTANGLE,
	EmfRecordTypeRoundRect                     = EMR_ROUNDRECT,
	EmfRecordTypeArc                           = EMR_ARC,
	EmfRecordTypeChord                         = EMR_CHORD,
	EmfRecordTypePie                           = EMR_PIE,
	EmfRecordTypeSelectPalette                 = EMR_SELECTPALETTE,
	EmfRecordTypeCreatePalette                 = EMR_CREATEPALETTE,
	EmfRecordTypeSetPaletteEntries             = EMR_SETPALETTEENTRIES,
	EmfRecordTypeResizePalette                 = EMR_RESIZEPALETTE,
	EmfRecordTypeRealizePalette                = EMR_REALIZEPALETTE,
	EmfRecordTypeExtFloodFill                  = EMR_EXTFLOODFILL,
	EmfRecordTypeLineTo                        = EMR_LINETO,
	EmfRecordTypeArcTo                         = EMR_ARCTO,
	EmfRecordTypePolyDraw                      = EMR_POLYDRAW,
	EmfRecordTypeSetArcDirection               = EMR_SETARCDIRECTION,
	EmfRecordTypeSetMiterLimit                 = EMR_SETMITERLIMIT,
	EmfRecordTypeBeginPath                     = EMR_BEGINPATH,
	EmfRecordTypeEndPath                       = EMR_ENDPATH,
	EmfRecordTypeCloseFigure                   = EMR_CLOSEFIGURE,
	EmfRecordTypeFillPath                      = EMR_FILLPATH,
	EmfRecordTypeStrokeAndFillPath             = EMR_STROKEANDFILLPATH,
	EmfRecordTypeStrokePath                    = EMR_STROKEPATH,
	EmfRecordTypeFlattenPath                   = EMR_FLATTENPATH,
	EmfRecordTypeWidenPath                     = EMR_WIDENPATH,
	EmfRecordTypeSelectClipPath                = EMR_SELECTCLIPPATH,
	EmfRecordTypeAbortPath                     = EMR_ABORTPATH,
	EmfRecordTypeReserved_069                  = 69,
	EmfRecordTypeGdiComment                    = EMR_GDICOMMENT,
	EmfRecordTypeFillRgn                       = EMR_FILLRGN,
	EmfRecordTypeFrameRgn                      = EMR_FRAMERGN,
	EmfRecordTypeInvertRgn                     = EMR_INVERTRGN,
	EmfRecordTypePaintRgn                      = EMR_PAINTRGN,
	EmfRecordTypeExtSelectClipRgn              = EMR_EXTSELECTCLIPRGN,
	EmfRecordTypeBitBlt                        = EMR_BITBLT,
	EmfRecordTypeStretchBlt                    = EMR_STRETCHBLT,
	EmfRecordTypeMaskBlt                       = EMR_MASKBLT,
	EmfRecordTypePlgBlt                        = EMR_PLGBLT,
	EmfRecordTypeSetDIBitsToDevice             = EMR_SETDIBITSTODEVICE,
	EmfRecordTypeStretchDIBits                 = EMR_STRETCHDIBITS,
	EmfRecordTypeExtCreateFontIndirect         = EMR_EXTCREATEFONTINDIRECTW,
	EmfRecordTypeExtTextOutA                   = EMR_EXTTEXTOUTA,
	EmfRecordTypeExtTextOutW                   = EMR_EXTTEXTOUTW,
	EmfRecordTypePolyBezier16                  = EMR_POLYBEZIER16,
	EmfRecordTypePolygon16                     = EMR_POLYGON16,
	EmfRecordTypePolyline16                    = EMR_POLYLINE16,
	EmfRecordTypePolyBezierTo16                = EMR_POLYBEZIERTO16,
	EmfRecordTypePolylineTo16                  = EMR_POLYLINETO16,
	EmfRecordTypePolyPolyline16                = EMR_POLYPOLYLINE16,
	EmfRecordTypePolyPolygon16                 = EMR_POLYPOLYGON16,
	EmfRecordTypePolyDraw16                    = EMR_POLYDRAW16,
	EmfRecordTypeCreateMonoBrush               = EMR_CREATEMONOBRUSH,
	EmfRecordTypeCreateDIBPatternBrushPt       = EMR_CREATEDIBPATTERNBRUSHPT,
	EmfRecordTypeExtCreatePen                  = EMR_EXTCREATEPEN,
	EmfRecordTypePolyTextOutA                  = EMR_POLYTEXTOUTA,
	EmfRecordTypePolyTextOutW                  = EMR_POLYTEXTOUTW,
	EmfRecordTypeSetICMMode                    = 98,
	EmfRecordTypeCreateColorSpace              = 99,
	EmfRecordTypeSetColorSpace                 = 100,
	EmfRecordTypeDeleteColorSpace              = 101,
	EmfRecordTypeGLSRecord                     = 102,
	EmfRecordTypeGLSBoundedRecord              = 103,
	EmfRecordTypePixelFormat                   = 104,
	EmfRecordTypeDrawEscape                    = 105,
	EmfRecordTypeExtEscape                     = 106,
	EmfRecordTypeStartDoc                      = 107,
	EmfRecordTypeSmallTextOut                  = 108,
	EmfRecordTypeForceUFIMapping               = 109,
	EmfRecordTypeNamedEscape                   = 110,
	EmfRecordTypeColorCorrectPalette           = 111,
	EmfRecordTypeSetICMProfileA                = 112,
	EmfRecordTypeSetICMProfileW                = 113,
	EmfRecordTypeAlphaBlend                    = 114,
	EmfRecordTypeSetLayout                     = 115,
	EmfRecordTypeTransparentBlt                = 116,
	EmfRecordTypeReserved_117                  = 117,
	EmfRecordTypeGradientFill                  = 118,
	EmfRecordTypeSetLinkedUFIs                 = 119,
	EmfRecordTypeSetTextJustification          = 120,
	EmfRecordTypeColorMatchToTargetW           = 121,
	EmfRecordTypeCreateColorSpaceW             = 122,
	EmfRecordTypeMax                           = 122,
	EmfRecordTypeMin                           = 1,
	EmfPlusRecordTypeInvalid                   = GDIP_EMFPLUS_RECORD_BASE,
	EmfPlusRecordTypeHeader,
	EmfPlusRecordTypeEndOfFile,
	EmfPlusRecordTypeComment,
	EmfPlusRecordTypeGetDC,
	EmfPlusRecordTypeMultiFormatStart,
	EmfPlusRecordTypeMultiFormatSection,
	EmfPlusRecordTypeMultiFormatEnd,
	EmfPlusRecordTypeObject,
	EmfPlusRecordTypeClear,
	EmfPlusRecordTypeFillRects,
	EmfPlusRecordTypeDrawRects,
	EmfPlusRecordTypeFillPolygon,
	EmfPlusRecordTypeDrawLines,
	EmfPlusRecordTypeFillEllipse,
	EmfPlusRecordTypeDrawEllipse,
	EmfPlusRecordTypeFillPie,
	EmfPlusRecordTypeDrawPie,
	EmfPlusRecordTypeDrawArc,
	EmfPlusRecordTypeFillRegion,
	EmfPlusRecordTypeFillPath,
	EmfPlusRecordTypeDrawPath,
	EmfPlusRecordTypeFillClosedCurve,
	EmfPlusRecordTypeDrawClosedCurve,
	EmfPlusRecordTypeDrawCurve,
	EmfPlusRecordTypeDrawBeziers,
	EmfPlusRecordTypeDrawImage,
	EmfPlusRecordTypeDrawImagePoints,
	EmfPlusRecordTypeDrawString,
	EmfPlusRecordTypeSetRenderingOrigin,
	EmfPlusRecordTypeSetAntiAliasMode,
	EmfPlusRecordTypeSetTextRenderingHint,
	EmfPlusRecordTypeSetTextContrast,
	EmfPlusRecordTypeSetGammaValue,
	EmfPlusRecordTypeSetInterpolationMode,
	EmfPlusRecordTypeSetPixelOffsetMode,
	EmfPlusRecordTypeSetCompositingMode,
	EmfPlusRecordTypeSetCompositingQuality,
	EmfPlusRecordTypeSave,
	EmfPlusRecordTypeRestore,
	EmfPlusRecordTypeBeginContainer,
	EmfPlusRecordTypeBeginContainerNoParams,
	EmfPlusRecordTypeEndContainer,
	EmfPlusRecordTypeSetWorldTransform,
	EmfPlusRecordTypeResetWorldTransform,
	EmfPlusRecordTypeMultiplyWorldTransform,
	EmfPlusRecordTypeTranslateWorldTransform,
	EmfPlusRecordTypeScaleWorldTransform,
	EmfPlusRecordTypeRotateWorldTransform,
	EmfPlusRecordTypeSetPageTransform,
	EmfPlusRecordTypeResetClip,
	EmfPlusRecordTypeSetClipRect,
	EmfPlusRecordTypeSetClipPath,
	EmfPlusRecordTypeSetClipRegion,
	EmfPlusRecordTypeOffsetClip,
	EmfPlusRecordTypeDrawDriverString,
	EmfPlusRecordTypeStrokeFillPath,
	EmfPlusRecordTypeSerializableObject,
	EmfPlusRecordTypeSetTSGraphics,
	EmfPlusRecordTypeSetTSClip,
	EmfPlusRecordTotal,
	EmfPlusRecordTypeMax = EmfPlusRecordTotal-1,
	EmfPlusRecordTypeMin = EmfPlusRecordTypeHeader
} EmfPlusRecordType;

typedef enum EmfToWmfBitsFlags {
	EmfToWmfBitsFlagsDefault = 0,
	EmfToWmfBitsFlagsEmbedEmf = 1,
	EmfToWmfBitsFlagsIncludePlaceable = 2,
	EmfToWmfBitsFlagsNoXORClip = 4
} EmfToWmfBitsFlags;

typedef enum EmfType {
	EmfTypeEmfOnly = 3,
	EmfTypeEmfPlusOnly = 4,
	EmfTypeEmfPlusDual = 5
} EmfType;

typedef enum EncoderParameterValueType {
	EncoderParameterValueTypeByte = 1,
	EncoderParameterValueTypeASCII = 2,
	EncoderParameterValueTypeShort = 3,
	EncoderParameterValueTypeLong = 4,
	EncoderParameterValueTypeRational = 5,
	EncoderParameterValueTypeLongRange = 6,
	EncoderParameterValueTypeUndefined = 7,
	EncoderParameterValueTypeRationalRange = 8,
	EncoderParameterValueTypePointer = 9
} EncoderParameterValueType;

typedef enum EncoderValue {
	EncoderValueColorTypeCMYK = 0,
	EncoderValueColorTypeYCCK = 1,
	EncoderValueCompressionLZW = 2,
	EncoderValueCompressionCCITT3 = 3,
	EncoderValueCompressionCCITT4 = 4,
	EncoderValueCompressionRle = 5,
	EncoderValueCompressionNone = 6,
	EncoderValueScanMethodInterlaced = 7,
	EncoderValueScanMethodNonInterlaced = 8,
	EncoderValueVersionGif87 = 9,
	EncoderValueVersionGif89 = 10,
	EncoderValueRenderProgressive = 11,
	EncoderValueRenderNonProgressive = 12,
	EncoderValueTransformRotate90 = 13,
	EncoderValueTransformRotate180 = 14,
	EncoderValueTransformRotate270 = 15,
	EncoderValueTransformFlipHorizontal = 16,
	EncoderValueTransformFlipVertical = 17,
	EncoderValueMultiFrame = 18,
	EncoderValueLastFrame = 19,
	EncoderValueFlush = 20,
	EncoderValueFrameDimensionTime = 21,
	EncoderValueFrameDimensionResolution = 22,
	EncoderValueFrameDimensionPage = 23
} EncoderValue;

typedef enum FillMode {
	FillModeAlternate = 0,
	FillModeWinding = 1
} FillMode;

typedef enum FlushIntention {
	FlushIntentionFlush = 0,
	FlushIntentionSync = 1
} FlushIntention;

typedef enum FontStyle {
	FontStyleRegular = 0,
	FontStyleBold = 1,
	FontStyleItalic = 2,
	FontStyleBoldItalic = 3,
	FontStyleUnderline = 4,
	FontStyleStrikeout = 8
} FontStyle;

typedef enum HatchStyle {
	HatchStyleHorizontal = 0,
	HatchStyleVertical = 1,
	HatchStyleForwardDiagonal = 2,
	HatchStyleBackwardDiagonal = 3,
	HatchStyleCross = 4,
	HatchStyleLargeGrid = 4,
	HatchStyleDiagonalCross = 5,
	HatchStyle05Percent = 6,
	HatchStyle10Percent = 7,
	HatchStyle20Percent = 8,
	HatchStyle25Percent = 9,
	HatchStyle30Percent = 10,
	HatchStyle40Percent = 11,
	HatchStyle50Percent = 12,
	HatchStyle60Percent = 13,
	HatchStyle70Percent = 14,
	HatchStyle75Percent = 15,
	HatchStyle80Percent = 16,
	HatchStyle90Percent = 17,
	HatchStyleLightDownwardDiagonal = 18,
	HatchStyleLightUpwardDiagonal = 19,
	HatchStyleDarkDownwardDiagonal = 20,
	HatchStyleDarkUpwardDiagonal = 21,
	HatchStyleWideDownwardDiagonal = 22,
	HatchStyleWideUpwardDiagonal = 23,
	HatchStyleLightVertical = 24,
	HatchStyleLightHorizontal = 25,
	HatchStyleNarrowVertical = 26,
	HatchStyleNarrowHorizontal = 27,
	HatchStyleDarkVertical = 28,
	HatchStyleDarkHorizontal = 29,
	HatchStyleDashedDownwardDiagonal = 30,
	HatchStyleDashedUpwardDiagonal = 31,
	HatchStyleDashedHorizontal = 32,
	HatchStyleDashedVertical = 33,
	HatchStyleSmallConfetti = 34,
	HatchStyleLargeConfetti = 35,
	HatchStyleZigZag = 36,
	HatchStyleWave = 37,
	HatchStyleDiagonalBrick = 38,
	HatchStyleHorizontalBrick = 39,
	HatchStyleWeave = 40,
	HatchStylePlaid = 41,
	HatchStyleDivot = 42,
	HatchStyleDottedGrid = 43,
	HatchStyleDottedDiamond = 44,
	HatchStyleShingle = 45,
	HatchStyleTrellis = 46,
	HatchStyleSphere = 47,
	HatchStyleSmallGrid = 48,
	HatchStyleSmallCheckerBoard = 49,
	HatchStyleLargeCheckerBoard = 50,
	HatchStyleOutlinedDiamond = 51,
	HatchStyleSolidDiamond = 52,
	HatchStyleTotal = 53,
	HatchStyleMin = HatchStyleHorizontal,
	HatchStyleMax = HatchStyleTotal - 1
} HatchStyle;

typedef enum HotkeyPrefix {
	HotkeyPrefixNone = 0,
	HotkeyPrefixShow = 1,
	HotkeyPrefixHide = 2
} HotkeyPrefix;

typedef enum ImageType {
	ImageTypeUnknown = 0,
	ImageTypeBitmap = 1,
	ImageTypeMetafile = 2
} ImageType;

typedef enum QualityMode {
	QualityModeInvalid = -1,
	QualityModeDefault = 0,
	QualityModeLow = 1,
	QualityModeHigh = 2
} QualityMode;

/* TODO: InterpolationMode */
typedef enum InterpolationMode {
	InterpolationModeInvalid = QualityModeInvalid, // Internally used
	InterpolationModeDefault = 0,
	InterpolationModeLowQuality = 1,
	InterpolationModeHighQuality = 2,
	InterpolationModeBilinear = 3,
	InterpolationModeBicubic = 4,
	InterpolationModeNearestNeighbor = 5,
	InterpolationModeHighQualityBilinear = 6,
	InterpolationModeHighQualityBicubic = 7
} InterpolationMode;

typedef enum LinearGradientMode {
	LinearGradientModeHorizontal = 0,
	LinearGradientModeVertical = 1,
	LinearGradientModeForwardDiagonal = 2,
	LinearGradientModeBackwardDiagonal = 3 
} LinearGradientMode;

typedef enum LineCap {
	LineCapFlat = 0,
	LineCapSquare = 1,
	LineCapRound = 2,
	LineCapTriangle = 3,
	LineCapNoAnchor = 16,
	LineCapSquareAnchor = 17,
	LineCapRoundAnchor = 18,
	LineCapDiamondAnchor = 19,
	LineCapArrowAnchor = 20,
	LineCapCustom = 255
} LineCap;

typedef enum LineJoin {
	LineJoinMiter = 0,
	LineJoinBevel = 1,
	LineJoinRound = 2,
	LineJoinMiterClipped = 3
} LineJoin;

typedef enum MatrixOrder {
	MatrixOrderPrepend = 0,
	MatrixOrderAppend = 1
} MatrixOrder;

typedef enum MetafileFrameUnit {
	MetafileFrameUnitPixel = 2,
	MetafileFrameUnitPoint = 3,
	MetafileFrameUnitInch = 4,
	MetafileFrameUnitDocument = 5,
	MetafileFrameUnitMillimeter = 6,
	MetafileFrameUnitGdi = 7
} MetafileFrameUnit;

typedef enum MetafileType {
	MetafileTypeInvalid = 0,
	MetafileTypeWmf = 1,
	MetafileTypeWmfPlaceable = 2,
	MetafileTypeEmf = 3,
	MetafileTypeEmfPlusOnly = 4,
	MetafileTypeEmfPlusDual = 5
} MetafileType;

typedef enum ObjectType {
	ObjectTypeInvalid = 0,
	ObjectTypeBrush = 1,
	ObjectTypePen = 2,
	ObjectTypePath = 3,
	ObjectTypeRegion = 4,
	ObjectTypeFont = 5,
	ObjectTypeStringFormat = 6,
	ObjectTypeImageAttributes = 7,
	ObjectTypeCustomLineCap = 8,
	ObjectTypeGraphics = 9,
	ObjectTypeMin = ObjectTypeBrush,
	ObjectTypeMax = ObjectTypeGraphics
} ObjectType;

typedef enum PathPointType {
	PathPointTypeStart = 0x00,
	PathPointTypeLine = 0x01,
	PathPointTypeBezier = 0x03,
	PathPointTypeBezier3 = 0x03,
	PathPointTypePathTypeMask = 0x07,
	PathPointTypePathDashMode = 0x10,
	PathPointTypePathMarker = 0x20,
	PathPointTypeCloseSubpath = 0x80
} PathPointType;

typedef enum PenAlignment {
	PenAlignmentCenter = 0,
	PenAlignmentInset = 1
} PenAlignment;

typedef enum PenType {
	PenTypeUnknown = -1, 
	PenTypeSolidColor = 0,
	PenTypeHatchFill = 1,
	PenTypeTextureFill = 2,
	PenTypePathGradient = 3,
	PenTypeLinearGradient = 4
} PenType;

typedef enum PixelOffsetMode {
	PixelOffsetModeInvalid = QualityModeInvalid,
	PixelOffsetModeDefault = 0,
	PixelOffsetModeHighSpeed = 1,
	PixelOffsetModeHighQuality = 2,
	PixelOffsetModeNone = 3,
	PixelOffsetModeHalf = 4
} PixelOffsetMode;

typedef enum SmoothingMode {
	SmoothingModeInvalid = QualityModeInvalid,
	SmoothingModeDefault = 0,
	SmoothingModeHighSpeed = 1,
	SmoothingModeHighQuality = 2,
	SmoothingModeNone = 3,
	SmoothingModeAntiAlias8x4 = 4,
	SmoothingModeAntiAlias = 4,
	SmoothingModeAntiAlias8x8 = 5
} SmoothingMode;

typedef enum StringAlignment {
	StringAlignmentNear = 0,
	StringAlignmentCenter = 1,
	StringAlignmentFar = 2
} StringAlignment;

typedef enum StringDigitSubstitute {
	StringDigitSubstituteUser = 0,
	StringDigitSubstituteNone = 1,
	StringDigitSubstituteNational = 2,
	StringDigitSubstituteTraditional = 3
} StringDigitSubstitute;

typedef enum StringFormatFlags {
	StringFormatFlagsDirectionRightToLeft = 0x00000001,
	StringFormatFlagsDirectionVertical = 0x00000002,
	StringFormatFlagsNoFitBlackBox = 0x00000004,
	StringFormatFlagsDisplayFormatControl = 0x00000020,
	StringFormatFlagsNoFontFallback = 0x00000400,
	StringFormatFlagsMeasureTrailingSpaces = 0x00000800,
	StringFormatFlagsNoWrap = 0x00001000,
	StringFormatFlagsLineLimit = 0x00002000,
	StringFormatFlagsNoClip = 0x00004000
} StringFormatFlags;

typedef enum StringTrimming {
	StringTrimmingNone = 0,
	StringTrimmingCharacter = 1,
	StringTrimmingWord = 2,
	StringTrimmingEllipsisCharacter = 3,
	StringTrimmingEllipsisWord = 4,
	StringTrimmingEllipsisPath = 5
} StringTrimming;

typedef enum TextRenderingHint {
	TextRenderingHintSystemDefault = 0,
	TextRenderingHintSingleBitPerPixelGridFit = 1,
	TextRenderingHintSingleBitPerPixel = 2,
	TextRenderingHintAntiAliasGridFit = 3,
	TextRenderingHintAntiAlias = 4,
	TextRenderingHintClearTypeGridFit = 5
} TextRenderingHint;

typedef enum Unit {
	UnitWorld = 0,
	UnitDisplay = 1,
	UnitPixel = 2,
	UnitPoint = 3,
	UnitInch = 4,
	UnitDocument = 5,
	UnitMillimeter = 6
} Unit;

typedef enum WarpMode {
	WarpModePerspective = 0,
	WarpModeBilinear = 1
} WarpMode;

typedef enum WrapMode {
	WrapModeTile = 0,
	WrapModeTileFlipX = 1,
	WrapModeTileFlipY = 2,
	WrapModeTileFlipXY = 3,
	WrapModeClamp = 4
} WrapMode;

typedef enum GpTestControlEnum {
	TestControlForceBilinear = 0,
	TestControlForceNoICM = 1,
	TestControlGetBuildNumber = 2
} GpTestControlEnum;

/* Opaque handles to information blocks on an internal GDI+ stack. */
typedef DWORD GraphicsContainer;
typedef DWORD GraphicsState;

/* Default flatness for GraphicsPath methods Flatten, Outline, Warp, Widen */
/* FIXME: Is FlatnessDefault = 0.25f correct? */
#ifdef __cplusplus
const REAL FlatnessDefault = 0.25f;
#else
#define FlatnessDefault ((REAL) 0.25f)
#endif

#endif /* __GDIPLUS_ENUMS_H */

// * gdiplustypes.h
#ifndef __GDIPLUS_TYPES_H
#define __GDIPLUS_TYPES_H

#define WINGDIPAPI __stdcall
#define GDIPCONST const

typedef enum GpStatus {
	Ok = 0,
	GenericError = 1,
	InvalidParameter = 2,
	OutOfMemory = 3,
	ObjectBusy = 4,
	InsufficientBuffer = 5,
	NotImplemented = 6,
	Win32Error = 7,
	WrongState = 8,
	Aborted = 9,
	FileNotFound = 10,
	ValueOverflow = 11,
	AccessDenied = 12,
	UnknownImageFormat = 13,
	FontFamilyNotFound = 14,
	FontStyleNotFound = 15,
	NotTrueTypeFont = 16,
	UnsupportedGdiplusVersion = 17,
	GdiplusNotInitialized = 18,
	PropertyNotFound = 19,
	PropertyNotSupported = 20,
	ProfileNotFound = 21
} GpStatus;


typedef struct Size {
	INT Width;
	INT Height;
} Size;

typedef struct SizeF {
	REAL Width;
	REAL Height;
} SizeF;

typedef struct Point {
	INT X;
	INT Y;
} Point;

typedef struct PointF {
	REAL X;
	REAL Y;
} PointF;

typedef struct Rect {
	INT X;
	INT Y;
	INT Width;
	INT Height;
} Rect;

typedef struct RectF {
	REAL X;
	REAL Y;
	REAL Width;
	REAL Height;
} RectF;

/* FIXME: Are descendants of this class, when compiled with g++,
   binary compatible with MSVC++ code (especially GDIPLUS.DLL of course)? */
#ifdef __cplusplus
struct GdiplusAbort {
	virtual HRESULT __stdcall Abort(void) {}
};
#else
typedef struct GdiplusAbort GdiplusAbort;  /* incomplete type */
#endif

typedef struct CharacterRange {
	INT First;
	INT Length;
} CharacterRange;

typedef struct PathData {
	INT Count;
	PointF *Points;
	BYTE *Types;
} PathData;

/* Callback function types */
/* FIXME: need a correct definition for these function pointer types */
typedef void *DebugEventProc;
typedef BOOL (CALLBACK *EnumerateMetafileProc)(EmfPlusRecordType,UINT,UINT,const BYTE*,VOID*);
typedef void *DrawImageAbort;
typedef void *GetThumbnailImageAbort;

#endif /* __GDIPLUS_TYPES_H */

// * gdiplusgpstubs.h
#ifndef __GDIPLUS_GPSTUBS_H
#define __GDIPLUS_GPSTUBS_H

typedef Point GpPoint;
typedef PointF GpPointF;
typedef Rect GpRect;
typedef RectF GpRectF;
typedef Size GpSize;
typedef SizeF GpSizeF;

typedef enum BrushType GpBrushType;
typedef enum CombineMode GpCombineMode;
typedef enum CompositingMode GpCompositingMode;
typedef enum CompositingQuality GpCompositingQuality;
typedef enum CoordinateSpace GpCoordinateSpace;
typedef enum CustomLineCapType GpCustomLineCapType;
typedef enum DashCap GpDashCap;
typedef enum DashStyle GpDashStyle;
typedef enum DitherType GpDitherType;
typedef enum DriverStringOptions GpDriverStringOptions;
typedef enum EmfPlusRecordType GpEmfPlusRecordType;
typedef enum EmfToWmfBitsFlags GpEmfToWmfBitsFlags;
typedef enum EmfType GpEmfType;
typedef enum EncoderParameterValueType GpEncoderParameterValueType;
typedef enum EncoderValue GpEncoderValue;
typedef enum FillMode GpFillMode;
typedef enum FlushIntention GpFlushIntention;
typedef enum FontStyle GpFontStyle;
typedef enum HatchStyle GpHatchStyle;
typedef enum HotkeyPrefix GpHotkeyPrefix;
typedef enum ImageType GpImageType;
typedef enum InterpolationMode GpInterpolationMode;
typedef enum LinearGradientMode GpLinearGradientMode;
typedef enum LineCap GpLineCap;
typedef enum LineJoin GpLineJoin;
typedef enum MatrixOrder GpMatrixOrder;
typedef enum MetafileFrameUnit GpMetafileFrameUnit;
typedef enum MetafileType GpMetafileType;
typedef enum ObjectType GpObjectType;
typedef enum PathPointType GpPathPointType;
typedef enum PenAlignment GpPenAlignment;
typedef enum PenType GpPenType;
typedef enum PixelOffsetMode GpPixelOffsetMode;
typedef enum QualityMode GpQualityMode;
typedef enum SmoothingMode GpSmoothingMode;
typedef enum StringAlignment GpStringAlignment;
typedef enum StringDigitSubstitute GpStringDigitSubstitute;
typedef enum StringFormatFlags GpStringFormatFlags;
typedef enum StringTrimming GpStringTrimming;
typedef enum TextRenderingHint GpTextRenderingHint;
typedef enum Unit GpUnit;
typedef enum WarpMode GpWarpMode;
typedef enum WrapMode GpWrapMode;

typedef void CGpEffect;
typedef void GpAdjustableArrowCap;
typedef void GpBitmap;
typedef void GpBrush;
typedef void GpCachedBitmap;
typedef void GpCustomLineCap;
typedef void GpFont;
typedef void GpFontFamily;
typedef void GpFontCollection;
typedef void GpGraphics;
typedef void GpHatch;
typedef void GpImage;
typedef void GpImageAttributes;
typedef void GpLineGradient;
typedef void GpMatrix;
typedef void GpMetafile;
typedef void GpPath;
typedef void GpPathData;
typedef void GpPathGradient;
typedef void GpPathIterator;
typedef void GpPen;
typedef void GpRegion;
typedef void GpSolidFill;
typedef void GpStringFormat;
typedef void GpTexture;

#endif /* __GDIPLUS_GPSTUBS_H */

// * gdiplusimaging.h
#ifndef __GDIPLUS_IMAGING_H
#define __GDIPLUS_IMAGING_H

typedef enum ImageCodecFlags {
	ImageCodecFlagsEncoder = 0x00000001,
	ImageCodecFlagsDecoder = 0x00000002,
	ImageCodecFlagsSupportBitmap = 0x00000004,
	ImageCodecFlagsSupportVector = 0x00000008,
	ImageCodecFlagsSeekableEncode = 0x00000010,
	ImageCodecFlagsBlockingDecode = 0x00000020,
	ImageCodecFlagsBuiltin = 0x00010000,
	ImageCodecFlagsSystem = 0x00020000,
	ImageCodecFlagsUser = 0x00040000
} ImageCodecFlags;

typedef enum ImageFlags {
	ImageFlagsNone = 0,
	ImageFlagsScalable = 0x00000001,
	ImageFlagsHasAlpha = 0x00000002,
	ImageFlagsHasTranslucent = 0x00000004,
	ImageFlagsPartiallyScalable = 0x00000008,
	ImageFlagsColorSpaceRGB = 0x00000010,
	ImageFlagsColorSpaceCMYK = 0x00000020,
	ImageFlagsColorSpaceGRAY = 0x00000040,
	ImageFlagsColorSpaceYCBCR = 0x00000080,
	ImageFlagsColorSpaceYCCK = 0x00000100,
	ImageFlagsHasRealDPI = 0x00001000,
	ImageFlagsHasRealPixelSize = 0x00002000,
	ImageFlagsReadOnly = 0x00010000,
	ImageFlagsCaching = 0x00020000
} ImageFlags;

typedef enum ImageLockMode {
	ImageLockModeRead = 1,
	ImageLockModeWrite = 2,
	ImageLockModeUserInputBuf = 4
} ImageLockMode;

typedef enum ItemDataPosition {
	ItemDataPositionAfterHeader = 0,
	ItemDataPositionAfterPalette = 1,
	ItemDataPositionAfterBits = 2
} ItemDataPosition;

typedef enum RotateFlipType {
	RotateNoneFlipNone = 0,
	Rotate90FlipNone = 1,
	Rotate180FlipNone = 2,
	Rotate270FlipNone = 3,
	RotateNoneFlipX = 4,
	Rotate90FlipX = 5,
	Rotate180FlipX = 6,
	Rotate270FlipX = 7,
	Rotate180FlipXY = 0,
	Rotate270FlipXY = 1, 
	RotateNoneFlipXY = 2,
	Rotate90FlipXY = 3,
	Rotate180FlipY = 4,
	Rotate270FlipY = 5,
	RotateNoneFlipY = 6,
	Rotate90FlipY = 7
} RotateFlipType;

typedef struct BitmapData {
	UINT Width;
	UINT Height;
	INT Stride;
	INT PixelFormat;  /* MSDN: "PixelFormat PixelFormat;" */
	VOID *Scan0;
	UINT_PTR Reserved;
} BitmapData;

typedef struct EncoderParameter {
	GUID Guid;
	ULONG NumberOfValues;
	ULONG Type;
	VOID *Value;
} EncoderParameter;

typedef struct EncoderParameters {
	UINT Count;
	EncoderParameter Parameter[1];
} EncoderParameters;

typedef struct ImageCodecInfo {
	CLSID Clsid;
	GUID FormatID;
	WCHAR *CodecName;
	WCHAR *DllName;
	WCHAR *FormatDescription;
	WCHAR *FilenameExtension;
	WCHAR *MimeType;
	DWORD Flags;
	DWORD Version;
	DWORD SigCount;
	DWORD SigSize;
	BYTE *SigPattern;
	BYTE *SigMask;
} ImageCodecInfo;

/* FIXME: The order of fields is probably wrong. Please don't use this
 * structure until this problem is resolved!  Can't test because
 * ImageItemData is not supported by the redistributable GDI+ 1.0 DLL. */
typedef struct ImageItemData {
	UINT Size;
	UINT Position;
	VOID *Desc;
	UINT DescSize;
	UINT *Data;
	UINT DataSize;
	UINT Cookie;
} ImageItemData;

typedef struct PropertyItem {
	PROPID id;
	ULONG length;
	WORD type;
	VOID *value;
} PropertyItem;

#define PropertyTagGpsVer ((PROPID) 0x0000)
#define PropertyTagGpsLatitudeRef ((PROPID) 0x0001)
#define PropertyTagGpsLatitude ((PROPID) 0x0002)
#define PropertyTagGpsLongitudeRef ((PROPID) 0x0003)
#define PropertyTagGpsLongitude ((PROPID) 0x0004)
#define PropertyTagGpsAltitudeRef ((PROPID) 0x0005)
#define PropertyTagGpsAltitude ((PROPID) 0x0006)
#define PropertyTagGpsGpsTime ((PROPID) 0x0007)
#define PropertyTagGpsGpsSatellites ((PROPID) 0x0008)
#define PropertyTagGpsGpsStatus ((PROPID) 0x0009)
#define PropertyTagGpsGpsMeasureMode ((PROPID) 0x000A)
#define PropertyTagGpsGpsDop ((PROPID) 0x000B)
#define PropertyTagGpsSpeedRef ((PROPID) 0x000C)
#define PropertyTagGpsSpeed ((PROPID) 0x000D)
#define PropertyTagGpsTrackRef ((PROPID) 0x000E)
#define PropertyTagGpsTrack ((PROPID) 0x000F)
#define PropertyTagGpsImgDirRef ((PROPID) 0x0010)
#define PropertyTagGpsImgDir ((PROPID) 0x0011)
#define PropertyTagGpsMapDatum ((PROPID) 0x0012)
#define PropertyTagGpsDestLatRef ((PROPID) 0x0013)
#define PropertyTagGpsDestLat ((PROPID) 0x0014)
#define PropertyTagGpsDestLongRef ((PROPID) 0x0015)
#define PropertyTagGpsDestLong ((PROPID) 0x0016)
#define PropertyTagGpsDestBearRef ((PROPID) 0x0017)
#define PropertyTagGpsDestBear ((PROPID) 0x0018)
#define PropertyTagGpsDestDistRef ((PROPID) 0x0019)
#define PropertyTagGpsDestDist ((PROPID) 0x001A)
#define PropertyTagNewSubfileType ((PROPID) 0x00FE)
#define PropertyTagSubfileType ((PROPID) 0x00FF)
#define PropertyTagImageWidth ((PROPID) 0x0100)
#define PropertyTagImageHeight ((PROPID) 0x0101)
#define PropertyTagBitsPerSample ((PROPID) 0x0102)
#define PropertyTagCompression ((PROPID) 0x0103)
#define PropertyTagPhotometricInterp ((PROPID) 0x0106)
#define PropertyTagThreshHolding ((PROPID) 0x0107)
#define PropertyTagCellWidth ((PROPID) 0x0108)
#define PropertyTagCellHeight ((PROPID) 0x0109)
#define PropertyTagFillOrder ((PROPID) 0x010A)
#define PropertyTagDocumentName ((PROPID) 0x010D)
#define PropertyTagImageDescription ((PROPID) 0x010E)
#define PropertyTagEquipMake ((PROPID) 0x010F)
#define PropertyTagEquipModel ((PROPID) 0x0110)
#define PropertyTagStripOffsets ((PROPID) 0x0111)
#define PropertyTagOrientation ((PROPID) 0x0112)
#define PropertyTagSamplesPerPixel ((PROPID) 0x0115)
#define PropertyTagRowsPerStrip ((PROPID) 0x0116)
#define PropertyTagStripBytesCount ((PROPID) 0x0117)
#define PropertyTagMinSampleValue ((PROPID) 0x0118)
#define PropertyTagMaxSampleValue ((PROPID) 0x0119)
#define PropertyTagXResolution ((PROPID) 0x011A)
#define PropertyTagYResolution ((PROPID) 0x011B)
#define PropertyTagPlanarConfig ((PROPID) 0x011C)
#define PropertyTagPageName ((PROPID) 0x011D)
#define PropertyTagXPosition ((PROPID) 0x011E)
#define PropertyTagYPosition ((PROPID) 0x011F)
#define PropertyTagFreeOffset ((PROPID) 0x0120)
#define PropertyTagFreeByteCounts ((PROPID) 0x0121)
#define PropertyTagGrayResponseUnit ((PROPID) 0x0122)
#define PropertyTagGrayResponseCurve ((PROPID) 0x0123)
#define PropertyTagT4Option ((PROPID) 0x0124)
#define PropertyTagT6Option ((PROPID) 0x0125)
#define PropertyTagResolutionUnit ((PROPID) 0x0128)
#define PropertyTagPageNumber ((PROPID) 0x0129)
#define PropertyTagTransferFunction ((PROPID) 0x012D)
#define PropertyTagSoftwareUsed ((PROPID) 0x0131)
#define PropertyTagDateTime ((PROPID) 0x0132)
#define PropertyTagArtist ((PROPID) 0x013B)
#define PropertyTagHostComputer ((PROPID) 0x013C)
#define PropertyTagPredictor ((PROPID) 0x013D)
#define PropertyTagWhitePoint ((PROPID) 0x013E)
#define PropertyTagPrimaryChromaticities ((PROPID) 0x013F)
#define PropertyTagColorMap ((PROPID) 0x0140)
#define PropertyTagHalftoneHints ((PROPID) 0x0141)
#define PropertyTagTileWidth ((PROPID) 0x0142)
#define PropertyTagTileLength ((PROPID) 0x0143)
#define PropertyTagTileOffset ((PROPID) 0x0144)
#define PropertyTagTileByteCounts ((PROPID) 0x0145)
#define PropertyTagInkSet ((PROPID) 0x014C)
#define PropertyTagInkNames ((PROPID) 0x014D)
#define PropertyTagNumberOfInks ((PROPID) 0x014E)
#define PropertyTagDotRange ((PROPID) 0x0150)
#define PropertyTagTargetPrinter ((PROPID) 0x0151)
#define PropertyTagExtraSamples ((PROPID) 0x0152)
#define PropertyTagSampleFormat ((PROPID) 0x0153)
#define PropertyTagSMinSampleValue ((PROPID) 0x0154)
#define PropertyTagSMaxSampleValue ((PROPID) 0x0155)
#define PropertyTagTransferRange ((PROPID) 0x0156)
#define PropertyTagJPEGProc ((PROPID) 0x0200)
#define PropertyTagJPEGInterFormat ((PROPID) 0x0201)
#define PropertyTagJPEGInterLength ((PROPID) 0x0202)
#define PropertyTagJPEGRestartInterval ((PROPID) 0x0203)
#define PropertyTagJPEGLosslessPredictors ((PROPID) 0x0205)
#define PropertyTagJPEGPointTransforms ((PROPID) 0x0206)
#define PropertyTagJPEGQTables ((PROPID) 0x0207)
#define PropertyTagJPEGDCTables ((PROPID) 0x0208)
#define PropertyTagJPEGACTables ((PROPID) 0x0209)
#define PropertyTagYCbCrCoefficients ((PROPID) 0x0211)
#define PropertyTagYCbCrSubsampling ((PROPID) 0x0212)
#define PropertyTagYCbCrPositioning ((PROPID) 0x0213)
#define PropertyTagREFBlackWhite ((PROPID) 0x0214)
#define PropertyTagGamma ((PROPID) 0x0301)
#define PropertyTagICCProfileDescriptor ((PROPID) 0x0302)
#define PropertyTagSRGBRenderingIntent ((PROPID) 0x0303)
#define PropertyTagImageTitle ((PROPID) 0x0320)
#define PropertyTagResolutionXUnit ((PROPID) 0x5001)
#define PropertyTagResolutionYUnit ((PROPID) 0x5002)
#define PropertyTagResolutionXLengthUnit ((PROPID) 0x5003)
#define PropertyTagResolutionYLengthUnit ((PROPID) 0x5004)
#define PropertyTagPrintFlags ((PROPID) 0x5005)
#define PropertyTagPrintFlagsVersion ((PROPID) 0x5006)
#define PropertyTagPrintFlagsCrop ((PROPID) 0x5007)
#define PropertyTagPrintFlagsBleedWidth ((PROPID) 0x5008)
#define PropertyTagPrintFlagsBleedWidthScale ((PROPID) 0x5009)
#define PropertyTagHalftoneLPI ((PROPID) 0x500A)
#define PropertyTagHalftoneLPIUnit ((PROPID) 0x500B)
#define PropertyTagHalftoneDegree ((PROPID) 0x500C)
#define PropertyTagHalftoneShape ((PROPID) 0x500D)
#define PropertyTagHalftoneMisc ((PROPID) 0x500E)
#define PropertyTagHalftoneScreen ((PROPID) 0x500F)
#define PropertyTagJPEGQuality ((PROPID) 0x5010)
#define PropertyTagGridSize ((PROPID) 0x5011)
#define PropertyTagThumbnailFormat ((PROPID) 0x5012)
#define PropertyTagThumbnailWidth ((PROPID) 0x5013)
#define PropertyTagThumbnailHeight ((PROPID) 0x5014)
#define PropertyTagThumbnailColorDepth ((PROPID) 0x5015)
#define PropertyTagThumbnailPlanes ((PROPID) 0x5016)
#define PropertyTagThumbnailRawBytes ((PROPID) 0x5017)
#define PropertyTagThumbnailSize ((PROPID) 0x5018)
#define PropertyTagThumbnailCompressedSize ((PROPID) 0x5019)
#define PropertyTagColorTransferFunction ((PROPID) 0x501A)
#define PropertyTagThumbnailData ((PROPID) 0x501B)
#define PropertyTagThumbnailImageWidth ((PROPID) 0x5020)
#define PropertyTagThumbnailImageHeight ((PROPID) 0x5021)
#define PropertyTagThumbnailBitsPerSample ((PROPID) 0x5022)
#define PropertyTagThumbnailCompression ((PROPID) 0x5023)
#define PropertyTagThumbnailPhotometricInterp ((PROPID) 0x5024)
#define PropertyTagThumbnailImageDescription ((PROPID) 0x5025)
#define PropertyTagThumbnailEquipMake ((PROPID) 0x5026)
#define PropertyTagThumbnailEquipModel ((PROPID) 0x5027)
#define PropertyTagThumbnailStripOffsets ((PROPID) 0x5028)
#define PropertyTagThumbnailOrientation ((PROPID) 0x5029)
#define PropertyTagThumbnailSamplesPerPixel ((PROPID) 0x502A)
#define PropertyTagThumbnailRowsPerStrip ((PROPID) 0x502B)
#define PropertyTagThumbnailStripBytesCount ((PROPID) 0x502C)
#define PropertyTagThumbnailResolutionX ((PROPID) 0x502D)
#define PropertyTagThumbnailResolutionY ((PROPID) 0x502E)
#define PropertyTagThumbnailPlanarConfig ((PROPID) 0x502F)
#define PropertyTagThumbnailResolutionUnit ((PROPID) 0x5030)
#define PropertyTagThumbnailTransferFunction ((PROPID) 0x5031)
#define PropertyTagThumbnailSoftwareUsed ((PROPID) 0x5032)
#define PropertyTagThumbnailDateTime ((PROPID) 0x5033)
#define PropertyTagThumbnailArtist ((PROPID) 0x5034)
#define PropertyTagThumbnailWhitePoint ((PROPID) 0x5035)
#define PropertyTagThumbnailPrimaryChromaticities ((PROPID) 0x5036)
#define PropertyTagThumbnailYCbCrCoefficients ((PROPID) 0x5037)
#define PropertyTagThumbnailYCbCrSubsampling ((PROPID) 0x5038)
#define PropertyTagThumbnailYCbCrPositioning ((PROPID) 0x5039)
#define PropertyTagThumbnailRefBlackWhite ((PROPID) 0x503A)
#define PropertyTagThumbnailCopyRight ((PROPID) 0x503B)
#define PropertyTagLuminanceTable ((PROPID) 0x5090)
#define PropertyTagChrominanceTable ((PROPID) 0x5091)
#define PropertyTagFrameDelay ((PROPID) 0x5100)
#define PropertyTagLoopCount ((PROPID) 0x5101)
#define PropertyTagGlobalPalette ((PROPID) 0x5102)
#define PropertyTagIndexBackground ((PROPID) 0x5103)
#define PropertyTagIndexTransparent ((PROPID) 0x5104)
#define PropertyTagPixelUnit ((PROPID) 0x5110)
#define PropertyTagPixelPerUnitX ((PROPID) 0x5111)
#define PropertyTagPixelPerUnitY ((PROPID) 0x5112)
#define PropertyTagPaletteHistogram ((PROPID) 0x5113)
#define PropertyTagCopyright ((PROPID) 0x8298)
#define PropertyTagExifExposureTime ((PROPID) 0x829A)
#define PropertyTagExifFNumber ((PROPID) 0x829D)
#define PropertyTagExifIFD ((PROPID) 0x8769)
#define PropertyTagICCProfile ((PROPID) 0x8773)
#define PropertyTagExifExposureProg ((PROPID) 0x8822)
#define PropertyTagExifSpectralSense ((PROPID) 0x8824)
#define PropertyTagGpsIFD ((PROPID) 0x8825)
#define PropertyTagExifISOSpeed ((PROPID) 0x8827)
#define PropertyTagExifOECF ((PROPID) 0x8828)
#define PropertyTagExifVer ((PROPID) 0x9000)
#define PropertyTagExifDTOrig ((PROPID) 0x9003)
#define PropertyTagExifDTDigitized ((PROPID) 0x9004)
#define PropertyTagExifCompConfig ((PROPID) 0x9101)
#define PropertyTagExifCompBPP ((PROPID) 0x9102)
#define PropertyTagExifShutterSpeed ((PROPID) 0x9201)
#define PropertyTagExifAperture ((PROPID) 0x9202)
#define PropertyTagExifBrightness ((PROPID) 0x9203)
#define PropertyTagExifExposureBias ((PROPID) 0x9204)
#define PropertyTagExifMaxAperture ((PROPID) 0x9205)
#define PropertyTagExifSubjectDist ((PROPID) 0x9206)
#define PropertyTagExifMeteringMode ((PROPID) 0x9207)
#define PropertyTagExifLightSource ((PROPID) 0x9208)
#define PropertyTagExifFlash ((PROPID) 0x9209)
#define PropertyTagExifFocalLength ((PROPID) 0x920A)
#define PropertyTagExifMakerNote ((PROPID) 0x927C)
#define PropertyTagExifUserComment ((PROPID) 0x9286)
#define PropertyTagExifDTSubsec ((PROPID) 0x9290)
#define PropertyTagExifDTOrigSS ((PROPID) 0x9291)
#define PropertyTagExifDTDigSS ((PROPID) 0x9292)
#define PropertyTagExifFPXVer ((PROPID) 0xA000)
#define PropertyTagExifColorSpace ((PROPID) 0xA001)
#define PropertyTagExifPixXDim ((PROPID) 0xA002)
#define PropertyTagExifPixYDim ((PROPID) 0xA003)
#define PropertyTagExifRelatedWav ((PROPID) 0xA004)
#define PropertyTagExifInterop ((PROPID) 0xA005)
#define PropertyTagExifFlashEnergy ((PROPID) 0xA20B)
#define PropertyTagExifSpatialFR ((PROPID) 0xA20C)
#define PropertyTagExifFocalXRes ((PROPID) 0xA20E)
#define PropertyTagExifFocalYRes ((PROPID) 0xA20F)
#define PropertyTagExifFocalResUnit ((PROPID) 0xA210)
#define PropertyTagExifSubjectLoc ((PROPID) 0xA214)
#define PropertyTagExifExposureIndex ((PROPID) 0xA215)
#define PropertyTagExifSensingMethod ((PROPID) 0xA217)
#define PropertyTagExifFileSource ((PROPID) 0xA300)
#define PropertyTagExifSceneType ((PROPID) 0xA301)
#define PropertyTagExifCfaPattern ((PROPID) 0xA302)

#define PropertyTagTypeByte ((WORD) 1)
#define PropertyTagTypeASCII ((WORD) 2)
#define PropertyTagTypeShort ((WORD) 3)
#define PropertyTagTypeLong ((WORD) 4)
#define PropertyTagTypeRational ((WORD) 5)
#define PropertyTagTypeUndefined ((WORD) 7)
#define PropertyTagTypeSLONG ((WORD) 9)
#define PropertyTagTypeSRational ((WORD) 10)

extern const GUID EncoderChrominanceTable;   /* f2e455dc-09b3-4316-8260-676ada32481c */
extern const GUID EncoderColorDepth;         /* 66087055-ad66-4c7c-9a18-38a2310b8337 */
extern const GUID EncoderColorSpace;         /* ? */
extern const GUID EncoderCompression;        /* e09d739d-ccd4-44ee-8eba-3fbf8be4fc58 */
extern const GUID EncoderImageItems;         /* ? */
extern const GUID EncoderLuminanceTable;     /* edb33bce-0266-4a77-b904-27216099e717 */
extern const GUID EncoderQuality;            /* 1d5be4b5-fa4a-452d-9cdd-5db35105e7eb */
extern const GUID EncoderRenderMethod;       /* 6d42c53a-229a-4825-8bb7-5c99e2b9a8b8 */
extern const GUID EncoderSaveAsCMYK;         /* ? */
extern const GUID EncoderSaveFlag;           /* 292266fc-ac40-47bf-8cfc-a85b89a655de */
extern const GUID EncoderScanMethod;         /* 3a4e2661-3109-4e56-8536-42c156e7dcfa */
extern const GUID EncoderTransformation;     /* 8d0eb2d1-a58e-4ea8-aa14-108074b7b6f9 */
extern const GUID EncoderVersion;            /* 24d18c76-814a-41a4-bf53-1c219cccf797 */

extern const GUID ImageFormatBMP;            /* b96b3cab-0728-11d3-9d7b-0000f81ef32e */
extern const GUID ImageFormatEMF;            /* b96b3cac-0728-11d3-9d7b-0000f81ef32e */
extern const GUID ImageFormatEXIF;           /* ? */
extern const GUID ImageFormatGIF;            /* b96b3cb0-0728-11d3-9d7b-0000f81ef32e */
extern const GUID ImageFormatIcon;           /* b96b3cb5-0728-11d3-9d7b-0000f81ef32e */
extern const GUID ImageFormatJPEG;           /* b96b3cae-0728-11d3-9d7b-0000f81ef32e */
extern const GUID ImageFormatMemoryBMP;      /* b96b3caa-0728-11d3-9d7b-0000f81ef32e */
extern const GUID ImageFormatPNG;            /* b96b3caf-0728-11d3-9d7b-0000f81ef32e */
extern const GUID ImageFormatTIFF;           /* b96b3cb1-0728-11d3-9d7b-0000f81ef32e */
extern const GUID ImageFormatUndefined;      /* ? */
extern const GUID ImageFormatWMF;            /* b96b3cad-0728-11d3-9d7b-0000f81ef32e */

extern const GUID FrameDimensionPage;        /* 7462dc86-6180-4c7e-8e3f-ee7333a7a483 */
extern const GUID FrameDimensionResolution;  /* ? */
extern const GUID FrameDimensionTime;        /* 6aedbd6d-3fb5-418a-83a6-7f45229dc872 */

#endif /* __GDIPLUS_IMAGING_H */

// * gdiplusinit.h
#ifndef __GDIPLUS_INIT_H
#define __GDIPLUS_INIT_H

typedef struct GdiplusStartupInput {
	UINT32			GdiplusVersion;
	DebugEventProc	DebugEventCallback;
	BOOL			SuppressBackgroundThread;
	BOOL			SuppressExternalCodecs;
} GdiplusStartupInput;

typedef GpStatus (WINGDIPAPI * NotificationHookProc)(ULONG_PTR *token);
typedef VOID (WINGDIPAPI * NotificationUnhookProc)(ULONG_PTR token);

typedef struct GdiplusStartupOutput {
	NotificationHookProc NotificationHook;
	NotificationUnhookProc NotificationUnhook;
} GdiplusStartupOutput;

GpStatus WINGDIPAPI GdiplusStartup(ULONG_PTR*,GDIPCONST GdiplusStartupInput*,GdiplusStartupOutput*);
VOID WINGDIPAPI GdiplusShutdown(ULONG_PTR);
GpStatus WINGDIPAPI GdiplusNotificationHook(ULONG_PTR*);
VOID WINGDIPAPI GdiplusNotificationUnhook(ULONG_PTR);

#endif /* __GDIPLUS_INIT_H */

// * gdiplusmem.h
#ifndef __GDIPLUS_MEM_H
#define __GDIPLUS_MEM_H

VOID* WINGDIPAPI GdipAlloc(size_t);
VOID WINGDIPAPI GdipFree(VOID*);

#endif /* __GDIPLUS_MEM_H */

// * gdiplusmetaheader.h
#ifndef __GDIPLUS_METAHEADER_H
#define __GDIPLUS_METAHEADER_H

/*
 * FIXME: is 1 the correct value for GDIP_EMFPLUSFLAGS_DISPLAY? This number
 * has been determined by calling Metafile::GetMetafileHeader() on a EMF+
 * metafile which was recorded on a display device context (SampleMetafile.emf).
 */
#ifdef __cplusplus
const UINT GDIP_EMFPLUSFLAGS_DISPLAY = 1;
#else
#define GDIP_EMFPLUSFLAGS_DISPLAY ((UINT) 1)
#endif

typedef struct tagENHMETAHEADER3 {
	DWORD iType;
	DWORD nSize;
	RECTL rclBounds;
	RECTL rclFrame;
	DWORD dSignature;
	DWORD nVersion;
	DWORD nBytes;
	DWORD nRecords;
	WORD nHandles;
	WORD sReserved;
	DWORD nDescription;
	DWORD offDescription;
	DWORD nPalEntries;
	SIZEL szlDevice;
	SIZEL szlMillimeters;
} ENHMETAHEADER3,*LPENHMETAHEADER3;

typedef struct PWMFRect16 {
	INT16 Left;
	INT16 Top;
	INT16 Right;
	INT16 Bottom;
} PWMFRect16;

typedef struct WmfPlaceableFileHeader {
	UINT32 Key;
	INT16 Hmf;
	PWMFRect16 BoundingBox;
	INT16 Inch;
	UINT32 Reserved;
	INT16 Checksum;
} WmfPlaceableFileHeader;

typedef struct MetafileHeader {
	MetafileType Type;
	UINT Size;
	UINT Version;
	UINT EmfPlusFlags;
	REAL DpiX;
	REAL DpiY;
	INT X;
	INT Y;
	INT Width;
	INT Height;
	union hdr {
		METAHEADER WmfHeader;
		ENHMETAHEADER3 EmfHeader;
	} hdr;
	INT EmfPlusHeaderSize;
	INT LogicalDpiX;
	INT LogicalDpiY;
} MetafileHeader;

#endif /* __GDIPLUS_METAHEADER_H */

// * gdipluspixelformats.h
#ifndef __GDIPLUS_PIXELFORMATS_H
#define __GDIPLUS_PIXELFORMATS_H

typedef DWORD ARGB;
typedef INT PixelFormat;

#define PixelFormatIndexed ((INT) 0x00010000)
#define PixelFormatGDI ((INT) 0x00020000)
#define PixelFormatAlpha ((INT) 0x00040000)
#define PixelFormatPAlpha ((INT) 0x00080000)
#define PixelFormatExtended ((INT) 0x00100000)
#define PixelFormatCanonical ((INT) 0x00200000)
#define PixelFormatUndefined ((INT) 0)
#define PixelFormatDontCare ((INT) 0)
#define PixelFormat1bppIndexed ((INT) \
	(1 | (1<<8) | PixelFormatIndexed | PixelFormatGDI))
#define PixelFormat4bppIndexed ((INT) \
	(2 | (4<<8) | PixelFormatIndexed | PixelFormatGDI))
#define PixelFormat8bppIndexed ((INT) \
	(3 | (8<<8) | PixelFormatIndexed | PixelFormatGDI))
#define PixelFormat16bppGrayScale ((INT) \
	(4 | (16<<8) | PixelFormatExtended))
#define PixelFormat16bppRGB555 ((INT) \
	(5 | (16<<8) | PixelFormatGDI))
#define PixelFormat16bppRGB565 ((INT) \
	(6 | (16<<8) | PixelFormatGDI))
#define PixelFormat16bppARGB1555 ((INT) \
	(7 | (16<<8) | PixelFormatAlpha | PixelFormatGDI))
#define PixelFormat24bppRGB ((INT) \
	(8 | (24<<8) | PixelFormatGDI))
#define PixelFormat32bppRGB ((INT) \
	(9 | (32<<8) | PixelFormatGDI))
#define PixelFormat32bppARGB ((INT) \
	(10 | (32<<8) | PixelFormatAlpha | PixelFormatGDI | PixelFormatCanonical))
#define PixelFormat32bppPARGB ((INT) \
	(11 | (32<<8) | PixelFormatAlpha | PixelFormatPAlpha | PixelFormatGDI))
#define PixelFormat48bppRGB ((INT) \
	(12 | (48<<8) | PixelFormatExtended))
#define PixelFormat64bppARGB ((INT) \
	(13 | (64<<8) | PixelFormatAlpha | PixelFormatCanonical | PixelFormatExtended))
#define PixelFormat64bppPARGB ((INT) \
	(14 | (64<<8) | PixelFormatAlpha | PixelFormatPAlpha | PixelFormatExtended))
#define PixelFormatMax ((INT) 15)

typedef enum PaletteFlags {
	PaletteFlagsHasAlpha = 1,
	PaletteFlagsGrayScale = 2,
	PaletteFlagsHalftone = 4
} PaletteFlags;

typedef enum PaletteType {
	PaletteTypeCustom = 0,
	PaletteTypeOptimal = 1,
	PaletteTypeFixedBW = 2,
	PaletteTypeFixedHalftone8 = 3,
	PaletteTypeFixedHalftone27 = 4,
	PaletteTypeFixedHalftone64 = 5,
	PaletteTypeFixedHalftone125 = 6,
	PaletteTypeFixedHalftone216 = 7,
	PaletteTypeFixedHalftone252 = 8,
	PaletteTypeFixedHalftone256 = 9 
} PaletteType;

typedef struct ColorPalette {
	UINT Flags;
	UINT Count;
	ARGB Entries[1];
} ColorPalette;

#define GetPixelFormatSize(pixfmt)		(UINT)((((UINT) pixfmt) & 0xff00U) >> 8)
#define IsAlphaPixelFormat(pixfmt)		(BOOL)((pixfmt & PixelFormatAlpha) != 0)
#define IsCanonicalPixelFormat(pixfmt)	(BOOL)((pixfmt & PixelFormatCanonical) != 0)
#define IsExtendedPixelFormat(pixfmt)	(BOOL)((pixfmt & PixelFormatExtended) != 0)
#define IsIndexedPixelFormat(pixfmt)	(BOOL)((pixfmt & PixelFormatIndexed) != 0)

#endif /* __GDIPLUS_PIXELFORMATS_H */

// * gdipluscolor.h
#ifndef __GDIPLUS_COLOR_H
#define __GDIPLUS_COLOR_H

typedef enum ColorChannelFlags {
	ColorChannelFlagsC = 0,
	ColorChannelFlagsM = 1,
	ColorChannelFlagsY = 2,
	ColorChannelFlagsK = 3,
	ColorChannelFlagsLast = 4
} ColorChannelFlags;

#define MAKEARGB(a, r, g, b)	(ARGB)((((DWORD)a) << 24) | (((DWORD)r) << 16) | (((DWORD)g) << 8) | ((DWORD)b))
#define RGB2ARGB(a, c)			(ARGB)((((DWORD)a) << 24) | ((c & 0x000000FF) << 16) | (c & 0x0000FF00) | ((c & 0x00FF0000) >> 16))
#define ARGBSETALPHA(c, a)		(ARGB)((DWORD)(c & 0x00FFFFFF) | (((DWORD)a) << 24))

#define ARGBGETA(c)				(BYTE)((c & 0xFF000000) >> 24)
#define ARGBGETB(c)				(BYTE)(c & 0x000000FF)
#define ARGBGETG(c)				(BYTE)((c & 0x0000FF00) >> 8)
#define ARGBGETR(c)				(BYTE)((c & 0x00FF0000) >> 16)

_inline ARGB APIENTRY ARGBModifyAlpha(ARGB Col, int iKey) {
	ARGB Clean = Col & 0x00FFFFFF;
	int iAlpha = ((Col & 0xFF000000) >> 24);
	iAlpha += iKey;
	if (iAlpha > 255) iAlpha = 255;
	if (iAlpha < 0) iAlpha = 0;
	return (Clean | (((DWORD)iAlpha) << 24));
}

#ifndef __cplusplus
enum tagGdipColors {
	AliceBlue = 0xFFF0F8FF,
	AntiqueWhite = 0xFFFAEBD7,
	Aqua = 0xFF00FFFF,
	Aquamarine = 0xFF7FFFD4,
	Azure = 0xFFF0FFFF,
	Beige = 0xFFF5F5DC,
	Bisque = 0xFFFFE4C4,
	Black = 0xFF000000,
	BlanchedAlmond = 0xFFFFEBCD,
	Blue = 0xFF0000FF,
	BlueViolet = 0xFF8A2BE2,
	Brown = 0xFFA52A2A,
	BurlyWood = 0xFFDEB887,
	CadetBlue = 0xFF5F9EA0,
	Chartreuse = 0xFF7FFF00,
	Chocolate = 0xFFD2691E,
	Coral = 0xFFFF7F50,
	CornflowerBlue = 0xFF6495ED,
	Cornsilk = 0xFFFFF8DC,
	Crimson = 0xFFDC143C,
	Cyan = 0xFF00FFFF,
	DarkBlue = 0xFF00008B,
	DarkCyan = 0xFF008B8B,
	DarkGoldenrod = 0xFFB8860B,
	DarkGray = 0xFFA9A9A9,
	DarkGreen = 0xFF006400,
	DarkKhaki = 0xFFBDB76B,
	DarkMagenta = 0xFF8B008B,
	DarkOliveGreen = 0xFF556B2F,
	DarkOrange = 0xFFFF8C00,
	DarkOrchid = 0xFF9932CC,
	DarkRed = 0xFF8B0000,
	DarkSalmon = 0xFFE9967A,
	DarkSeaGreen = 0xFF8FBC8F,
	DarkSlateBlue = 0xFF483D8B,
	DarkSlateGray = 0xFF2F4F4F,
	DarkTurquoise = 0xFF00CED1,
	DarkViolet = 0xFF9400D3,
	DeepPink = 0xFFFF1493,
	DeepSkyBlue = 0xFF00BFFF,
	DimGray = 0xFF696969,
	DodgerBlue = 0xFF1E90FF,
	Firebrick = 0xFFB22222,
	FloralWhite = 0xFFFFFAF0,
	ForestGreen = 0xFF228B22,
	Fuchsia = 0xFFFF00FF,
	Gainsboro = 0xFFDCDCDC,
	GhostWhite = 0xFFF8F8FF,
	Gold = 0xFFFFD700,
	Goldenrod = 0xFFDAA520,
	Gray = 0xFF808080,
	Green = 0xFF008000,
	GreenYellow = 0xFFADFF2F,
	Honeydew = 0xFFF0FFF0,
	HotPink = 0xFFFF69B4,
	IndianRed = 0xFFCD5C5C,
	Indigo = 0xFF4B0082,
	Ivory = 0xFFFFFFF0,
	Khaki = 0xFFF0E68C,
	Lavender = 0xFFE6E6FA,
	LavenderBlush = 0xFFFFF0F5,
	LawnGreen = 0xFF7CFC00,
	LemonChiffon = 0xFFFFFACD,
	LightBlue = 0xFFADD8E6,
	LightCoral = 0xFFF08080,
	LightCyan = 0xFFE0FFFF,
	LightGoldenrodYellow = 0xFFFAFAD2,
	LightGray = 0xFFD3D3D3,
	LightGreen = 0xFF90EE90,
	LightPink = 0xFFFFB6C1,
	LightSalmon = 0xFFFFA07A,
	LightSeaGreen = 0xFF20B2AA,
	LightSkyBlue = 0xFF87CEFA,
	LightSlateGray = 0xFF778899,
	LightSteelBlue = 0xFFB0C4DE,
	LightYellow = 0xFFFFFFE0,
	Lime = 0xFF00FF00,
	LimeGreen = 0xFF32CD32,
	Linen = 0xFFFAF0E6,
	Magenta = 0xFFFF00FF,
	Maroon = 0xFF800000,
	MediumAquamarine = 0xFF66CDAA,
	MediumBlue = 0xFF0000CD,
	MediumOrchid = 0xFFBA55D3,
	MediumPurple = 0xFF9370DB,
	MediumSeaGreen = 0xFF3CB371,
	MediumSlateBlue = 0xFF7B68EE,
	MediumSpringGreen = 0xFF00FA9A,
	MediumTurquoise = 0xFF48D1CC,
	MediumVioletRed = 0xFFC71585,
	MidnightBlue = 0xFF191970,
	MintCream = 0xFFF5FFFA,
	MistyRose = 0xFFFFE4E1,
	Moccasin = 0xFFFFE4B5,
	NavajoWhite = 0xFFFFDEAD,
	Navy = 0xFF000080,
	OldLace = 0xFFFDF5E6,
	Olive = 0xFF808000,
	OliveDrab = 0xFF6B8E23,
	Orange = 0xFFFFA500,
	OrangeRed = 0xFFFF4500,
	Orchid = 0xFFDA70D6,
	PaleGoldenrod = 0xFFEEE8AA,
	PaleGreen = 0xFF98FB98,
	PaleTurquoise = 0xFFAFEEEE,
	PaleVioletRed = 0xFFDB7093,
	PapayaWhip = 0xFFFFEFD5,
	PeachPuff = 0xFFFFDAB9,
	Peru = 0xFFCD853F,
	Pink = 0xFFFFC0CB,
	Plum = 0xFFDDA0DD,
	PowderBlue = 0xFFB0E0E6,
	Purple = 0xFF800080,
	Red = 0xFFFF0000,
	RosyBrown = 0xFFBC8F8F,
	RoyalBlue = 0xFF4169E1,
	SaddleBrown = 0xFF8B4513,
	Salmon = 0xFFFA8072,
	SandyBrown = 0xFFF4A460,
	SeaGreen = 0xFF2E8B57,
	SeaShell = 0xFFFFF5EE,
	Sienna = 0xFFA0522D,
	Silver = 0xFFC0C0C0,
	SkyBlue = 0xFF87CEEB,
	SlateBlue = 0xFF6A5ACD,
	SlateGray = 0xFF708090,
	Snow = 0xFFFFFAFA,
	SpringGreen = 0xFF00FF7F,
	SteelBlue = 0xFF4682B4,
	Tan = 0xFFD2B48C,
	Teal = 0xFF008080,
	Thistle = 0xFFD8BFD8,
	Tomato = 0xFFFF6347,
	Transparent = 0x00FFFFFF,
	Turquoise = 0xFF40E0D0,
	Violet = 0xFFEE82EE,
	Wheat = 0xFFF5DEB3,
	White = 0xFFFFFFFF,
	WhiteSmoke = 0xFFF5F5F5,
	Yellow = 0xFFFFFF00,
	YellowGreen = 0xFF9ACD32,
} GdipColors;

#endif /* NOT __cplusplus */

typedef struct Color
{
	ARGB Value;

	#ifdef __cplusplus
	public:
	friend class Bitmap;
	friend class Graphics;
	friend class HatchBrush;
	friend class PathGradientBrush;
	friend class Pen;
	friend class SolidBrush;

	static ARGB MakeARGB(BYTE a, BYTE r, BYTE g, BYTE b)
	{
		return (ARGB) ((((DWORD) a) << 24) | (((DWORD) r) << 16)
		             | (((DWORD) g) << 8) | ((DWORD) b));
	}

	static const ARGB AlphaMask            = 0xFF000000;

	static const ARGB AliceBlue            = 0xFFF0F8FF;
	static const ARGB AntiqueWhite         = 0xFFFAEBD7;
	static const ARGB Aqua                 = 0xFF00FFFF;
	static const ARGB Aquamarine           = 0xFF7FFFD4;
	static const ARGB Azure                = 0xFFF0FFFF;
	static const ARGB Beige                = 0xFFF5F5DC;
	static const ARGB Bisque               = 0xFFFFE4C4;
	static const ARGB Black                = 0xFF000000;
	static const ARGB BlanchedAlmond       = 0xFFFFEBCD;
	static const ARGB Blue                 = 0xFF0000FF;
	static const ARGB BlueViolet           = 0xFF8A2BE2;
	static const ARGB Brown                = 0xFFA52A2A;
	static const ARGB BurlyWood            = 0xFFDEB887;
	static const ARGB CadetBlue            = 0xFF5F9EA0;
	static const ARGB Chartreuse           = 0xFF7FFF00;
	static const ARGB Chocolate            = 0xFFD2691E;
	static const ARGB Coral                = 0xFFFF7F50;
	static const ARGB CornflowerBlue       = 0xFF6495ED;
	static const ARGB Cornsilk             = 0xFFFFF8DC;
	static const ARGB Crimson              = 0xFFDC143C;
	static const ARGB Cyan                 = 0xFF00FFFF;
	static const ARGB DarkBlue             = 0xFF00008B;
	static const ARGB DarkCyan             = 0xFF008B8B;
	static const ARGB DarkGoldenrod        = 0xFFB8860B;
	static const ARGB DarkGray             = 0xFFA9A9A9;
	static const ARGB DarkGreen            = 0xFF006400;
	static const ARGB DarkKhaki            = 0xFFBDB76B;
	static const ARGB DarkMagenta          = 0xFF8B008B;
	static const ARGB DarkOliveGreen       = 0xFF556B2F;
	static const ARGB DarkOrange           = 0xFFFF8C00;
	static const ARGB DarkOrchid           = 0xFF9932CC;
	static const ARGB DarkRed              = 0xFF8B0000;
	static const ARGB DarkSalmon           = 0xFFE9967A;
	static const ARGB DarkSeaGreen         = 0xFF8FBC8F;
	static const ARGB DarkSlateBlue        = 0xFF483D8B;
	static const ARGB DarkSlateGray        = 0xFF2F4F4F;
	static const ARGB DarkTurquoise        = 0xFF00CED1;
	static const ARGB DarkViolet           = 0xFF9400D3;
	static const ARGB DeepPink             = 0xFFFF1493;
	static const ARGB DeepSkyBlue          = 0xFF00BFFF;
	static const ARGB DimGray              = 0xFF696969;
	static const ARGB DodgerBlue           = 0xFF1E90FF;
	static const ARGB Firebrick            = 0xFFB22222;
	static const ARGB FloralWhite          = 0xFFFFFAF0;
	static const ARGB ForestGreen          = 0xFF228B22;
	static const ARGB Fuchsia              = 0xFFFF00FF;
	static const ARGB Gainsboro            = 0xFFDCDCDC;
	static const ARGB GhostWhite           = 0xFFF8F8FF;
	static const ARGB Gold                 = 0xFFFFD700;
	static const ARGB Goldenrod            = 0xFFDAA520;
	static const ARGB Gray                 = 0xFF808080;
	static const ARGB Green                = 0xFF008000;
	static const ARGB GreenYellow          = 0xFFADFF2F;
	static const ARGB Honeydew             = 0xFFF0FFF0;
	static const ARGB HotPink              = 0xFFFF69B4;
	static const ARGB IndianRed            = 0xFFCD5C5C;
	static const ARGB Indigo               = 0xFF4B0082;
	static const ARGB Ivory                = 0xFFFFFFF0;
	static const ARGB Khaki                = 0xFFF0E68C;
	static const ARGB Lavender             = 0xFFE6E6FA;
	static const ARGB LavenderBlush        = 0xFFFFF0F5;
	static const ARGB LawnGreen            = 0xFF7CFC00;
	static const ARGB LemonChiffon         = 0xFFFFFACD;
	static const ARGB LightBlue            = 0xFFADD8E6;
	static const ARGB LightCoral           = 0xFFF08080;
	static const ARGB LightCyan            = 0xFFE0FFFF;
	static const ARGB LightGoldenrodYellow = 0xFFFAFAD2;
	static const ARGB LightGray            = 0xFFD3D3D3;
	static const ARGB LightGreen           = 0xFF90EE90;
	static const ARGB LightPink            = 0xFFFFB6C1;
	static const ARGB LightSalmon          = 0xFFFFA07A;
	static const ARGB LightSeaGreen        = 0xFF20B2AA;
	static const ARGB LightSkyBlue         = 0xFF87CEFA;
	static const ARGB LightSlateGray       = 0xFF778899;
	static const ARGB LightSteelBlue       = 0xFFB0C4DE;
	static const ARGB LightYellow          = 0xFFFFFFE0;
	static const ARGB Lime                 = 0xFF00FF00;
	static const ARGB LimeGreen            = 0xFF32CD32;
	static const ARGB Linen                = 0xFFFAF0E6;
	static const ARGB Magenta              = 0xFFFF00FF;
	static const ARGB Maroon               = 0xFF800000;
	static const ARGB MediumAquamarine     = 0xFF66CDAA;
	static const ARGB MediumBlue           = 0xFF0000CD;
	static const ARGB MediumOrchid         = 0xFFBA55D3;
	static const ARGB MediumPurple         = 0xFF9370DB;
	static const ARGB MediumSeaGreen       = 0xFF3CB371;
	static const ARGB MediumSlateBlue      = 0xFF7B68EE;
	static const ARGB MediumSpringGreen    = 0xFF00FA9A;
	static const ARGB MediumTurquoise      = 0xFF48D1CC;
	static const ARGB MediumVioletRed      = 0xFFC71585;
	static const ARGB MidnightBlue         = 0xFF191970;
	static const ARGB MintCream            = 0xFFF5FFFA;
	static const ARGB MistyRose            = 0xFFFFE4E1;
	static const ARGB Moccasin             = 0xFFFFE4B5;
	static const ARGB NavajoWhite          = 0xFFFFDEAD;
	static const ARGB Navy                 = 0xFF000080;
	static const ARGB OldLace              = 0xFFFDF5E6;
	static const ARGB Olive                = 0xFF808000;
	static const ARGB OliveDrab            = 0xFF6B8E23;
	static const ARGB Orange               = 0xFFFFA500;
	static const ARGB OrangeRed            = 0xFFFF4500;
	static const ARGB Orchid               = 0xFFDA70D6;
	static const ARGB PaleGoldenrod        = 0xFFEEE8AA;
	static const ARGB PaleGreen            = 0xFF98FB98;
	static const ARGB PaleTurquoise        = 0xFFAFEEEE;
	static const ARGB PaleVioletRed        = 0xFFDB7093;
	static const ARGB PapayaWhip           = 0xFFFFEFD5;
	static const ARGB PeachPuff            = 0xFFFFDAB9;
	static const ARGB Peru                 = 0xFFCD853F;
	static const ARGB Pink                 = 0xFFFFC0CB;
	static const ARGB Plum                 = 0xFFDDA0DD;
	static const ARGB PowderBlue           = 0xFFB0E0E6;
	static const ARGB Purple               = 0xFF800080;
	static const ARGB Red                  = 0xFFFF0000;
	static const ARGB RosyBrown            = 0xFFBC8F8F;
	static const ARGB RoyalBlue            = 0xFF4169E1;
	static const ARGB SaddleBrown          = 0xFF8B4513;
	static const ARGB Salmon               = 0xFFFA8072;
	static const ARGB SandyBrown           = 0xFFF4A460;
	static const ARGB SeaGreen             = 0xFF2E8B57;
	static const ARGB SeaShell             = 0xFFFFF5EE;
	static const ARGB Sienna               = 0xFFA0522D;
	static const ARGB Silver               = 0xFFC0C0C0;
	static const ARGB SkyBlue              = 0xFF87CEEB;
	static const ARGB SlateBlue            = 0xFF6A5ACD;
	static const ARGB SlateGray            = 0xFF708090;
	static const ARGB Snow                 = 0xFFFFFAFA;
	static const ARGB SpringGreen          = 0xFF00FF7F;
	static const ARGB SteelBlue            = 0xFF4682B4;
	static const ARGB Tan                  = 0xFFD2B48C;
	static const ARGB Teal                 = 0xFF008080;
	static const ARGB Thistle              = 0xFFD8BFD8;
	static const ARGB Tomato               = 0xFFFF6347;
	static const ARGB Transparent          = 0x00FFFFFF;
	static const ARGB Turquoise            = 0xFF40E0D0;
	static const ARGB Violet               = 0xFFEE82EE;
	static const ARGB Wheat                = 0xFFF5DEB3;
	static const ARGB White                = 0xFFFFFFFF;
	static const ARGB WhiteSmoke           = 0xFFF5F5F5;
	static const ARGB Yellow               = 0xFFFFFF00;
	static const ARGB YellowGreen          = 0xFF9ACD32;

	Color(): Value(0xFF000000) {}
	Color(ARGB argb): Value(argb) {}
	Color(BYTE r, BYTE g, BYTE b): Value(MakeARGB(0xFF, r, g, b)) {}
	Color(BYTE a, BYTE r, BYTE g, BYTE b): Value(MakeARGB(a, r, g, b)) {}

	BYTE GetA() const
	{
		return (BYTE) (Value >> 24);
	}
	BYTE GetAlpha() const
	{
		return (BYTE) (Value >> 24);
	}
	BYTE GetB() const
	{
		return (BYTE) Value;
	}
	BYTE GetBlue() const
	{
		return (BYTE) Value;
	}
	BYTE GetG() const
	{
		return (BYTE) (Value >> 8);
	}
	BYTE GetGreen() const
	{
		return (BYTE) (Value >> 8);
	}
	BYTE GetR() const
	{
		return (BYTE) (Value >> 16);
	}
	BYTE GetRed() const
	{
		return (BYTE) (Value >> 16);
	}
	ARGB GetValue() const
	{
		return Value;
	}
	VOID SetFromCOLORREF(COLORREF rgb)
	{
		BYTE r = (BYTE) rgb;
		BYTE g = (BYTE) (rgb >> 8);
		BYTE b = (BYTE) (rgb >> 16);
		Value = MakeARGB(0xFF, r, g, b);
	}
	VOID SetValue(ARGB argb)
	{
		Value = argb;
	}
	COLORREF ToCOLORREF() const
	{
		return RGB(GetRed(), GetGreen(), GetBlue());
	}
	#endif /* __cplusplus */
} Color;

#endif /* __GDIPLUS_COLOR_H */

// * gdipluscolormatrix.h
#ifndef __GDIPLUS_COLORMATRIX_H
#define __GDIPLUS_COLORMATRIX_H
#if __GNUC__ >=3
#pragma GCC system_header
#endif

typedef enum ColorAdjustType {
	ColorAdjustTypeDefault = 0,
	ColorAdjustTypeBitmap = 1,
	ColorAdjustTypeBrush = 2,
	ColorAdjustTypePen = 3,
	ColorAdjustTypeText = 4,
	ColorAdjustTypeCount = 5,
	ColorAdjustTypeAny = 6
} ColorAdjustType;

typedef enum ColorMatrixFlags {
	ColorMatrixFlagsDefault = 0,
	ColorMatrixFlagsSkipGrays = 1,
	ColorMatrixFlagsAltGray = 2
} ColorMatrixFlags;

typedef enum HistogramFormat {
	HistogramFormatARGB = 0,
	HistogramFormatPARGB = 1,
	HistogramFormatRGB = 2,
	HistogramFormatGray = 3,
	HistogramFormatB = 4,
	HistogramFormatG = 5,
	HistogramFormatR = 6,
	HistogramFormatA = 7
} HistogramFormat;

typedef struct ColorMap {
	Color oldColor;
	Color newColor;
} ColorMap;

typedef struct ColorMatrix {
	REAL m[5][5];
} ColorMatrix;

typedef BYTE ColorChannelLUT[256];

#endif /* __GDIPLUS_COLORMATRIX_H */

// * gdiplusflat.h
#ifndef __GDIPLUS_FLAT_H
#define __GDIPLUS_FLAT_H

/* AdjustableArrowCap functions */
GpStatus WINGDIPAPI GdipCreateAdjustableArrowCap(REAL,REAL,BOOL,GpAdjustableArrowCap**);
GpStatus WINGDIPAPI GdipSetAdjustableArrowCapHeight(GpAdjustableArrowCap*,REAL);
GpStatus WINGDIPAPI GdipGetAdjustableArrowCapHeight(GpAdjustableArrowCap*,REAL*);
GpStatus WINGDIPAPI GdipSetAdjustableArrowCapWidth(GpAdjustableArrowCap*,REAL);
GpStatus WINGDIPAPI GdipGetAdjustableArrowCapWidth(GpAdjustableArrowCap*,REAL*);
GpStatus WINGDIPAPI GdipSetAdjustableArrowCapMiddleInset(GpAdjustableArrowCap*,REAL);
GpStatus WINGDIPAPI GdipGetAdjustableArrowCapMiddleInset(GpAdjustableArrowCap*,REAL*);
GpStatus WINGDIPAPI GdipSetAdjustableArrowCapFillState(GpAdjustableArrowCap*,BOOL);
GpStatus WINGDIPAPI GdipGetAdjustableArrowCapFillState(GpAdjustableArrowCap*,BOOL*);

/* Bitmap functions */
GpStatus WINGDIPAPI GdipCreateBitmapFromStream(IStream*,GpBitmap**);
GpStatus WINGDIPAPI GdipCreateBitmapFromFile(GDIPCONST WCHAR*,GpBitmap**);
GpStatus WINGDIPAPI GdipCreateBitmapFromStreamICM(IStream*,GpBitmap**);
GpStatus WINGDIPAPI GdipCreateBitmapFromFileICM(GDIPCONST WCHAR*,GpBitmap**);
GpStatus WINGDIPAPI GdipCreateBitmapFromScan0(INT,INT,INT,PixelFormat,BYTE*,GpBitmap**);
GpStatus WINGDIPAPI GdipCreateBitmapFromGraphics(INT,INT,GpGraphics*,GpBitmap**);
GpStatus WINGDIPAPI GdipCreateBitmapFromDirectDrawSurface(IDirectDrawSurface7*,GpBitmap**);
GpStatus WINGDIPAPI GdipCreateBitmapFromGdiDib(GDIPCONST BITMAPINFO*,VOID*,GpBitmap**);
GpStatus WINGDIPAPI GdipCreateBitmapFromHBITMAP(HBITMAP,HPALETTE,GpBitmap**);
GpStatus WINGDIPAPI GdipCreateHBITMAPFromBitmap(GpBitmap*,HBITMAP*,ARGB);
GpStatus WINGDIPAPI GdipCreateBitmapFromHICON(HICON,GpBitmap**);
GpStatus WINGDIPAPI GdipCreateHICONFromBitmap(GpBitmap*,HICON*);
GpStatus WINGDIPAPI GdipCreateBitmapFromResource(HINSTANCE,GDIPCONST WCHAR*,GpBitmap**);
GpStatus WINGDIPAPI GdipCloneBitmapArea(REAL,REAL,REAL,REAL,PixelFormat,GpBitmap*,GpBitmap**);
GpStatus WINGDIPAPI GdipCloneBitmapAreaI(INT,INT,INT,INT,PixelFormat,GpBitmap*,GpBitmap**);
GpStatus WINGDIPAPI GdipBitmapLockBits(GpBitmap*,GDIPCONST GpRect*,UINT,PixelFormat,BitmapData*);
GpStatus WINGDIPAPI GdipBitmapUnlockBits(GpBitmap*,BitmapData*);
GpStatus WINGDIPAPI GdipBitmapGetPixel(GpBitmap*,INT,INT,ARGB*);
GpStatus WINGDIPAPI GdipBitmapSetPixel(GpBitmap*,INT,INT,ARGB);
GpStatus WINGDIPAPI GdipBitmapSetResolution(GpBitmap*,REAL,REAL);
GpStatus WINGDIPAPI GdipBitmapConvertFormat(GpBitmap*,PixelFormat,DitherType,PaletteType,ColorPalette*,REAL);
GpStatus WINGDIPAPI GdipInitializePalette(ColorPalette*,PaletteType,INT,BOOL,GpBitmap*);
GpStatus WINGDIPAPI GdipBitmapApplyEffect(GpBitmap*,CGpEffect*,RECT*,BOOL,VOID**,INT*);
GpStatus WINGDIPAPI GdipBitmapCreateApplyEffect(GpBitmap**,INT,CGpEffect*,RECT*,RECT*,GpBitmap**,BOOL,VOID**,INT*);
GpStatus WINGDIPAPI GdipBitmapGetHistogram(GpBitmap*,HistogramFormat,UINT,UINT*,UINT*,UINT*,UINT*);
GpStatus WINGDIPAPI GdipBitmapGetHistogramSize(HistogramFormat,UINT*);

/* Brush functions */
GpStatus WINGDIPAPI GdipCloneBrush(GpBrush*,GpBrush**);
GpStatus WINGDIPAPI GdipDeleteBrush(GpBrush*);
GpStatus WINGDIPAPI GdipGetBrushType(GpBrush*,GpBrushType*);

/* CachedBitmap functions */
GpStatus WINGDIPAPI GdipCreateCachedBitmap(GpBitmap*,GpGraphics*,GpCachedBitmap**);
GpStatus WINGDIPAPI GdipDeleteCachedBitmap(GpCachedBitmap*);
GpStatus WINGDIPAPI GdipDrawCachedBitmap(GpGraphics*,GpCachedBitmap*,INT,INT);

/* CustomLineCap functions */
GpStatus WINGDIPAPI GdipCreateCustomLineCap(GpPath*,GpPath*,GpLineCap,REAL,GpCustomLineCap**);
GpStatus WINGDIPAPI GdipDeleteCustomLineCap(GpCustomLineCap*);
GpStatus WINGDIPAPI GdipCloneCustomLineCap(GpCustomLineCap*,GpCustomLineCap**);
GpStatus WINGDIPAPI GdipGetCustomLineCapType(GpCustomLineCap*,CustomLineCapType*);
GpStatus WINGDIPAPI GdipSetCustomLineCapStrokeCaps(GpCustomLineCap*,GpLineCap,GpLineCap);
GpStatus WINGDIPAPI GdipGetCustomLineCapStrokeCaps(GpCustomLineCap*,GpLineCap*,GpLineCap*);
GpStatus WINGDIPAPI GdipSetCustomLineCapStrokeJoin(GpCustomLineCap*,GpLineJoin);
GpStatus WINGDIPAPI GdipGetCustomLineCapStrokeJoin(GpCustomLineCap*,GpLineJoin*);
GpStatus WINGDIPAPI GdipSetCustomLineCapBaseCap(GpCustomLineCap*,GpLineCap);
GpStatus WINGDIPAPI GdipGetCustomLineCapBaseCap(GpCustomLineCap*,GpLineCap*);
GpStatus WINGDIPAPI GdipSetCustomLineCapBaseInset(GpCustomLineCap*,REAL);
GpStatus WINGDIPAPI GdipGetCustomLineCapBaseInset(GpCustomLineCap*,REAL*);
GpStatus WINGDIPAPI GdipSetCustomLineCapWidthScale(GpCustomLineCap*,REAL);
GpStatus WINGDIPAPI GdipGetCustomLineCapWidthScale(GpCustomLineCap*,REAL*);

/* Effect functions */
GpStatus WINGDIPAPI GdipCreateEffect(GDIPCONST GUID,CGpEffect**);
GpStatus WINGDIPAPI GdipDeleteEffect(CGpEffect*);
GpStatus WINGDIPAPI GdipGetEffectParameterSize(CGpEffect*,UINT*);
GpStatus WINGDIPAPI GdipSetEffectParameters(CGpEffect*,GDIPCONST VOID*,UINT);
GpStatus WINGDIPAPI GdipGetEffectParameters(CGpEffect*,UINT*,VOID*);

/* Font functions */
GpStatus WINGDIPAPI GdipCreateFontFromDC(HDC,GpFont**);
GpStatus WINGDIPAPI GdipCreateFontFromLogfontA(HDC,GDIPCONST LOGFONTA*,GpFont**);
GpStatus WINGDIPAPI GdipCreateFontFromLogfontW(HDC,GDIPCONST LOGFONTW*,GpFont**);
GpStatus WINGDIPAPI GdipCreateFont(GDIPCONST GpFontFamily*,REAL,INT,Unit,GpFont**);
GpStatus WINGDIPAPI GdipCloneFont(GpFont*,GpFont**);
GpStatus WINGDIPAPI GdipDeleteFont(GpFont*);
GpStatus WINGDIPAPI GdipGetFamily(GpFont*,GpFontFamily**);
GpStatus WINGDIPAPI GdipGetFontStyle(GpFont*,INT*);
GpStatus WINGDIPAPI GdipGetFontSize(GpFont*,REAL*);
GpStatus WINGDIPAPI GdipGetFontUnit(GpFont*,Unit*);
GpStatus WINGDIPAPI GdipGetFontHeight(GDIPCONST GpFont*,GDIPCONST GpGraphics*,REAL*);
GpStatus WINGDIPAPI GdipGetFontHeightGivenDPI(GDIPCONST GpFont*,REAL,REAL*);
GpStatus WINGDIPAPI GdipGetLogFontA(GpFont*,GpGraphics*,LOGFONTA*);
GpStatus WINGDIPAPI GdipGetLogFontW(GpFont*,GpGraphics*,LOGFONTW*);
GpStatus WINGDIPAPI GdipNewInstalledFontCollection(GpFontCollection**);
GpStatus WINGDIPAPI GdipNewPrivateFontCollection(GpFontCollection**);
GpStatus WINGDIPAPI GdipDeletePrivateFontCollection(GpFontCollection**);
GpStatus WINGDIPAPI GdipGetFontCollectionFamilyCount(GpFontCollection*,INT*);
GpStatus WINGDIPAPI GdipGetFontCollectionFamilyList(GpFontCollection*,INT,GpFontFamily**,INT*);
GpStatus WINGDIPAPI GdipPrivateAddFontFile(GpFontCollection*,GDIPCONST WCHAR*);
GpStatus WINGDIPAPI GdipPrivateAddMemoryFont(GpFontCollection*,GDIPCONST void*,INT);

/* FontFamily functions */
GpStatus WINGDIPAPI GdipCreateFontFamilyFromName(GDIPCONST WCHAR*,GpFontCollection*,GpFontFamily**);
GpStatus WINGDIPAPI GdipDeleteFontFamily(GpFontFamily*);
GpStatus WINGDIPAPI GdipCloneFontFamily(GpFontFamily*,GpFontFamily**);
GpStatus WINGDIPAPI GdipGetGenericFontFamilySansSerif(GpFontFamily**);
GpStatus WINGDIPAPI GdipGetGenericFontFamilySerif(GpFontFamily**);
GpStatus WINGDIPAPI GdipGetGenericFontFamilyMonospace(GpFontFamily**);
GpStatus WINGDIPAPI GdipGetFamilyName(GDIPCONST GpFontFamily*,WCHAR[LF_FACESIZE],LANGID);
GpStatus WINGDIPAPI GdipIsStyleAvailable(GDIPCONST GpFontFamily*,INT,BOOL*);
GpStatus WINGDIPAPI GdipFontCollectionEnumerable(GpFontCollection*,GpGraphics*,INT*);
GpStatus WINGDIPAPI GdipFontCollectionEnumerate(GpFontCollection*,INT,GpFontFamily**,INT*,GpGraphics*);
GpStatus WINGDIPAPI GdipGetEmHeight(GDIPCONST GpFontFamily*,INT,UINT16*);
GpStatus WINGDIPAPI GdipGetCellAscent(GDIPCONST GpFontFamily*,INT,UINT16*);
GpStatus WINGDIPAPI GdipGetCellDescent(GDIPCONST GpFontFamily*,INT,UINT16*);
GpStatus WINGDIPAPI GdipGetLineSpacing(GDIPCONST GpFontFamily*,INT,UINT16*);

/* Graphics functions */
GpStatus WINGDIPAPI GdipFlush(GpGraphics*,GpFlushIntention);
GpStatus WINGDIPAPI GdipCreateFromHDC(HDC,GpGraphics**);
GpStatus WINGDIPAPI GdipCreateFromHDC2(HDC,HANDLE,GpGraphics**);
GpStatus WINGDIPAPI GdipCreateFromHWND(HWND,GpGraphics**);
GpStatus WINGDIPAPI GdipCreateFromHWNDICM(HWND,GpGraphics**);
GpStatus WINGDIPAPI GdipDeleteGraphics(GpGraphics*);
GpStatus WINGDIPAPI GdipGetDC(GpGraphics*,HDC*);
GpStatus WINGDIPAPI GdipReleaseDC(GpGraphics*,HDC);
GpStatus WINGDIPAPI GdipSetCompositingMode(GpGraphics*,CompositingMode);
GpStatus WINGDIPAPI GdipGetCompositingMode(GpGraphics*,CompositingMode*);
GpStatus WINGDIPAPI GdipSetRenderingOrigin(GpGraphics*,INT,INT);
GpStatus WINGDIPAPI GdipGetRenderingOrigin(GpGraphics*,INT*,INT*);
GpStatus WINGDIPAPI GdipSetCompositingQuality(GpGraphics*,CompositingQuality);
GpStatus WINGDIPAPI GdipGetCompositingQuality(GpGraphics*,CompositingQuality*);
GpStatus WINGDIPAPI GdipSetSmoothingMode(GpGraphics*,SmoothingMode);
GpStatus WINGDIPAPI GdipGetSmoothingMode(GpGraphics*,SmoothingMode*);
GpStatus WINGDIPAPI GdipSetPixelOffsetMode(GpGraphics*,PixelOffsetMode);
GpStatus WINGDIPAPI GdipGetPixelOffsetMode(GpGraphics*,PixelOffsetMode*);
GpStatus WINGDIPAPI GdipSetTextRenderingHint(GpGraphics*,TextRenderingHint);
GpStatus WINGDIPAPI GdipGetTextRenderingHint(GpGraphics*,TextRenderingHint*);
GpStatus WINGDIPAPI GdipSetTextContrast(GpGraphics*,UINT);
GpStatus WINGDIPAPI GdipGetTextContrast(GpGraphics*,UINT*);
GpStatus WINGDIPAPI GdipSetInterpolationMode(GpGraphics*,InterpolationMode);
GpStatus WINGDIPAPI GdipGraphicsSetAbort(GpGraphics*,GdiplusAbort*);
GpStatus WINGDIPAPI GdipGetInterpolationMode(GpGraphics*,InterpolationMode*);
GpStatus WINGDIPAPI GdipSetWorldTransform(GpGraphics*,GpMatrix*);
GpStatus WINGDIPAPI GdipResetWorldTransform(GpGraphics*);
GpStatus WINGDIPAPI GdipMultiplyWorldTransform(GpGraphics*,GDIPCONST GpMatrix*,GpMatrixOrder);
GpStatus WINGDIPAPI GdipTranslateWorldTransform(GpGraphics*,REAL,REAL,GpMatrixOrder);
GpStatus WINGDIPAPI GdipScaleWorldTransform(GpGraphics*,REAL,REAL,GpMatrixOrder);
GpStatus WINGDIPAPI GdipRotateWorldTransform(GpGraphics*,REAL,GpMatrixOrder);
GpStatus WINGDIPAPI GdipGetWorldTransform(GpGraphics*,GpMatrix*);
GpStatus WINGDIPAPI GdipResetPageTransform(GpGraphics*);
GpStatus WINGDIPAPI GdipGetPageUnit(GpGraphics*,GpUnit*);
GpStatus WINGDIPAPI GdipGetPageScale(GpGraphics*,REAL*);
GpStatus WINGDIPAPI GdipSetPageUnit(GpGraphics*,GpUnit);
GpStatus WINGDIPAPI GdipSetPageScale(GpGraphics*,REAL);
GpStatus WINGDIPAPI GdipGetDpiX(GpGraphics*,REAL*);
GpStatus WINGDIPAPI GdipGetDpiY(GpGraphics*,REAL*);
GpStatus WINGDIPAPI GdipTransformPoints(GpGraphics*,GpCoordinateSpace,GpCoordinateSpace,GpPointF*,INT);
GpStatus WINGDIPAPI GdipTransformPointsI(GpGraphics*,GpCoordinateSpace,GpCoordinateSpace,GpPoint*,INT);
GpStatus WINGDIPAPI GdipGetNearestColor(GpGraphics*,ARGB*);
HPALETTE WINGDIPAPI GdipCreateHalftonePalette(void);
GpStatus WINGDIPAPI GdipDrawLine(GpGraphics*,GpPen*,REAL,REAL,REAL,REAL);
GpStatus WINGDIPAPI GdipDrawLineI(GpGraphics*,GpPen*,INT,INT,INT,INT);
GpStatus WINGDIPAPI GdipDrawLines(GpGraphics*,GpPen*,GDIPCONST GpPointF*,INT);
GpStatus WINGDIPAPI GdipDrawLinesI(GpGraphics*,GpPen*,GDIPCONST GpPoint*,INT);
GpStatus WINGDIPAPI GdipDrawArc(GpGraphics*,GpPen*,REAL,REAL,REAL,REAL,REAL,REAL);
GpStatus WINGDIPAPI GdipDrawArcI(GpGraphics*,GpPen*,INT,INT,INT,INT,REAL,REAL);
GpStatus WINGDIPAPI GdipDrawBezier(GpGraphics*,GpPen*,REAL,REAL,REAL,REAL,REAL,REAL,REAL,REAL);
GpStatus WINGDIPAPI GdipDrawBezierI(GpGraphics*,GpPen*,INT,INT,INT,INT,INT,INT,INT,INT);
GpStatus WINGDIPAPI GdipDrawBeziers(GpGraphics*,GpPen*,GDIPCONST GpPointF*,INT);
GpStatus WINGDIPAPI GdipDrawBeziersI(GpGraphics*,GpPen*,GDIPCONST GpPoint*,INT);
GpStatus WINGDIPAPI GdipDrawRectangle(GpGraphics*,GpPen*,REAL,REAL,REAL,REAL);
GpStatus WINGDIPAPI GdipDrawRectangleI(GpGraphics*,GpPen*,INT,INT,INT,INT);
GpStatus WINGDIPAPI GdipDrawRectangles(GpGraphics*,GpPen*,GDIPCONST GpRectF*,INT);
GpStatus WINGDIPAPI GdipDrawRectanglesI(GpGraphics*,GpPen*,GDIPCONST GpRect*,INT);
GpStatus WINGDIPAPI GdipDrawEllipse(GpGraphics*,GpPen*,REAL,REAL,REAL,REAL);
GpStatus WINGDIPAPI GdipDrawEllipseI(GpGraphics*,GpPen*,INT,INT,INT,INT);
GpStatus WINGDIPAPI GdipDrawPie(GpGraphics*,GpPen*,REAL,REAL,REAL,REAL,REAL,REAL);
GpStatus WINGDIPAPI GdipDrawPieI(GpGraphics*,GpPen*,INT,INT,INT,INT,REAL,REAL);
GpStatus WINGDIPAPI GdipDrawPolygon(GpGraphics*,GpPen*,GDIPCONST GpPointF*,INT);
GpStatus WINGDIPAPI GdipDrawPolygonI(GpGraphics*,GpPen*,GDIPCONST GpPoint*,INT);
GpStatus WINGDIPAPI GdipDrawPath(GpGraphics*,GpPen*,GpPath*);
GpStatus WINGDIPAPI GdipDrawCurve(GpGraphics*,GpPen*,GDIPCONST GpPointF*,INT);
GpStatus WINGDIPAPI GdipDrawCurveI(GpGraphics*,GpPen*,GDIPCONST GpPoint*,INT);
GpStatus WINGDIPAPI GdipDrawCurve2(GpGraphics*,GpPen*,GDIPCONST GpPointF*,INT,REAL);
GpStatus WINGDIPAPI GdipDrawCurve2I(GpGraphics*,GpPen*,GDIPCONST GpPoint*,INT,REAL);
GpStatus WINGDIPAPI GdipDrawCurve3(GpGraphics*,GpPen*,GDIPCONST GpPointF*,INT,INT,INT,REAL);
GpStatus WINGDIPAPI GdipDrawCurve3I(GpGraphics*,GpPen*,GDIPCONST GpPoint*,INT,INT,INT,REAL);
GpStatus WINGDIPAPI GdipDrawClosedCurve(GpGraphics*,GpPen*,GDIPCONST GpPointF*,INT);
GpStatus WINGDIPAPI GdipDrawClosedCurveI(GpGraphics*,GpPen*,GDIPCONST GpPoint*,INT);
GpStatus WINGDIPAPI GdipDrawClosedCurve2(GpGraphics*,GpPen*,GDIPCONST GpPointF*,INT,REAL);
GpStatus WINGDIPAPI GdipDrawClosedCurve2I(GpGraphics*,GpPen*,GDIPCONST GpPoint*,INT,REAL);
GpStatus WINGDIPAPI GdipGraphicsClear(GpGraphics*,ARGB);
GpStatus WINGDIPAPI GdipFillRectangle(GpGraphics*,GpBrush*,REAL,REAL,REAL,REAL);
GpStatus WINGDIPAPI GdipFillRectangleI(GpGraphics*,GpBrush*,INT,INT,INT,INT);
GpStatus WINGDIPAPI GdipFillRectangles(GpGraphics*,GpBrush*,GDIPCONST GpRectF*,INT);
GpStatus WINGDIPAPI GdipFillRectanglesI(GpGraphics*,GpBrush*,GDIPCONST GpRect*,INT);
GpStatus WINGDIPAPI GdipFillPolygon(GpGraphics*,GpBrush*,GDIPCONST GpPointF*,INT,GpFillMode);
GpStatus WINGDIPAPI GdipFillPolygonI(GpGraphics*,GpBrush*,GDIPCONST GpPoint*,INT,GpFillMode);
GpStatus WINGDIPAPI GdipFillPolygon2(GpGraphics*,GpBrush*,GDIPCONST GpPointF*,INT);
GpStatus WINGDIPAPI GdipFillPolygon2I(GpGraphics*,GpBrush*,GDIPCONST GpPoint*,INT);
GpStatus WINGDIPAPI GdipFillEllipse(GpGraphics*,GpBrush*,REAL,REAL,REAL,REAL);
GpStatus WINGDIPAPI GdipFillEllipseI(GpGraphics*,GpBrush*,INT,INT,INT,INT);
GpStatus WINGDIPAPI GdipFillPie(GpGraphics*,GpBrush*,REAL,REAL,REAL,REAL,REAL,REAL);
GpStatus WINGDIPAPI GdipFillPieI(GpGraphics*,GpBrush*,INT,INT,INT,INT,REAL,REAL);
GpStatus WINGDIPAPI GdipFillPath(GpGraphics*,GpBrush*,GpPath*);
GpStatus WINGDIPAPI GdipFillClosedCurve(GpGraphics*,GpBrush*,GDIPCONST GpPointF*,INT);
GpStatus WINGDIPAPI GdipFillClosedCurveI(GpGraphics*,GpBrush*,GDIPCONST GpPoint*,INT);
GpStatus WINGDIPAPI GdipFillClosedCurve2(GpGraphics*,GpBrush*,GDIPCONST GpPointF*,INT,REAL,GpFillMode);
GpStatus WINGDIPAPI GdipFillClosedCurve2I(GpGraphics*,GpBrush*,GDIPCONST GpPoint*,INT,REAL,GpFillMode);
GpStatus WINGDIPAPI GdipFillRegion(GpGraphics*,GpBrush*,GpRegion*);
GpStatus WINGDIPAPI GdipDrawImage(GpGraphics*,GpImage*,REAL,REAL);
GpStatus WINGDIPAPI GdipDrawImageI(GpGraphics*,GpImage*,INT,INT);
GpStatus WINGDIPAPI GdipDrawImageRect(GpGraphics*,GpImage*,REAL,REAL,REAL,REAL);
GpStatus WINGDIPAPI GdipDrawImageRectI(GpGraphics*,GpImage*,INT,INT,INT,INT);
GpStatus WINGDIPAPI GdipDrawImagePoints(GpGraphics*,GpImage*,GDIPCONST GpPointF*,INT);
GpStatus WINGDIPAPI GdipDrawImagePointsI(GpGraphics*,GpImage*,GDIPCONST GpPoint*,INT);
GpStatus WINGDIPAPI GdipDrawImagePointRect(GpGraphics*,GpImage*,REAL,REAL,REAL,REAL,REAL,REAL,GpUnit);
GpStatus WINGDIPAPI GdipDrawImagePointRectI(GpGraphics*,GpImage*,INT,INT,INT,INT,INT,INT,GpUnit);
GpStatus WINGDIPAPI GdipDrawImageRectRect(GpGraphics*,GpImage*,REAL,REAL,REAL,REAL,REAL,REAL,REAL,REAL,GpUnit,GDIPCONST GpImageAttributes*,DrawImageAbort,VOID*);
GpStatus WINGDIPAPI GdipDrawImageRectRectI(GpGraphics*,GpImage*,INT,INT,INT,INT,INT,INT,INT,INT,GpUnit,GDIPCONST GpImageAttributes*,DrawImageAbort,VOID*);
GpStatus WINGDIPAPI GdipDrawImagePointsRect(GpGraphics*,GpImage*,GDIPCONST GpPointF*,INT,REAL,REAL,REAL,REAL,GpUnit,GDIPCONST GpImageAttributes*,DrawImageAbort,VOID*);
GpStatus WINGDIPAPI GdipDrawImagePointsRectI(GpGraphics*,GpImage*,GDIPCONST GpPoint*,INT,INT,INT,INT,INT,GpUnit,GDIPCONST GpImageAttributes*,DrawImageAbort,VOID*);
GpStatus WINGDIPAPI GdipDrawImageFX(GpGraphics*,GpImage*,GpRectF*,GpMatrix*,CGpEffect*,GpImageAttributes*,GpUnit);
#ifdef __cplusplus
GpStatus WINGDIPAPI GdipEnumerateMetafileDestPoint(GpGraphics*,GDIPCONST GpMetafile*,GDIPCONST PointF&,EnumerateMetafileProc,VOID*,GDIPCONST GpImageAttributes*);
GpStatus WINGDIPAPI GdipEnumerateMetafileDestPointI(GpGraphics*,GDIPCONST GpMetafile*,GDIPCONST Point&,EnumerateMetafileProc,VOID*,GDIPCONST GpImageAttributes*);
GpStatus WINGDIPAPI GdipEnumerateMetafileDestRect(GpGraphics*,GDIPCONST GpMetafile*,GDIPCONST RectF&,EnumerateMetafileProc,VOID*,GDIPCONST GpImageAttributes*);
GpStatus WINGDIPAPI GdipEnumerateMetafileDestRectI(GpGraphics*,GDIPCONST GpMetafile*,GDIPCONST Rect&,EnumerateMetafileProc,VOID*,GDIPCONST GpImageAttributes*);
#endif
GpStatus WINGDIPAPI GdipEnumerateMetafileDestPoints(GpGraphics*,GDIPCONST GpMetafile*,GDIPCONST PointF*,INT,EnumerateMetafileProc,VOID*,GDIPCONST GpImageAttributes*);
GpStatus WINGDIPAPI GdipEnumerateMetafileDestPointsI(GpGraphics*,GDIPCONST GpMetafile*,GDIPCONST Point*,INT,EnumerateMetafileProc,VOID*,GDIPCONST GpImageAttributes*);
#ifdef __cplusplus
GpStatus WINGDIPAPI GdipEnumerateMetafileSrcRectDestPoint(GpGraphics*,GDIPCONST GpMetafile*,GDIPCONST PointF&,GDIPCONST RectF&,Unit,EnumerateMetafileProc,VOID*,GDIPCONST GpImageAttributes*);
GpStatus WINGDIPAPI GdipEnumerateMetafileSrcRectDestPointI(GpGraphics*,GDIPCONST GpMetafile*,GDIPCONST Point&,GDIPCONST Rect&,Unit,EnumerateMetafileProc,VOID*,GDIPCONST GpImageAttributes*);
GpStatus WINGDIPAPI GdipEnumerateMetafileSrcRectDestRect(GpGraphics*,GDIPCONST GpMetafile*,GDIPCONST RectF&,GDIPCONST RectF&,Unit,EnumerateMetafileProc,VOID*,GDIPCONST GpImageAttributes*);
GpStatus WINGDIPAPI GdipEnumerateMetafileSrcRectDestRectI(GpGraphics*,GDIPCONST GpMetafile*,GDIPCONST Rect&,GDIPCONST Rect&,Unit,EnumerateMetafileProc,VOID*,GDIPCONST GpImageAttributes*);
GpStatus WINGDIPAPI GdipEnumerateMetafileSrcRectDestPoints(GpGraphics*,GDIPCONST GpMetafile*,GDIPCONST PointF*,INT,GDIPCONST RectF&,Unit,EnumerateMetafileProc,VOID*,GDIPCONST GpImageAttributes*);
GpStatus WINGDIPAPI GdipEnumerateMetafileSrcRectDestPointsI(GpGraphics*,GDIPCONST GpMetafile*,GDIPCONST Point*,INT,GDIPCONST Rect&,Unit,EnumerateMetafileProc,VOID*,GDIPCONST GpImageAttributes*);
#endif
GpStatus WINGDIPAPI GdipSetClipGraphics(GpGraphics*,GpGraphics*,CombineMode);
GpStatus WINGDIPAPI GdipSetClipRect(GpGraphics*,REAL,REAL,REAL,REAL,CombineMode);
GpStatus WINGDIPAPI GdipSetClipRectI(GpGraphics*,INT,INT,INT,INT,CombineMode);
GpStatus WINGDIPAPI GdipSetClipPath(GpGraphics*,GpPath*,CombineMode);
GpStatus WINGDIPAPI GdipSetClipRegion(GpGraphics*,GpRegion*,CombineMode);
GpStatus WINGDIPAPI GdipSetClipHrgn(GpGraphics*,HRGN,CombineMode);
GpStatus WINGDIPAPI GdipResetClip(GpGraphics*);
GpStatus WINGDIPAPI GdipTranslateClip(GpGraphics*,REAL,REAL);
GpStatus WINGDIPAPI GdipTranslateClipI(GpGraphics*,INT,INT);
GpStatus WINGDIPAPI GdipGetClip(GpGraphics*,GpRegion*);
GpStatus WINGDIPAPI GdipGetClipBounds(GpGraphics*,GpRectF*);
GpStatus WINGDIPAPI GdipGetClipBoundsI(GpGraphics*,GpRect*);
GpStatus WINGDIPAPI GdipIsClipEmpty(GpGraphics*,BOOL*);
GpStatus WINGDIPAPI GdipGetVisibleClipBounds(GpGraphics*,GpRectF*);
GpStatus WINGDIPAPI GdipGetVisibleClipBoundsI(GpGraphics*,GpRect*);
GpStatus WINGDIPAPI GdipIsVisibleClipEmpty(GpGraphics*,BOOL*);
GpStatus WINGDIPAPI GdipIsVisiblePoint(GpGraphics*,REAL,REAL,BOOL*);
GpStatus WINGDIPAPI GdipIsVisiblePointI(GpGraphics*,INT,INT,BOOL*);
GpStatus WINGDIPAPI GdipIsVisibleRect(GpGraphics*,REAL,REAL,REAL,REAL,BOOL*);
GpStatus WINGDIPAPI GdipIsVisibleRectI(GpGraphics*,INT,INT,INT,INT,BOOL*);
GpStatus WINGDIPAPI GdipSaveGraphics(GpGraphics*,GraphicsState*);
GpStatus WINGDIPAPI GdipRestoreGraphics(GpGraphics*,GraphicsState);
GpStatus WINGDIPAPI GdipBeginContainer(GpGraphics*,GDIPCONST GpRectF*,GDIPCONST GpRectF*,GpUnit,GraphicsContainer*);
GpStatus WINGDIPAPI GdipBeginContainerI(GpGraphics*,GDIPCONST GpRect*,GDIPCONST GpRect*,GpUnit,GraphicsContainer*);
GpStatus WINGDIPAPI GdipBeginContainer2(GpGraphics*,GraphicsContainer*);
GpStatus WINGDIPAPI GdipEndContainer(GpGraphics*,GraphicsContainer);
GpStatus WINGDIPAPI GdipComment(GpGraphics*,UINT,GDIPCONST BYTE*);

/* GraphicsPath functions */
GpStatus WINGDIPAPI GdipCreatePath(GpFillMode,GpPath**);
GpStatus WINGDIPAPI GdipCreatePath2(GDIPCONST GpPointF*,GDIPCONST BYTE*,INT,GpFillMode,GpPath**);
GpStatus WINGDIPAPI GdipCreatePath2I(GDIPCONST GpPoint*,GDIPCONST BYTE*,INT,GpFillMode,GpPath**);
GpStatus WINGDIPAPI GdipClonePath(GpPath*,GpPath**);
GpStatus WINGDIPAPI GdipDeletePath(GpPath*);
GpStatus WINGDIPAPI GdipResetPath(GpPath*);
GpStatus WINGDIPAPI GdipGetPointCount(GpPath*,INT*);
GpStatus WINGDIPAPI GdipGetPathTypes(GpPath*,BYTE*,INT);
GpStatus WINGDIPAPI GdipGetPathPoints(GpPath*,GpPointF*,INT);
GpStatus WINGDIPAPI GdipGetPathPointsI(GpPath*,GpPoint*,INT);
GpStatus WINGDIPAPI GdipGetPathFillMode(GpPath*,GpFillMode*);
GpStatus WINGDIPAPI GdipSetPathFillMode(GpPath*,GpFillMode);
GpStatus WINGDIPAPI GdipGetPathData(GpPath*,GpPathData*);
GpStatus WINGDIPAPI GdipStartPathFigure(GpPath*);
GpStatus WINGDIPAPI GdipClosePathFigure(GpPath*);
GpStatus WINGDIPAPI GdipClosePathFigures(GpPath*);
GpStatus WINGDIPAPI GdipSetPathMarker(GpPath*);
GpStatus WINGDIPAPI GdipClearPathMarkers(GpPath*);
GpStatus WINGDIPAPI GdipReversePath(GpPath*);
GpStatus WINGDIPAPI GdipGetPathLastPoint(GpPath*,GpPointF*);
GpStatus WINGDIPAPI GdipAddPathLine(GpPath*,REAL,REAL,REAL,REAL);
GpStatus WINGDIPAPI GdipAddPathLine2(GpPath*,GDIPCONST GpPointF*,INT);
GpStatus WINGDIPAPI GdipAddPathArc(GpPath*,REAL,REAL,REAL,REAL,REAL,REAL);
GpStatus WINGDIPAPI GdipAddPathBezier(GpPath*,REAL,REAL,REAL,REAL,REAL,REAL,REAL,REAL);
GpStatus WINGDIPAPI GdipAddPathBeziers(GpPath*,GDIPCONST GpPointF*,INT);
GpStatus WINGDIPAPI GdipAddPathCurve(GpPath*,GDIPCONST GpPointF*,INT);
GpStatus WINGDIPAPI GdipAddPathCurve2(GpPath*,GDIPCONST GpPointF*,INT,REAL);
GpStatus WINGDIPAPI GdipAddPathCurve3(GpPath*,GDIPCONST GpPointF*,INT,INT,INT,REAL);
GpStatus WINGDIPAPI GdipAddPathClosedCurve(GpPath*,GDIPCONST GpPointF*,INT);
GpStatus WINGDIPAPI GdipAddPathClosedCurve2(GpPath*,GDIPCONST GpPointF*,INT,REAL);
GpStatus WINGDIPAPI GdipAddPathRectangle(GpPath*,REAL,REAL,REAL,REAL);
GpStatus WINGDIPAPI GdipAddPathRectangles(GpPath*,GDIPCONST GpRectF*,INT);
GpStatus WINGDIPAPI GdipAddPathEllipse(GpPath*,REAL,REAL,REAL,REAL);
GpStatus WINGDIPAPI GdipAddPathPie(GpPath*,REAL,REAL,REAL,REAL,REAL,REAL);
GpStatus WINGDIPAPI GdipAddPathPolygon(GpPath*,GDIPCONST GpPointF*,INT);
GpStatus WINGDIPAPI GdipAddPathPath(GpPath*,GDIPCONST GpPath*,BOOL);
GpStatus WINGDIPAPI GdipAddPathString(GpPath*,GDIPCONST WCHAR*,INT,GDIPCONST GpFontFamily*,INT,REAL,GDIPCONST RectF*,GDIPCONST GpStringFormat*);
GpStatus WINGDIPAPI GdipAddPathStringI(GpPath*,GDIPCONST WCHAR*,INT,GDIPCONST GpFontFamily*,INT,REAL,GDIPCONST Rect*,GDIPCONST GpStringFormat*);
GpStatus WINGDIPAPI GdipAddPathLineI(GpPath*,INT,INT,INT,INT);
GpStatus WINGDIPAPI GdipAddPathLine2I(GpPath*,GDIPCONST GpPoint*,INT);
GpStatus WINGDIPAPI GdipAddPathArcI(GpPath*,INT,INT,INT,INT,REAL,REAL);
GpStatus WINGDIPAPI GdipAddPathBezierI(GpPath*,INT,INT,INT,INT,INT,INT,INT,INT);
GpStatus WINGDIPAPI GdipAddPathBeziersI(GpPath*,GDIPCONST GpPoint*,INT);
GpStatus WINGDIPAPI GdipAddPathCurveI(GpPath*,GDIPCONST GpPoint*,INT);
GpStatus WINGDIPAPI GdipAddPathCurve2I(GpPath*,GDIPCONST GpPoint*,INT,REAL);
GpStatus WINGDIPAPI GdipAddPathCurve3I(GpPath*,GDIPCONST GpPoint*,INT,INT,INT,REAL);
GpStatus WINGDIPAPI GdipAddPathClosedCurveI(GpPath*,GDIPCONST GpPoint*,INT);
GpStatus WINGDIPAPI GdipAddPathClosedCurve2I(GpPath*,GDIPCONST GpPoint*,INT,REAL);
GpStatus WINGDIPAPI GdipAddPathRectangleI(GpPath*,INT,INT,INT,INT);
GpStatus WINGDIPAPI GdipAddPathRectanglesI(GpPath*,GDIPCONST GpRect*,INT);
GpStatus WINGDIPAPI GdipAddPathEllipseI(GpPath*,INT,INT,INT,INT);
GpStatus WINGDIPAPI GdipAddPathPieI(GpPath*,INT,INT,INT,INT,REAL,REAL);
GpStatus WINGDIPAPI GdipAddPathPolygonI(GpPath*,GDIPCONST GpPoint*,INT);
GpStatus WINGDIPAPI GdipFlattenPath(GpPath*,GpMatrix*,REAL);
GpStatus WINGDIPAPI GdipWindingModeOutline(GpPath*,GpMatrix*,REAL);
GpStatus WINGDIPAPI GdipWidenPath(GpPath*,GpPen*,GpMatrix*,REAL);
GpStatus WINGDIPAPI GdipWarpPath(GpPath*,GpMatrix*,GDIPCONST GpPointF*,INT,REAL,REAL,REAL,REAL,WarpMode,REAL);
GpStatus WINGDIPAPI GdipTransformPath(GpPath*,GpMatrix*);
GpStatus WINGDIPAPI GdipGetPathWorldBounds(GpPath*,GpRectF*,GDIPCONST GpMatrix*,GDIPCONST GpPen*);
GpStatus WINGDIPAPI GdipGetPathWorldBoundsI(GpPath*,GpRect*,GDIPCONST GpMatrix*,GDIPCONST GpPen*);
GpStatus WINGDIPAPI GdipIsVisiblePathPoint(GpPath*,REAL,REAL,GpGraphics*,BOOL*);
GpStatus WINGDIPAPI GdipIsVisiblePathPointI(GpPath*,INT,INT,GpGraphics*,BOOL*);
GpStatus WINGDIPAPI GdipIsOutlineVisiblePathPoint(GpPath*,REAL,REAL,GpPen*,GpGraphics*,BOOL*);
GpStatus WINGDIPAPI GdipIsOutlineVisiblePathPointI(GpPath*,INT,INT,GpPen*,GpGraphics*,BOOL*);

/* HatchBrush functions */
GpStatus WINGDIPAPI GdipCreateHatchBrush(GpHatchStyle,ARGB,ARGB,GpHatch**);
GpStatus WINGDIPAPI GdipGetHatchStyle(GpHatch*,GpHatchStyle*);
GpStatus WINGDIPAPI GdipGetHatchForegroundColor(GpHatch*,ARGB*);
GpStatus WINGDIPAPI GdipGetHatchBackgroundColor(GpHatch*,ARGB*);

/* Image functions */
GpStatus WINGDIPAPI GdipLoadImageFromStream(IStream*,GpImage**);
GpStatus WINGDIPAPI GdipLoadImageFromFile(GDIPCONST WCHAR*,GpImage**);
GpStatus WINGDIPAPI GdipLoadImageFromStreamICM(IStream*,GpImage**);
GpStatus WINGDIPAPI GdipLoadImageFromFileICM(GDIPCONST WCHAR*,GpImage**);
GpStatus WINGDIPAPI GdipCloneImage(GpImage*,GpImage**);
GpStatus WINGDIPAPI GdipDisposeImage(GpImage*);
GpStatus WINGDIPAPI GdipSaveImageToFile(GpImage*,GDIPCONST WCHAR*,GDIPCONST CLSID*,GDIPCONST EncoderParameters*);
GpStatus WINGDIPAPI GdipSaveImageToStream(GpImage*,IStream*,GDIPCONST CLSID*,GDIPCONST EncoderParameters*);
GpStatus WINGDIPAPI GdipSaveAdd(GpImage*,GDIPCONST EncoderParameters*);
GpStatus WINGDIPAPI GdipSaveAddImage(GpImage*,GpImage*,GDIPCONST EncoderParameters*);
GpStatus WINGDIPAPI GdipGetImageGraphicsContext(GpImage*,GpGraphics**);
GpStatus WINGDIPAPI GdipGetImageBounds(GpImage*,GpRectF*,GpUnit*);
GpStatus WINGDIPAPI GdipGetImageDimension(GpImage*,REAL*,REAL*);
GpStatus WINGDIPAPI GdipGetImageType(GpImage*,ImageType*);
GpStatus WINGDIPAPI GdipGetImageWidth(GpImage*,UINT*);
GpStatus WINGDIPAPI GdipGetImageHeight(GpImage*,UINT*);
GpStatus WINGDIPAPI GdipGetImageHorizontalResolution(GpImage*,REAL*);
GpStatus WINGDIPAPI GdipGetImageVerticalResolution(GpImage*,REAL*);
GpStatus WINGDIPAPI GdipGetImageFlags(GpImage*,UINT*);
GpStatus WINGDIPAPI GdipGetImageRawFormat(GpImage*,GUID*);
GpStatus WINGDIPAPI GdipGetImagePixelFormat(GpImage*,PixelFormat*);
GpStatus WINGDIPAPI GdipGetImageThumbnail(GpImage*,UINT,UINT,GpImage**,GetThumbnailImageAbort,VOID*);
GpStatus WINGDIPAPI GdipGetEncoderParameterListSize(GpImage*,GDIPCONST CLSID*,UINT*);
GpStatus WINGDIPAPI GdipGetEncoderParameterList(GpImage*,GDIPCONST CLSID*,UINT,EncoderParameters*);
GpStatus WINGDIPAPI GdipImageGetFrameDimensionsCount(GpImage*,UINT*);
GpStatus WINGDIPAPI GdipImageGetFrameDimensionsList(GpImage*,GUID*,UINT);
GpStatus WINGDIPAPI GdipImageGetFrameCount(GpImage*,GDIPCONST GUID*,UINT*);
GpStatus WINGDIPAPI GdipImageSelectActiveFrame(GpImage*,GDIPCONST GUID*,UINT);
GpStatus WINGDIPAPI GdipImageRotateFlip(GpImage*,RotateFlipType);
GpStatus WINGDIPAPI GdipGetImagePalette(GpImage*,ColorPalette*,INT);
GpStatus WINGDIPAPI GdipSetImagePalette(GpImage*,GDIPCONST ColorPalette*);
GpStatus WINGDIPAPI GdipGetImagePaletteSize(GpImage*,INT*);
GpStatus WINGDIPAPI GdipGetPropertyCount(GpImage*,UINT*);
GpStatus WINGDIPAPI GdipGetPropertyIdList(GpImage*,UINT,PROPID*);
GpStatus WINGDIPAPI GdipGetPropertyItemSize(GpImage*,PROPID,UINT*);
GpStatus WINGDIPAPI GdipGetPropertyItem(GpImage*,PROPID,UINT,PropertyItem*);
GpStatus WINGDIPAPI GdipGetPropertySize(GpImage*,UINT*,UINT*);
GpStatus WINGDIPAPI GdipGetAllPropertyItems(GpImage*,UINT,UINT,PropertyItem*);
GpStatus WINGDIPAPI GdipRemovePropertyItem(GpImage*,PROPID);
GpStatus WINGDIPAPI GdipSetPropertyItem(GpImage*,GDIPCONST PropertyItem*);
GpStatus WINGDIPAPI GdipFindFirstImageItem(GpImage*,ImageItemData*);
GpStatus WINGDIPAPI GdipFindNextImageItem(GpImage*,ImageItemData*);
GpStatus WINGDIPAPI GdipGetImageItemData(GpImage*,ImageItemData*);
GpStatus WINGDIPAPI GdipImageSetAbort(GpImage*,GdiplusAbort*);
GpStatus WINGDIPAPI GdipImageForceValidation(GpImage*);

/* Image codec functions */
GpStatus WINGDIPAPI GdipGetImageDecodersSize(UINT*,UINT*);
GpStatus WINGDIPAPI GdipGetImageDecoders(UINT,UINT,ImageCodecInfo*);
GpStatus WINGDIPAPI GdipGetImageEncodersSize(UINT*,UINT*);
GpStatus WINGDIPAPI GdipGetImageEncoders(UINT,UINT,ImageCodecInfo*);

/* ImageAttributes functions */
GpStatus WINGDIPAPI GdipCreateImageAttributes(GpImageAttributes**);
GpStatus WINGDIPAPI GdipCloneImageAttributes(GDIPCONST GpImageAttributes*,GpImageAttributes**);
GpStatus WINGDIPAPI GdipDisposeImageAttributes(GpImageAttributes*);
GpStatus WINGDIPAPI GdipSetImageAttributesToIdentity(GpImageAttributes*,ColorAdjustType);
GpStatus WINGDIPAPI GdipResetImageAttributes(GpImageAttributes*,ColorAdjustType);
GpStatus WINGDIPAPI GdipSetImageAttributesColorMatrix(GpImageAttributes*,ColorAdjustType,BOOL,GDIPCONST ColorMatrix*,GDIPCONST ColorMatrix*,ColorMatrixFlags);
GpStatus WINGDIPAPI GdipSetImageAttributesThreshold(GpImageAttributes*,ColorAdjustType,BOOL,REAL);
GpStatus WINGDIPAPI GdipSetImageAttributesGamma(GpImageAttributes*,ColorAdjustType,BOOL,REAL);
GpStatus WINGDIPAPI GdipSetImageAttributesNoOp(GpImageAttributes*,ColorAdjustType,BOOL);
GpStatus WINGDIPAPI GdipSetImageAttributesColorKeys(GpImageAttributes*,ColorAdjustType,BOOL,ARGB,ARGB);
GpStatus WINGDIPAPI GdipSetImageAttributesOutputChannel(GpImageAttributes*,ColorAdjustType,BOOL,ColorChannelFlags);
GpStatus WINGDIPAPI GdipSetImageAttributesOutputChannelColorProfile(GpImageAttributes*,ColorAdjustType,BOOL,GDIPCONST WCHAR*);
GpStatus WINGDIPAPI GdipSetImageAttributesRemapTable(GpImageAttributes*,ColorAdjustType,BOOL,UINT,GDIPCONST ColorMap*);
GpStatus WINGDIPAPI GdipSetImageAttributesWrapMode(GpImageAttributes*,WrapMode,ARGB,BOOL);
GpStatus WINGDIPAPI GdipSetImageAttributesICMMode(GpImageAttributes*,BOOL);
GpStatus WINGDIPAPI GdipGetImageAttributesAdjustedPalette(GpImageAttributes*,ColorPalette*,ColorAdjustType);
GpStatus WINGDIPAPI GdipSetImageAttributesCachedBackground(GpImageAttributes*,BOOL);

/* LinearGradientBrush functions */
GpStatus WINGDIPAPI GdipCreateLineBrush(GDIPCONST GpPointF*,GDIPCONST GpPointF*,ARGB,ARGB,GpWrapMode,GpLineGradient**);
GpStatus WINGDIPAPI GdipCreateLineBrushI(GDIPCONST GpPoint*,GDIPCONST GpPoint*,ARGB,ARGB,GpWrapMode,GpLineGradient**);
GpStatus WINGDIPAPI GdipCreateLineBrushFromRect(GDIPCONST GpRectF*,ARGB,ARGB,LinearGradientMode,GpWrapMode,GpLineGradient**);
GpStatus WINGDIPAPI GdipCreateLineBrushFromRectI(GDIPCONST GpRect*,ARGB,ARGB,LinearGradientMode,GpWrapMode,GpLineGradient**);
GpStatus WINGDIPAPI GdipCreateLineBrushFromRectWithAngle(GDIPCONST GpRectF*,ARGB,ARGB,REAL,BOOL,GpWrapMode,GpLineGradient**);
GpStatus WINGDIPAPI GdipCreateLineBrushFromRectWithAngleI(GDIPCONST GpRect*,ARGB,ARGB,REAL,BOOL,GpWrapMode,GpLineGradient**);
GpStatus WINGDIPAPI GdipSetLineColors(GpLineGradient*,ARGB,ARGB);
GpStatus WINGDIPAPI GdipGetLineColors(GpLineGradient*,ARGB*);
GpStatus WINGDIPAPI GdipGetLineRect(GpLineGradient*,GpRectF*);
GpStatus WINGDIPAPI GdipGetLineRectI(GpLineGradient*,GpRect*);
GpStatus WINGDIPAPI GdipSetLineGammaCorrection(GpLineGradient*,BOOL);
GpStatus WINGDIPAPI GdipGetLineGammaCorrection(GpLineGradient*,BOOL*);
GpStatus WINGDIPAPI GdipGetLineBlendCount(GpLineGradient*,INT*);
GpStatus WINGDIPAPI GdipGetLineBlend(GpLineGradient*,REAL*,REAL*,INT);
GpStatus WINGDIPAPI GdipSetLineBlend(GpLineGradient*,GDIPCONST REAL*,GDIPCONST REAL*,INT);
GpStatus WINGDIPAPI GdipGetLinePresetBlendCount(GpLineGradient*,INT*);
GpStatus WINGDIPAPI GdipGetLinePresetBlend(GpLineGradient*,ARGB*,REAL*,INT);
GpStatus WINGDIPAPI GdipSetLinePresetBlend(GpLineGradient*,GDIPCONST ARGB*,GDIPCONST REAL*,INT);
GpStatus WINGDIPAPI GdipSetLineSigmaBlend(GpLineGradient*,REAL,REAL);
GpStatus WINGDIPAPI GdipSetLineLinearBlend(GpLineGradient*,REAL,REAL);
GpStatus WINGDIPAPI GdipSetLineWrapMode(GpLineGradient*,GpWrapMode);
GpStatus WINGDIPAPI GdipGetLineWrapMode(GpLineGradient*,GpWrapMode*);
GpStatus WINGDIPAPI GdipGetLineTransform(GpLineGradient*,GpMatrix*);
GpStatus WINGDIPAPI GdipSetLineTransform(GpLineGradient*,GDIPCONST GpMatrix*);
GpStatus WINGDIPAPI GdipResetLineTransform(GpLineGradient*);
GpStatus WINGDIPAPI GdipMultiplyLineTransform(GpLineGradient*,GDIPCONST GpMatrix*,GpMatrixOrder);
GpStatus WINGDIPAPI GdipTranslateLineTransform(GpLineGradient*,REAL,REAL,GpMatrixOrder);
GpStatus WINGDIPAPI GdipScaleLineTransform(GpLineGradient*,REAL,REAL,GpMatrixOrder);
GpStatus WINGDIPAPI GdipRotateLineTransform(GpLineGradient*,REAL,GpMatrixOrder);

/* Matrix functions */
GpStatus WINGDIPAPI GdipCreateMatrix(GpMatrix**);
GpStatus WINGDIPAPI GdipCreateMatrix2(REAL,REAL,REAL,REAL,REAL,REAL,GpMatrix**);
GpStatus WINGDIPAPI GdipCreateMatrix3(GDIPCONST GpRectF*,GDIPCONST GpPointF*,GpMatrix**);
GpStatus WINGDIPAPI GdipCreateMatrix3I(GDIPCONST GpRect*,GDIPCONST GpPoint*,GpMatrix**);
GpStatus WINGDIPAPI GdipCloneMatrix(GpMatrix*,GpMatrix**);
GpStatus WINGDIPAPI GdipDeleteMatrix(GpMatrix*);
GpStatus WINGDIPAPI GdipSetMatrixElements(GpMatrix*,REAL,REAL,REAL,REAL,REAL,REAL);
GpStatus WINGDIPAPI GdipMultiplyMatrix(GpMatrix*,GpMatrix*,GpMatrixOrder);
GpStatus WINGDIPAPI GdipTranslateMatrix(GpMatrix*,REAL,REAL,GpMatrixOrder);
GpStatus WINGDIPAPI GdipScaleMatrix(GpMatrix*,REAL,REAL,GpMatrixOrder);
GpStatus WINGDIPAPI GdipRotateMatrix(GpMatrix*,REAL,GpMatrixOrder);
GpStatus WINGDIPAPI GdipShearMatrix(GpMatrix*,REAL,REAL,GpMatrixOrder);
GpStatus WINGDIPAPI GdipInvertMatrix(GpMatrix*);
GpStatus WINGDIPAPI GdipTransformMatrixPoints(GpMatrix*,GpPointF*,INT);
GpStatus WINGDIPAPI GdipTransformMatrixPointsI(GpMatrix*,GpPoint*,INT);
GpStatus WINGDIPAPI GdipVectorTransformMatrixPoints(GpMatrix*,GpPointF*,INT);
GpStatus WINGDIPAPI GdipVectorTransformMatrixPointsI(GpMatrix*,GpPoint*,INT);
GpStatus WINGDIPAPI GdipGetMatrixElements(GDIPCONST GpMatrix*,REAL*);
GpStatus WINGDIPAPI GdipIsMatrixInvertible(GDIPCONST GpMatrix*,BOOL*);
GpStatus WINGDIPAPI GdipIsMatrixIdentity(GDIPCONST GpMatrix*,BOOL*);
GpStatus WINGDIPAPI GdipIsMatrixEqual(GDIPCONST GpMatrix*,GDIPCONST GpMatrix*,BOOL*);

/* Metafile functions */
GpStatus WINGDIPAPI GdipGetMetafileHeaderFromEmf(HENHMETAFILE,MetafileHeader*);
GpStatus WINGDIPAPI GdipGetMetafileHeaderFromFile(GDIPCONST WCHAR*,MetafileHeader*);
GpStatus WINGDIPAPI GdipGetMetafileHeaderFromStream(IStream*,MetafileHeader*);
GpStatus WINGDIPAPI GdipGetMetafileHeaderFromMetafile(GpMetafile*,MetafileHeader*);
GpStatus WINGDIPAPI GdipGetHemfFromMetafile(GpMetafile*,HENHMETAFILE*);
GpStatus WINGDIPAPI GdipCreateStreamOnFile(GDIPCONST WCHAR*,UINT,IStream**);
GpStatus WINGDIPAPI GdipCreateMetafileFromWmf(HMETAFILE,BOOL,GDIPCONST WmfPlaceableFileHeader*,GpMetafile**);
GpStatus WINGDIPAPI GdipCreateMetafileFromEmf(HENHMETAFILE,BOOL,GpMetafile**);
GpStatus WINGDIPAPI GdipCreateMetafileFromFile(GDIPCONST WCHAR*,GpMetafile**);
GpStatus WINGDIPAPI GdipCreateMetafileFromWmfFile(GDIPCONST WCHAR*,GDIPCONST WmfPlaceableFileHeader*,GpMetafile**);
GpStatus WINGDIPAPI GdipCreateMetafileFromStream(IStream*,GpMetafile**);
GpStatus WINGDIPAPI GdipRecordMetafile(HDC,EmfType,GDIPCONST GpRectF*,MetafileFrameUnit,GDIPCONST WCHAR*,GpMetafile**);
GpStatus WINGDIPAPI GdipRecordMetafileI(HDC,EmfType,GDIPCONST GpRect*,MetafileFrameUnit,GDIPCONST WCHAR*,GpMetafile**);
GpStatus WINGDIPAPI GdipRecordMetafileFileName(GDIPCONST WCHAR*,HDC,EmfType,GDIPCONST GpRectF*,MetafileFrameUnit,GDIPCONST WCHAR*,GpMetafile**);
GpStatus WINGDIPAPI GdipRecordMetafileFileNameI(GDIPCONST WCHAR*,HDC,EmfType,GDIPCONST GpRect*,MetafileFrameUnit,GDIPCONST WCHAR*,GpMetafile**);
GpStatus WINGDIPAPI GdipRecordMetafileStream(IStream*,HDC,EmfType,GDIPCONST GpRectF*,MetafileFrameUnit,GDIPCONST WCHAR*,GpMetafile**);
GpStatus WINGDIPAPI GdipRecordMetafileStreamI(IStream*,HDC,EmfType,GDIPCONST GpRect*,MetafileFrameUnit,GDIPCONST WCHAR*,GpMetafile**);
GpStatus WINGDIPAPI GdipPlayMetafileRecord(GDIPCONST GpMetafile*,EmfPlusRecordType,UINT,UINT,GDIPCONST BYTE*);
GpStatus WINGDIPAPI GdipSetMetafileDownLevelRasterizationLimit(GpMetafile*,UINT);
GpStatus WINGDIPAPI GdipGetMetafileDownLevelRasterizationLimit(GDIPCONST GpMetafile*,UINT*);
GpStatus WINGDIPAPI GdipConvertToEmfPlus(GDIPCONST GpGraphics*,GpMetafile*,BOOL*,EmfType,GDIPCONST WCHAR*,GpMetafile**);
GpStatus WINGDIPAPI GdipConvertToEmfPlusToFile(GDIPCONST GpGraphics*,GpMetafile*,BOOL*,GDIPCONST WCHAR*,EmfType,GDIPCONST WCHAR*,GpMetafile**);
GpStatus WINGDIPAPI GdipConvertToEmfPlusToStream(GDIPCONST GpGraphics*,GpMetafile*,BOOL*,IStream*,EmfType,GDIPCONST WCHAR*,GpMetafile**);
UINT WINGDIPAPI GdipEmfToWmfBits(HENHMETAFILE,UINT,LPBYTE,INT,INT);

/* PathGradientBrush functions */
GpStatus WINGDIPAPI GdipCreatePathGradient(GDIPCONST GpPointF*,INT,GpWrapMode,GpPathGradient**);
GpStatus WINGDIPAPI GdipCreatePathGradientI(GDIPCONST GpPoint*,INT,GpWrapMode,GpPathGradient**);
GpStatus WINGDIPAPI GdipCreatePathGradientFromPath(GDIPCONST GpPath*,GpPathGradient**);
GpStatus WINGDIPAPI GdipGetPathGradientCenterColor(GpPathGradient*,ARGB*);
GpStatus WINGDIPAPI GdipSetPathGradientCenterColor(GpPathGradient*,ARGB);
GpStatus WINGDIPAPI GdipGetPathGradientSurroundColorsWithCount(GpPathGradient*,ARGB*,INT*);
GpStatus WINGDIPAPI GdipSetPathGradientSurroundColorsWithCount(GpPathGradient*,GDIPCONST ARGB*,INT*);
GpStatus WINGDIPAPI GdipGetPathGradientPath(GpPathGradient*,GpPath*);
GpStatus WINGDIPAPI GdipSetPathGradientPath(GpPathGradient*,GDIPCONST GpPath*);
GpStatus WINGDIPAPI GdipGetPathGradientCenterPoint(GpPathGradient*,GpPointF*);
GpStatus WINGDIPAPI GdipGetPathGradientCenterPointI(GpPathGradient*,GpPoint*);
GpStatus WINGDIPAPI GdipSetPathGradientCenterPoint(GpPathGradient*,GDIPCONST GpPointF*);
GpStatus WINGDIPAPI GdipSetPathGradientCenterPointI(GpPathGradient*,GDIPCONST GpPoint*);
GpStatus WINGDIPAPI GdipGetPathGradientRect(GpPathGradient*,GpRectF*);
GpStatus WINGDIPAPI GdipGetPathGradientRectI(GpPathGradient*,GpRect*);
GpStatus WINGDIPAPI GdipGetPathGradientPointCount(GpPathGradient*,INT*);
GpStatus WINGDIPAPI GdipGetPathGradientSurroundColorCount(GpPathGradient*,INT*);
GpStatus WINGDIPAPI GdipSetPathGradientGammaCorrection(GpPathGradient*,BOOL);
GpStatus WINGDIPAPI GdipGetPathGradientGammaCorrection(GpPathGradient*,BOOL*);
GpStatus WINGDIPAPI GdipGetPathGradientBlendCount(GpPathGradient*,INT*);
GpStatus WINGDIPAPI GdipGetPathGradientBlend(GpPathGradient*,REAL*,REAL*,INT);
GpStatus WINGDIPAPI GdipSetPathGradientBlend(GpPathGradient*,GDIPCONST REAL*,GDIPCONST REAL*,INT);
GpStatus WINGDIPAPI GdipGetPathGradientPresetBlendCount(GpPathGradient*,INT*);
GpStatus WINGDIPAPI GdipGetPathGradientPresetBlend(GpPathGradient*,ARGB*,REAL*,INT);
GpStatus WINGDIPAPI GdipSetPathGradientPresetBlend(GpPathGradient*,GDIPCONST ARGB*,GDIPCONST REAL*,INT);
GpStatus WINGDIPAPI GdipSetPathGradientSigmaBlend(GpPathGradient*,REAL,REAL);
GpStatus WINGDIPAPI GdipSetPathGradientLinearBlend(GpPathGradient*,REAL,REAL);
GpStatus WINGDIPAPI GdipGetPathGradientWrapMode(GpPathGradient*,GpWrapMode*);
GpStatus WINGDIPAPI GdipSetPathGradientWrapMode(GpPathGradient*,GpWrapMode);
GpStatus WINGDIPAPI GdipGetPathGradientTransform(GpPathGradient*,GpMatrix*);
GpStatus WINGDIPAPI GdipSetPathGradientTransform(GpPathGradient*,GpMatrix*);
GpStatus WINGDIPAPI GdipResetPathGradientTransform(GpPathGradient*);
GpStatus WINGDIPAPI GdipMultiplyPathGradientTransform(GpPathGradient*,GDIPCONST GpMatrix*,GpMatrixOrder);
GpStatus WINGDIPAPI GdipTranslatePathGradientTransform(GpPathGradient*,REAL,REAL,GpMatrixOrder);
GpStatus WINGDIPAPI GdipScalePathGradientTransform(GpPathGradient*,REAL,REAL,GpMatrixOrder);
GpStatus WINGDIPAPI GdipRotatePathGradientTransform(GpPathGradient*,REAL,GpMatrixOrder);
GpStatus WINGDIPAPI GdipGetPathGradientFocusScales(GpPathGradient*,REAL*,REAL*);
GpStatus WINGDIPAPI GdipSetPathGradientFocusScales(GpPathGradient*,REAL,REAL);

/* PathIterator functions */
GpStatus WINGDIPAPI GdipCreatePathIter(GpPathIterator**,GpPath*);
GpStatus WINGDIPAPI GdipDeletePathIter(GpPathIterator*);
GpStatus WINGDIPAPI GdipPathIterNextSubpath(GpPathIterator*,INT*,INT*,INT*,BOOL*);
GpStatus WINGDIPAPI GdipPathIterNextSubpathPath(GpPathIterator*,INT*,GpPath*,BOOL*);
GpStatus WINGDIPAPI GdipPathIterNextPathType(GpPathIterator*,INT*,BYTE*,INT*,INT*);
GpStatus WINGDIPAPI GdipPathIterNextMarker(GpPathIterator*,INT*,INT*,INT*);
GpStatus WINGDIPAPI GdipPathIterNextMarkerPath(GpPathIterator*,INT*,GpPath*);
GpStatus WINGDIPAPI GdipPathIterGetCount(GpPathIterator*,INT*);
GpStatus WINGDIPAPI GdipPathIterGetSubpathCount(GpPathIterator*,INT*);
GpStatus WINGDIPAPI GdipPathIterIsValid(GpPathIterator*,BOOL*);
GpStatus WINGDIPAPI GdipPathIterHasCurve(GpPathIterator*,BOOL*);
GpStatus WINGDIPAPI GdipPathIterRewind(GpPathIterator*);
GpStatus WINGDIPAPI GdipPathIterEnumerate(GpPathIterator*,INT*,GpPointF*,BYTE*,INT);
GpStatus WINGDIPAPI GdipPathIterCopyData(GpPathIterator*,INT*,GpPointF*,BYTE*,INT,INT);

/* Pen functions */
GpStatus WINGDIPAPI GdipCreatePen1(ARGB,REAL,GpUnit,GpPen**);
GpStatus WINGDIPAPI GdipCreatePen2(GpBrush*,REAL,GpUnit,GpPen**);
GpStatus WINGDIPAPI GdipClonePen(GpPen*,GpPen**);
GpStatus WINGDIPAPI GdipDeletePen(GpPen*);
GpStatus WINGDIPAPI GdipSetPenWidth(GpPen*,REAL);
GpStatus WINGDIPAPI GdipGetPenWidth(GpPen*,REAL*);
GpStatus WINGDIPAPI GdipSetPenUnit(GpPen*,GpUnit);
GpStatus WINGDIPAPI GdipGetPenUnit(GpPen*,GpUnit*);
GpStatus WINGDIPAPI GdipSetPenLineCap197819(GpPen*,GpLineCap,GpLineCap,GpDashCap);
GpStatus WINGDIPAPI GdipSetPenStartCap(GpPen*,GpLineCap);
GpStatus WINGDIPAPI GdipSetPenEndCap(GpPen*,GpLineCap);
GpStatus WINGDIPAPI GdipSetPenDashCap197819(GpPen*,GpDashCap);
GpStatus WINGDIPAPI GdipGetPenStartCap(GpPen*,GpLineCap*);
GpStatus WINGDIPAPI GdipGetPenEndCap(GpPen*,GpLineCap*);
GpStatus WINGDIPAPI GdipGetPenDashCap197819(GpPen*,GpDashCap*);
GpStatus WINGDIPAPI GdipSetPenLineJoin(GpPen*,GpLineJoin);
GpStatus WINGDIPAPI GdipGetPenLineJoin(GpPen*,GpLineJoin*);
GpStatus WINGDIPAPI GdipSetPenCustomStartCap(GpPen*,GpCustomLineCap*);
GpStatus WINGDIPAPI GdipGetPenCustomStartCap(GpPen*,GpCustomLineCap**);
GpStatus WINGDIPAPI GdipSetPenCustomEndCap(GpPen*,GpCustomLineCap*);
GpStatus WINGDIPAPI GdipGetPenCustomEndCap(GpPen*,GpCustomLineCap**);
GpStatus WINGDIPAPI GdipSetPenMiterLimit(GpPen*,REAL);
GpStatus WINGDIPAPI GdipGetPenMiterLimit(GpPen*,REAL*);
GpStatus WINGDIPAPI GdipSetPenMode(GpPen*,GpPenAlignment);
GpStatus WINGDIPAPI GdipGetPenMode(GpPen*,GpPenAlignment*);
GpStatus WINGDIPAPI GdipSetPenTransform(GpPen*,GpMatrix*);
GpStatus WINGDIPAPI GdipGetPenTransform(GpPen*,GpMatrix*);
GpStatus WINGDIPAPI GdipResetPenTransform(GpPen*);
GpStatus WINGDIPAPI GdipMultiplyPenTransform(GpPen*,GDIPCONST GpMatrix*,GpMatrixOrder);
GpStatus WINGDIPAPI GdipTranslatePenTransform(GpPen*,REAL,REAL,GpMatrixOrder);
GpStatus WINGDIPAPI GdipScalePenTransform(GpPen*,REAL,REAL,GpMatrixOrder);
GpStatus WINGDIPAPI GdipRotatePenTransform(GpPen*,REAL,GpMatrixOrder);
GpStatus WINGDIPAPI GdipSetPenColor(GpPen*,ARGB);
GpStatus WINGDIPAPI GdipGetPenColor(GpPen*,ARGB*);
GpStatus WINGDIPAPI GdipSetPenBrushFill(GpPen*,GpBrush*);
GpStatus WINGDIPAPI GdipGetPenBrushFill(GpPen*,GpBrush**);
GpStatus WINGDIPAPI GdipGetPenFillType(GpPen*,GpPenType*);
GpStatus WINGDIPAPI GdipGetPenDashStyle(GpPen*,GpDashStyle*);
GpStatus WINGDIPAPI GdipSetPenDashStyle(GpPen*,GpDashStyle);
GpStatus WINGDIPAPI GdipGetPenDashOffset(GpPen*,REAL*);
GpStatus WINGDIPAPI GdipSetPenDashOffset(GpPen*,REAL);
GpStatus WINGDIPAPI GdipGetPenDashCount(GpPen*,INT*);
GpStatus WINGDIPAPI GdipSetPenDashArray(GpPen*,GDIPCONST REAL*,INT);
GpStatus WINGDIPAPI GdipGetPenDashArray(GpPen*,REAL*,INT);
GpStatus WINGDIPAPI GdipGetPenCompoundCount(GpPen*,INT*);
GpStatus WINGDIPAPI GdipSetPenCompoundArray(GpPen*,GDIPCONST REAL*,INT);
GpStatus WINGDIPAPI GdipGetPenCompoundArray(GpPen*,REAL*,INT);

/* Region functions */
GpStatus WINGDIPAPI GdipCreateRegion(GpRegion**);
GpStatus WINGDIPAPI GdipCreateRegionRect(GDIPCONST GpRectF*,GpRegion**);
GpStatus WINGDIPAPI GdipCreateRegionRectI(GDIPCONST GpRect*,GpRegion**);
GpStatus WINGDIPAPI GdipCreateRegionPath(GpPath*,GpRegion**);
GpStatus WINGDIPAPI GdipCreateRegionRgnData(GDIPCONST BYTE*,INT,GpRegion**);
GpStatus WINGDIPAPI GdipCreateRegionHrgn(HRGN,GpRegion**);
GpStatus WINGDIPAPI GdipCloneRegion(GpRegion*,GpRegion**);
GpStatus WINGDIPAPI GdipDeleteRegion(GpRegion*);
GpStatus WINGDIPAPI GdipSetInfinite(GpRegion*);
GpStatus WINGDIPAPI GdipSetEmpty(GpRegion*);
GpStatus WINGDIPAPI GdipCombineRegionRect(GpRegion*,GDIPCONST GpRectF*,CombineMode);
GpStatus WINGDIPAPI GdipCombineRegionRectI(GpRegion*,GDIPCONST GpRect*,CombineMode);
GpStatus WINGDIPAPI GdipCombineRegionPath(GpRegion*,GpPath*,CombineMode);
GpStatus WINGDIPAPI GdipCombineRegionRegion(GpRegion*,GpRegion*,CombineMode);
GpStatus WINGDIPAPI GdipTranslateRegion(GpRegion*,REAL,REAL);
GpStatus WINGDIPAPI GdipTranslateRegionI(GpRegion*,INT,INT);
GpStatus WINGDIPAPI GdipTransformRegion(GpRegion*,GpMatrix*);
GpStatus WINGDIPAPI GdipGetRegionBounds(GpRegion*,GpGraphics*,GpRectF*);
GpStatus WINGDIPAPI GdipGetRegionBoundsI(GpRegion*,GpGraphics*,GpRect*);
GpStatus WINGDIPAPI GdipGetRegionHRgn(GpRegion*,GpGraphics*,HRGN*);
GpStatus WINGDIPAPI GdipIsEmptyRegion(GpRegion*,GpGraphics*,BOOL*);
GpStatus WINGDIPAPI GdipIsInfiniteRegion(GpRegion*,GpGraphics*,BOOL*);
GpStatus WINGDIPAPI GdipIsEqualRegion(GpRegion*,GpRegion*,GpGraphics*,BOOL*);
GpStatus WINGDIPAPI GdipGetRegionDataSize(GpRegion*,UINT*);
GpStatus WINGDIPAPI GdipGetRegionData(GpRegion*,BYTE*,UINT,UINT*);
GpStatus WINGDIPAPI GdipIsVisibleRegionPoint(GpRegion*,REAL,REAL,GpGraphics*,BOOL*);
GpStatus WINGDIPAPI GdipIsVisibleRegionPointI(GpRegion*,INT,INT,GpGraphics*,BOOL*);
GpStatus WINGDIPAPI GdipIsVisibleRegionRect(GpRegion*,REAL,REAL,REAL,REAL,GpGraphics*,BOOL*);
GpStatus WINGDIPAPI GdipIsVisibleRegionRectI(GpRegion*,INT,INT,INT,INT,GpGraphics*,BOOL*);
GpStatus WINGDIPAPI GdipGetRegionScansCount(GpRegion*,UINT*,GpMatrix*);
GpStatus WINGDIPAPI GdipGetRegionScans(GpRegion*,GpRectF*,INT*,GpMatrix*);
GpStatus WINGDIPAPI GdipGetRegionScansI(GpRegion*,GpRect*,INT*,GpMatrix*);

/* SolidBrush functions */
GpStatus WINGDIPAPI GdipCreateSolidFill(ARGB,GpSolidFill**);
GpStatus WINGDIPAPI GdipSetSolidFillColor(GpSolidFill*,ARGB);
GpStatus WINGDIPAPI GdipGetSolidFillColor(GpSolidFill*,ARGB*);

/* StringFormat functions */
GpStatus WINGDIPAPI GdipCreateStringFormat(INT,LANGID,GpStringFormat**);
GpStatus WINGDIPAPI GdipStringFormatGetGenericDefault(GpStringFormat**);
GpStatus WINGDIPAPI GdipStringFormatGetGenericTypographic(GpStringFormat**);
GpStatus WINGDIPAPI GdipDeleteStringFormat(GpStringFormat*);
GpStatus WINGDIPAPI GdipCloneStringFormat(GDIPCONST GpStringFormat*,GpStringFormat**);
GpStatus WINGDIPAPI GdipSetStringFormatFlags(GpStringFormat*,INT);
GpStatus WINGDIPAPI GdipGetStringFormatFlags(GDIPCONST GpStringFormat*,INT*);
GpStatus WINGDIPAPI GdipSetStringFormatAlign(GpStringFormat*,StringAlignment);
GpStatus WINGDIPAPI GdipGetStringFormatAlign(GDIPCONST GpStringFormat*,StringAlignment*);
GpStatus WINGDIPAPI GdipSetStringFormatLineAlign(GpStringFormat*,StringAlignment);
GpStatus WINGDIPAPI GdipGetStringFormatLineAlign(GDIPCONST GpStringFormat*,StringAlignment*);
GpStatus WINGDIPAPI GdipSetStringFormatTrimming(GpStringFormat*,StringTrimming);
GpStatus WINGDIPAPI GdipGetStringFormatTrimming(GDIPCONST GpStringFormat*,StringTrimming*);
GpStatus WINGDIPAPI GdipSetStringFormatHotkeyPrefix(GpStringFormat*,INT);
GpStatus WINGDIPAPI GdipGetStringFormatHotkeyPrefix(GDIPCONST GpStringFormat*,INT*);
GpStatus WINGDIPAPI GdipSetStringFormatTabStops(GpStringFormat*,REAL,INT,GDIPCONST REAL*);
GpStatus WINGDIPAPI GdipGetStringFormatTabStops(GDIPCONST GpStringFormat*,INT,REAL*,REAL*);
GpStatus WINGDIPAPI GdipGetStringFormatTabStopCount(GDIPCONST GpStringFormat*,INT*);
GpStatus WINGDIPAPI GdipSetStringFormatDigitSubstitution(GpStringFormat*,LANGID,StringDigitSubstitute);
GpStatus WINGDIPAPI GdipGetStringFormatDigitSubstitution(GDIPCONST GpStringFormat*,LANGID*,StringDigitSubstitute*);
GpStatus WINGDIPAPI GdipGetStringFormatMeasurableCharacterRangeCount(GDIPCONST GpStringFormat*,INT*);
GpStatus WINGDIPAPI GdipSetStringFormatMeasurableCharacterRanges(GpStringFormat*,INT,GDIPCONST CharacterRange*);

/* Text functions */
GpStatus WINGDIPAPI GdipDrawString(GpGraphics*,GDIPCONST WCHAR*,INT,GDIPCONST GpFont*,GDIPCONST RectF*,GDIPCONST GpStringFormat*,GDIPCONST GpBrush*);
GpStatus WINGDIPAPI GdipMeasureString(GpGraphics*,GDIPCONST WCHAR*,INT,GDIPCONST GpFont*,GDIPCONST RectF*,GDIPCONST GpStringFormat*,RectF*,INT*,INT*);
#ifdef __cplusplus
GpStatus WINGDIPAPI GdipMeasureCharacterRanges(GpGraphics*,GDIPCONST WCHAR*,INT,GDIPCONST GpFont*,GDIPCONST RectF&,GDIPCONST GpStringFormat*,INT,GpRegion**);
#endif
GpStatus WINGDIPAPI GdipDrawDriverString(GpGraphics*,GDIPCONST UINT16*,INT,GDIPCONST GpFont*,GDIPCONST GpBrush*,GDIPCONST PointF*,INT,GDIPCONST GpMatrix*);
GpStatus WINGDIPAPI GdipMeasureDriverString(GpGraphics*,GDIPCONST UINT16*,INT,GDIPCONST GpFont*,GDIPCONST PointF*,INT,GDIPCONST GpMatrix*,RectF*);

/* TextureBrush functions */
GpStatus WINGDIPAPI GdipCreateTexture(GpImage*,GpWrapMode,GpTexture**);
GpStatus WINGDIPAPI GdipCreateTexture2(GpImage*,GpWrapMode,REAL,REAL,REAL,REAL,GpTexture**);
GpStatus WINGDIPAPI GdipCreateTexture2I(GpImage*,GpWrapMode,INT,INT,INT,INT,GpTexture**);
GpStatus WINGDIPAPI GdipCreateTextureIA(GpImage*,GDIPCONST GpImageAttributes*,REAL,REAL,REAL,REAL,GpTexture**);
GpStatus WINGDIPAPI GdipCreateTextureIAI(GpImage*,GDIPCONST GpImageAttributes*,INT,INT,INT,INT,GpTexture**);
GpStatus WINGDIPAPI GdipGetTextureTransform(GpTexture*,GpMatrix*);
GpStatus WINGDIPAPI GdipSetTextureTransform(GpTexture*,GDIPCONST GpMatrix*);
GpStatus WINGDIPAPI GdipResetTextureTransform(GpTexture*);
GpStatus WINGDIPAPI GdipMultiplyTextureTransform(GpTexture*,GDIPCONST GpMatrix*,GpMatrixOrder);
GpStatus WINGDIPAPI GdipTranslateTextureTransform(GpTexture*,REAL,REAL,GpMatrixOrder);
GpStatus WINGDIPAPI GdipScaleTextureTransform(GpTexture*,REAL,REAL,GpMatrixOrder);
GpStatus WINGDIPAPI GdipRotateTextureTransform(GpTexture*,REAL,GpMatrixOrder);
GpStatus WINGDIPAPI GdipSetTextureWrapMode(GpTexture*,GpWrapMode);
GpStatus WINGDIPAPI GdipGetTextureWrapMode(GpTexture*,GpWrapMode*);
GpStatus WINGDIPAPI GdipGetTextureImage(GpTexture*,GpImage**);

/* uncategorized functions */
GpStatus WINGDIPAPI GdipTestControl(GpTestControlEnum,void*);

#endif /* __GDIPLUS_FLAT_H */

#endif // _GDIPLUSFLATC_H
