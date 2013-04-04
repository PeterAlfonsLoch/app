#include "framework.h"


namespace user
{


   user::user()
   {
      m_pkeyboardfocus  = ::null();
      m_pshellimageset  = ::null();
      m_pkeyboard       = ::null();
   }

   user::~user()
   {
   }


   bool user::initialize1()
   {

      if(m_papp->is_system())
      {
         m_pwindowmap = new class ::user::window_map();
      }
      else
      {
         m_pwindowmap = System.user()->m_pwindowmap;
      }

      m_pkeyboard = new ::user::keyboard(m_papp);

      if(m_pkeyboard == ::null())
         return false;







      if(m_papp->is_system())
      {
         System.factory().creatable_small < keyboard_layout > ();
      }

      m_pshellimageset = new filemanager::_shell::ImageSet(m_papp);

      if(!::ca::section::initialize1())
         return false;

      return true;

   }

   bool user::initialize()
   {




      if(!::ca::section::initialize())
         return false;


      Application.simpledb().get_data_server()->add_client(this);


      TRACE("::user::application::initialize");

      xml::document docUser(get_app());
      string strUser = Application.file().as_string(Application.dir().userappdata("langstyle_settings.xml"));
      string strLangUser;
      string strStyleUser;
      if(docUser.load(strUser))
      {
         if(docUser.get_child("lang") != ::null())
         {
            strLangUser = docUser.get_child("lang")->get_value();
         }
         if(docUser.get_child("style") != ::null())
         {
            strStyleUser = docUser.get_child("style")->get_value();
         }
      }

      if(strLangUser.has_char())
         Application.set_locale(strLangUser, false);
      if(strStyleUser.has_char())
         Application.set_schema(strStyleUser, false);

      string strLicense = Application.get_license_id();


      var & varTopicQuey = System.directrix().m_varTopicQuery;

      bool bHasInstall = varTopicQuey.has_property("install");

      bool bHasUninstall = varTopicQuey.has_property("uninstall");

      if(!(bHasInstall || bHasUninstall)
         && Application.m_bLicense
         && strLicense.has_char())
      {

         if(&ApplicationUser == ::null())
         {
            return false;
         }

         // call application's is_licensed function
         // because if delay is needed for authentication -
         // or either asking for authentication -
         // current application startup won't be
         // exited by timeout.

         int32_t iRetry = 3;

retry_license:

         iRetry--;

         if(!Application.is_licensed(strLicense))
         {

            Application.license().m_mapInfo.remove_key(strLicense);

            if(iRetry > 0)
               goto retry_license;

            return false;

         }

      }

      return true;

   }

   filemanager::_shell::ImageSet & user::shellimageset()
   {
      return *m_pshellimageset;
   }

   string user::message_box(const char * pszMatter, ::ca::property_set & propertyset)
   {      throw not_implemented(get_app());
   /*      class message_box box(this);
   box.show(pszMatter, propertyset);
   return box.m_strResponse;*/
   return "";
   }

   int32_t user::simple_message_box(::user::interaction * pwndOwner, const char * pszMessage, UINT fuStyle)
   {

      if(m_papp->m_psession != ::null() && m_papp->m_psession->m_pbergedgeInterface != ::null())
      {
         return m_papp->m_psession->m_pbergedgeInterface->simple_message_box(pwndOwner, pszMessage, fuStyle);
      }

      class message_box box(get_app());

      ::ca::property_set propertyset;
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
         return MessageBox(pwndOwner == ::null() ? ::null() : pwndOwner->get_wnd()->get_os_data(), strMessage, m_strAppName, fuStyle);
         }*/
      }
      catch(...)
      {
         string strMessage = pszMessage;
         strMessage.replace("<br>", "\r\n");
         return MessageBox(pwndOwner == ::null() ? ::ca::null() : pwndOwner->get_handle(), strMessage, Application.m_strAppName, fuStyle);
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

   int32_t user::simple_message_box_timeout(::user::interaction * puiOwner, const char * pszMessage, int32_t iTimeout, UINT fuStyle)
   {

      UNREFERENCED_PARAMETER(puiOwner);

      class message_box box(get_app());

      ::ca::property_set propertyset;
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
      throw not_implemented(get_app());
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

   int32_t user::track_popup_menu(const char * pszMatter, point pt, ::user::interaction * puie)
   {
      UNREFERENCED_PARAMETER(pszMatter);
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(puie);
      return 1;
   }


   bool user::get_fs_size(string & strSize, const char * pszPath, bool & bPending)
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

   bool user::get_fs_size(int64_t & i64Size, const char * pszPath, bool & bPending)
   {
      db_server * pcentral = dynamic_cast < db_server * > (&System.m_simpledb.db());
      if(pcentral == ::null())
         return false;
      return pcentral->m_pfilesystemsizeset->get_cache_fs_size(i64Size, pszPath, bPending);
   }

   void user::data_on_after_change(::ca::signal_object * pobj)
   {
      SCAST_PTR(::database::change_event, pchange, pobj);
      if(pchange->m_key.m_idKey == "ca2")
      {
         if(pchange->m_key.m_idIndex  == "savings")
         {
            pchange->data_get(Application.savings().m_eresourceflagsShouldSave);
         }
      }
   }


   ::user::keyboard_focus * user::get_keyboard_focus()
   {
      if(Application.is_session() || Application.is_bergedge())
      {
         ::user::interaction * puieFocus = Application.get_focus_guie();
         if(m_pkeyboardfocus != ::null() && puieFocus != ::null())
         {
            if((bool)oprop("NativeWindowFocus") && puieFocus != m_pkeyboardfocus->get_wnd())
               return ::null();
            return m_pkeyboardfocus;
         }
         else
         {
            return ::null();
         }
      }
      else if(Application.is_system() || Application.is_cube())
      {
         return m_pkeyboardfocus;
      }
      else if(Application.m_psession != ::null())
      {
         return Sess(get_app()).user()->get_keyboard_focus();
      }
      else if(Application.m_psystem != ::null())
      {
         return Sys(get_app()).user()->get_keyboard_focus();
      }
      else
      {
         return ::null();
      }
   }

   void user::set_keyboard_focus(::user::keyboard_focus * pkeyboardfocus)
   {
      if(Application.is_session() || Application.is_bergedge())
      {
         if(pkeyboardfocus == ::null() || pkeyboardfocus->keyboard_focus_OnSetFocus())
         {
            m_pkeyboardfocus = pkeyboardfocus;
         }
         if(Application.m_psystem != ::null())
         {
            return Sys(get_app()).user()->set_keyboard_focus(pkeyboardfocus);
         }
      }
      else if(Application.is_system() || Application.is_cube())
      {
         if(pkeyboardfocus == ::null() || pkeyboardfocus->keyboard_focus_OnSetFocus())
         {
            m_pkeyboardfocus = pkeyboardfocus;
         }
      }
      else if(Application.m_psession != ::null())
      {
         return Sess(get_app()).user()->set_keyboard_focus(pkeyboardfocus);
      }
      else if(Application.m_psystem != ::null())
      {
         return Sys(get_app()).user()->set_keyboard_focus(pkeyboardfocus);
      }
   }

   ::user::mouse_focus * user::get_mouse_focus_LButtonDown()
   {
      return m_pmousefocusLButtonDown;
   }

   void user::set_mouse_focus_LButtonDown(::user::mouse_focus * pmousefocus)
   {
      m_pmousefocusLButtonDown = pmousefocus;
   }

   ::user::mouse_focus * user::get_mouse_focus_RButtonDown()
   {
      return m_pmousefocusRButtonDown;
   }

   void user::set_mouse_focus_RButtonDown(::user::mouse_focus * pmousefocus)
   {
      m_pmousefocusRButtonDown = pmousefocus;
   }


   bool user::set_keyboard_layout(const char * pszPath, bool bUser)
   {

      if(pszPath == ::null())
      {

         if(&keyboard().layout() != ::null())
         {

            if(Application.fontopus().m_puser != ::null()
               && Application.fontopus().m_puser->m_strFontopusServerSessId.has_char())
            {

               data_set("keyboard_layout", keyboard().layout().m_strPath);

            }

            return true;
         }

         if(keyboard().get_current_system_layout().is_empty())
            return false;

         if(!set_keyboard_layout(keyboard().get_current_system_layout(), false))
            return false;

         if(Application.fontopus().m_puser != ::null()
            && Application.fontopus().m_puser->m_strFontopusServerSessId.has_char())
         {

            data_set("keyboard_layout", keyboard().layout().m_strPath);

         }

         return true;
      }

      if(!System.user()->keyboard().load_layout(pszPath, bUser))
         return false;

      Application.simpledb().on_set_keyboard_layout(pszPath, bUser);

      return true;
   }


   ::user::keyboard & user::keyboard()
   {
      if(!Application.is_system())
      {
         return System.user()->keyboard();
      }
      return *m_pkeyboard;
   }


   class window_map & user::window_map()
   {
      return *m_pwindowmap;
   }


   ::ca::type_info user::controltype_to_typeinfo(::user::control::e_type e_type)
   {

      return ::ca::type_info();

   }

   int32_t user::GetVisibleTopLevelFrameCountExcept(::user::interaction * pwndExcept)
   {

      if(m_papp->m_psession->m_pbergedgeInterface->user() == this)
      {

         throw not_implemented(get_app());

      }

      return m_papp->m_psession->m_pbergedgeInterface->user()->GetVisibleTopLevelFrameCountExcept(pwndExcept);

   }

   void user::SendMessageToWindows(UINT message, WPARAM wparam, LPARAM lparam)
   {
      ::user::interaction_ptr_array wnda = Application.frames();
      for(int32_t i = 0; i < wnda.get_size(); i++)
      {
         ::user::interaction * pwnd = wnda.element_at(i);
         if(pwnd != ::null() && pwnd->IsWindow())
         {
            pwnd->send_message(message, wparam, lparam);
            pwnd->SendMessageToDescendants(message, wparam, lparam);
         }
      }
   }


} //namespace user



