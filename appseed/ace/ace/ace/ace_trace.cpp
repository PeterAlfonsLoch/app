//#include "framework.h"

/*
category traceMultiApp("MultiApp");
category traceAppMsg("AppMsg");
category traceWinMsg("WinMsg");
category traceCmdRouting("CmdRouting");
category traceOle("Ole");
category traceDatabase("Database");
category traceInternet("Internet");
category tracedumpContext("dump_context");
category traceMemory("Memory");
category traceGdi("GDI");
category traceUser("User");
category traceKernel("Kernel");
category traceHtml("HTML");
category traceSocket("socket");
*/


namespace ace
{

   namespace trace
   {
      typedef void ( * PFN_trace_v)(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * pszFmt, va_list args);
      CLASS_DECL_ACE void raw_trace_v(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * pszFmt, va_list args);
      CLASS_DECL_ACE PFN_trace_v trace_v = &raw_trace_v;

      /*   category::category( const char * pszCategoryName, UINT nStartingLevel ) throw() :
      m_dwCategory( 0 )
      {
      m_dwCategory = ::core::CTrace::s_trace.RegisterCategory( pszCategoryName );
      ::core::CTrace::s_trace.ChangeCategory( m_dwCategory, nStartingLevel, TRACESTATUS_INHERIT);
      }*/

      void trace::TraceV(const char *pszFileName, int32_t nLine, uint_ptr dwCategory, UINT nLevel, const char * pszFormat, va_list args) const
      {
         UNREFERENCED_PARAMETER(pszFileName);
         UNREFERENCED_PARAMETER(nLine);
         /*      const category *pCategory;
         trace_module * pmodule = NULL;
         static const int32_t nCount = 1024;
         CHAR szBuf[nCount] = {'\0'};
         int32_t nLen = 0;*/

         category & category = ((trace *) this)->m_map[(uint32_t ) dwCategory];

         //if(ShouldTraceOutput(dwModule, dwCategory, nLevel, &pCategory, &pmodule))
         if(category.m_estatus == ::ace::trace::status_disabled || nLevel > category.m_uiLevel)
            return;
         /*      if (nLen >= 0 && nLen < nCount)
         {
         if(g_Allocator.GetProcess()->m_bFileNameAndLineNo)
         {
         int32_t nTemp;
         C_RUNTIME_ERRORCHECK_SPRINTF(nTemp = _snprintf_s(szBuf + nLen, nCount - nLen, nCount - nLen - 1, "%s(%d) : ", pszFileName, nLine));
         if( nTemp < 0 )
         nLen = nCount;
         else
         nLen += nTemp;
         }
         }
         if (nLen >= 0 && nLen < nCount)
         {
         if(pCategory && g_Allocator.GetProcess()->m_bFuncAndCategoryNames)
         {
         int32_t nTemp;
         C_RUNTIME_ERRORCHECK_SPRINTF(nTemp = _snprintf_s(szBuf + nLen, nCount - nLen, nCount - nLen - 1, "%S: ", pCategory->Name()));
         if( nTemp < 0 )
         nLen = nCount;
         else
         nLen += nTemp;
         }
         }*/
         /*if (nLen >= 0 && nLen < nCount)
         {
         C_RUNTIME_ERRORCHECK_SPRINTF(_vsnprintf_s(szBuf + nLen, nCount - nLen, nCount - nLen - 1, pszFormat, ptr));
         }*/

         string str;

         str.FormatV(pszFormat, args);

         ::OutputDebugStringW(::str::international::utf8_to_unicode(str));

         /*if(pmodule != NULL)
         pmodule->DebugReport(_CRT_WARN, NULL, 0, NULL, pszFormat, ptr);
         else
         OutputDebugStringA(szBuf);*/
      }


      category::category()
      {
         m_uiLevel      = 3000;
         m_estatus      = status_enabled;
         m_dwCategory   = 0;
      }

      category::~category()
      {
      }


      void category::SetLevel( UINT nLevel ) throw()
      {
         m_uiLevel = nLevel;
      }

      e_status category::GetStatus() const throw()
      {
         return m_estatus;
      }

      void category::SetStatus( e_status eStatus ) throw()
      {
         m_estatus = eStatus;
      }


      category::operator uint32_t() const throw()
      {
         return( m_dwCategory );
      }

      UINT category::GetLevel() const throw()
      {
         return m_uiLevel;
      }

      CLASS_DECL_ACE void raw_trace_v(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * pszFmt, va_list args)
      {
         UNREFERENCED_PARAMETER(pszFileName);
         UNREFERENCED_PARAMETER(nLine);
         UNREFERENCED_PARAMETER(dwCategory);
         UNREFERENCED_PARAMETER(nLevel);

         string str;
         str.FormatV(pszFmt, args);
         ::OutputDebugStringW(::str::international::utf8_to_unicode(str));
      }

      /*CLASS_DECL_ACE void system_log_trace_v(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * pszFmt, va_list args)
      {
      System.log().trace_v(pszFileName, nLine, dwCategory, nLevel, pszFmt, args);
      }*/


   } // namespace trace

}  // namespace core





#define DEFINE_MESSAGE(wm)  { wm, #wm }


struct MAP_WM_MESSAGE
{


   UINT              nMsg;
   const char *      lpszMsg;


};




static const MAP_WM_MESSAGE allMessagesArray[] =
{
   DEFINE_MESSAGE(WM_CREATE),
   DEFINE_MESSAGE(WM_DESTROY),
   DEFINE_MESSAGE(WM_MOVE),
   DEFINE_MESSAGE(WM_SIZE),
   DEFINE_MESSAGE(WM_ACTIVATE),
   DEFINE_MESSAGE(WM_SETFOCUS),
   DEFINE_MESSAGE(WM_KILLFOCUS),
   DEFINE_MESSAGE(WM_ENABLE),
   DEFINE_MESSAGE(WM_SETREDRAW),
   DEFINE_MESSAGE(WM_SETTEXT),
   DEFINE_MESSAGE(WM_GETTEXT),
   DEFINE_MESSAGE(WM_GETTEXTLENGTH),
   DEFINE_MESSAGE(WM_PAINT),
   DEFINE_MESSAGE(WM_CLOSE),
   DEFINE_MESSAGE(WM_QUERYENDSESSION),
   DEFINE_MESSAGE(WM_QUIT),
   DEFINE_MESSAGE(WM_QUERYOPEN),
   DEFINE_MESSAGE(WM_ERASEBKGND),
   DEFINE_MESSAGE(WM_SYSCOLORCHANGE),
   DEFINE_MESSAGE(WM_ENDSESSION),
   DEFINE_MESSAGE(WM_SHOWWINDOW),
   DEFINE_MESSAGE(WM_CTLCOLORMSGBOX),
   DEFINE_MESSAGE(WM_CTLCOLOREDIT),
   DEFINE_MESSAGE(WM_CTLCOLORLISTBOX),
   DEFINE_MESSAGE(WM_CTLCOLORBTN),
   DEFINE_MESSAGE(WM_CTLCOLORDLG),
   DEFINE_MESSAGE(WM_CTLCOLORSCROLLBAR),
   DEFINE_MESSAGE(WM_CTLCOLORSTATIC),
   DEFINE_MESSAGE(WM_WININICHANGE),
   DEFINE_MESSAGE(WM_SETTINGCHANGE),
   DEFINE_MESSAGE(WM_DEVMODECHANGE),
   DEFINE_MESSAGE(WM_ACTIVATEAPP),
   DEFINE_MESSAGE(WM_FONTCHANGE),
   DEFINE_MESSAGE(WM_TIMECHANGE),
   DEFINE_MESSAGE(WM_CANCELMODE),
   DEFINE_MESSAGE(WM_SETCURSOR),
   DEFINE_MESSAGE(WM_MOUSEACTIVATE),
   DEFINE_MESSAGE(WM_CHILDACTIVATE),
   DEFINE_MESSAGE(WM_QUEUESYNC),
   DEFINE_MESSAGE(WM_GETMINMAXINFO),
   DEFINE_MESSAGE(WM_ICONERASEBKGND),
   DEFINE_MESSAGE(WM_NEXTDLGCTL),
   DEFINE_MESSAGE(WM_SPOOLERSTATUS),
   DEFINE_MESSAGE(WM_DRAWITEM),
   DEFINE_MESSAGE(WM_MEASUREITEM),
   DEFINE_MESSAGE(WM_DELETEITEM),
   DEFINE_MESSAGE(WM_VKEYTOITEM),
   DEFINE_MESSAGE(WM_CHARTOITEM),
   DEFINE_MESSAGE(WM_SETFONT),
   DEFINE_MESSAGE(WM_GETFONT),
   DEFINE_MESSAGE(WM_QUERYDRAGICON),
   DEFINE_MESSAGE(WM_COMPAREITEM),
   DEFINE_MESSAGE(WM_COMPACTING),
   DEFINE_MESSAGE(WM_NCCREATE),
   DEFINE_MESSAGE(WM_NCDESTROY),
   DEFINE_MESSAGE(WM_NCCALCSIZE),
   DEFINE_MESSAGE(WM_NCHITTEST),
   DEFINE_MESSAGE(WM_NCPAINT),
   DEFINE_MESSAGE(WM_NCACTIVATE),
   DEFINE_MESSAGE(WM_GETDLGCODE),
   DEFINE_MESSAGE(WM_NCMOUSEMOVE),
   DEFINE_MESSAGE(WM_NCLBUTTONDOWN),
   DEFINE_MESSAGE(WM_NCLBUTTONUP),
   DEFINE_MESSAGE(WM_NCLBUTTONDBLCLK),
   DEFINE_MESSAGE(WM_NCRBUTTONDOWN),
   DEFINE_MESSAGE(WM_NCRBUTTONUP),
   DEFINE_MESSAGE(WM_NCRBUTTONDBLCLK),
   DEFINE_MESSAGE(WM_NCMBUTTONDOWN),
   DEFINE_MESSAGE(WM_NCMBUTTONUP),
   DEFINE_MESSAGE(WM_NCMBUTTONDBLCLK),
   DEFINE_MESSAGE(WM_KEYDOWN),
   DEFINE_MESSAGE(WM_KEYUP),
   DEFINE_MESSAGE(WM_CHAR),
   DEFINE_MESSAGE(WM_DEADCHAR),
   DEFINE_MESSAGE(WM_SYSKEYDOWN),
   DEFINE_MESSAGE(WM_SYSKEYUP),
   DEFINE_MESSAGE(WM_SYSCHAR),
   DEFINE_MESSAGE(WM_SYSDEADCHAR),
   DEFINE_MESSAGE(WM_KEYLAST),
   DEFINE_MESSAGE(WM_INITDIALOG),
   DEFINE_MESSAGE(WM_COMMAND),
   DEFINE_MESSAGE(WM_SYSCOMMAND),
   DEFINE_MESSAGE(WM_TIMER),
   DEFINE_MESSAGE(WM_HSCROLL),
   DEFINE_MESSAGE(WM_VSCROLL),
   DEFINE_MESSAGE(WM_INITMENU),
   DEFINE_MESSAGE(WM_INITMENUPOPUP),
   DEFINE_MESSAGE(WM_MENUSELECT),
   DEFINE_MESSAGE(WM_MENUCHAR),
   DEFINE_MESSAGE(WM_ENTERIDLE),
   DEFINE_MESSAGE(WM_MOUSEWHEEL),
   DEFINE_MESSAGE(WM_MOUSEMOVE),
   DEFINE_MESSAGE(WM_LBUTTONDOWN),
   DEFINE_MESSAGE(WM_LBUTTONUP),
   DEFINE_MESSAGE(WM_LBUTTONDBLCLK),
   DEFINE_MESSAGE(WM_RBUTTONDOWN),
   DEFINE_MESSAGE(WM_RBUTTONUP),
   DEFINE_MESSAGE(WM_RBUTTONDBLCLK),
   DEFINE_MESSAGE(WM_MBUTTONDOWN),
   DEFINE_MESSAGE(WM_MBUTTONUP),
   DEFINE_MESSAGE(WM_MBUTTONDBLCLK),
   DEFINE_MESSAGE(WM_PARENTNOTIFY),
   DEFINE_MESSAGE(WM_MDICREATE),
   DEFINE_MESSAGE(WM_MDIDESTROY),
   DEFINE_MESSAGE(WM_MDIACTIVATE),
   DEFINE_MESSAGE(WM_MDIRESTORE),
   DEFINE_MESSAGE(WM_MDINEXT),
   DEFINE_MESSAGE(WM_MDIMAXIMIZE),
   DEFINE_MESSAGE(WM_MDITILE),
   DEFINE_MESSAGE(WM_MDICASCADE),
   DEFINE_MESSAGE(WM_MDIICONARRANGE),
   DEFINE_MESSAGE(WM_MDIGETACTIVE),
   DEFINE_MESSAGE(WM_MDISETMENU),
   DEFINE_MESSAGE(WM_CUT),
   DEFINE_MESSAGE(WM_COPYDATA),
   DEFINE_MESSAGE(WM_COPY),
   DEFINE_MESSAGE(WM_PASTE),
   DEFINE_MESSAGE(WM_CLEAR),
   DEFINE_MESSAGE(WM_UNDO),
   DEFINE_MESSAGE(WM_RENDERFORMAT),
   DEFINE_MESSAGE(WM_RENDERALLFORMATS),
   DEFINE_MESSAGE(WM_DESTROYCLIPBOARD),
   DEFINE_MESSAGE(WM_DRAWCLIPBOARD),
   DEFINE_MESSAGE(WM_PAINTCLIPBOARD),
   DEFINE_MESSAGE(WM_VSCROLLCLIPBOARD),
   DEFINE_MESSAGE(WM_SIZECLIPBOARD),
   DEFINE_MESSAGE(WM_ASKCBFORMATNAME),
   DEFINE_MESSAGE(WM_CHANGECBCHAIN),
   DEFINE_MESSAGE(WM_HSCROLLCLIPBOARD),
   DEFINE_MESSAGE(WM_QUERYNEWPALETTE),
   DEFINE_MESSAGE(WM_PALETTEISCHANGING),
   DEFINE_MESSAGE(WM_PALETTECHANGED),
   /*   DEFINE_MESSAGE(WM_DDE_INITIATE),
   DEFINE_MESSAGE(WM_DDE_TERMINATE),
   DEFINE_MESSAGE(WM_DDE_ADVISE),
   DEFINE_MESSAGE(WM_DDE_UNADVISE),
   DEFINE_MESSAGE(WM_DDE_ACK),
   DEFINE_MESSAGE(WM_DDE_DATA),
   DEFINE_MESSAGE(WM_DDE_REQUEST),
   DEFINE_MESSAGE(WM_DDE_POKE),
   DEFINE_MESSAGE(WM_DDE_EXECUTE),*/
   DEFINE_MESSAGE(WM_DROPFILES),
   DEFINE_MESSAGE(WM_POWER),
   DEFINE_MESSAGE(WM_WINDOWPOSCHANGED),
   DEFINE_MESSAGE(WM_WINDOWPOSCHANGING),
   // ca2 API specific messages
   DEFINE_MESSAGE(WM_SIZEPARENT),
   DEFINE_MESSAGE(WM_SETMESSAGESTRING),
   DEFINE_MESSAGE(WM_IDLEUPDATECMDUI),
   DEFINE_MESSAGE(WM_INITIALUPDATE),
   DEFINE_MESSAGE(WM_COMMANDHELP),
   DEFINE_MESSAGE(WM_HELPHITTEST),
   DEFINE_MESSAGE(WM_EXITHELPMODE),
   DEFINE_MESSAGE(WM_HELP),
   DEFINE_MESSAGE(WM_NOTIFY),
   DEFINE_MESSAGE(WM_CONTEXTMENU),
   DEFINE_MESSAGE(WM_TCARD),
   DEFINE_MESSAGE(WM_MDIREFRESHMENU),
   DEFINE_MESSAGE(WM_MOVING),
   DEFINE_MESSAGE(WM_STYLECHANGED),
   DEFINE_MESSAGE(WM_STYLECHANGING),
   DEFINE_MESSAGE(WM_SIZING),
   DEFINE_MESSAGE(WM_SETHOTKEY),
   DEFINE_MESSAGE(WM_PRINT),
   DEFINE_MESSAGE(WM_PRINTCLIENT),
   DEFINE_MESSAGE(WM_POWERBROADCAST),
   DEFINE_MESSAGE(WM_HOTKEY),
   DEFINE_MESSAGE(WM_GETICON),
   DEFINE_MESSAGE(WM_EXITMENULOOP),
   DEFINE_MESSAGE(WM_ENTERMENULOOP),
   DEFINE_MESSAGE(WM_DISPLAYCHANGE),
   DEFINE_MESSAGE(WM_STYLECHANGED),
   DEFINE_MESSAGE(WM_STYLECHANGING),
   DEFINE_MESSAGE(WM_GETICON),
   DEFINE_MESSAGE(WM_SETICON),
   DEFINE_MESSAGE(WM_SIZING),
   DEFINE_MESSAGE(WM_MOVING),
   DEFINE_MESSAGE(WM_CAPTURECHANGED),
   DEFINE_MESSAGE(WM_DEVICECHANGE),
   {0,NULL,}    // end of message list
};


CLASS_DECL_ACE const char *  get_windows_message_name(UINT nMsg)
{

   MAP_WM_MESSAGE * pmessage = (MAP_WM_MESSAGE *) allMessagesArray;

   while(pmessage->nMsg != 0)
   {

      if(pmessage->nMsg == nMsg)
         return pmessage->lpszMsg;

      pmessage++;

   }

   return NULL;

}


#undef DEFINE_MESSAGE
