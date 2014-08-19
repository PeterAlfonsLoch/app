#include "framework.h"


namespace base
{


   uint32_t g_dwFirstTick = ::get_tick_count();


   log::log(sp(::axis::application) papp) :
      element(papp)
   {

#if defined(WINDOWSEX)
      m_bTrace          = ::file_exists_dup("C:\\core\\trace.txt") || ::is_debugger_attached();
#elif defined(METROWIN)
      m_bTrace          = ::file_exists_dup(::dir::appdata("trace.txt")) || ::is_debugger_attached();
#elif defined(LINUX)
      m_bTrace          = ::file_exists_dup("/etc/core/trace.txt") || ::is_debugger_attached();
#elif defined(ANDROID)
      m_bTrace = ::file_exists_dup("/etc/core/trace.txt") || ::is_debugger_attached();
#else
      m_bTrace          = ::file_exists_dup("/etc/core/trace.txt") || ::is_debugger_attached();
#endif

      m_pcsTrace        = new critical_section();
      m_pmutex          = new mutex(papp);
      m_ptrace          = new ::base::trace::trace(papp);
      m_pstraSeparator  = new stringa;
      m_pstrLogPath     = new string;
      m_pid             = new id;
      m_bLog            = true;

      m_pfile           = NULL;

      m_bInitialized    = false;



      m_iYear           = -1;
      m_iMonth          = -1;
      m_iDay            = -1;
      m_pstraSeparator->add("\r\n");
      m_pstraSeparator->add("\r");
      m_pstraSeparator->add("\n");

      set_trace_category(::base::trace::category_General, "category_General", 3000);
      set_trace_category(::base::trace::category_COM, "category_COM", 0);
      set_trace_category(::base::trace::category_QI, "category_QI", 0);
      set_trace_category(::base::trace::category_Registrar, "category_Registrar", 0);
      set_trace_category(::base::trace::category_Refcount, "category_Refcount", 0);
      set_trace_category(::base::trace::category_Windowing, "category_Windowing", 0);
      set_trace_category(::base::trace::category_Controls, "category_Controls", 0);
      set_trace_category(::base::trace::category_Hosting, "category_Hosting", 0);
      set_trace_category(::base::trace::category_DBClient, "category_DBClient", 0);
      set_trace_category(::base::trace::category_DBProvider, "category_DBProvider", 0);
      set_trace_category(::base::trace::category_Snapin, "category_Snapin", 0);
      set_trace_category(::base::trace::category_NotImpl, "category_NotImpl", 0);
      set_trace_category(::base::trace::category_Allocation, "category_Allocation", 0);
      set_trace_category(::base::trace::category_Exception, "category_Exception", 0);
      set_trace_category(::base::trace::category_Time, "category_Time", 0);
      set_trace_category(::base::trace::category_Cache, "category_Cache", 0);
      set_trace_category(::base::trace::category_Stencil, "category_Stencil", 0);
      set_trace_category(::base::trace::category_String, "category_String", 0);
      set_trace_category(::base::trace::category_Map, "category_Map", 0);
      set_trace_category(::base::trace::category_Util, "category_Util", 0);
      set_trace_category(::base::trace::category_Security, "category_Security", 0);
      set_trace_category(::base::trace::category_Sync, "category_Sync", 0);
      set_trace_category(::base::trace::category_ISAPI, "category_ISAPI", 0);

      set_trace_category(::base::trace::category_User, "category_User", 0);
      set_trace_category(::base::trace::category_User2, "category_User2", 0);
      set_trace_category(::base::trace::category_User3, "category_User3", 0);
      set_trace_category(::base::trace::category_User4, "category_User4", 0);


      set_trace_category(::base::trace::category_AppMsg, "AppMsg", 0);        // main message pump trace (includes DDE)
      set_trace_category(::base::trace::category_WinMsg , "category_WinMsg", 0);        // Windows message tracing
      set_trace_category(::base::trace::category_CmdRouting , "category_CmdRouting", 0);    // Windows command routing trace
      set_trace_category(::base::trace::category_Ole , "category_Ole", 0);          // special OLE callback trace
      set_trace_category(::base::trace::category_Database , "category_Database", 0);     // special database trace
      set_trace_category(::base::trace::category_Internet , "category_Internet", 0);     // special Internet client trace
      set_trace_category(::base::trace::category_dumpContext , "category_dumpContext", 0);   // traces from dump_context
      set_trace_category(::base::trace::category_Memory , "category_Memory", 0);      // generic non-kernel primitive::memory traces
      set_trace_category(::base::trace::category_Html , "category_Html", 0);         // Html traces
      set_trace_category(::base::trace::category_Socket , "category_Socket", 0);      // socket traces

   }

   log::~log()
   {
   }


//   extern sp(::axis::application) g_papp;

   CLASS_DECL_BASE int32_t SimpleDebugReport(int32_t iReportType, const char * pszFileName,int32_t iLine,const char *,const char * pszFormat, va_list list)
   {
      #ifdef WIN32

      if(iReportType == _CRT_ASSERT)
      {

         if(is_debugger_attached())
         {

            string str;

            str += "\r\nAssertion Failed \r\n";
            str += "File : ";
            str += pszFileName;
            str += "\r\nLine : ";
            str += ::str::from(iLine);
            str += "\r\n";

            string strCaption;

            strCaption = "Assertion Failed";

            OutputDebugStringW(wstring(str));
            /*if(simple_message_box(NULL, str, strCaption, MB_ICONINFORMATION | MB_OKCANCEL | MB_DEFBUTTON1) == IDCANCEL)
            {
               string strCmdLine = "\"C:\\Program Files (x86)\\Microsoft Visual Studio 11.0\\Common7\\IDE\\devenv.exe\" /edit \""+string(pszFileName)+ "\" /command \"edit.goto "+::str::from(iLine)+"\"";
               ::system(strCmdLine);
               exit(0);
            }
            */
         }



      }
      else
      {

         char buf[2048];
         vsnprintf_s(buf, sizeof(buf), sizeof(buf), pszFormat, list);
         OutputDebugStringW(wstring(buf));

      }

      #else
      vprintf(pszFormat, list);
      #endif
      return 0;
   }

   void log::set_extended_log(bool bSet)
   {
      m_bExtendedLog = bSet;
   }

   bool log::get_extended_log()
   {
      return m_bExtendedLog;
   }


   void log::success(const char * psz)
   {
      print(psz);
   }

   void log::trace_v(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * pszFormat, va_list args) const
   {

      if(!m_bTrace)
         return;

      string str;

      str.FormatV(pszFormat, args);

      trace_str(pszFileName, nLine, dwCategory, nLevel, str);

   }

   void log::trace_str(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * psz) const
   {

      if(!m_bTrace)
         return;

      UNREFERENCED_PARAMETER(nLevel);
      UNREFERENCED_PARAMETER(nLine);
      UNREFERENCED_PARAMETER(pszFileName);

      single_lock sl(((log *)this)->m_pcsTrace);

      //((log * )this)->print(pszFormat, args);
      //m_trace.TraceV(pszFileName, nLine, dwCategory, nLevel, pszFmt, args);

      sl.lock();
      log * plog = (log *) this;
      ::base::trace::category & category = plog->m_ptrace->m_map[dwCategory];
      if(category.m_estatus == ::base::trace::status_disabled || category.m_uiLevel > category.m_uiLevel)
         return;
      sl.unlock();
      stringa stra;
      stra.add_smallest_tokens(psz, *plog->m_pstraSeparator, FALSE);
      /*for(int32_t i = 0; i < stra.get_size(); i++)
      {
         if(stra[i].get_length() > 200)
         {
            string & strLine = stra[i];
            const char * psz = strLine;
            int32_t j = 200;
            while(*psz != NULL && j >= 0 && !::str::ch::is_space_char(psz))
            {
               j--;
               psz = ::str::utf8_inc(psz);
            }
            if(j <= 0)
               j = 200;
            stra.insert_at(i + 1, string(strLine, psz - (LPCSTR)strLine));
            stra[i] = stra[i].Left(j);
            continue;
         }
      }*/
      string strPre;
      ::datetime::time time;
      time = time.get_current_time();
      time.Format(strPre, "%Y-%m-%d %H:%M:%S");
      string strTick;
      strTick.Format(" %011d ", ::get_tick_count() - g_dwFirstTick);

      sl.lock();
      if(plog->m_pfile == NULL
      || plog->m_iYear != time.GetYear()
      || plog->m_iMonth != time.GetMonth()
      || plog->m_iDay != time.GetDay())
      {
         if(plog->m_pfile != NULL)
         {
            fflush(plog->m_pfile);
            fclose(plog->m_pfile);
            plog->m_pfile = NULL;
         }
         int32_t iRetry = 0;
         retry:
         string strRelative;
         time.Format(strRelative, "%Y/%m/%d");
         string strIndex;
         strIndex.Format("%05d", iRetry);
         *plog->m_pstrLogPath = ::dir::path(::get_sys_temp_path(), *m_pid, strRelative + "-" + strIndex + ".log");

         try
         {
            if(!::dir::is(::dir::name(*plog->m_pstrLogPath)))
            {
               ::dir::mk(::dir::name(*plog->m_pstrLogPath));
            }
            if(!(plog->m_pfile = fopen(*m_pstrLogPath, "at")))
            {
               int32_t iError = errno;
               if(iError == EAGAIN)
               {
               }
               iRetry++;
               if(iRetry >= 100000)
                  return;
               goto retry;
            }
         }
         catch(...)
         {
            try
            {
               if(plog->m_pfile)
               {
                  fclose(plog->m_pfile);
                  plog->m_pfile = NULL;
               }

               iRetry++;
               if(iRetry >= 100000)
                  return;
               goto retry;
            }
            catch(...)
            {
            }
         }
         plog->m_iYear     = time.GetYear();
         plog->m_iMonth    = time.GetMonth();
         plog->m_iDay      = time.GetDay();
         plog->print("<log>Starting Log</log>");
      }
      fseek(plog->m_pfile, 0, SEEK_END);
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         string strLine = strPre + strTick + stra[i] + "\r\n";
         try
         {
            ::OutputDebugStringW(::str::international::utf8_to_unicode(strLine));
            fputs(strLine, plog->m_pfile);
         }
         catch(::exception::exception &)
         {
            // Ignore exception here because this class/function is used for debugging
         }
      }

   }

/*   void log::trace_v(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const wchar_t * pszFmt, va_list args) const
   {
   }*/

/*   void log::set_trace_category(uint32_t dwCategory, const char * pszName, uint32_t uiLevel)
   {
   }*/

   void log::trace2(uint32_t dwCategory, UINT nLevel, const char * pszFormat, ...)
   {
      if(!m_bTrace)
         return;
      va_list ptr;
      va_start(ptr, pszFormat);
      trace_v(NULL, -1, dwCategory, nLevel, pszFormat, ptr);
      va_end(ptr);
   }



   void log::print(const char * pszFormat, ...)
   {
      va_list ptr;
      va_start(ptr, pszFormat);
      trace_v(NULL, -1, ::base::trace::category_General, 0, pszFormat, ptr);
      va_end(ptr);
   }

   bool log::initialize(const char * pszId)
   {
      return initialize(id(pszId));
   }

   bool log::initialize(id id)
   {
      single_lock sl(m_pmutex, TRUE);
      if(m_bInitialized)
         return false;
      //if(!::axis::log::initialize(id))
        // return false;
      *m_pid = id;
      m_bInitialized = true;
      if(file_exists_dup(::dir::appdata("debug.txt")))
      {
         string str = file_as_string_dup(::dir::appdata("debug.txt"));
         if(str.get_length() == 0 || str.Left(2).trim() != "0")
         {
            m_bLog = true;
         }
         else
         {
            m_bLog = false;
         }
      }
      else
      {
         m_bLog = is_debugger_attached();
      }
      sl.unlock();
      print("<log>Log Initialized!!</log>");
      return true;
   }

   bool log::finalize()
   {
      single_lock sl(m_pmutex, TRUE);
      if(!m_bInitialized)
         return false;
      bool bOk = ::axis::log::finalize();
      fclose(m_pfile);
      m_pfile = NULL;
      m_bInitialized = false;
      return bOk;
   }


/*   void log::trace_v(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * pszFormat, va_list args) const
   {
      if(!m_bTrace)
         return;
      UNREFERENCED_PARAMETER(nLevel);
      UNREFERENCED_PARAMETER(nLine);
      UNREFERENCED_PARAMETER(pszFileName);
      single_lock sl(&((log *)this)->m_csTrace, TRUE);

      //((log * )this)->print(pszFormat, args);
      //m_trace.TraceV(pszFileName, nLine, dwCategory, nLevel, pszFmt, args);
      log * plog = (log *) this;
      ::base::trace::category & category = plog->m_trace.m_map[dwCategory];
      if(category.m_estatus == ::base::trace::status_disabled || category.m_uiLevel > category.m_uiLevel)
         return;
      string str;
      str.FormatV(pszFormat, args);
      va_end(args);
      stringa stra;
      stra.add_smallest_tokens(str, plog->m_straSeparator, FALSE);
      /*for(int32_t i = 0; i < stra.get_size(); i++)
      {
         if(stra[i].get_length() > 200)
         {
            string & strLine = stra[i];
            const char * psz = strLine;
            int32_t j = 200;
            while(*psz != NULL && j >= 0 && !::str::ch::is_space_char(psz))
            {
               j--;
               psz = ::str::utf8_inc(psz);
            }
            if(j <= 0)
               j = 200;
            stra.insert_at(i + 1, string(strLine, psz - (LPCSTR)strLine));
            stra[i] = stra[i].Left(j);
            continue;
         }
      }*/
  /*    string strPre;
      ::datetime::time time;
      time = time.get_current_time();
      time.Format(strPre, "%Y-%m-%d %H:%M:%S");
      string strTick;
      strTick.Format(" %011d ", ::get_tick_count() - g_dwFirstTick);

      if(!plog->m_spfile->IsOpened()
      || plog->m_iYear != time.GetYear()
      || plog->m_iMonth != time.GetMonth()
      || plog->m_iDay != time.GetDay())
      {
         if(plog->m_spfile->IsOpened())
         {
            plog->m_spfile->flush();
            plog->m_spfile->close();
         }
         int32_t iRetry = 0;
         retry:
         string strRelative;
         time.Format(strRelative, "%Y/%m/%d");
         string strIndex;
         strIndex.Format("%05d", iRetry);
         plog->m_strLogPath = System.dir().path(
                           System.dir().time_log(m_id),
                           strRelative + "-" + strIndex + ".log");

         try
         {
            if(!plog->m_spfile->open(m_strLogPath, ::file::type_text
               | ::file::mode_write
               | ::file::share_deny_write | ::file::mode_create | ::file::mode_no_truncate
               | ::file::defer_create_directory))
            {
               if(plog->m_spfile->IsOpened())
               {
                  plog->m_spfile->close();
               }
               iRetry++;
               if(iRetry >= 100000)
                  return;
               goto retry;
            }
         }
         catch(...)
         {
            try
            {
               if(plog->m_spfile->IsOpened())
               {
                  plog->m_spfile->close();
               }
               iRetry++;
               if(iRetry >= 100000)
                  return;
               goto retry;
            }
            catch(...)
            {
            }
         }
         plog->m_iYear     = time.GetYear();
         plog->m_iMonth    = time.GetMonth();
         plog->m_iDay      = time.GetDay();
         plog->print("<log>Starting Log</log>");
      }
      plog->m_spfile->seek_to_end();
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         string strLine = strPre + strTick + stra[i] + "\r\n";
         try
         {
            ::OutputDebugStringW(::str::international::utf8_to_unicode(strLine));
            plog->m_spfile->write(strLine, strLine.get_length());
         }
         catch(::exception::exception &)
         {
            // Ignore exception here because this class/function is used for debugging
         }
      }
   }*/

   void log::set_trace_category(uint32_t dwCategory, const char * pszName, uint32_t uiLevel)
   {
      ::base::trace::category & category = m_ptrace->operator[](dwCategory);
      category.m_strCategory = pszName;
      category.m_dwCategory = dwCategory;
      category.m_uiLevel = uiLevel;
      category.m_estatus = uiLevel >= 1 ? ::base::trace::status_enabled : ::base::trace::status_disabled;
   }


   void log::trace(const char * pszFormat, ...)
   {
      if(this == NULL)
      {
         va_list ptr;
         va_start(ptr, pszFormat);
         vprintf(pszFormat, ptr);
         va_end(ptr);
         return;
      }
      if(!m_bTrace)
         return;
      va_list ptr;
      va_start(ptr, pszFormat);
      trace_v(NULL, -1, ::base::trace::category_General, 0, pszFormat, ptr);
      va_end(ptr);
   }

   /*void log::trace2(uint32_t dwCategory, UINT nLevel, const char * pszFormat, ...)
   {
      if(!m_bTrace)
         return;
      va_list ptr;
      va_start(ptr, pszFormat);
      trace_v(NULL, -1, dwCategory, nLevel, pszFormat, ptr);
      va_end(ptr);
   }*/

} // namespace core
