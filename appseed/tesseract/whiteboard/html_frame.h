#pragma once

namespace whiteboard
{

   class CLASS_DECL_CA2_TESSERACT html_frame : public userbase::frame_window
   {
   public:

      toolbar    m_toolbarHtml;


      html_frame(::ca::application * papp);
      virtual ~html_frame();


      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);


      void OnClose();
      int OnCreate(LPCREATESTRUCT lpCreateStruct);
      void OnToolsOptions();
      void OnActivate(UINT nState, ::ca::window* pWndOther, BOOL bMinimized);


   };

} // namespace whiteboard