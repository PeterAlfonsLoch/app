#pragma once


namespace userbase
{


   class CLASS_DECL_ca2 base_static :
      virtual public ::user::control
   {
   public:


      base_static(::ca::application * papp);
      virtual ~base_static();


      virtual bool create(::user::interaction* puiParent, id id);

      HICON SetIcon(HICON hIcon);
      HICON GetIcon();

      HENHMETAFILE SetEnhMetaFile(HENHMETAFILE hMetaFile);
      HENHMETAFILE GetEnhMetaFile();
      HBITMAP from(HBITMAP hBitmap);
      HBITMAP GetBitmap();
      HCURSOR SetCursor(HCURSOR hCursor);
      HCURSOR GetCursor();

#ifdef WINDOWS
      virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
#endif

      virtual BOOL OnChildNotify(UINT, WPARAM, LPARAM, LRESULT*);
   };


} // namespace userbase


