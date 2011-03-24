#include "StdAfx.h"

namespace whiteboard
{

    // BEGIN_MESSAGE_MAP(application, application)
      //{{AFX_MSG_MAP(application)
      
   /*   ON_COMMAND(ID_FILE_NEW, _001OnFileNew)
      ON_COMMAND(ID_APP_EXIT, OnAppExit)
      //}}AFX_MSG_MAP
      // Standard file based document commands
      ON_COMMAND(ID_FILE_NEW, application::_001OnFileNew)
      ON_COMMAND(ID_FILE_OPEN, application::on_file_open)
      // Standard print setup command
      ON_COMMAND(ID_FILE_PRINT_SETUP, application::OnFilePrintSetup)*/
    // END_MESSAGE_MAP()

   /////////////////////////////////////////////////////////////////////////////
   // application construction

   application::application()
   {
   }

   void application::construct()
   {
      m_strAppName         = "whiteboard";
      m_strBaseSupportId   = "votagus_ca2_whiteboard";
      m_strInstallToken    = "whiteboard";
      //m_strLicense         = "whiteboard";
      m_eexclusiveinstance = ::radix::ExclusiveInstanceLocal;
   }

   bool application::initialize_instance()
   {
      System.factory().cloneable_small < document >();
      System.factory().cloneable_small < whiteboard::main_frame >();
      System.factory().creatable_small < view >();
      System.factory().cloneable_small < html_view >();

      m_pregistry = new registry(this);
      m_psites = new sites;
      m_psites->add(
         site(
            SiteUpHomeUrl,
            "http://cur1303x/elmdb/index.php",
            "UpHomeURL",
            "Up Home URL"));

      m_psites->add(
         site(
            SiteHomeUrl,
            "http://whiteboard.veriwell.net/",
            "HomeURL",
            "Bookmark Home URL"));

      m_psites->add(
         site(
            SiteBookmark,
            "http://bookmark.veriwell.net/",
            "BookmarkURL",
            "Bookmark Home URL"));

      m_psites->add(
         site(
            SiteAnnotate,
            "http://annotate.veriwell.net/",
            "AnnotateURL",
            "Annotate Home URL"));

      m_psites->add(
         site(
            SiteNotifyUrl,
            "http://cur1303x/elmdb/whiteboard/wbapp/",
            "NotifyURL",
            "Notify URL"));

      m_psites->add(
         site(
            SiteCalendar,
            "http://cur1303x/elmdb/whiteboard/calendar.php",
            "CalendarURL",
            "Calendar URL"));

      m_psites->add(
         site(
            SiteLogin,
            "http://cur1303x/elmdb/whiteboard/login.php",
            "LoginURL",
            "Login URL"));

      m_psites->add(
         site(
            SitePulseUserEvent,
            "http://cur1303x/elmdb/whiteboard/pulseUserEvent.php",
            "PulseUserEventURL",
            "Pulse User Event URL"));

      m_psites->add(
         site(
            SiteDbHomeBaseUrl,
            "http://cur1303x/elmdb/",
            "DBHomeBaseURL",
            "DB Home Base URL"));

      m_psites->add(
         site(
            SiteWb,
            "http://wb.veriwell.net/more",
            "More",
            "More"));

      m_psites->add(
         site(
            SiteMrts,
            "http://mrtsserv.mch4.siemens.de/cgi-auth/MRTS/pgConnect",
            "MRTS",
            "MRTS"));

      m_pregistry->AddWhiteboardSitesProperties(*m_psites);


      if(!ca84::application::initialize_instance())
         return false;


      m_pconnectionthread = AfxBeginThread < http_thread > (get_app());

      ::CoInitialize(NULL);

      SetRegistryKey("Com EN PSY DB");

      //LoadStdProfileSettings();  // Load standard INI file options (including MRU)


      


      return true;
   }




   /////////////////////////////////////////////////////////////////////////////
   // application message handlers


   #define WM_INITIALUPDATE    0x0364
   void application::_001OnFileNew() 
   {

      ::document * pdocument  = m_ptemplate->open_document_file(NULL, FALSE);
   //   m_ptemplateHtml->add_document(pdocument);
      GetMainWnd()->SendMessageToDescendants(WM_INITIALUPDATE, 0, 0, TRUE, TRUE);

      
   }



   bool application::WriteProfileTime(const char * lpszSection, const char * lpszEntry, const class time &time)
   {
      string str;
      time.ToString(str);
      return System.WriteProfileString(lpszSection, lpszEntry, str) != FALSE;
   }


   bool application::GetProfileTime(const char * lpszSection, const char * lpszEntry, class time &time)
   {
      string str;
      str = System.GetProfileString(lpszSection, lpszEntry);
      return time.FromString(str);
   }

   bool application::SetProfileTime(class time & time, e_time etime)
   {
      string strEntry;
      strEntry.Format("%d", etime);
      return WriteProfileTime("time", strEntry, time);
   }

   bool application::GetProfileTime(class time & time, e_time etime)
   {
      string strEntry;
      strEntry.Format("%d", etime);
      if(!GetProfileTime("time", strEntry, time))
         return false;
      return true;
   }

   void application::OnAppExit() 
   {
      close_all_documents(TRUE);
      PostThreadMessage(WM_QUIT, 0, 0);
   }

   bool application::bergedge_start()
   {
      m_ptemplate = new document_template(this);
      ::document * pdoc = m_ptemplate->open_document_file(NULL, FALSE);
      ::view * pview = pdoc->get_view(0);
      SetMainWnd(pview->GetParentFrame());
      whiteboard::main_frame * pframe = dynamic_cast < whiteboard::main_frame * > (GetMainWnd());
      document * pwbdoc = dynamic_cast < document * > (pdoc);
      update_hint uh;
      uh.m_etype = update_hint::TypeUserHour;
      uh.m_euserhourevent = user_hour::event_start_application;
      pwbdoc->update_all_views(NULL, 0, &uh);
      return true;
   }




   int application::GetSiteCount()
   {
      return m_psites->get_count();
   }

   bool application::GetSiteTag(e_site esite, string & strTag)
   {
      site * psite = m_psites->get(esite);
      if(psite == NULL)
         return false;
      strTag = psite->m_strTag;
      return true;
   }

   bool application::GetSiteUrl(e_site esite, string & strUrl)
   {
      site * psite = m_psites->get(esite);
      if(psite == NULL)
         return false;
      registry * pregistry = &Application.GetRegistry();
      pregistry->LoadFile();
      strUrl = Application.GetRegistry().m_propertysetSites[psite->m_strProfileKey];
      return true;
   }

   void application::SetSiteUrl(e_site esite, const char * lpcszUrl)
   {
      site * psite = m_psites->get(esite);
      Application.GetRegistry().m_propertysetSites[psite->m_strProfileKey];
      Application.GetRegistry().WriteFile();
   }


   /*wb::command_handler & application::GetWbCommandHandler()
   {
      return *m_pcommandhandler;
   }
   */

   void application::GetBaseUrl(string &str)
   {
      GetSiteUrl(SiteNotifyUrl, str);
   }

   http_thread & application::GetConnectionThread(void)
   {
      return * m_pconnectionthread;
   }


   site * application::GetSite(int iIndex)
   {
      return m_psites->get_at(iIndex);
   }

   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
         
   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }


   site::site()
   {
   }

   site::site(
         e_site esite,
         const char * lpcszDefaultUrl,
         const char * lpcszProfileKey,
         const char * lpcszTag)
   {
      m_esite           = esite;
      m_strDefaultUrl   = lpcszDefaultUrl;
      m_strProfileKey   = lpcszProfileKey;
      m_strTag          = lpcszTag;
   }


   site * sites::get(e_site esite)
   {
      for(int i = 0; i < m_sitea.get_size(); i++)
      {
         if(m_sitea[i].m_esite == esite)
            return &m_sitea[i];
      }
      return NULL;
   }

   site * sites::get_at(int iIndex)
   {
      return &m_sitea[iIndex];
   }

   void sites::add(const site & site)
   {
      m_sitea.add(site);
   }

   int sites::get_count()
   {
      return m_sitea.get_size();
   }



} // namespace whiteboard