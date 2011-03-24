// WinBitmap.h: interface for the WinBitmap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINBITMAP_H__AEDF5A2B_7E26_4728_8B84_2D1460924D68__INCLUDED_)
#define AFX_WINBITMAP_H__AEDF5A2B_7E26_4728_8B84_2D1460924D68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class WinBitmap : public ::ca::graphics_object
{
	

public:
	static WinBitmap* PASCAL from_handle(HBITMAP hBitmap);

// Constructors
	WinBitmap();

	BOOL LoadBitmap(const char * lpszResourceName);
	BOOL LoadBitmap(UINT nIDResource);
	BOOL LoadOEMBitmap(UINT nIDBitmap); // for OBM_/OCR_/OIC_
	BOOL LoadMappedBitmap(UINT nIDBitmap, UINT nFlags = 0,
		LPCOLORMAP lpColorMap = NULL, int nMapSize = 0);
	BOOL CreateBitmap(int nWidth, int nHeight, UINT nPlanes, UINT nBitcount,
			const void * lpBits);
	BOOL CreateBitmapIndirect(LPBITMAP lpBitmap);
	BOOL CreateCompatibleBitmap(::ca::graphics * pgraphics, int nWidth, int nHeight);
	BOOL CreateDiscardableBitmap(::ca::graphics * pgraphics, int nWidth, int nHeight);

// Attributes
	operator HBITMAP() const;
	int GetBitmap(BITMAP* pBitMap);

// Operations
	DWORD SetBitmapBits(DWORD dwCount, const void * lpBits);
	DWORD GetBitmapBits(DWORD dwCount, LPVOID lpBits) const;
	size SetBitmapDimension(int nWidth, int nHeight);
	size GetBitmapDimension() const;

// ementation
public:
	virtual ~WinBitmap();
#ifdef _DEBUG
	virtual void dump(dump_context & dumpcontext) const;
#endif
};

#endif // !defined(AFX_WINBITMAP_H__AEDF5A2B_7E26_4728_8B84_2D1460924D68__INCLUDED_)
