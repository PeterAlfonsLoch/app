#include "framework.h"


namespace user
{


   application::application()
   {
      m_pkeyboardfocus  = NULL;
      m_pshellimageset  = NULL;
      m_pkeyboard       = NULL;
   }

   application::~application()
   {
   }


   bool application::initialize1()
   {

      m_dwAlive = ::GetTickCount();

      if(is_system())
      {
         m_pwindowmap = new class ::user::window_map();
      }
      else
      {
         m_pwindowmap = System.m_pwindowmap;
      }

      m_pkeyboard = new ::user::keyboard(this);


      m_dwAlive = ::GetTickCount();

      if(is_system())
      {
         System.factory().creatable_small < keyboard_layout > ();
      }

      m_pshellimageset = new filemanager::_shell::ImageSet(this);

      if(!visual::application::initialize1())
         return false;

      return true;

   }

   bool application::initialize()
   {




      if(!visual::application::initialize())
         return false;

      xml::document docUser(this);
      string strUser = App(this).file().as_string(App(this).dir().userappdata("langstyle_settings.xml"));
      string strLangUser;
      string strStyleUser;
      if(docUser.load(strUser))
      {
         if(docUser.get_child("lang") != NULL)
         {
            strLangUser = docUser.get_child("lang")->get_value();
         }
         if(docUser.get_child("style") != NULL)
         {
            strStyleUser = docUser.get_child("style")->get_value();
         }
      }

      if(strLangUser.has_char())
         set_locale(strLangUser, false);
      if(strStyleUser.has_char())
         set_schema(strStyleUser, false);


      if(!(System.directrix().m_varTopicQuery.has_property("install")
      ||  System.directrix().m_varTopicQuery.has_property("uninstall"))
      &&  m_bLicense)
      {

         string strLicense = get_license_id();

         if(&AppUser(this) == NULL)
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

         if(!App(this).is_licensed(strLicense))
         {
            
            App(this).license().m_mapInfo.remove_key(strLicense);
            
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
   {      throw not_implemented_exception();
/*      class message_box box(this);
      box.show(pszMatter, propertyset);
      return box.m_strResponse;*/
      return "";
   }

   int application::simple_message_box(::user::interaction * pwndOwner, const char * pszMessage, UINT fuStyle)
   {

      if(m_psession != NULL && m_psession->m_pbergedgeInterface != NULL)
      {
         return m_psession->m_pbergedgeInterface->simple_message_box(pwndOwner, pszMessage, fuStyle);
      }



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
/*         if(!box.show(strMatter, propertyset))
         {
            string strMessage = pszMessage;
            strMessage.replace("<br>", "\r\n");
            return MessageBox(pwndOwner == NULL ? NULL : (HWND) pwndOwner->get_wnd()->get_os_data(), strMessage, m_strAppName, fuStyle);
         }*/
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
      throw not_implemented_exception();
//      box.show(strMatter, propertyset);
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


   bool application::get_fs_size(string & strSize, const char * pszPath, bool & bPending)
   {
      int64_t i64Size;
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

   bool application::get_fs_size(int64_t & i64Size, const char * pszPath, bool & bPending)
   {
      db_server * pcentral = dynamic_cast < db_server * > (&System.db());
      if(pcentral == NULL)
         return false;
      return pcentral->m_pfilesystemsizeset->get_cache_fs_size(i64Size, pszPath, bPending);
   }

   void application::data_on_after_change(gen::signal_object * pobj)
   {
      visual::application::data_on_after_change(pobj);
      SCAST_PTR(::database::change_event, pchange, pobj);
      if(pchange->m_key.m_idKey == "ca2_fontopus_votagus")
      {
         if(pchange->m_key.m_idIndex  == "savings")
         {
            pchange->data_get(savings().m_eresourceflagsShouldSave);
         }
      }
   }


      ::user::keyboard_focus * application::get_keyboard_focus()
      {
         if(is_session() || is_bergedge())
         {
            ::user::interaction * puieFocus = get_focus_guie();
            if(m_pkeyboardfocus != NULL && puieFocus != NULL)
            {
               if((bool)oprop("NativeWindowFocus") && puieFocus != m_pkeyboardfocus->get_wnd())
                  return NULL;
               return m_pkeyboardfocus;
            }
            else
            {
               return NULL;
            }
         }
         else if(is_system() || is_cube())
         {
            return m_pkeyboardfocus;
         }
         else if(m_psession != NULL)
         {
            return Sess(this).get_keyboard_focus();
         }
         else if(m_psystem != NULL)
         {
            return Sys(this).get_keyboard_focus();
         }
         else
         {
            return NULL;
         }
      }

      void application::set_keyboard_focus(::user::keyboard_focus * pkeyboardfocus)
      {
         if(is_session() || is_bergedge())
         {
            if(pkeyboardfocus == NULL || pkeyboardfocus->keyboard_focus_OnSetFocus())
            {
               m_pkeyboardfocus = pkeyboardfocus;
            }
            if(m_psystem != NULL)
            {
               return Sys(this).set_keyboard_focus(pkeyboardfocus);
            }
         }
         else if(is_system() || is_cube())
         {
            if(pkeyboardfocus == NULL || pkeyboardfocus->keyboard_focus_OnSetFocus())
            {
               m_pkeyboardfocus = pkeyboardfocus;
            }
         }
         else if(m_psession != NULL)
         {
            return Sess(this).set_keyboard_focus(pkeyboardfocus);
         }
         else if(m_psystem != NULL)
         {
            return Sys(this).set_keyboard_focus(pkeyboardfocus);
         }
      }

      ::user::mouse_focus * application::get_mouse_focus_LButtonDown()
      {
         return m_pmousefocusLButtonDown;
      }

      void application::set_mouse_focus_LButtonDown(::user::mouse_focus * pmousefocus)
      {
         m_pmousefocusLButtonDown = pmousefocus;
      }

      ::user::mouse_focus * application::get_mouse_focus_RButtonDown()
      {
         return m_pmousefocusRButtonDown;
      }

      void application::set_mouse_focus_RButtonDown(::user::mouse_focus * pmousefocus)
      {
         m_pmousefocusRButtonDown = pmousefocus;
      }


   bool application::set_keyboard_layout(const char * pszPath, bool bUser)
   {

      if(pszPath == NULL)
      {

         if(&keyboard().layout() != NULL)
         {
            
            if(Application.m_puser != NULL)
            {
            
               data_set("keyboard_layout", keyboard().layout().m_strPath);

            }

            return true;
         }

         if(keyboard().get_current_system_layout().is_empty())
            return false;

         if(!set_keyboard_layout(keyboard().get_current_system_layout(), false))
            return false;

         if(Application.m_puser != NULL)
         {

            data_set("keyboard_layout", keyboard().layout().m_strPath);

         }

         return true;
      }

      if(!System.keyboard().load_layout(pszPath, bUser))
         return false;

      on_set_keyboard_layout(pszPath, bUser);

      return true;
   }


   ::user::keyboard & application::keyboard()
   {
      if(this != &System)
      {
         application * papp = dynamic_cast < application * > (&System);
         return papp->keyboard();
      }
      return *m_pkeyboard;
   }


   class window_map & application::window_map()
   {
      return *m_pwindowmap;
   }


   ca::type_info application::controltype_to_typeinfo(user::control::e_type e_type)
   {
      switch(e_type)
      {
      case user::control::e_type::type_edit_plain_text:
         return typeid(edit_plain_text);
      default:
         return ::ca::type_info();
      }
   }


} //namespace user
