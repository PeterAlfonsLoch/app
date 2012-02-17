#include "StdAfx.h"


namespace cube8
{


   CLASS_DECL_ca2 LPFN_instantiate_application g_lpfn_instantiate_application = NULL;


   application::application()
   {


      m_dir.set_app(this);
      m_file.set_app(this);
      m_http.set_app(this);

      m_bIfs            = true;


   }

   application::~application()
   {
   }



   int application::exit_instance()
   {

      m_iReturnCode = 0;

      try
      {
         m_iReturnCode = ::ca2::fontopus::application::exit_instance();
      }
      catch(...)
      {
      }

      try
      {
         System.unregister_bergedge_application(this);
      }
      catch(...)
      {
      }

      try
      {
         if(System.appptra().get_count() <= 1)
         {
            System.PostThreadMessageA(WM_QUIT, 0, 0);
         }
      }
      catch(...)
      {
      }



      return m_iReturnCode;
   }

   /*bool application::is_licensed(const char * pszId, bool bInteractive)
   {
      return license().has(pszId, bInteractive);
   }

   class ::fontopus::license & application::license()
   {
      return m_splicense;
   }*/

   /*
      ::radix::application * pradixapp = dynamic_cast < ::radix::application * > (papp);
      if(pradixapp != NULL)
      {
         try
         {
            pradixapp->m_dwAlive = ::GetTickCount();
         }
         catch(...)
         {
         }
      }
   */

   bool application::initialize()
   {


      if(!::ca2::fontopus::application::initialize())
         return false;



      m_dwAlive = ::GetTickCount();

      m_splicense(new class ::fontopus::license(this));


      if(!is_system())
      {
         System.register_bergedge_application(this);
      }




      return true;

   }

   bool application::initialize1()
   {

      if(!is_system() && !is_bergedge())
      {
         if(m_spfsdata.is_null())
            m_spfsdata(new ::fs::set(this));
         ::fs::set * pset = dynamic_cast < ::fs::set * > ((class ::fs::data *) m_spfsdata);
         pset->m_spafsdata.add(new ::fs::native(this));
         stringa stra;
         pset->root_ones(stra);
      }


      if(m_puser == NULL &&
        (App(this).directrix().m_varTopicQuery.has_property("install")
      || App(this).directrix().m_varTopicQuery.has_property("uninstall")))
      {
         m_puser                 = new ::fontopus::user(this);
         m_puser->m_strLogin     = "system";
         create_user(m_puser);
      }

      if(!::ca2::fontopus::application::initialize1())
         return false;


      return true;

   }


   /*class ::fs::data * application::fs()
   {
      return m_spfsdata;
   }*/


   void application::set_title(const char * pszTitle)
   {

      Bergedge.set_app_title(m_strAppName, pszTitle);

   }


   /*bool application::on_install()
   {
      return ::ca2::fontopus::application::on_install();
   }

   bool application::on_uninstall()
   {
      return ::ca2::fontopus::application::on_uninstall();
   }

   bool application::is_serviceable()
   {
      return ::ca2::fontopus::application::is_serviceable();
   }

   service_base * application::allocate_new_service()
   {
      return ::ca2::fontopus::application::allocate_new_service();
   }*/


} //namespace cube8


