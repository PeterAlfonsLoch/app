#include "framework.h"


namespace userpresence
{


   userpresence::userpresence(sp(::axis::application) papp) :
      element(papp),
      ::axis::departament(papp),
      m_queue(papp)
   {

      m_bUserPresenceFeatureRequired = false;

   }

   userpresence::~userpresence()
   {
   }

   bool userpresence::initialize()
   {


      if (!(bool)System.oprop("do_not_initialize_user_presence"))
      {
         // xxx
         // defer_initialize_user_presence();
         //
      }

      

      return true;

   }

   bool userpresence::finalize()
   {

      if(!m_pbaseapp->is_system())
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

         if(!m_queue.create_message_queue("ca5::user::userpresence::message_queue"))
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

      if(Application.command()->m_varTopicQuery["app"] == "app-core/netnode_dynamic_web_server_cfg")
         return true;

      if(Application.command()->m_varTopicQuery["app"] == "app-core/netnode_dynamic_web_server")
         return true;

      if(Application.command()->m_varTopicQuery["app"] == "app-gtech/sensible_netnode")
         return true;
	  
      if(Application.command()->m_varTopicQuery["app"] == "app-gtech/sensible_service")
         return true;
	  
	  // it may not be initialized, due
      // licensing for example
      if(!session().is_licensed("user_presence", m_bUserPresenceFeatureRequired))
      {
         TRACE("user presence not licensed for this user");
         return false;
      }
      else
      {
         TRACE("user presence is licensed for this user");
      }


      m_queue.SetTimer(8888, 1000, NULL);

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
      || Application.command()->m_varTopicQuery["app"] == "app-core/netnodelite")
         return true;

      if(!is_initialized())
      {
         return true;
      }

      if(m_queue.IsWindow())
      {

         m_queue.KillTimer(1984);

         m_queue.DestroyWindow();

      }

      if(ApplicationUser.m_ppresence != NULL)
      {
         ApplicationUser.m_ppresence.release();
      }

      return true;

      return true;

   }




   bool userpresence::is_initialized()
   {

      if(!m_queue.IsWindow())
         return false;

      return true;

   }


   void userpresence::message_queue_message_handler(signal_details * pobj)
   {

      SCAST_PTR(::message::axis, pbase, pobj);

      if(pbase->m_uiMessage == WM_TIMER)
      {

         SCAST_PTR(::message::timer, ptimer, pobj);

         if(&ApplicationUser != NULL)
         {

            presence * ppresence = ApplicationUser.m_ppresence;

            if(ptimer->m_nIDEvent == 8888 && ppresence != NULL)
            {

               ppresence->defer_pulse_user_presence();

            }

         }

      }

   }



} //namespace userpresence











