#pragma once


namespace whiteboard
{

   class document;

   class CLASS_DECL_CA2_CUBE html_view :
      public ::html_view
   {
   public:

      enum e_state
      {
         state_initial,
         state_login,
      };

      enum EMessageReceive
      {
         MessageHttpGet = WM_APP,
         MessageOnAfterDocumentComplete
      };

      DWORD          _dwROTcookie;
      e_state        m_estate;
      string         m_strAfterLogin;
      string         m_strUrl;
      bool           m_bSetTargetFrameName;
      string         m_strTargetFrameName;

      
      
      html_view(::ca::application * papp);




      void OpenNewInIe(const char * lpcszURL);



      virtual void on_document_complete(const char * lpszURL);
      afx_msg LRESULT OnAfterDocumentComplete(WPARAM wparam, LPARAM lparam);
      virtual ~html_view();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      document * get_document();

      // Generated message ::collection::map functions
      //{{AFX_MSG(html_view)
      afx_msg BOOL OnEraseBkgnd(::ca::graphics * pgraphics);
      afx_msg void OnViewGoForward();
      afx_msg void OnUpdateViewGoForward(cmd_ui * pcmdui);
      afx_msg void OnViewGoUpHome();
      afx_msg void OnViewGoWbHome();
      afx_msg void OnViewGoBack();
      afx_msg void OnUpdateViewGoBack(cmd_ui * pcmdui);
      afx_msg void OnViewInIe();
      afx_msg void OnViewRefresh();
      afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
      afx_msg void OnViewGoCalendar();
      DECL_GEN_SIGNAL(_001OnViewUserHour)
      DECL_GEN_SIGNAL(_001OnUpdateViewUserHour)
      DECL_GEN_SIGNAL(_001OnViewBookmark)
      DECL_GEN_SIGNAL(_001OnUpdateViewBookmark)
      DECL_GEN_SIGNAL(_001OnViewAnnotate)
      DECL_GEN_SIGNAL(_001OnUpdateViewAnnotate)
      afx_msg LRESULT OnExMouseMessage(WPARAM wparam, LPARAM lparam);
      void Login(void);
      void WBNavigate(const char * lpcsz);
      virtual void OnBeforeNavigate2(html::data * pdata, const char * lpszURL, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);
      afx_msg void OnSize(UINT nType, int cx, int cy);
      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 
      virtual void OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel);
   };

} // namespace whiteboard
