#include "framework.h"


namespace userex
{


   userex::userex(sp(::axis::application) papp):
      element(papp),
      ::axis::departament(papp),
      ::user::core(papp)
   {


         m_pshellimageset  = NULL;
         m_pufeschema      = NULL;
         m_pufe            = NULL;


         //::core::user * papp = dynamic_cast <::core::user *>(::get_thread()->m_pAppThread);
         //::core::connect(papp->m_pcoreapp->m_signalAppLanguageChange, this, &userex::VmsGuiiOnAppLanguage);

         //m_pwindowmap = NULL;

      }

   userex::~userex()
   {
   }


   bool userex::initialize1()
   {








      if(m_paxisapp->is_system())
      {
         System.factory().creatable_small < keyboard_layout >();
      }

      m_pshellimageset = new filemanager::_shell::ImageSet(m_paxisapp);

      if(!::axis::departament::initialize1())
         return false;

      return true;

   }

   bool userex::initialize()
   {


      if(!::user::core::initialize())
         return false;


      Application.simpledb().get_data_server()->add_client(this);


      TRACE("::userex::application::initialize");

      xml::document docUser(get_app());
      string strUser = Application.file().as_string(Application.dir().userappdata("langstyle_settings.xml"));
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
         Session.set_locale(strLangUser,::action::source::database());
      if(strStyleUser.has_char())
         Session.set_schema(strStyleUser,::action::source::database());

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

         int32_t iRetry = 1;

      retry_license:

         iRetry--;

         if(!Session.is_licensed(strLicense))
         {

            Session.licensing().m_mapInfo.remove_key(strLicense);

            if(iRetry > 0)
               goto retry_license;

            return false;

         }

      }

      set_data_server(Application.simpledb().get_data_server());


      if(!Application.is_system())
      {

         m_pufeschema      = new ::user::front_end_schema(get_app());
         m_pufe            = new ::user::front_end();

      }

      if(Application.is_system())
      {


         // form
         System.factory().creatable_small < form_document >();
         System.factory().creatable_small < pane_tab_view >();
         System.factory().creatable_small < form_frame >();
         System.factory().creatable_small < form_child_frame >();
         System.factory().creatable_small < form_view >();


         // hour (alarm configuration with ease ...

         System.factory().creatable_small < hour_list_view >();
         System.factory().creatable_small < minute_list_view >();
         System.factory().creatable_small < second_list_view >();
         System.factory().creatable_small < simple_toolbar >();
         System.factory().creatable_small < OrtoButton >();

      }


      //if(Application.m_pdocmanager != NULL)
      // Application.m_pdocmanager->add_document_template(NULL);

      if(!BaseMenuCentralContainer::initialize_central_container(get_app()))
         return false;


      if(!::axis::departament::initialize())
         return false;

      return true;

   }




   bool userex::initialize2()
   {


      if(!::axis::departament::initialize2())
         return false;

      m_ptemplateForm = new ::user::multiple_document_template(
         get_app(),
         "system/form",
         System.type_info < form_document >(),
         System.type_info < form_frame >(),
         System.type_info < form_view >());

      m_ptemplateChildForm = new ::user::multiple_document_template(
         get_app(),
         "system/form",
         System.type_info < form_document >(),
         System.type_info < form_child_frame >(),
         System.type_info < form_view >());

      m_ptemplatePlaceHolder = new ::user::multiple_document_template(
         get_app(),
         "system/form",
         System.type_info < simple_document >(),
         System.type_info < simple_frame_window >(),
         System.type_info < ::user::place_holder >());


      return true;


   }


   bool userex::finalize()
   {
      try
      {
         ::axis::departament::finalize();
      }
      catch(...)
      {
      }

      try
      {
         if(m_pufeschema != NULL)
         {
            delete m_pufeschema;
            m_pufeschema = NULL;
         }
      }
      catch(...)
      {
      }

      try
      {
         if(m_pufe != NULL)
         {
            delete m_pufe;
            m_pufe = NULL;
         }
      }
      catch(...)
      {
      }

      try
      {
         if(!BaseMenuCentralContainer::finalize_central_container())
         {
            TRACE("Errors occurred while finalizing BaseMenuCentralContainer");
         }
      }
      catch(...)
      {
      }

      return true;

   }


   filemanager::_shell::ImageSet & userex::shellimageset()
   {

      return *m_pshellimageset;

   }


   string userex::message_box(const char * pszMatter,property_set & propertyset)
   {

      class ::userex::message_box box(get_app());

      box.show(pszMatter,&propertyset);

      return box.m_strResponse;

   }


   int32_t userex::simple_message_box(sp(::user::interaction) pwndOwner,const char * pszMessage,UINT fuStyle)
   {

      int iRet = ::simple_message_box(pwndOwner->get_safe_handle(), pszMessage, "ca2", fuStyle);

      return iRet;

      class ::userex::message_box box(get_app());

      property_set propertyset;
      propertyset["message"] = pszMessage;
      propertyset["application_name"] = pwndOwner == NULL ? Application.m_strAppName : App(pwndOwner->get_app()).m_strAppName;

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
         if(!box.show(strMatter,&propertyset))
         {
            string strMessage = pszMessage;
            strMessage.replace("<br>","\r\n");
            return ::simple_message_box((oswindow)(pwndOwner.is_null() ? NULL : pwndOwner->GetWindow()->get_os_data()),strMessage,Application.m_strAppName,fuStyle);
         }
      }
      catch(...)
      {
         string strMessage = pszMessage;
         strMessage.replace("<br>","\r\n");
         return ::simple_message_box(pwndOwner == NULL ? NULL : pwndOwner->get_handle(),strMessage,Application.m_strAppName,fuStyle);
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

   int32_t userex::simple_message_box_timeout(sp(::user::interaction) puiOwner,const char * pszMessage,::duration durationTimeout,UINT fuStyle)
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

      box.show(strMatter,&propertyset);

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

   int32_t userex::track_popup_menu(const char * pszMatter,point pt,sp(::user::interaction) puie)
   {
      UNREFERENCED_PARAMETER(pszMatter);
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(puie);
      return 1;
   }


   bool userex::get_fs_size(string & strSize,const char * pszPath,bool & bPending)
   {
      int64_t i64Size;
      if(!get_fs_size(i64Size,pszPath,bPending))
      {
         strSize.Empty();
         return false;
      }
      if(i64Size > 1024 * 1024 * 1024)
      {
         double d = (double)i64Size / (1024.0 * 1024.0 * 1024.0);
         strSize.Format("%0.2f GB",d);
      }
      else if(i64Size > 1024 * 1024)
      {
         double d = (double)i64Size / (1024.0 * 1024.0);
         strSize.Format("%0.1f MB",d);
      }
      else if(i64Size > 1024)
      {
         double d = (double)i64Size / (1024.0);
         strSize.Format("%0.0f KB",d);
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

   bool userex::get_fs_size(int64_t & i64Size,const char * pszPath,bool & bPending)
   {
      db_server * pcentral = dynamic_cast <db_server *> (&System.m_simpledb.db());
      if(pcentral == NULL)
         return false;
      return pcentral->m_pfilesystemsizeset->get_cache_fs_size(i64Size,pszPath,bPending);
   }

   void userex::data_on_after_change(signal_details * pobj)
   {
      SCAST_PTR(::database::change_event,pchange,pobj);
      if(pchange->m_key.m_idKey == "ca2")
      {
         if(pchange->m_key.m_idIndex == "savings")
         {
            pchange->data_get(Session.savings().m_eresourceflagsShouldSave);
         }
      }
   }


   sp(type) userex::controltype_to_typeinfo(::user::control::e_type e_type)
   {

      return sp(type)();

   }

   void userex::SendMessageToWindows(UINT message,WPARAM wparam,LPARAM lparam)
   {
      ::user::interaction_ptr_array wnda = Application.frames();
      for(int32_t i = 0; i < wnda.get_size(); i++)
      {
         sp(::user::interaction) pwnd = wnda.element_at(i);
         if(pwnd != NULL && pwnd->IsWindow())
         {
            pwnd->send_message(message,wparam,lparam);
            pwnd->SendMessageToDescendants(message,wparam,lparam);
         }
      }
   }






   void userex::add_document_template(sp(::user::impact_system) ptemplate)
   {
      if(Application.m_pdocmanager == NULL)
         Application.m_pdocmanager = new ::user::document_manager(get_app());
      Application.m_pdocmanager->add_document_template(ptemplate);
   }


   void userex::defer_add_document_template(sp(::user::impact_system) ptemplate)
   {
      sp(::user::impact_system) puserbasetemplate = (ptemplate);

      if(puserbasetemplate == NULL)
         throw "should add user base document template";

      add_document_template(puserbasetemplate);

   }

   sp(::user::document) userex::_vmsguserbaseOpenDocumentFile(const char * lpszFileName)
   {
      ASSERT(Application.m_pdocmanager != NULL);
      sp(::create_context) cc(allocer());
      cc->m_spCommandLine->m_varFile = lpszFileName;
      return (Application.m_pdocmanager->open_document_file(cc));
   }


   void  userex::AddToRecentFileList(const char * lpszPathName)
   {

      UNREFERENCED_PARAMETER(lpszPathName);

   }

   void  userex::_001CloseAllDocuments(bool bEndSession)
   {
      if(Application.m_pdocmanager != NULL)
      {
         Application.m_pdocmanager->close_all_documents(bEndSession);
      }
   }


   ::user::front_end_schema * GetUfeSchema(sp(::axis::application) papp)
   {

      return App(papp).userex()->GetUfeSchema();

   }

   ::user::front_end * GetUfe(sp(::axis::application) papp)
   {
      return App(papp).userex()->GetUfe();
   }


   void userex::_001OnFileNew()
   {
      Application.m_pdocmanager->_001OnFileNew();
   }

   ::user::front_end_schema * userex::GetUfeSchema()
   {
      return m_pufeschema;
   }

   ::user::front_end * userex::GetUfe()
   {
      return m_pufe;
   }



   int32_t userex::exit_instance()
   {

      return 0;

   }




   int32_t userex::GetVisibleFrameCountExcept(sp(::user::interaction) pwndExcept)
   {
      ::user::interaction_ptr_array wnda = Application.frames();
      int32_t iCount = 0;
      for(int32_t i = 0; i < wnda.get_size(); i++)
      {
         sp(::user::interaction) pwnd = wnda.element_at(i);
         if(pwnd != NULL &&
            pwnd != pwndExcept &&
            pwnd->IsWindowVisible())
         {
            iCount++;
         }
      }
      return iCount;
   }

   int32_t userex::GetVisibleTopLevelFrameCountExcept(sp(::user::interaction) pwndExcept)
   {
      ::user::interaction_ptr_array wnda = Application.frames();
      int32_t iCount = 0;
      for(int32_t i = 0; i < wnda.get_size(); i++)
      {
         sp(::user::interaction) pwnd = wnda.element_at(i);
         if(pwnd != NULL &&
            pwnd != pwndExcept &&
            pwnd->IsWindow() &&
            pwnd->IsWindowVisible() &&
            !(pwnd->GetStyle() & WS_CHILD))
         {
            iCount++;
         }
      }
      return iCount;
   }

   int32_t userex::GetVisibleFrameCount()
   {
      ::user::interaction_ptr_array wnda = Application.frames();
      int32_t iCount = 0;
      for(int32_t i = 0; i < wnda.get_size(); i++)
      {
         sp(::user::interaction) pwnd = wnda.element_at(i);
         if(pwnd != NULL
            && pwnd->IsWindow()
            && pwnd->IsWindowVisible())
         {
            iCount++;
         }
      }
      return iCount;
   }

   void userex::VmsGuiiOnAppLanguage(signal_details * pobject)
   {
      SendMessageToWindows(::base::application::APPM_LANGUAGE,0,(LPARAM)pobject);
   }


   sp(::form_document) userex::create_form(sp(form_view) pview,::user::form_callback * pcallback,sp(::user::interaction) pwndParent,var var)
   {
      sp(::form_document) pdoc;
      if(m_ptemplateForm == NULL)
         return NULL;
      sp(::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible                   = false;
      createcontext->m_puiParent                      = pwndParent;
      createcontext->m_puiAlloc                       = pview;

      if(var.get_type() == var::type_propset && var.has_property("hold") && !(bool)var["hold"])
      {
         createcontext->m_bHold                       = false;
      }

      pdoc = (m_ptemplateForm->open_document_file(createcontext));
      pview = pdoc->get_typed_view < form_view >();
      pdoc->get_html_data()->m_pform = pview;
      pdoc->get_html_data()->m_pform->m_pcallback = pcallback;
      return pdoc;
   }

   sp(::form_document) userex::create_form(::user::form_callback * pcallback,sp(::user::interaction) pwndParent,var var)
   {
      if(pwndParent != NULL && pwndParent->m_paxisapp != get_app())
      {
         return App(pwndParent->m_paxisapp).userex()->create_form(pcallback,pwndParent,var);
      }
      sp(::form_document) pdoc;
      if(m_ptemplateForm == NULL)
         return NULL;
      sp(::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible                   = false;
      createcontext->m_puiParent                      = pwndParent;
      if(var.get_type() == var::type_propset && var.has_property("hold") && !(bool)var["hold"])
      {
         createcontext->m_bHold                       = false;
      }

      pdoc = (m_ptemplateForm->open_document_file(createcontext));
      sp(::user::impact) pview = pdoc->get_view(0);
      pdoc->get_html_data()->m_pform =  (pview);
      pdoc->get_html_data()->m_pform->m_pcallback = pcallback;
      return pdoc;
   }


   sp(::form_document) userex::create_child_form(sp(form_view) pview,::user::form_callback * pcallback,sp(::user::interaction) pwndParent,var var)
   {
      sp(::form_document) pdoc;
      if(m_ptemplateChildForm == NULL)
         return NULL;
      sp(::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible                   = false;
      createcontext->m_puiParent                      = pwndParent;
      createcontext->m_puiAlloc                       = pview;

      if(var.get_type() == var::type_propset && var.has_property("hold") && !(bool)var["hold"])
      {
         createcontext->m_bHold                       = false;
      }

      pdoc = (m_ptemplateChildForm->open_document_file(createcontext));
      pview = pdoc->get_typed_view < form_view >();
      pdoc->get_html_data()->m_pform = pview;
      pdoc->get_html_data()->m_pform->m_pcallback = pcallback;
      return pdoc;
   }

   sp(::form_document) userex::create_child_form(::user::form_callback * pcallback,sp(::user::interaction) pwndParent,var var)
   {
      if(pwndParent != NULL && pwndParent->m_paxisapp != get_app())
      {
         return App(pwndParent->m_paxisapp).userex()->create_child_form(pcallback,pwndParent,var);
      }
      if(m_ptemplateChildForm == NULL)
         return NULL;
      sp(::form_document) pdoc;
      sp(::create_context) createcontext(allocer());
      createcontext->m_bMakeVisible                   = false;
      createcontext->m_puiParent                      = pwndParent;
      pdoc = (m_ptemplateChildForm->open_document_file(createcontext));
      sp(::user::impact) pview = pdoc->get_view(0);
      pdoc->get_html_data()->m_pform =  (pview);
      pdoc->get_html_data()->m_pform->m_pcallback = pcallback;
      return pdoc;
   }


   sp(::user::document) userex::hold(sp(::user::interaction) pui)
   {

      sp(::create_context) createcontext(allocer());

      createcontext->m_bMakeVisible    = false;
      createcontext->m_bHold           = false;

      sp(simple_document) pdoc =  (m_ptemplatePlaceHolder->open_document_file(createcontext));

      sp(::user::place_holder) pholder = pdoc->get_typed_view < ::user::place_holder  >();

      pholder->hold(pui);

      return pdoc;

   }


   bool userex::_001OnCmdMsg(::axis::cmd_msg * pcmdmsg)
   {

      UNREFERENCED_PARAMETER(pcmdmsg);

      return false;

   }


} //namespace userex



