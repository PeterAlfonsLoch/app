#pragma once


namespace whiteboard
{

   class document;

   class CLASS_DECL_CA2_TESSERACT html_view :
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
      LRESULT OnAfterDocumentComplete(WPARAM wparam, LPARAM lparam);
      virtual ~html_view();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      document * get_document();

      // Generated message ::collection::map functions
      //{{AFX_MSG(html_view)
      BOOL OnEraseBkgnd(::ca::graphics * pgraphics);
      void OnViewGoForward();
      void OnUpdateViewGoForward(cmd_ui * pcmdui);
      void OnViewGoUpHome();
      void OnViewGoWbHome();
      void OnViewGoBack();
      void OnUpdateViewGoBack(cmd_ui * pcmdui);
      void OnViewInIe();
      void OnViewRefresh();
      int OnCreate(LPCREATESTRUCT lpCreateStruct);
      void OnViewGoCalendar();
      DECL_GEN_SIGNAL(_001OnViewUserHour)
      DECL_GEN_SIGNAL(_001OnUpdateViewUserHour)
      DECL_GEN_SIGNAL(_001OnViewBookmark)
      DECL_GEN_SIGNAL(_001OnUpdateViewBookmark)
      DECL_GEN_SIGNAL(_001OnViewAnnotate)
      DECL_GEN_SIGNAL(_001OnUpdateViewAnnotate)
      LRESULT OnExMouseMessage(WPARAM wparam, LPARAM lparam);
      void Login(void);
      void WBNavigate(const char * lpcsz);
      virtual void OnBeforeNavigate2(var & varFile, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);
      void OnSize(UINT nType, int cx, int cy);
      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 
      virtual void OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel);
   };

} // namespace whiteboard
