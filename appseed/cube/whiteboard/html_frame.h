#pragma once

namespace whiteboard
{

   class CLASS_DECL_CA2_CUBE html_frame : public userbase::frame_window
   {
   //   // DECLARE_DYNCREATE(html_frame)
   public:
      html_frame(::ca::application * papp);

   // Attributes
   public:
      //int                  m_iHistory;
      //int                  m_iHistoryMax;


      toolbar    m_toolbarHtml;

   // Operations
   public:

   // Overrides
      // ClassWizard generated virtual function overrides
      //{{AFX_VIRTUAL(html_frame)
      protected:
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      //}}AFX_VIRTUAL

   // Implementation
   protected:
      virtual ~html_frame();

      // Generated message ::collection::map functions
      //{{AFX_MSG(html_frame)
      afx_msg void OnClose();
      afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
      afx_msg void OnToolsOptions();
      afx_msg void OnActivate(UINT nState, ::ca::window* pWndOther, BOOL bMinimized);
      //}}AFX_MSG
      ()


   };

} // namespace whiteboard