/////////////////////////////////////////////////////////////////////////////
// Implementation of PrintPreview

class CLASS_DECL_ca preview_dc : public ::ca::graphics_sp
{
   

public:
   virtual void SetAttribDC(HDC hDC);  // Set the Attribute DC
   virtual void SetOutputDC(HDC hDC);

   virtual void ReleaseOutputDC();

// Constructors
   preview_dc();

// Implementation
public:
   virtual ~preview_dc();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   void SetScaleRatio(int nNumerator, int nDenominator);
   void SetTopLeftOffset(size top_left);
   void ClipToPage();

   // These conversion functions can be used without an output DC

   void PrinterDPtoScreenDP(LPPOINT lpPoint) const;

// Device-Context Functions
   virtual int SaveDC();
   virtual BOOL RestoreDC(int nSavedDC);

public:
   virtual ::ca::graphics_object* SelectStockObject(int nIndex);
   virtual ::ca::font* SelectObject(::ca::font* pFont);

// Drawing-Attribute Functions
   virtual COLORREF SetBkColor(COLORREF crColor);
   virtual COLORREF SetTextColor(COLORREF crColor);

// Mapping Functions
   virtual int SetMapMode(int nMapMode);
   virtual point SetViewportOrg(int x, int y);
   virtual point OffsetViewportOrg(int nWidth, int nHeight);
   virtual size SetViewportExt(int x, int y);
   virtual size ScaleViewportExt(int xNum, int xDenom, int yNum, int yDenom);
   virtual size SetWindowExt(int x, int y);
   virtual size ScaleWindowExt(int xNum, int xDenom, int yNum, int yDenom);

// Text Functions
   virtual BOOL TextOut(int x, int y, const char * lpszString, int nCount);
   virtual BOOL ExtTextOut(int x, int y, UINT nOptions, LPCRECT lpRect,
            const char * lpszString, UINT nCount, LPINT lpDxWidths);
   virtual size TabbedTextOut(int x, int y, const char * lpszString, int nCount,
            int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);
   virtual int _AFX_FUNCNAME(DrawText)(const char * lpszString, int nCount, LPRECT lpRect,
            UINT nFormat);
   virtual int _AFX_FUNCNAME(DrawTextEx)(LPTSTR lpszString, int nCount, LPRECT lpRect,
            UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);
#pragma push_macro("DrawText")
#pragma push_macro("DrawTextEx")
#undef DrawText
#undef DrawTextEx
   int DrawText(const char * lpszString, int nCount, LPRECT lpRect,
            UINT nFormat)
   {
      return _AFX_FUNCNAME(DrawText)(lpszString, nCount, lpRect, nFormat);
   }
   int DrawTextEx(LPTSTR lpszString, int nCount, LPRECT lpRect,
            UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
   {
      return _AFX_FUNCNAME(DrawTextEx)(lpszString, nCount, lpRect, nFormat, lpDTParams);
   }
#pragma pop_macro("DrawText")
#pragma pop_macro("DrawTextEx")
   virtual BOOL GrayString(::ca::brush* pBrush,
            BOOL (CALLBACK* lpfnOutput)(HDC, LPARAM, int),
               LPARAM lpData, int nCount,
               int x, int y, int nWidth, int nHeight);

// Printer Escape Functions
   virtual int Escape(int nEscape, int nCount, const char * lpszInData, LPVOID lpOutData);

// Implementation
protected:
   void MirrorMappingMode(BOOL bCompute);
   void MirrorViewportOrg();
   void MirrorFont();
   void MirrorAttributes();

   size ComputeDeltas(int& x, __in_z const char * lpszString, UINT& nCount, __in BOOL bTabbed,
               __in UINT nTabStops, __in_ecount(nTabStops) LPINT lpnTabStops, __in int nTabOrigin,
               __out_z LPTSTR lpszOutputString, int* pnDxWidths, int& nRightFixup);

protected:
   int m_nScaleNum;    // Scale ratio Numerator
   int m_nScaleDen;    // Scale ratio Denominator
   int m_nSaveDCIndex; // DC Save index when Screen DC Attached
   int m_nSaveDCDelta; // delta between Attrib and output restore indices
   size m_sizeTopLeft;// Offset for top left corner of page
   HFONT m_hFont;      // font selected into the screen DC (NULL if none)
   HFONT m_hPrinterFont; // font selected into the print DC

   size m_sizeWinExt; // cached ::ca::window extents computed for screen
   size m_sizeVpExt;  // cached viewport extents computed for screen
};


// Zoom States
#define ZOOM_OUT    0
#define ZOOM_MIDDLE 1
#define ZOOM_IN     2
