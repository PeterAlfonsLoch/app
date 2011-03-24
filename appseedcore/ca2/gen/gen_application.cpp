#include "StdAfx.h"


namespace gen
{

   UINT application::APPM_LANGUAGE = WM_APP + 117;
   WPARAM application::WPARAM_LANGUAGE_UPDATE = 1;


   application::application()
   {  
      m_plemonarray = new lemon::array(this);
      m_base64.set_app(this);
      m_pmath = new math::math(this);
      m_pgeometry = new geometry::geometry(this);
      //m_pidspace = new id_space("veribell-{E856818A-2447-4a4e-B9CC-4400C803EE7A}", NULL);
      m_iResourceId = 8001;
      m_psavings = new class savings(this);
      
   }

   application::~application()
   {
      if(m_plemonarray != NULL)
      {
         delete m_plemonarray;
         m_plemonarray = NULL;
      }
      if(m_pmath != NULL)
      {
         delete m_pmath;
         m_pmath = NULL;
      }
      if(m_pgeometry != NULL)
      {
         delete m_pgeometry;
         m_pgeometry = NULL;
      }
      if(m_psavings != NULL)
      {
         delete m_psavings;
         m_psavings = NULL;
      }
   }

   math::math & application::math()
   {
      return *m_pmath;
   }

   geometry::geometry & application::geometry()
   {
      return *m_pgeometry;
   }

   savings & application::savings()
   {
      return *m_psavings;
   }
   lemon::array & application::lemon_array()
   {
      return *m_plemonarray;
   }

   class base64 & application::base64()
   {
      return m_base64;
   }

   bool application::process_initialize()
   {
      
      if(is_system())
      {
         {
            char lpszModuleFilePath[MAX_PATH + 1];
            GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);
            m_strModulePath = lpszModuleFilePath;
            char lpszModuleFolder[MAX_PATH + 1];
            LPTSTR lpszModuleFileName;
            GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
            string strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);
            m_strModuleFolder = strModuleFolder;
         }

         {
            char lpszModuleFilePath[MAX_PATH + 1];
            GetModuleFileName(::GetModuleHandleA("ca2.dll"), lpszModuleFilePath, MAX_PATH + 1);
            m_strCa2ModulePath = lpszModuleFilePath;
            char lpszModuleFolder[MAX_PATH + 1];
            LPTSTR lpszModuleFileName;
            GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
            string strModuleFolder(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);
            m_strCa2ModuleFolder = strModuleFolder;
         }


      }
      else
      {
         m_strModulePath   = System.m_strModulePath;
         m_strModuleFolder = System.m_strModuleFolder;
      }

      if(!::ex1::application::process_initialize())
         return false;

      if(is_system())
      {
         System.factory().cloneable_large < stringa > ();
      }
      return true;
   }

   void application::on_process_initialize_command_line()
   {
   }

   bool application::initialize_instance() 
   {


      if(!ex1::application::initialize_instance())
        return FALSE;


      return TRUE;
   }
      

   int application::exit_instance() 
   {



      return ex1::application::exit_instance();
   }

   LRESULT application::GetPaintMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
   {
      UNREFERENCED_PARAMETER(nCode);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);
      return 0;
   }





   bool application::CreateFileFromRawResource(UINT nID, const char * lpcszType, const char * lpcszFilePath)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpcszType);
      UNREFERENCED_PARAMETER(lpcszFilePath);
/*      HINSTANCE hinst = ::AfxFindResourceHandle(MAKEINTRESOURCE(nID), lpcszType);
      if(hinst == NULL)
         return false;
      HRSRC hrsrc = ::FindResource(
         hinst,
         MAKEINTRESOURCE(nID), 
         lpcszType);
      if(hrsrc == NULL)
         return false;
       HGLOBAL hres = ::LoadResource(hinst, hrsrc);
      if(hres == NULL)
         return false;
       DWORD dwResSize = ::SizeofResource(hinst, hrsrc);

      if(hres != NULL)
       {
         UINT FAR* lpnRes = (UINT FAR*)::LockResource(hres);
           try
           {
              // create the .mdb file
              ex1::filesp f(get_app());
              
              if(f->open(lpcszFilePath, ::ex1::file::mode_create | ::ex1::file::mode_write ))
              {
                 // write the ::fontopus::user-defined resource to the .mdb file
                 f->write(lpnRes, dwResSize);
                 f->Flush();
              }
              else
              {
               #ifdef _DEBUG
                  afxdump << "File could not be opened \n";
               #endif
              }
           }
           catch(ex1::file_exception_sp * pe)
           {
         #ifdef _DEBUG
   //         afxdump << "File could not be opened " << pe->m_cause << "\n";
         #endif
           }
           

         #ifndef WIN32 //Unlock Resource is obsolete in the Win32 API
            ::UnlockResource(hres);
         #endif
               ::FreeResource(hres);
      }
      return true;*/

      return false;
   }


   bool application::OnMessageWindowMessage(LPMSG lpmsg)
   {
      UNREFERENCED_PARAMETER(lpmsg);
      return false;
   }

   void application::OnAppLanguage(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      m_signalAppLanguageChange.emit();
   }

   string application::get_ca2_module_folder()
   {
      return m_strCa2ModuleFolder;
   }

   string application::get_ca2_module_file_path()
   {
      char lpszModuleFilePath[MAX_PATH + 1];
      GetModuleFileName(::GetModuleHandleA("ca2.dll"), lpszModuleFilePath, MAX_PATH + 1);

      string strModuleFileName(lpszModuleFilePath);

      return strModuleFileName;
   }

   string application::get_module_folder()
   {
      return m_strModuleFolder;
   }

   string application::get_module_file_path()
   {
      char lpszModuleFilePath[MAX_PATH + 1];
      GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);

      string strModuleFileName(lpszModuleFilePath);

      return strModuleFileName;
   }


   void application::OnUpdateRecentFileMenu(cmd_ui * pcmdui) 
   {
      UNREFERENCED_PARAMETER(pcmdui);
      /*TRACE("\nCVmsGenApp::OnUpdateRecentFileMenu");
      if(m_pRecentFileList == NULL)
      {
         pcmdui->Enable(FALSE);
         //string str;
         //str.load_string(IDS_RECENT_FILE);
         //pcmdui->SetText(str);
         for (int iMRU = 1; iMRU < 10; iMRU++)
            pcmdui->m_pMenu->DeleteMenu(pcmdui->m_nID + iMRU, MF_BYCOMMAND);
         return;
      }
      
      ASSERT(m_pRecentFileList->m_arrNames != NULL);

      ::userbase::menu* pMenu = pcmdui->m_pMenu;
      if (m_pRecentFileList->m_strOriginal.is_empty() && pMenu != NULL)
         pMenu->GetMenuString(pcmdui->m_nID, m_pRecentFileList->m_strOriginal, MF_BYCOMMAND);

      if (m_pRecentFileList->m_arrNames[0].is_empty())
      {
         // no MRU files
         if (!m_pRecentFileList->m_strOriginal.is_empty())
            pcmdui->SetText(m_pRecentFileList->m_strOriginal);
         pcmdui->Enable(FALSE);
         return;
      }

      if (pcmdui->m_pMenu == NULL)
         return;

      ::userbase::menu * pmenu = CMenuUtil::FindPopupMenuFromID(pcmdui->m_pMenu, pcmdui->m_nID);

      //if(pmenu == NULL)
      //{
        // pmenu = pcmdui->m_pMenu;
      //}

      bool bCmdUIMenu = pmenu == pcmdui->m_pMenu;

      if(!bCmdUIMenu)
         return;

      int nID = pcmdui->m_nID;
      int nIndex = CMenuUtil::GetMenuPosition(pmenu, nID);

      for (int iMRU = 0; iMRU < m_pRecentFileList->m_nSize; iMRU++)
         pcmdui->m_pMenu->DeleteMenu(pcmdui->m_nID + iMRU, MF_BYCOMMAND);

       

      char szCurDir[_MAX_PATH];
      GetCurrentDirectory(_MAX_PATH, szCurDir);
      int nCurDir = lstrlen(szCurDir);
      ASSERT(nCurDir >= 0);
      szCurDir[nCurDir] = '\\';
      szCurDir[++nCurDir] = '\0';

      string strName;
      string strTemp;
      for (iMRU = 0; iMRU < m_pRecentFileList->m_nSize; iMRU++)
      {
         if (!m_pRecentFileList->GetDisplayName(strName, iMRU, szCurDir, nCurDir))
            break;

         // double up any '&' characters so they are not underlined
         const char * lpszSrc = strName;
         LPTSTR lpszDest = strTemp.GetBuffer(strName.get_length()*2);
         while (*lpszSrc != 0)
         {
            if (*lpszSrc == '&')
               *lpszDest++ = '&';
            if (_istlead(*lpszSrc))
               *lpszDest++ = *lpszSrc++;
            *lpszDest++ = *lpszSrc++;
         }
         *lpszDest = 0;
         strTemp.ReleaseBuffer();

         // insert mnemonic + the file name
         char buf[10];
         wsprintf(buf, "&%d ", (iMRU+1+m_pRecentFileList->m_nStart) % 10);
           
   //      pcmdui->m_pMenu->InsertMenu(pcmdui->m_nIndex++,
   //         MF_STRING | MF_BYPOSITION, pcmdui->m_nID++,
   //         string(buf) + strTemp);
         pmenu->InsertMenu(nIndex,
            MF_STRING | MF_BYPOSITION, nID,
            string(buf) + strTemp);
           nIndex++;
           nID++;
           if(bCmdUIMenu)
           {
               pcmdui->m_nIndex = nIndex;
               pcmdui->m_nID = nID;
           }
      }

      // update end menu count
       if(bCmdUIMenu)
       {
          pcmdui->m_nIndex--; // point to last menu added
          pcmdui->m_nIndexMax = pcmdui->m_pMenu->GetMenuItemCount();
       }

      pcmdui->m_bEnableChanged = TRUE;    // all the added items are enabled*/

   }

   bool application::GetResourceData(UINT nID, const char * lpcszType, primitive::memory &storage)
   {
      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(lpcszType);
      UNREFERENCED_PARAMETER(storage);
/*      HINSTANCE hinst = ::AfxFindResourceHandle(MAKEINTRESOURCE(nID), lpcszType);
      
      if(hinst == NULL)
         return false;
      
      HRSRC hrsrc = ::FindResource(
         hinst,
         MAKEINTRESOURCE(nID), 
         lpcszType);
      
      if(hrsrc == NULL)
         return false;

      HGLOBAL hres = ::LoadResource(hinst, hrsrc);
      if(hres == NULL)
         return false;
      
      DWORD dwResSize = ::SizeofResource(hinst, hrsrc);

      if(hres != NULL)
      {
         UINT FAR* lpnRes = (UINT FAR*)::LockResource(hres);
         try
         {
            storage.set_data(lpnRes, dwResSize);
         }
         catch(ex1::file_exception_sp * pe)
         {
            #ifdef _DEBUG
   //            afxdump << "File could not be opened " << pe->m_cause << "\n";
            #endif
         }
         

         #ifndef WIN32 //Unlock Resource is obsolete in the Win32 API
         ::UnlockResource(hres);
         #endif
         ::FreeResource(hres);
      }
      return true;*/
      return false;

   }

   HENHMETAFILE application::LoadEnhMetaFile(UINT uiResource)
   {
      primitive::memory storage;
      if(!GetResourceData(uiResource, "EnhMetaFile", storage))
      {
         return NULL;
      }
      return SetEnhMetaFileBits(storage.GetStorageSize(), storage.GetAllocation());
   }

   /////////////////////////////////////////////////////////////////////////////
   // WinApp UI related functions

   void application::EnableModelessEx(BOOL bEnable)
   {
      UNREFERENCED_PARAMETER(bEnable);
   #ifdef _AFX_NO_OLE_SUPPORT
      UNUSED(bEnable);
   #endif

      // no-op if main ::ca::window is NULL or not a frame_window_interface
/*      ::user::interaction* pMainWnd = System.GetMainWnd();
      if (pMainWnd == NULL || !pMainWnd->IsFrameWnd())
         return;*/

   #ifndef _AFX_NO_OLE_SUPPORT
      // check if notify hook installed
   /*   gen::frame_window_interface* pFrameWnd = 
         dynamic_cast < gen::frame_window_interface * > (pMainWnd);
      ASSERT(pFrameWnd != NULL);
      if (pFrameWnd->GetNotifyHook() != NULL)
         pFrameWnd->GetNotifyHook()->OnEnableModeless(bEnable);*/
   #endif
   }


   /*id_space * application::GetGenIdSpace()
   {
      return m_pidspace;
   }*/

   /*
   string application::load_string(const id_space * pspace, int iKey)
   {
      string str;
      int iId = GetResourceId(pspace, iKey);
      if(iId == -1)
         return str;
      str.load_string(iId);
      return str;
   }
   */


   #ifdef _DEBUG
   void application::assert_valid() const
   {
      ex1::application::assert_valid();
   }

   void application::dump(dump_context & dumpcontext) const
   {
      ex1::application::dump(dumpcontext);
   }
   #endif

   int application::run()
   {
      return ex1::application::run();
   }

   BOOL application::on_idle(LONG lCount)
   {
      return ex1::application::on_idle(lCount);
   }

   void application::ProcessWndProcException(base_exception* e, gen::signal_object * pobj)
   {
      return ex1::application::ProcessWndProcException(e, pobj);
   }

   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
         
   {
      if(command_target_interface::_001OnCmdMsg(pcmdmsg))
         return TRUE;
      return ex1::application::_001OnCmdMsg(pcmdmsg);
   }

   ::ca::application * application::get_app() const
   {
      return ex1::application::get_app();
   }

   string application::get_module_title()
   {
      return file_title(get_module_file_path());
   }
      
   string application::get_module_name()
   {
      return file_name(get_module_file_path());
   }

   string application::get_local_mutex_id()
   {
      return command_line().m_varQuery["local_mutex_id"];
   }

   string application::get_global_mutex_id()
   {
      return command_line().m_varQuery["global_mutex_id"];
   }

   class command_line & application::command_line()
   {
      return *m_pcommandline;
   }

} // namespace gen



#define NULWCHAR     L'\0'
#define TABWCHAR     L'\t'
#define SLASHWCHAR   L'\\'
#define SPACEWCHAR   L' '
#define DQUOTEWCHAR  L'\"'

/***
*static void parse_cmdline(cmdstart, argv, args, numargs, numchars)
*
*Purpose:
*       Parses the command line and sets up the argv[] base_array.
*       On entry, cmdstart should point to the command line,
*       argv should point to primitive::memory for the argv base_array, args
*       points to primitive::memory to place the text of the arguments.
*       If these are NULL, then no storing (only coujting)
*       is done.  On exit, *numargs has the number of
*       arguments (plus one for a final NULL argument),
*       and *numchars has the number of bytes used in the buffer
*       pointed to by args.
*
*Entry:
*       _TSCHAR *cmdstart - pointer to command line of the form
*           <progname><nul><args><nul>
*       _TSCHAR **argv - where to build argv base_array; NULL means don't
*                       build base_array
*       _TSCHAR *args - where to place argument text; NULL means don't
*                       store text
*
*Exit:
*       no return value
*       int *numargs - returns number of argv entries created
*       int *numchars - number of characters used in args buffer
*
*Exceptions:
*
*******************************************************************************/

void __cdecl wparse_cmdline (
    WCHAR *cmdstart,
    WCHAR **argv,
    WCHAR *args,
    int *numargs,
    int *numchars
    )
{
        WCHAR *p;
        WCHAR c;
        int inquote;                    /* 1 = inside quotes */
        int copychar;                   /* 1 = copy char to *args */
        unsigned numslash;              /* num of backslashes seen */

        *numchars = 0;
        *numargs = 1;                   /* the program name at least */

        /* first scan the program name, copy it, and count the bytes */
        p = cmdstart;
        if (argv)
            *argv++ = args;

#ifdef WILDCARD
        /* To handle later wild card expansion, we prefix each entry by
        it's first character before quote handling.  This is done
        so _[w]cwild() knows whether to expand an entry or not. */
        if (args)
            *args++ = *p;
        ++*numchars;

#endif  /* WILDCARD */

        /* A quoted program name is handled here. The handling is much
           simpler than for other arguments. Basically, whatever lies
           between the leading double-quote and next one, or a terminal null
           character is simply accepted. Fancier handling is not required
           because the program name must be a legal NTFS/HPFS file name.
           Note that the double-quote characters are not copied, nor do they
           contribute to numchars. */
        if ( *p == DQUOTEWCHAR ) {
            /* scan from just past the first double-quote through the next
               double-quote, or up to a null, whichever comes first */
            while ( (*(++p) != DQUOTEWCHAR) && (*p != NULWCHAR) ) {

/*#ifdef _MBCS
                if (_ismbblead(*p)) {
                    ++*numchars;
                    if ( args )
                        *args++ = *p++;
                }
#endif  /* _MBCS */
                ++*numchars;
                if ( args )
                    *args++ = *p;
            }
            /* append the terminating null */
            ++*numchars;
            if ( args )
                *args++ = NULWCHAR;

            /* if we stopped on a double-quote (usual case), skip over it */
            if ( *p == DQUOTEWCHAR )
                p++;
        }
        else {
            /* Not a quoted program name */
            do {
                ++*numchars;
                if (args)
                    *args++ = *p;

                c = (WCHAR) *p++;
/*#ifdef _MBCS
                if (_ismbblead(c)) {
                    ++*numchars;
                    if (args)
                        *args++ = *p;   /* copy 2nd byte too */
    //                p++;  /* skip over trail byte */
  //              }
//#endif  /* _MBCS */

            } while ( c != SPACEWCHAR && c != NULWCHAR && c != TABWCHAR );

            if ( c == NULWCHAR ) {
                p--;
            } else {
                if (args)
                    *(args-1) = NULWCHAR;
            }
        }

        inquote = 0;

        /* loop on each argument */
        for(;;) {

            if ( *p ) {
                while (*p == SPACEWCHAR || *p == TABWCHAR)
                    ++p;
            }

            if (*p == NULWCHAR)
                break;              /* end of args */

            /* scan an argument */
            if (argv)
                *argv++ = args;     /* store ptr to arg */
            ++*numargs;

#ifdef WILDCARD
        /* To handle later wild card expansion, we prefix each entry by
        it's first character before quote handling.  This is done
        so _[w]cwild() knows whether to expand an entry or not. */
        if (args)
            *args++ = *p;
        ++*numchars;

#endif  /* WILDCARD */

        /* loop through scanning one argument */
        for (;;) {
            copychar = 1;
            /* Rules: 2N backslashes + " ==> N backslashes and begin/end quote
               2N+1 backslashes + " ==> N backslashes + literal "
               N backslashes ==> N backslashes */
            numslash = 0;
            while (*p == SLASHWCHAR) {
                /* count number of backslashes for use below */
                ++p;
                ++numslash;
            }
            if (*p == DQUOTEWCHAR) {
                /* if 2N backslashes before, start/end quote, otherwise
                    copy literally */
                if (numslash % 2 == 0) {
                    if (inquote) {
                        if (p[1] == DQUOTEWCHAR)
                            p++;    /* Double quote inside quoted string */
                        else        /* skip first quote char and copy second */
                            copychar = 0;
                    } else
                        copychar = 0;       /* don't copy quote */

                    inquote = !inquote;
                }
                numslash /= 2;          /* divide numslash by two */
            }

            /* copy slashes */
            while (numslash--) {
                if (args)
                    *args++ = SLASHWCHAR;
                ++*numchars;
            }

            /* if at end of arg, break loop */
            if (*p == NULWCHAR || (!inquote && (*p == SPACEWCHAR || *p == TABWCHAR)))
                break;

            /* copy character into argument */
/*#ifdef _MBCS
            if (copychar) {
                if (args) {
                    if (_ismbblead(*p)) {
                        *args++ = *p++;
                        ++*numchars;
                    }
                    *args++ = *p;
                } else {
                    if (_ismbblead(*p)) {
                        ++p;
                        ++*numchars;
                    }
                }
                ++*numchars;
            }
            ++p;
#else  /* _MBCS */
            if (copychar) {
                if (args)
                    *args++ = *p;
                ++*numchars;
            }
            ++p;
//#endif  /* _MBCS */
            }

            /* null-terminate the argument */

            if (args)
                *args++ = NULWCHAR;          /* terminate string */
            ++*numchars;
        }

        /* We put one last argument in -- a null ptr */
        if (argv)
            *argv++ = NULL;
        ++*numargs;
}



