// WinFont.h: interface for the WinFont class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINFONT_H__71ABAA76_60D2_4243_9BD1_3D18C0A7BBE0__INCLUDED_)
#define AFX_WINFONT_H__71ABAA76_60D2_4243_9BD1_3D18C0A7BBE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class WinFont : public ::ca::graphics_object
{
	

public:
	static WinFont* PASCAL from_handle(HFONT hFont);

// Constructors
	WinFont();
	BOOL CreateFontIndirect(const LOGFONT* lpLogFont);
	BOOL CreateFont(int nHeight, int nWidth, int nEscapement,
			int nOrientation, int nWeight, BYTE bItalic, BYTE bUnderline,
			BYTE cStrikeOut, BYTE nCharSet, BYTE nOutPrecision,
			BYTE nClipPrecision, BYTE nQuality, BYTE nPitchAndFamily,
			const char * lpszFacename);
	BOOL CreatePointFont(int nPointSize, const char * lpszFaceName, ::ca::graphics * pgraphics = NULL);
	BOOL CreatePointFontIndirect(const LOGFONT* lpLogFont, ::ca::graphics * pgraphics = NULL);

// Attributes
	operator HFONT() const;
	int GetLogFont(LOGFONT* pLogFont);

// ementation
public:
	virtual ~WinFont();
#ifdef _DEBUG
	virtual void dump(dump_context & dumpcontext) const;
#endif
};

#endif // !defined(AFX_WINFONT_H__71ABAA76_60D2_4243_9BD1_3D18C0A7BBE0__INCLUDED_)
