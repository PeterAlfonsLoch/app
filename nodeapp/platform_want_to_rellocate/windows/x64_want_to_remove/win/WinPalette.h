// WinPalette.h: interface for the WinPalette class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINPALETTE_H__C4FF870C_6905_4364_ACFC_E5457C2E0028__INCLUDED_)
#define AFX_WINPALETTE_H__C4FF870C_6905_4364_ACFC_E5457C2E0028__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class WinPalette : public ::ca::graphics_object
{
	

public:
	static WinPalette* PASCAL from_handle(HPALETTE hPalette);

// Constructors
	WinPalette();
	BOOL CreatePalette(LPLOGPALETTE lpLogPalette);
	BOOL CreateHalftonePalette(::ca::graphics * pgraphics);

// Attributes
	operator HPALETTE() const;
	int GetEntryCount();
	UINT GetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
			LPPALETTEENTRY lpPaletteColors) const;
	UINT SetPaletteEntries(UINT nStartIndex, UINT nNumEntries,
			LPPALETTEENTRY lpPaletteColors);

// Operations
	void AnimatePalette(UINT nStartIndex, UINT nNumEntries,
			LPPALETTEENTRY lpPaletteColors);
	UINT GetNearestPaletteIndex(COLORREF crColor) const;
	BOOL ResizePalette(UINT nNumEntries);

// ementation
	virtual ~WinPalette();
};

#endif // !defined(AFX_WINPALETTE_H__C4FF870C_6905_4364_ACFC_E5457C2E0028__INCLUDED_)
