#include "StdAfx.h"


namespace ca4
{

   application::application()
   {
      m_signal.connect(this, &::ca4::application::on_application_signal);
   }

   application::~application()
   {
   }

   bool application::base_support()
   {

      if(!ca2::application::base_support())
         return false;

      if(m_strBaseSupportId.is_empty())
      {
         gen::property_set propertyset;
         message_box("err\\developer\\base_support\\support_id_not_specified.xml", propertyset);
         return false;
      }

      return true;

   }

   bool application::initialize()
   {

      if(is_system())
      {
         System.factory().cloneable_large < ::xml::node > ();
         System.m_plicense = new class ::fontopus::license(m_psystem);
      }

      if(!ca2::application::initialize())
         return false;

      if(!colorertake5::application::initialize())
         return false;

      if(is_system())
      {
         ::sockets::SSLInitializer ssl_init(m_psystem);
         System.m_pcopydesk = new class copydesk();
         System.m_pcopydesk->create(this);
         if(!System.copydesk().initialize())
            return false;
      }

      return true;
   }



   void application::on_application_signal(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(signal_object, psignal, pobj);
      /*if(psignal->m_esignal == signal_exit_instance)
      {
         if(m_copydesk.is_set()
         && m_copydesk->IsWindow())
         {
            m_copydesk->DestroyWindow();
         }
      }*/
   }


   int application::exit_instance()
   {
      try
      {
         if(is_system())
         {
            if(System.m_pcopydesk != NULL)
            {
               (*System.m_pcopydesk)->DestroyWindow();
               delete System.m_pcopydesk;
               System.m_pcopydesk = NULL;
            }
            gen::del(System.m_plicense);
         }
      }
      catch(...)
      {
      }
      try
      {
         ::ca2::application::exit_instance();
      }
      catch(...)
      {
      }
      return 0;
   }

} //namespace ca8