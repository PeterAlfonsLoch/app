#pragma once

namespace whiteboard
{

   class options_view;
   class view;

   class CLASS_DECL_CA2_TESSERACT update_hint :
      public ::radix::object
   {
   public:
   //   // DECLARE_DYNCREATE(update_hint)
      enum e_type
      {
         TypeUserHour,
      };
      e_type         m_etype;
      user_hour::e_event  m_euserhourevent;
   };

   class CLASS_DECL_CA2_TESSERACT document : public html_document
   {
   public:
      document(::ca::application * papp);
   //   // DECLARE_DYNCREATE(document)

   // Attributes
   public:
      bool wb_create_file(string & strFile, const char * lpcszTopic);

      void GetUserHourDir(string & strDir);
      bool userhour_create_file(const char * lpcszPath, const char * lpcszTopic);
      void QueryUserHour(string & strPath, const char * lpcszQuery);
      void WriteUserHourFile(string & strPath, const char * lpcszQuery);
      void GetUserHourFilePath(string & strPath, const char * lpcszQuery);
      void GetSimpleQueryFilePath(string & strPath, const char * lpcszQuery);
      void SimpleQuery(string & strPath, const char * lpcszQuery);
      void WriteSimpleQueryFile(string & strPath, const char * lpcszQuery);

      bool GetUserHourFilePath(string & str);
      void OnBeforeNavigate2(html::data * pdata, var & varFile, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);

      enum EHint
      {
         HintUpdateCalendarTrayIcon  = 111,
         HintShowToolsOptions,
         HintShowHtmlView,
         HintUpdateFrameTitle,
         HintUpdateMrtsTrayIcon,
         HintUpdateMrtsQuerylistTrayIcon,
         HintShowMrts,
         HintShowCalendar,
        HintShowUserHour,
        HintShowBookmark,
        HintShowAnnotate,
         HintShowMrtsQuerylist,
         HintShowAbout,
         HintRefresh,
      };


      bool                    m_bRead;
      map_string_to_ptr         m_mapTargetHtmlView;
      bool                    m_bMrtsQuerylist;

   // Operations
   public:

   // Overrides
      // ClassWizard generated virtual function overrides
      //{{AFX_VIRTUAL(document)
      public:
      virtual BOOL on_new_document();
   //   virtual void Serialize(CArchive& ar);
      //}}AFX_VIRTUAL

   // Implementation
   public:
      void ShowCalendarTrayIcon(bool bShow);
      bool GetShowCalendarTrayIcon();
      void ShowMrtsTrayIcon(bool bShow);
      void SetShowableMrtsQuerylistTrayIcon(bool bShow);
      bool GetShowMrtsTrayIcon();
      bool GetShowMrtsQuerylistTrayIcon();
      bool GetShowableMrtsQuerylistTrayIcon();
      options_view * GetWbView();
      view * GetRootView();
      void GetUserOp(string &str);
      void GetUserPassword(string &str);
      void SetUserPassword(const char * lpcsz);
      bool GetUpHomeUrl(string & strUrl);
      void SetUpHomeUrl(const char * lpcszUrl);
      virtual ~document();
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   protected:

   // Generated message ::collection::map functions
   protected:
      //{{AFX_MSG(document)
         // NOTE - the ClassWizard will add and remove member functions here.
         //    DO NOT EDIT what you see in these blocks of generated code !
      //}}AFX_MSG
   //   ()

   public:
      void OnToolsOptions();
      void OnAppAbout();
   };

} // namespace whiteboard