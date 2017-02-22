//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{


   user::user(::aura::application * papp):
      ::object(papp),
      ::aura::department(papp)
   {

      m_pufeschema = NULL;
      m_pufe = NULL;

   }


   user::~user()
   {

   }


   bool user::initialize1()
   {

      m_pufeschema = new ::user::front_end_schema(get_app());
      m_pufe = new ::user::front_end();



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
      

      ::aura::del(m_pufeschema);

      ::aura::del(m_pufe);


      try
      {

         ::aura::department::finalize();

      }
      catch(...)
      {

      }

      return true;

   }


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


   void user::SendMessageToWindows(UINT message,WPARAM wparam,LPARAM lparam)
   {

      synch_lock sl(&Application.m_mutexFrame);

      sp(::user::interaction) pui;

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

   ::user::front_end_schema * GetUfeSchema(::aura::application * papp)
   {

      return Sess(papp).user()->GetUfeSchema();

   }


   ::user::front_end * GetUfe(::aura::application * papp)
   {

      return Sess(papp).user()->GetUfe();

   }


   ::user::front_end_schema * user::GetUfeSchema()
   {

      return m_pufeschema;

   }


   ::user::front_end * user::GetUfe()
   {

      return m_pufe;

   }

   sp(type) user::controltype_to_typeinfo(::user::e_control_type e_type)
   {

      return sp(type)();

   }



} //namespace user



