#include "StdAfx.h"


namespace simpleuser
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

      m_dwAlive = ::GetTickCount();

      if(!userex::application::initialize1())     
         return false;
      return true;
   }

   bool application::initialize()
   {

      m_dwAlive = ::GetTickCount();

      if(is_system())
      {
         System.factory().creatable_small < keyboard_layout > ();
      }
      
      m_pshellimageset = new filemanager::_shell::ImageSet(this);



      if(!userex::application::initialize())     
         return false;

      xml::node nodeUser(this);
      string strUser = App(this).file().as_string(App(this).dir().userappdata("langstyle_settings.xml"));
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


      if(m_strLicense.has_char())    
      {

         if(&ApplicationUser == NULL)
         {
            return false;
         }

         // call application's is_licensed function
         // because if delay is needed for authentication -
         // or either asking for authentication -
         // current application startup won't be
         // exited by timeout.
         int iRetry = 3;
retry_license:
         iRetry--;
         if(!App(this).is_licensed(m_strLicense))
         {      
            App(this).license().m_mapInfo.remove_key(m_strLicense);
            if(iRetry > 0)
               goto retry_license;
            return false;      
         }   
      }     

      
      
      return true;
   }

   filemanager::_shell::ImageSet & application::shellimageset()
   {
      return *m_pshellimageset;
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


} //namespace simpleuser