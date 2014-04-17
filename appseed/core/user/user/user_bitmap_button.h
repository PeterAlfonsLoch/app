#pragma once

namespace user
{

   class bitmap_button :
      public button,
      public ::user::tool_tip_tool
   {
   public:
      bitmap_button(sp(base_application) papp);

      bool  m_bHover;            // set if cursor is over the button
      bool  m_bCommandEnable;    // set if command is enabled

      ::draw2d::bitmap m_bitmap;          // not pressed default bitmap
      ::draw2d::bitmap m_bitmapSel;       // pressed bitmap
      ::draw2d::bitmap m_bitmapFocus;     // focus bitmap
      ::draw2d::bitmap m_bitmapDisabled;  // disabled bitmap
      ::draw2d::bitmap m_bitmapHover;     // hover bitmap

#ifdef WINDOWS
      bool LoadBitmaps(UINT nIDBitmapResource,
         UINT nIDBitmapResourceSel = 0,
         UINT nIDBitmapResourceFocus = 0,
         UINT nIDBitmapResourceDisabled = 0,
         UINT nIDBitmapResourceHover = 0);
#endif

      bool LoadBitmaps(
         const char * lpszBitmapResource,
         const char * lpszBitmapResourceSel = NULL,
         const char * lpszBitmapResourceFocus = NULL,
         const char * lpszBitmapResourceDisabled = NULL,
         const char * lpszBitmapResourceHover = NULL);

      void UpdateHover();

      virtual void BaseToolTipGetRect(LPRECT lprect);
      virtual int32_t BaseToolTipGetIndex();

      virtual void install_message_handling(::message::dispatch * pinterface);
#ifdef WINDOWSEX
      virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
#endif
      virtual void pre_translate_message(signal_details * pobj);
      virtual void message_handler(signal_details * pobj);

      void ResizeToFit();
      virtual ~bitmap_button();

      DECL_GEN_SIGNAL(_001OnMouseMove);
   };

#ifdef WINDOWSEX
   inline bool bitmap_button::LoadBitmaps(UINT nIDBitmapResource,
       UINT nIDBitmapResourceSel, UINT nIDBitmapResourceFocus,
       UINT nIDBitmapResourceDisabled, UINT nIDBitmapResourceHover)
       { return LoadBitmaps(MAKEINTRESOURCE(nIDBitmapResource),
           MAKEINTRESOURCE(nIDBitmapResourceSel),
           MAKEINTRESOURCE(nIDBitmapResourceFocus),
           MAKEINTRESOURCE(nIDBitmapResourceDisabled),
         MAKEINTRESOURCE(nIDBitmapResourceHover)); }
#endif

} // namespace user
