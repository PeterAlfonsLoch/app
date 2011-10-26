#include "StdAfx.h"


namespace winactionarea
{


   application::application()
   {
      ::SetPriorityClass(::GetCurrentProcess(), HIGH_PRIORITY_CLASS);
      m_strAppName            = "winactionarea";
      m_strLicense            = "_set_windesk";
      m_strBaseSupportId      = "votagus_ca2_winactionarea";
      m_eexclusiveinstance    = ::radix::ExclusiveInstanceLocal;
   }

   application::~application(void)
   {
   }



   bool application::initialize_instance()
   {
      //::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
      System.factory().creatable_small < document >();
      System.factory().creatable_small < frame >();
      System.factory().creatable_small < view >();
      System.factory().creatable_small < winactionarea::pane_view >();
      System.factory().creatable_small < winactionarea::menu_right_view >();
      System.factory().creatable_small < winactionarea::menu_view >();

      if(!cube2::application::initialize_instance())
         return false;

      



      GetStdFileManagerTemplate()->m_strLevelUp = "1000";


      SetRegistryKey("ca2core");

	   ::userbase::single_document_template* pDocTemplate;
	   pDocTemplate = new ::userbase::single_document_template(
         this,
		   "system/form",
		   ::ca::get_type_info < document > (),
		   ::ca::get_type_info < frame > (),
		   ::ca::get_type_info < pane_view > ());
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;


      return TRUE;
   }

   int application::exit_instance()
   {
      for(int i = 0; i < m_hwndaHidden.get_count(); i++)
      {
         ShowWindow(m_hwndaHidden[i], SW_RESTORE);
      }
      Sleep((1984 + 1977) * 2);
      return TRUE;
   }

   void application::on_request(::ca::create_context * pcreatecontext)
   {

      try
      {
   #ifdef DEBUG
         if (command().m_varTopicQuery.has_property("debugbreak"))
         {
            ::DebugBreak();
         }
   #endif
         if (command().m_varTopicQuery.has_property("run"))
         {
         }
      }
      catch(...)
      {
      }

      AfxBeginThread < helper_thread > (get_app());

      m_ptemplate_html->open_document_file(NULL, FALSE);

   }

   void application::_001OnFileNew()
   {
      userbase::application::m_pdocmanager->_001OnFileNew();
   }


   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
   		
   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }


   bool application::on_assert_failed_line(const char * lpszFileName, int iLine)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(iLine);
      if(m_pwndMain != NULL)
      {
         m_pwndMain->PostMessage(12578);
      }
      return true;
   }


   bool application::final_handle_exception(::ca::exception & e)
   {
      for(int i = 0; i < m_hwndaHidden.get_count(); i++)
      {
         ShowWindow(m_hwndaHidden[i], SW_RESTORE);
      }
      return cube2::application::final_handle_exception(e);
   }

   application::helper_thread::helper_thread(::ca::application * papp) :
      ca(papp),
      thread(papp)
   {
   }

   int application::helper_thread::run()
   {
      application * papp = dynamic_cast < application * > (get_app());
      string strDir = Application.dir().userappdata("winactionarea\\menu");
      papp->menu_view_check_menu_dir(strDir);
      HANDLE hDirectory =
         ::CreateFile((const char *) strDir,    // folder path 
                      FILE_LIST_DIRECTORY,
                      FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
                      NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
   
      if(INVALID_HANDLE_VALUE == hDirectory)
      {
         DWORD dwError = ::GetLastError();
         // handle error (see this FAQ)
         return dwError;
      }

      DWORD dwBytesReturned = 0;
      const DWORD dwBuffLength = 4096;
      BYTE buffer[dwBuffLength];
      WCHAR wchFileName[_MAX_PATH + 1];
      
      while(::ReadDirectoryChangesW(hDirectory, buffer, dwBuffLength, TRUE,
                                    FILE_NOTIFY_CHANGE_FILE_NAME |
                                    FILE_NOTIFY_CHANGE_LAST_WRITE |
                                    FILE_NOTIFY_CHANGE_CREATION, &dwBytesReturned, 
                                    NULL, NULL))
      {
         DWORD dwNextEntryOffset = 0;
         PFILE_NOTIFY_INFORMATION pfni = NULL;
         do
         {
            pfni = (PFILE_NOTIFY_INFORMATION)(buffer + dwNextEntryOffset);
            
            memcpy(wchFileName, pfni->FileName, pfni->FileNameLength);
            wchFileName[pfni->FileNameLength / sizeof(WCHAR)] = L'\0';
            string str;
            str = gen::international::unicode_to_utf8(wchFileName);
            papp->menu_view_check_menu_dir(strDir);
            dwNextEntryOffset += pfni->NextEntryOffset; // next please!
         }while(pfni->NextEntryOffset != 0);
      } 
      ::CloseHandle(hDirectory);
      return 0;
   }

   void application::menu_view_check_menu_dir(const char * psz)
   {
      stringa straPath;
      System.dir().ls(psz, &straPath);
      //if(straPath.get_size() == 0)
      {
         stringa straRelative;
         straPath.remove_all();
         string strSource;
         strSource = System.dir().commonprograms();
         if(strSource.has_char())
         {
            System.dir().rls(strSource, &straPath, NULL, &straRelative);
            for(int i = 0; i < straPath.get_size(); i++)
            {
               string str = System.dir().path(psz, straRelative[i]);
               System.dir().mk(System.dir().name(str));
               ::CopyFile(straPath[i], str , TRUE);
            }
         }
         straRelative.remove_all();
         straPath.remove_all();
         strSource = Application.dir().userprograms();
         if(strSource.has_char())
         {
            System.dir().rls(strSource, &straPath, NULL, &straRelative);
            for(int i = 0; i < straPath.get_size(); i++)
            {
               string str = System.dir().path(psz, straRelative[i]);
               System.dir().mk(System.dir().name(str));
               ::CopyFile(straPath[i], str, TRUE);
            }
         }
      }
   }


} // namespace winactionarea


::ca2::library * get_new_library()
{
   return new ::ca2::single_application_library < ::winactionarea::application > ();
}


