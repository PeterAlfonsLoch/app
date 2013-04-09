#include "framework.h"


namespace userpresence
{


   userpresence::userpresence(sp(::ca::application) papp) :
      ca(papp),
      message_window_simple_callback(papp)
   {

      m_bUserPresenceFeatureRequired = false;

   }

   userpresence::~userpresence()
   {
   }

   bool userpresence::initialize()
   {




      if(!defer_initialize_user_presence())
         return false;

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

      if(Application.command()->m_varTopicQuery["app"] == "mydns")
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


      m_spuiMessage->SetTimer(1984, 1000, ::null());

      if(ApplicationUser.m_ppresence == ::null())
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

      m_spuiMessage->KillTimer(1984);

      finalize_message_window();

      if(ApplicationUser.m_ppresence != ::null())
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


   void userpresence::message_window_message_handler(::ca::signal_object * pobj)
   {

      SCAST_PTR(::ca::message::base, pbase, pobj);

      if(pbase->m_uiMessage == WM_TIMER)
      {

         SCAST_PTR(::ca::message::timer, ptimer, pobj);

         if(&ApplicationUser != ::null())
         {

            presence * ppresence = ApplicationUser.m_ppresence;

            if(ptimer->m_nIDEvent == 1984 && ppresence != ::null())
            {

               ppresence->defer_pulse_user_presence();

            }

         }

      }

   }



} //namespace userpresence











