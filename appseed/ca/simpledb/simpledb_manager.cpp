#include "framework.h"


namespace simpledb
{


   manager::manager(::ca::applicationsp papp) :
      ca(papp),
      thread(papp),
      ::ca::message_window_simple_callback(papp),
      m_mutexSession(papp),
      m_mutexTagId(papp),
      m_mutexTagName(papp)
   {
      m_dwBuildTimeWindow = 84;
      m_dwBuildTimeRandomWindow = 77 * 5;

      m_iDatabaseWaitTimeOut = 1000 * 1000 * 60;

      begin();

   }

   manager::~manager()
   {
   }



   bool manager::initialize_instance()
   {
      initialize_message_window("::ca2::netnode::cgclcst");

      return true;
   }


   bool manager::handle(socket * psocket)
   {
      primitive::memory memory;
      if(!get_output_internal(psocket->inattr("request_uri"), memory))
      {
         string strError;
         strError = "Error processing command";
         psocket->response().file().write(strError, strError.get_length());
         return false;
      }
      psocket->response().file().write(memory.get_data(), memory.get_size());
      psocket->outheader("Content-Type") = "application/x-ca-var";
      return true;
   }

   bool manager::get_output_internal(const char * pszCommand, primitive::memory & memory)
   {
      UNREFERENCED_PARAMETER(pszCommand);
      UNREFERENCED_PARAMETER(memory);
      return true;
   }



   void manager::message_window_message_handler(::ca::signal_object * pobj)
   {
      SCAST_PTR(::ca::message::base, pbase, pobj);
      if(pbase->m_uiMessage == WM_APP + 13)
      {
         //if(wparam == 0)
           // ((script *) lparam)->Load(false);
         //else if(wparam == 13)
           // ((script *) lparam)->Unload(false);
         pbase->m_bRet = true;
      }
      else if(pbase->m_uiMessage == WM_APP + 14)
      {
      }
   }





   session * & manager::get_session(const char * pszId)
   {
      single_lock sl(&m_mutexSession, TRUE);
      session * & psession = m_mapSession[pszId];
      return psession;
   }



} // namespace simpledb



