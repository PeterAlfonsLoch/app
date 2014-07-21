#include "framework.h"


namespace user
{


   user::user(::base::application * papp) :
      element(papp),
      ::base::departament(papp)
   {
      
      
      m_pkeyboardfocus  = NULL;
//      m_pshellimageset  = NULL;
      m_pkeyboard       = NULL;
  //    m_pufeschema      = NULL;
    //  m_pufe            = NULL;


      //::core::user * papp = dynamic_cast <::core::user *>(::get_thread()->m_pAppThread);
      //::core::connect(papp->m_pplaneapp->m_signalAppLanguageChange, this, &user::VmsGuiiOnAppLanguage);

      m_pkeyboard = NULL;
      //m_pwindowmap = NULL;

   }

   user::~user()
   {
   }


   bool user::initialize1()
   {

      if(m_pbaseapp->is_session())
      {
         m_pwindowmap = new class ::user::window_map(get_app());
      }
      else
      {
         m_pwindowmap = session().user()->m_pwindowmap;
      }

      m_pkeyboard = new ::user::keyboard(m_pbaseapp);

      if(m_pkeyboard == NULL)
         return false;







      if(m_pbaseapp->is_system())
      {
         System.factory().creatable_small < keyboard_layout > ();
      }

//      m_pshellimageset = new filemanager::_shell::ImageSet(m_pbaseapp);

      if(!::base::departament::initialize1())
         return false;

      return true;

   }

   bool user::initialize()
   {




      if(!::base::departament::initialize())
         return false;


      TRACE("::user::application::initialize");

      xml::document docUser(get_app());
      string strUser = session().file().as_string(session().dir().userappdata("langstyle_settings.xml"));
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
         session().set_locale(strLangUser, ::action::source_database);
      if(strStyleUser.has_char())
         session().set_schema(strStyleUser,::action::source_database);

      string strLicense = Application.get_license_id();


      var & varTopicQuey = System.directrix()->m_varTopicQuery;

      bool bHasInstall = varTopicQuey.has_property("install");

      bool bHasUninstall = varTopicQuey.has_property("uninstall");

      if(!(bHasInstall || bHasUninstall)
         && Application.m_bLicense
         && strLicense.has_char())
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

         int32_t iRetry = 3;

retry_license:

         iRetry--;

         if(!session().is_licensed(strLicense))
         {

            Application.license().m_mapInfo.remove_key(strLicense);

            if(iRetry > 0)
               goto retry_license;

            return false;

         }

      }

// xxx      set_data_server(Application.simpledb().get_data_server());


      /* xxx if(!Application.is_system())
      {

         m_pufeschema      = new ::user::front_end_schema(get_app());
         m_pufe            = new ::user::front_end();

      }*/





      //if(Application.m_pdocmanager != NULL)
        // Application.m_pdocmanager->add_document_template(NULL);

//  xxx    if(!BaseMenuCentralContainer::initialize_central_container(get_app()))
  //       return false;


      if(!::base::departament::initialize())
         return false;

      return true;

   }




   bool user::initialize2()
   {


      if(!::base::departament::initialize2())
         return false;

/* xxx

      m_ptemplateForm = new ::user::multiple_document_template(
         get_app(),
         "system/form",
         System.type_info < form_document > (),
         System.type_info < form_frame > (),
         System.type_info < form_view > ());

      m_ptemplateChildForm = new ::user::multiple_document_template(
         get_app(),
         "system/form",
         System.type_info < form_document > (),
         System.type_info < form_child_frame > (),
         System.type_info < form_view > ());

      m_ptemplatePlaceHolder = new ::user::multiple_document_template(
         get_app(),
         "system/form",
         System.type_info < simple_document > (),
         System.type_info < simple_frame_window > (),
         System.type_info < ::user::place_holder > ());

*/

      return true;


   }


   bool user::finalize()
   {
      try
      {
         ::base::departament::finalize();
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

      //if(m_pbaseapp->m_pplaneapp->m_psession != NULL)
      //{
        // return m_pbaseapp->m_pplaneapp->m_psession->m_pplanesession->m_pplanesession->simple_message_box(pwndOwner, pszMessage, fuStyle);
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
            pchange->data_get(session().savings().m_eresourceflagsShouldSave);
         }
      }
   }
   */

   sp(::user::keyboard_focus) user::get_keyboard_focus()
   {
      if(Application.is_session())
      {
         sp(::user::interaction) puieFocus = Application.get_focus_guie();
         if(m_pkeyboardfocus != NULL && puieFocus != NULL)
         {
            if((bool)oprop("NativeWindowFocus") && puieFocus != m_pkeyboardfocus->GetWindow())
               return NULL;
            return m_pkeyboardfocus;
         }
         else
         {
            return NULL;
         }
      }
      else if(Application.is_system())
      {
         return m_pkeyboardfocus;
      }
      else if(Application.m_pbasesession != NULL)
      {
         return sess(get_app()).user()->get_keyboard_focus();
      }
      else if(Application.m_pbasesystem != NULL)
      {
         return sess(get_app()).user()->get_keyboard_focus();
      }
      else
      {
         return NULL;
      }
   }

   void user::set_keyboard_focus(sp(::user::keyboard_focus) pkeyboardfocus)
   {
      if(pkeyboardfocus == NULL || pkeyboardfocus->keyboard_focus_OnSetFocus())
      {
         m_pkeyboardfocus = pkeyboardfocus;
            
         if(m_pkeyboardfocus != NULL)
         {

            if(m_pkeyboardfocus->GetWindow() != NULL)
            {

               m_pkeyboardfocus->GetWindow()->on_keyboard_focus(m_pkeyboardfocus);

            }

         }
            
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


   bool user::set_keyboard_layout(const char * pszPath, ::action::context actioncontext)
   {

      if (get_app()->m_pbasesession == NULL)
         return false;

      if(pszPath == NULL)
      {

         if(&keyboard().layout() != NULL)
         {

            if(session().fontopus()->m_puser != NULL
               && session().fontopus()->m_puser->m_strFontopusServerSessId.has_char())
            {

               // xxx data_set("keyboard_layout", keyboard().layout().m_strPath);

            }

            return true;
         }

         if(keyboard().get_current_system_layout().is_empty())
            return false;

         if(!set_keyboard_layout(keyboard().get_current_system_layout(), ::action::source_database))
            return false;

         if(session().fontopus()->m_puser != NULL
            && session().fontopus()->m_puser->m_strFontopusServerSessId.has_char())
         {

// xxx            data_set("keyboard_layout", keyboard().layout().m_strPath);

         }

         return true;
      }

      if(!session().user()->keyboard().load_layout(pszPath, actioncontext))
         return false;

      // xxx Application.simpledb().on_set_keyboard_layout(pszPath, actioncontext);

      return true;
   }


   ::user::keyboard & user::keyboard()
   {
      if(!Application.is_session())
      {
         return session().user()->keyboard();
      }
      return *m_pkeyboard;
   }


   class window_map & user::window_map()
   {
      return *m_pwindowmap;
   }


/* xxx    sp(type) user::controltype_to_typeinfo(::user::control::e_type e_type)
   {

      return sp(type)();

   } */

   void user::SendMessageToWindows(UINT message, WPARAM wparam, LPARAM lparam)
   {
      ::user::interaction_ptr_array wnda = Application.frames();
      for(int32_t i = 0; i < wnda.get_size(); i++)
      {
         sp(::user::interaction) pwnd = wnda.element_at(i);
         if(pwnd != NULL && pwnd->IsWindow())
         {
            pwnd->send_message(message, wparam, lparam);
            pwnd->SendMessageToDescendants(message, wparam, lparam);
         }
      }
   }



} //namespace user



