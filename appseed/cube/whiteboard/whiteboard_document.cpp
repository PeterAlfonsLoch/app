#include "StdAfx.h"
#include <wincrypt.h>


// // BEGIN_MESSAGE_MAP(document, document)
   //{{AFX_MSG_MAP(document)
      // NOTE - the ClassWizard will add and remove mapping macros here.
      //    DO NOT EDIT what you see in these blocks of generated code!
   //}}AFX_MSG_MAP
/*   ON_COMMAND(ID_FILE_SEND_MAIL, on_file_send_mail)
   ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, on_update_file_send_mail)
   ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
   ON_COMMAND(ID_APP_ABOUT, OnAppAbout)*/
// // END_MESSAGE_MAP()


namespace whiteboard
{

   document::document(::ca::application * papp) :
      ca(papp),
      ::ca::data_container(papp),
      ::document(papp),
      ::userbase::document(papp),
      html_document(papp)
   {
      m_bMrtsQuerylist = false;
      m_bRead = false;

   }

   document::~document()
   {
   }

   BOOL document::on_new_document()
   {
      if (!html_document::on_new_document())
         return FALSE;

      return TRUE;
   }



   /////////////////////////////////////////////////////////////////////////////
   // document serialization

   /*
   void document::Serialize(CArchive& ar)
   {
      if (ar.IsStoring())
      {
         // TODO: add storing code here
      }
      else
      {
         // TODO: add loading code here
      }
   }
   */

   /////////////////////////////////////////////////////////////////////////////
   // document diagnostics

   #ifdef _DEBUG
   void document::assert_valid() const
   {
      ::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::document::dump(dumpcontext);
   }
   #endif //_DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // document commands

   bool document::GetUpHomeUrl(string & str)
   {
      str = Application.GetRegistry().m_propertysetSites["Up Home URL"];
      return true;
   }

   void document::SetUpHomeUrl(const char * lpcszUrl)
   {
      Application.GetRegistry().m_propertysetSites["Up Home URL"] = lpcszUrl;
      Application.GetRegistry().WriteFile();
   }

   options_view * document::GetWbView()
   {
      return get_typed_view < options_view > ();
   }  

   view * document::GetRootView()
   {
      return get_typed_view < view > ();
   }  

   void document::ShowCalendarTrayIcon(bool bShow)
   {
      int i = bShow ? 1: 0;
      System.WriteProfileInt(
         "0.1.0.10\\Options", 
         "Show Calendar Tray icon", 
         i);

      update_all_views(NULL, HintUpdateCalendarTrayIcon);

   }

   void document::SetShowableMrtsQuerylistTrayIcon(bool bShow)
   {
      int i = bShow ? 1: 0;
      System.WriteProfileInt(
         "0.1.0.10\\Options", 
         "Set Showable Calendar MRTS Query List icon", 
         i);

      update_all_views(NULL, HintUpdateMrtsQuerylistTrayIcon);

   }

   bool document::GetShowableMrtsQuerylistTrayIcon()
   {

      int i = System.GetProfileInt(
         "0.1.0.10\\Options", 
         "Set Showable Calendar MRTS Query List icon", 
         0);

      return i != 0 ? true : false;
   }

   bool document::GetShowCalendarTrayIcon()
   {

      int i = System.GetProfileInt(
         "0.1.0.10\\Options", 
         "Show Calendar Tray icon", 
         0);

      return i != 0 ? true : false;
   }

   void document::ShowMrtsTrayIcon(bool bShow)
   {
      int i = bShow ? 1: 0;
      System.WriteProfileInt(
         "0.1.0.10\\Options", 
         "Show MRTS Tray icon", 
         i);

      update_all_views(NULL, HintUpdateMrtsTrayIcon);

   }

   bool document::GetShowMrtsTrayIcon()
   {

      int i = System.GetProfileInt(
         "0.1.0.10\\Options", 
         "Show MRTS Tray icon", 
         0);

      return i != 0 ? true : false;
   }

   bool document::GetShowMrtsQuerylistTrayIcon()
   {
      return GetShowableMrtsQuerylistTrayIcon() && m_bMrtsQuerylist;
   }

   void document::GetUserOp(string &str)
   {
      str = System.GetProfileString("Options", "Nick", "");
   }


   void document::GetUserPassword(string &str) 
   {
      ASSERT(FALSE);
   /*   string strEnc;
      DWORD cbDataInput = 0;
      BYTE *pbDataInput = NULL;
      DATA_BLOB DataIn;
      DATA_BLOB DataOut;
      ex1::filesp spfile(get_app());
      string strFolder;
      ::SHGetSpecialFolderPath(NULL, strFolder.GetBufferSetLength(2048), CSIDL_LOCAL_APPDATA, TRUE);

      strFolder.ReleaseBuffer();
      strFolder += "\\whiteboard\\";

      if(!fs::defer_create_directory(strFolder))
      {
         System.simple_message_box("Cannot create application data folder!");;
         return;
      }

      string strPath;

      strPath = strFolder + "userdata1";

      if(!spfile->open(strPath, ::ex1::file::type_binary | ::ex1::file::mode_read))
      {
         return;
      }

      cbDataInput = spfile->get_length();
      pbDataInput =new BYTE[cbDataInput];


      spfile->read(pbDataInput, cbDataInput);

      spfile->close();

      

      //--------------------------------------------------------------------
      // Initialize the DataIn structure.

      DataIn.pbData = pbDataInput;    
      DataIn.cbData = cbDataInput;

      wchar_t * lpwsz = NULL;

      //--------------------------------------------------------------------
      //  Begin protect phase. Note that the encryption key is created
      //  by the function and is not passed.

      if(CryptUnprotectData(
           &DataIn,
           &lpwsz, // A description string
                                               // to be included with the
                                               // encrypted data. 
           NULL,                               // Optional entropy not used.
           NULL,                               // Reserved.
           NULL,                               // Pass NULL for the 
                                               // prompt structure.
           0,
           &DataOut))
      {
           TRACE("The encryption phase worked. \n");
      }
      else
      {
         System.simple_message_box("Encryption error! (1)");
      }

      delete [] pbDataInput;
      pbDataInput = NULL;

      LPTSTR lpsz = str.GetBufferSetLength(DataOut.cbData + 1);
      memcpy(lpsz, DataOut.pbData, DataOut.cbData);
      lpsz[DataOut.cbData] = 0;
      str.ReleaseBuffer();

      LocalFree(lpwsz);
      LocalFree(DataOut.pbData);*/
   }

   void document::SetUserPassword(const char * lpcsz) 
   {
      ASSERT(FALSE);
      /*
      string str(lpcsz);
      string strEnc;
      DWORD cbDataInput = 0;
      BYTE *pbDataInput = NULL;
      DATA_BLOB DataIn;
      DATA_BLOB DataOut;
      ex1::filesp spfile(get_app());
      string strFolder;
      ::SHGetSpecialFolderPath(NULL, strFolder.GetBufferSetLength(2048), CSIDL_LOCAL_APPDATA, TRUE);

      strFolder.ReleaseBuffer();
      strFolder += "\\whiteboard\\";

      if(!fs::defer_create_directory(strFolder))
      {
         System.simple_message_box("Cannot create application data folder!");;
         return;
      }


      

      //--------------------------------------------------------------------
      // Initialize the DataIn structure.

      DataIn.pbData = (BYTE *) lpcsz;    
      DataIn.cbData = _tcslen(lpcsz);

      wchar_t * lpwsz = NULL;

      //--------------------------------------------------------------------
      //  Begin protect phase. Note that the encryption key is created
      //  by the function and is not passed.

      if(CryptProtectData(
           &DataIn,
           L"", // A description string
                                               // to be included with the
                                               // encrypted data. 
           NULL,                               // Optional entropy not used.
           NULL,                               // Reserved.
           NULL,                               // Pass NULL for the 
                                               // prompt structure.
           0,
           &DataOut))
      {
           TRACE("The encryption phase worked. \n");
      }
      else
      {
         System.simple_message_box("Encryption error! (1)");
      }


      LPTSTR lpsz = str.GetBufferSetLength(DataOut.cbData + 1);
      memcpy(lpsz, DataOut.pbData, DataOut.cbData);
      lpsz[DataOut.cbData] = 0;
      str.ReleaseBuffer();

      string strPath;

      strPath = strFolder + "userdata1";

      if(!spfile->open(strPath, ::ex1::file::type_binary | ::ex1::file::mode_write | ::ex1::file::mode_create))
      {
         return;
      }

      cbDataInput = spfile->get_length();
      pbDataInput =new BYTE[cbDataInput];


      spfile->write(DataOut.pbData, DataOut.cbData);

      spfile->close();

      LocalFree(lpwsz);
      LocalFree(DataOut.pbData);*/
   }


   void document::OnToolsOptions()
   {
      update_all_views(NULL, HintShowToolsOptions);
   }

   void document::OnAppAbout()
   {
      update_all_views(NULL, HintShowAbout);
   }


   void document::OnBeforeNavigate2(html::data * pdata, const char * lpszUrl, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel)
   {
      string strUrl(lpszUrl);
      string strCmd(strUrl);
      string strUserHourUrl;

         GetUserHourDir(strUserHourUrl);


      if(gen::str::begins_eat_ci(strCmd, strUserHourUrl))
      {
         string strPath;
         userhour_create_file(lpszUrl, strCmd);
         //Navigate(strPath);
      }
      if(strCmd.Left(8) == "userhour")
      {
         userhour_create_file(System.dir().path(strUserHourUrl, strCmd), strCmd);
      }

   }

   void document::GetUserHourDir(string & strDir)
   {
      strDir = "C:\\Temp\\wb_userhour\\";
   }

   bool document::userhour_create_file(const char * lpcszPath, const char * lpcszTopic)
   {
      string strTopic(lpcszTopic);
      string strPath(lpcszPath);
      if(strTopic == "user_hour"
      || strTopic == "user_hour\\"
      || strTopic == "index.html")
      {
         QueryUserHour(strPath, "index");
      }
      else if(gen::str::begins_eat(strTopic, "userhour_")
         || gen::str::begins_eat(strTopic, "userhour_"))
      {
         QueryUserHour(strPath, strTopic);
      }
      return true;
   }

   void document::WriteSimpleQueryFile(string & strPath, const char * lpcszQuery)
   {
      ex1::text_file_sp spfile(get_app());
      string strQuery(lpcszQuery);
      string strTag;
      string str;

      spfile->open(strPath, ::ex1::file::type_text | ::ex1::file::mode_create
         | ::ex1::file::mode_write);

      if(strQuery == "about")
      {
         spfile->write_string("<html>");
         spfile->write_string("<head>");
         spfile->write_string("<title>");
         spfile->write_string("About whiteboard");
         spfile->write_string("</title>");
         spfile->write_string("</head>");
         spfile->write_string("<body style=\"font-family: Arial, sans-serif;\">");
         spfile->write_string("<h1>");
         spfile->write_string("About whiteboard");
         spfile->write_string("</h1>");
         spfile->write_string("Copyright (C) 2006");
         spfile->write_string("</body>");
      }
   }

   void document::WriteUserHourFile(string & strPath, const char * lpcszQuery)
   {
      ex1::text_file_sp spfile(get_app());
      string strQuery(lpcszQuery);
      string strTag;
      class time time;
      string str;


      spfile->open(strPath, ::ex1::file::type_text | ::ex1::file::mode_create
         | ::ex1::file::mode_write);

      string strUserHourFilePath;
      VERIFY(GetUserHourFilePath(strUserHourFilePath));

      user_hour::user_hour_set set(get_app());
      
      try
      {
         if(!set.LoadFile(strUserHourFilePath))
            goto ErrorFile;
      }
      catch(...)
      {
         goto ErrorFile;
      }
      spfile->write_string("<html>");
      spfile->write_string("<head>");
      spfile->write_string("<title>");
      spfile->write_string("User Hour");
      spfile->write_string("</title>");
      spfile->write_string("</head>");
      spfile->write_string("<body style=\"font-family: Arial, sans-serif;\">");
      spfile->write_string("<h1>");
      spfile->write_string("User Hour");
      spfile->write_string("</h1>");

      if(strQuery == "index")
      {

         for(int i = 0; i < set.m_montha.get_size(); i++)
         {
            strTag.Format("<a href=\"userhour_year=%d&month=%d\">", 
               set.m_montha.element_at(i).m_iYear, 
               set.m_montha.element_at(i).m_iMonth);
            spfile->write_string(strTag);
            spfile->write_string("<h2>");
            string strMonth;
            util::get_month_text(strMonth, set.m_montha.element_at(i).m_iMonth - 1);
            strTag.Format("%d %s", 
               set.m_montha.element_at(i).m_iYear, 
               strMonth);
            spfile->write_string(strTag);
            spfile->write_string("</h2>");
            spfile->write_string("</a>");

         }
         spfile->write_string("</body>");
      }
      else
      {
         gen::property_set map(get_app());
         map.parse_url_query(lpcszQuery);
         time.m_iYear = map["year"].get_value().get_integer(-1);
         time.m_iMonth = map["month"].get_value().get_integer(-1);

         user_hour::month * pmonth = set.FindMonth(time);
         if(pmonth != NULL)
         {
            spfile->write_string("<h2>");
            strTag.Format("Year %d month %d", 
            pmonth->m_iYear, 
            pmonth->m_iMonth);
            spfile->write_string(strTag);
            spfile->write_string("</h2>");
            spfile->write_string("<table>");
            spfile->write_string("<tbody>");
            spfile->write_string("<tr>");
            spfile->write_string("<td>");
            spfile->write_string("day");
            spfile->write_string("</td>");
            spfile->write_string("<td>");
            spfile->write_string("<span style=\"display: cell; background-color: #dddddd; margin-right: 0.75em; \">");
            spfile->write_string("<span style=\"font-size: 1.1em; font-weight: bold; color: #ffffff;\">");
            spfile->write_string("n: ");
            spfile->write_string("</span>");
            spfile->write_string("<span style=\"font-size: 1.1em; font-weight: bold; color: #aa7700;\">");
            spfile->write_string("open time");
            spfile->write_string("</span>");
            spfile->write_string(", ");
            spfile->write_string("Reason");
            spfile->write_string("<span style=\"font-size: 1.1em; font-weight: bold; color: #aa7700;\">");
            spfile->write_string("close time");
            spfile->write_string("</span>");
            spfile->write_string(", ");
            spfile->write_string("Reason");
            spfile->write_string("</span>");
            spfile->write_string("</td>");
            spfile->write_string("</tr>");
            for(int i = 0; i < pmonth->m_daya.get_size(); i++)
            {
               user_hour::day & day = pmonth->m_daya[i];
               spfile->write_string("<tr>");
               spfile->write_string("<td>");
               strTag.Format("%d", day.m_iDay);
               spfile->write_string(strTag);
               spfile->write_string("</td>");
               spfile->write_string("<td>");
               for(int j = 0; j < day.m_intervala.get_size(); j++)
               {
                  user_hour::interval & interval = day.m_intervala[j];
                  spfile->write_string("<span style=\"display: cell; background-color: #dddddd; margin-right: 0.75em; \">");
                  spfile->write_string("<span style=\"font-size: 1.1em; font-weight: bold; color: #ffffff;\">");
                  str.Format(" %d: ", j);
                  spfile->write_string(str);
                  spfile->write_string("</span>");
                  spfile->write_string("<span style=\"font-size: 1.1em; font-weight: bold; color: #aa7700;\">");
                  interval.m_timeStart.HourMinuteToString(str);
                  spfile->write_string(str);
                  spfile->write_string("</span>");
                  //reasonOpened;
                  str = (const char *) interval.m_varReasonOpened;
                  if(str == "Timer has opened interval.")
                  {
                     spfile->write_string(", ");
                     spfile->write_string("<span style=\"color: #55cc11;\">");
                     spfile->write_string("timer");
                     spfile->write_string("</span>");
                  }
                  else if(str == "Session Unlock")
                  {
                     spfile->write_string(", ");
                     spfile->write_string("<span style=\"color: #cc9933;\">");
                     spfile->write_string("unlock");
                     spfile->write_string("</span>");
                  }
                  else
                  {
                     spfile->write_string(", ");
                     spfile->write_string(str);
                  }
                  if(interval.m_bClosed)
                  {
                     spfile->write_string("<span style=\"font-size: 1.1em; font-weight: bold; color: #aa7700;\">");
                     interval.m_timeEnd.HourMinuteToString(str);
                     spfile->write_string(str);
                     spfile->write_string("</span>");
                     str = (const char *)  interval.m_varReasonClosed;
                     if(str == "Session Lock")
                     {
                        spfile->write_string(", ");
                        spfile->write_string("<span style=\"color: #cc9933;\">");
                        spfile->write_string("lock");
                        spfile->write_string("</span>");
                     }
                     else
                     {
                        spfile->write_string(", ");
                        spfile->write_string(str);
                     }
                  }
                  else
                  {
                     spfile->write_string(", ");
                     spfile->write_string("opened");
                  }
                  spfile->write_string("</span>");
               }
               spfile->write_string("</td>");
               spfile->write_string("</tr>");

            }
            spfile->write_string("</tbody>");
            spfile->write_string("</table>");
         }
         
      }

      return;
   ErrorFile:
         spfile->write_string("<html>");
         spfile->write_string("<head>");
         spfile->write_string("<title>");
         spfile->write_string("User Hour");
         spfile->write_string("</title>");
         spfile->write_string("</head>");
         spfile->write_string("<body>");
         spfile->write_string("<h1>");
         spfile->write_string("Failed to open User Hour spfile->");
         spfile->write_string("</h1>");
         spfile->write_string("<span style=\"color: #ff0000;\">");
         spfile->write_string("Try again later or contact administraddorz in DB.");
         spfile->write_string("</span>");
         spfile->write_string("</body>");
         return;
   }

   void document::QueryUserHour(string & strPath, const char * lpcszQuery)
   {
   //   GetUserHourFilePath(strPath, lpcszQuery);
      WriteUserHourFile(strPath, lpcszQuery);
   }




   bool document::wb_create_file(string & strPath, const char * lpcszTopic)
   {
      string strTopic(lpcszTopic);
      if(strTopic == "about" ||
         strTopic == "about/")
      {
         SimpleQuery(strPath, "about");
      }
      else if(strTopic == "user_hour"
      || strTopic == "user_hour/")
      {
         QueryUserHour(strPath, "index");
      }
      else if(gen::str::begins_eat(strTopic, "user_hour?")
         || gen::str::begins_eat(strTopic, "user_hour/?"))
      {
         QueryUserHour(strPath, strTopic);
      }
      return true;
   }

   void document::GetUserHourFilePath(string & strPath, const char * lpcszQuery)
   {
      GetUserHourDir(strPath);
      strPath += lpcszQuery;
      strPath += ".html";
      System.dir().mk(System.dir().name(strPath));
   }

   void document::GetSimpleQueryFilePath(string & strPath, const char * lpcszQuery)
   {
      strPath = "C:\\Temp\\wb_simplequery\\";
      DWORD dwFileAttributes = GetFileAttributes(strPath);
      if(dwFileAttributes == INVALID_FILE_ATTRIBUTES)
      {
         ::CreateDirectory(strPath, NULL);
      }
      strPath += lpcszQuery;
      strPath += ".html";
   }

   void document::SimpleQuery(string & strPath, const char * lpcszQuery)
   {
      GetSimpleQueryFilePath(strPath, lpcszQuery);
      WriteSimpleQueryFile(strPath, lpcszQuery);
   }




   bool document::GetUserHourFilePath(string & strPath)
   {
      string strFolder;
      strFolder = Application.dir().userappdata("whiteboard");
      if(!System.dir().mk(strFolder))
      {
         System.simple_message_box(NULL, "Cannot create application data folder!");;
         return false;
      }
      strPath = System.dir().path(strFolder, "user_hour.xml");
      return true;
   }

} // namespace whiteboard