#include "StdAfx.h"


namespace netshareservercfg
{


   application::application(void)
   {
      m_strAppName = "netshareservercfg";
      m_strLicense = "";
      m_pconfiguration = NULL;
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
      if(!cube2::application::initialize_instance())
         return false;

	   return true;
   }

   int application::exit_instance()
   {
      
      try
      {
         delete m_pconfiguration;
         m_pconfiguration = NULL;
      }
      catch(...)
      {
      }

      if(!cube::application::exit_instance())
         return false;

	   return true;
   }

   void application::on_request(::ca::create_context * pcreatecontext)
   {
    
      m_pconfiguration = new configuration(this);
      m_pconfiguration->set_configuration();

   }

      


} // namespace netshareservercfg


ca2::library * get_new_library()
{
   return new ::ca2::single_application_library < netshareservercfg::application > ();
}


