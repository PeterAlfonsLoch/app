#pragma once


namespace whiteboard
{


   class http_thread;
   class registry;
   class document_template;

   class time;



   class CLASS_DECL_CA2_TESSERACT application :
      public ::veriedit::application
   {
   public:


      critical_section        m_csUserHour;
      registry *              m_pregistry;
      sites *                 m_psites;
      http_thread *           m_pconnectionthread;
      document_template *     m_ptemplate;


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

      http_thread & GetConnectionThread(void);

      registry & GetRegistry();

      virtual void construct();

      virtual bool initialize_instance();
      
      virtual void on_request(::ca::create_context * pcreatecontext);

         
   };

   inline registry & application::GetRegistry()
   { 
      return *m_pregistry; 
   }


} // namespace whiteboard


