#pragma once


namespace userbase
{


   class CLASS_DECL_ca base_static : 
      public ::user::interaction
   {
   public:
      
      base_static(::ca::application * papp);
      virtual ~base_static();

      virtual BOOL create(const char * lpszText, DWORD dwStyle,
               const RECT& rect, ::user::interaction* pParentWnd, UINT nID = 0xffff);

      HICON SetIcon(HICON hIcon);
      HICON GetIcon();

      HENHMETAFILE SetEnhMetaFile(HENHMETAFILE hMetaFile);
      HENHMETAFILE GetEnhMetaFile();
      HBITMAP from(HBITMAP hBitmap);
      HBITMAP GetBitmap();
      HCURSOR SetCursor(HCURSOR hCursor);
      HCURSOR GetCursor();

      virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

      virtual BOOL OnChildNotify(UINT, WPARAM, LPARAM, LRESULT*);
   };


} // namespace userbase