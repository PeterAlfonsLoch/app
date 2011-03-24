#pragma once

namespace whiteboard
{
   class http_thread;
   class registry;
   class document_template;

   class time;



   class CLASS_DECL_CA2_CUBE application :
      public vmsp::application
   {
   public:


      critical_section     m_csUserHour;


      application();

      bool WriteProfileTime(const char * lpszSection, const char * lpszEntry, const class time & time);
      bool GetProfileTime(const char * lpszSection, const char * lpszEntry, class time & time);
      
      bool SetProfileTime(class time & time, e_time etime);
      bool GetProfileTime(class time & time, e_time etime);

      int  GetSiteCount();
      site * GetSite(int iIndex);
      bool GetSiteTag(e_site esite, string & strUrl);
      bool GetSiteUrl(e_site esite, string & strUrl);
      void SetSiteUrl(e_site esite, const char * lpcszUrl);
      void GetBaseUrl(string &str);

   //   wb::command_handler & GetWbCommandHandler();
      http_thread & GetConnectionThread(void);
      document_template * m_ptemplate;

      registry & GetRegistry();

      virtual void construct();
      virtual bool bergedge_start();

   protected:
      registry *         m_pregistry;
      sites *           m_psites;
      http_thread *     m_pconnectionthread;
      //stringa               m_straSiteProfileKey;
      //stringa               m_straSiteTag;
      //stringa               m_straSiteDefaultUrl;
   //   wb::command_handler * m_pcommandhandler;

   public:

      public:
      virtual bool initialize_instance();

      afx_msg void _001OnFileNew();
      afx_msg void OnAppExit();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
         
   };

   inline registry & application::GetRegistry()
   { 
      return *m_pregistry; 
   }

} // namespace whiteboard
