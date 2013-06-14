#include "framework.h"


namespace userpresence
{


   userpresence::userpresence(sp(::ca2::application) papp) :
      ca2(papp),
      ::ca2::section(papp),
      message_window_simple_callback(papp)
   {

      m_bUserPresenceFeatureRequired = false;

   }

   userpresence::~userpresence()
   {
   }

   bool userpresence::initialize()
   {




      defer_initialize_user_presence();

      return true;

   }

   bool userpresence::finalize()
   {

      if(!m_papp->is_system())
      {
         defer_finalize_user_presence();
      }

      return true;

   }

   bool userpresence::defer_initialize_user_presence()
   {

      if(!is_initialized())
      {

         //if(m_spuiMessage.is_null())
         {
           // m_spuiMessage = canew(::user::interaction());
         }
   
         if(!initialize_message_window("ca5::user::userpresence::message_window"))
            return false;

      }


      string strQuery = Application.command()->m_varTopicQuery["app"];

      if(Application.command()->m_varTopicQuery.has_property("install")
      || Application.command()->m_varTopicQuery.has_property("uninstall"))
         return true;

      if(Application.command()->m_varTopicQuery["app"] == "simpledbcfg"
      || Application.command()->m_varTopicQuery["app"] == "app-core/netnodelite"
      || Application.command()->m_varTopicQuery["app"] == "netshareclient")
         return true;

      if(Application.command()->m_varTopicQuery["app"] == "app-core/mydns")
         return true;

      if(Application.command()->m_varTopicQuery["app"] == "app-core/netnodecfg")
         return true;

      // it may not be initialized, due
      // licensing for example
      if(!Application.is_licensed("user_presence", m_bUserPresenceFeatureRequired))
      {
         TRACE("user presence not licensed for this user");
         return false;
      }
      else
      {
         TRACE("user presence is licensed for this user");
      }


      m_spuiMessage->SetTimer(1984, 1000, NULL);

      if(ApplicationUser.m_ppresence == NULL)
      {
         presence * ppresence = new presence(get_app());
         ppresence->report_activity();
         ppresence->pulse_user_presence();
         ApplicationUser.m_ppresence = ppresence;
      }

      return true;

   }

   bool userpresence::defer_finalize_user_presence()
   {

      if(!is_initialized())
         return true;

      if(Application.command()->m_varTopicQuery.has_property("install")
      || Application.command()->m_varTopicQuery.has_property("uninstall"))
         return true;

      if(Application.command()->m_varTopicQuery["app"] == "simpledbcfg"
      || Application.command()->m_varTopicQuery["app"] == "core_netnodelite")
         return true;

      if(!is_initialized())
      {
         return true;
      }

      if(m_spuiMessage.is_set() && m_spuiMessage->IsWindow())
      {
      
         m_spuiMessage->KillTimer(1984);

      }

      finalize_message_window();

      if(ApplicationUser.m_ppresence != NULL)
      {
         ApplicationUser.m_ppresence.release();
      }

      return true;

      return true;

   }




   bool userpresence::is_initialized()
   {

      if(m_spuiMessage.is_null())
         return false;


      if(!m_spuiMessage->IsWindow())
         return false;

      return true;

   }


   void userpresence::message_window_message_handler(::ca2::signal_object * pobj)
   {

      SCAST_PTR(::ca2::message::base, pbase, pobj);

      if(pbase->m_uiMessage == WM_TIMER)
      {

         SCAST_PTR(::ca2::message::timer, ptimer, pobj);

         if(&ApplicationUser != NULL)
         {

            presence * ppresence = ApplicationUser.m_ppresence;

            if(ptimer->m_nIDEvent == 1984 && ppresence != NULL)
            {

               ppresence->defer_pulse_user_presence();

            }

         }

      }

   }



} //namespace userpresence











