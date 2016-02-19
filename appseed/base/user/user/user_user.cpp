//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{


   user::user(::aura::application * papp):
      ::object(papp),
      ::aura::department(papp)
   {




      //::core::user * papp = dynamic_cast <::core::user *>(::get_thread()->m_pAppThread);
      //::core::connect(papp->m_pcoreapp->m_signalAppLanguageChange, this, &user::VmsGuiiOnAppLanguage);

      //m_pwindowmap = NULL;

   }


   user::~user()
   {

   }


   bool user::initialize1()
   {

      System.factory().creatable_small < ::user::document >();
      System.factory().creatable_small < ::user::application_as_proxy_document >();
      System.factory().creatable_small < ::user::message_queue >();


      if(m_pauraapp->is_session())
      {
         m_pwindowmap = canew(class ::user::window_map(get_app()));
      }
      else
      {
         m_pwindowmap = Session.user()->m_pwindowmap;
      }







      if(m_pauraapp->is_system())
      {
         System.factory().creatable_small < keyboard_layout >();
      }

      //      m_pshellimageset = new filemanager::_shell::ImageSet(m_pauraapp);

      if(!::aura::department::initialize1())
         return false;

      return true;

   }

   bool user::initialize()
   {




      if(!::aura::department::initialize())
         return false;


      TRACE("::user::application::initialize");

      xml::document docUser(get_app());
      string strUser = Application.file().as_string(Application.dir().userappdata()/"langstyle_settings.xml");
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
         Session.set_locale(strLangUser,::action::source_database);
      if(strStyleUser.has_char())
         Session.set_schema(strStyleUser,::action::source_database);

      string strLicense = Application.get_license_id();


      var & varTopicQuey = System.directrix()->m_varTopicQuery;

      bool bHasInstall = varTopicQuey.has_property("install");

      bool bHasUninstall = varTopicQuey.has_property("uninstall");

      debug_print("user::initialize bHasInstall %c", bHasInstall);

      debug_print("user::initialize bHasUninstall %c", bHasUninstall);

      if(!::aura::department::initialize())
         return false;

      return true;

   }




   bool user::initialize2()
   {


      if(!::aura::department::initialize2())
         return false;


      return true;


   }


   bool user::finalize()
   {
      try
      {
         ::aura::department::finalize();
      }
      catch(...)
      {
      }

      /* xxx      try
            {
            if(m_pufeschema != NULL)
            {
            delete m_pufeschema;
            m_pufeschema = NULL;
            }
            }
            catch(...)
            {
            } */

      /* xxx try
      {
      if(m_pufe != NULL)
      {
      delete m_pufe;
      m_pufe = NULL;
      }
      }
      catch(...)
      {
      } */

      /* xxx      try
            {
            if(!BaseMenuCentralContainer::finalize_central_container())
            {
            TRACE("Errors occurred while finalizing BaseMenuCentralContainer");
            }
            }
            catch(...)
            {
            } */

      return true;

   }


   /* xxx   filemanager::_shell::ImageSet & user::shellimageset()
      {
      return *m_pshellimageset;
      }
      */

   /* xxx

   string user::message_box(const char * pszMatter, property_set & propertyset)
   {
   class ::userex::message_box box(get_app());

   box.show(pszMatter, &propertyset);

   return box.m_strResponse;

   }

   int32_t user::simple_message_box(sp(::user::interaction) pwndOwner, const char * pszMessage, UINT fuStyle)
   {

   //if(m_pauraapp->m_pcoreapp->m_psession != NULL)
   //{
   // return m_pauraapp->m_pcoreapp->m_psession->m_pcoresession->m_pcoresession->simple_message_box(pwndOwner, pszMessage, fuStyle);
   //}

   class ::userex::message_box box(get_app());

   property_set propertyset;
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
   if(!box.show(strMatter, &propertyset))
   {
   string strMessage = pszMessage;
   strMessage.replace("<br>", "\r\n");
   return simple_message_box((oswindow) (pwndOwner.is_null() ? NULL : pwndOwner->get_wnd()->get_os_data()), strMessage, Application.m_strAppName, fuStyle);
   }
   }
   catch(...)
   {
   string strMessage = pszMessage;
   strMessage.replace("<br>", "\r\n");
   return simple_message_box(pwndOwner == NULL ? NULL : pwndOwner->get_handle(), strMessage, Application.m_strAppName, fuStyle);
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

   int32_t user::simple_message_box_timeout(sp(::user::interaction) puiOwner, const char * pszMessage, ::duration durationTimeout, UINT fuStyle)
   {

   UNREFERENCED_PARAMETER(puiOwner);

   class ::userex::message_box box(get_app());

   property_set propertyset;
   propertyset["message"] = pszMessage;
   propertyset["simple_message_box_timeout_ms"] = durationTimeout.get_total_milliseconds();

   string strMatter;
   if(fuStyle & MB_YESNOCANCEL)
   {
   strMatter = "system\\user\\simple_message_box\\yesnocancel.xhtml";
   }
   else
   {
   strMatter = "system\\user\\simple_message_box\\ok.xhtml";
   }

   box.show(strMatter, &propertyset);

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

   int32_t user::track_popup_menu(const char * pszMatter, point pt, sp(::user::interaction) puie)
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
   if(pcentral == NULL)
   return false;
   return pcentral->m_pfilesystemsizeset->get_cache_fs_size(i64Size, pszPath, bPending);
   }

   void user::data_on_after_change(signal_details * pobj)
   {
   SCAST_PTR(::database::change_event, pchange, pobj);
   if(pchange->m_key.m_idKey == "ca2")
   {
   if(pchange->m_key.m_idIndex  == "savings")
   {
   pchange->data_get(Session.savings().m_eresourceflagsShouldSave);
   }
   }
   }
   */


   ::user::elemental * user::get_mouse_focus_LButtonDown()
   {

      return m_pmousefocusLButtonDown;

   }


   void user::set_mouse_focus_LButtonDown(::user::elemental * pmousefocus)
   {

      m_pmousefocusLButtonDown = pmousefocus;

   }


   ::user::elemental * user::get_mouse_focus_RButtonDown()
   {
      return m_pmousefocusRButtonDown;
   }


   void user::set_mouse_focus_RButtonDown(::user::elemental * pmousefocus)
   {

      m_pmousefocusRButtonDown = pmousefocus;

   }






   class window_map & user::window_map()
   {

      return *m_pwindowmap;

   }


   /* xxx    sp(type) user::controltype_to_typeinfo(::user::e_control_type e_type)
      {

      return sp(type)();

      } */


   void user::SendMessageToWindows(UINT message,WPARAM wparam,LPARAM lparam)
   {

      synch_lock sl(&Application.m_mutexFrame);

      ::user::interaction * pui = NULL;

      while(Application.get_frame(pui))
      {

         if(pui != NULL && pui->IsWindow())
         {

            pui->send_message(message,wparam,lparam);

            pui->SendMessageToDescendants(message,wparam,lparam);

         }

      }

   }


#ifdef LINUX

   sp(::message::base) user::get_base(XEvent * pevent,::user::interaction * pwnd)
   {

      throw todo(get_app());

      return NULL;

   }

#endif


} //namespace user



