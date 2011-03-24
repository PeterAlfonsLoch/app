#include "StdAfx.h"


namespace ca8
{


   application::application()
   {
      m_pkeyboardfocus  = NULL;
      m_pshellimageset  = NULL;
   }

   application::~application()
   {
   }


   bool application::initialize1()
   {
      if(!html::application::initialize1())     
         return false;
      return true;
   }

   bool application::initialize()
   {
      System.factory().creatable_small < keyboard_layout > ();
      
      m_pshellimageset = new filemanager::_shell::ImageSet(this);



      if(!userex::application::initialize())     
         return false;

      xml::node nodeUser(get_app());
      string strUser = Application.file().as_string(Application.dir().userappdata("langstyle_settings.xml"));
      string strLangUser;
      string strStyleUser;
      if(nodeUser.load(strUser))
      {
         if(nodeUser.get_child("lang") != NULL)
         {
            strLangUser = nodeUser.get_child("lang")->m_strValue;
         }
         if(nodeUser.get_child("style") != NULL)
         {
            strStyleUser = nodeUser.get_child("style")->m_strValue;
         }
      }

      if(strLangUser.has_char())
         set_locale(strLangUser, false);
      if(strStyleUser.has_char())
         set_style(strStyleUser, false);

      if(&ApplicationUser == NULL)
      {
         return false;
      }

      if(!m_strLicense.is_empty())    
      {
         if(!System.is_licensed(m_strLicense))
         {              
            return false;      
         }   
      }     

      
      
      return true;
   }

   filemanager::_shell::ImageSet & application::shellimageset()
   {
      return *m_pshellimageset;
   }

   bool application::_001ProcessShellCommand(gen::command_line& rCmdInfo)
   {
      BOOL bResult = TRUE;
      switch (rCmdInfo.m_nShellCommand)
      {
      case gen::command_line::FileNew:
         if (!System._001SendCommand("file::new"))
            _001OnFileNew();
         if (System.GetMainWnd() == NULL)
            bResult = FALSE;
         break;

         // If we've been asked to open a file, call open_document_file()

      case gen::command_line::FileOpen:
         if (!_001OpenDocumentFile(rCmdInfo.m_varFile))
            bResult = FALSE;
         break;

         // If the user wanted to print, hide our main ::ca::window and
         // fire a message to ourselves to start the printing

      case gen::command_line::FilePrintTo:
      case gen::command_line::FilePrint:
         System.m_nCmdShow = SW_HIDE;
//         ASSERT(System.m_pCmdInfo == NULL);
         _001OpenDocumentFile(rCmdInfo.m_varFile);
         System.GetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_PRINT_DIRECT);
         bResult = FALSE;
         break;

         // If we're doing DDE, hide ourselves

      case gen::command_line::FileDDE:
         command_line().m_nCmdShow = m_nCmdShow;
         m_nCmdShow = SW_HIDE;
         break;

      // If we've been asked to unregister, unregister and then terminate
      case gen::command_line::AppUnregister:
         {
            //((CVmsGenApp *) &System)->UnregisterShellFileTypes();
   //xxx         System.UnregisterShellFileTypes();
   //xxx         BOOL bUnregistered = ((CVmsGenApp *) &System)->Unregister();

            // if you specify /EMBEDDED, we won't make an success/failure box
            // this use of /EMBEDDED is not related to OLE

   /*         if (!rCmdInfo.m_bRunEmbedded)
            {
               if (bUnregistered)
                  System.simple_message_box(AFX_IDP_UNREG_DONE);
               else
                  System.simple_message_box(AFX_IDP_UNREG_FAILURE);
            }
            bResult = FALSE;    // that's all we do

            // If nobody is using it already, we can use it.
            // We'll flag that we're unregistering and not save our state
            // on the way out. This new object gets deleted by the
            // cast object destructor.

            if (m_pcmdinfo == NULL)
            {
               m_pcmdinfo = new command_line;
               m_pcmdinfo->m_nShellCommand = command_line::AppUnregister;
            }*/
         }
         break;
      }
      return bResult != FALSE;
   }


   string application::message_box(const char * pszMatter, gen::property_set & propertyset)
   {
      class message_box box(this);
      box.show(pszMatter, propertyset);
      return box.m_strResponse;
   }

   int application::simple_message_box(::user::interaction * pwndOwner, const char * pszMessage, UINT fuStyle)
   {
      class message_box box(this);

      gen::property_set propertyset;
      propertyset["message"] = pszMessage;

      string strMatter;
      if(fuStyle & MB_YESNOCANCEL)
      {
        strMatter = "system\\user\\simple_message_box\\yesnocancel.xhtml";
      }
      else
      {
         strMatter = "system\\user\\simple_message_box\\ok.xhtml";
      }
      try
      {
         if(!box.show(strMatter, propertyset))
         {
            string strMessage = pszMessage;
            strMessage.replace("<br>", "\r\n");
            return MessageBox(pwndOwner == NULL ? NULL : (HWND) pwndOwner->get_wnd()->get_os_data(), strMessage, m_strAppName, fuStyle);
         }
      }
      catch(...)
      {
         string strMessage = pszMessage;
         strMessage.replace("<br>", "\r\n");
         return MessageBox(pwndOwner == NULL ? NULL : (HWND) pwndOwner->get_wnd()->get_os_data(), strMessage, m_strAppName, fuStyle);
      }
      if(box.m_strResponse == "ok")
      {
         return IDOK;
      }
      else if(box.m_strResponse == "yes")
      {
         return IDYES;
      }
      else if(box.m_strResponse == "no")
      {
         return IDNO;
      }
      else if(box.m_strResponse == "cancel")
      {
         return IDCANCEL;
      }
      if(fuStyle & MB_YESNOCANCEL)
      {
         return IDCANCEL;
      }
      else
      {
         return 0;
      }
   }

   int application::simple_message_box_timeout(::user::interaction * puiOwner, const char * pszMessage, int iTimeout, UINT fuStyle)
   {
      UNREFERENCED_PARAMETER(puiOwner);

      class message_box box(this);

      gen::property_set propertyset;
      propertyset["message"] = pszMessage;
      propertyset["simple_message_box_timeout_ms"] = iTimeout;

      string strMatter;
      if(fuStyle & MB_YESNOCANCEL)
      {
        strMatter = "system\\user\\simple_message_box\\yesnocancel.xhtml";
      }
      else
      {
         strMatter = "system\\user\\simple_message_box\\ok.xhtml";
      }
      box.show(strMatter, propertyset);
      if(box.m_strResponse == "ok")
      {
         return IDOK;
      }
      else if(box.m_strResponse == "yes")
      {
         return IDYES;
      }
      else if(box.m_strResponse == "no")
      {
         return IDNO;
      }
      else if(box.m_strResponse == "cancel")
      {
         return IDCANCEL;
      }
      if(fuStyle & MB_YESNOCANCEL)
      {
         return IDCANCEL;
      }
      else
      {
         return 0;
      }
   }

   int application::track_popup_menu(const char * pszMatter, point pt, ::user::interaction * puie)
   {
      UNREFERENCED_PARAMETER(pszMatter);
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(puie);
      return 1;
   }

   bool application::set_keyboard_layout(const char * pszPath, bool bUser)
   {
      return keyboard().load_layout(pszPath, bUser);
   }


   bool application::get_fs_size(string & strSize, const char * pszPath, bool & bPending)
   {
      __int64 i64Size;
      if(!get_fs_size(i64Size, pszPath, bPending))
      {
         strSize.Empty();
         return false;
      }
      if(i64Size > 1024 * 1024 * 1024)
      {
         double d = (double) i64Size / (1024.0 * 1024.0 * 1024.0);
         strSize.Format("%0.2f GB", d);
      }
      else if(i64Size > 1024 * 1024)
      {
         double d = (double) i64Size / (1024.0 * 1024.0);
         strSize.Format("%0.1f MB", d);
      }
      else if(i64Size > 1024)
      {
         double d = (double) i64Size / (1024.0);
         strSize.Format("%0.0f KB", d);
      }
      else if(i64Size > 0)
      {
         strSize.Format("1 KB");
      }
      else
      {
         strSize.Format("0 KB");
      }
      if(bPending)
      {
         strSize = "~" + strSize;
      }
      return true;
   }

   bool application::get_fs_size(__int64 & i64Size, const char * pszPath, bool & bPending)
   {
      db_server * pcentral = dynamic_cast < db_server * > (&System.db());
      if(pcentral == NULL)
         return false;
      return pcentral->m_pfilesystemsizeset->get_cache_fs_size(i64Size, pszPath, bPending);
   }

   void application::data_on_after_change(gen::signal_object * pobj)
   {
      simpledb::application::data_on_after_change(pobj);
      userbase::application::data_on_after_change(pobj);
      SCAST_PTR(::database::change_event, pchange, pobj);
      if(pchange->m_key.m_idKey == "ca2_fontopus_votagus")
      {
         if(pchange->m_key.m_idIndex  == "savings")
         {
            pchange->data_get(savings().m_eresourceflagsShouldSave);
         }
      }
   }


} //namespace ca8