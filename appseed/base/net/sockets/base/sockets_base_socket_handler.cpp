#include "framework.h"


namespace sockets
{


   base_socket_handler::base_socket_handler(sp(::aura::application) papp, logger * plogger) :
      element(papp),
      m_splogger(plogger)
   {

   }


   base_socket_handler::~base_socket_handler()
   {

   }


   void base_socket_handler::set_logger(logger * plogger)
   {

      m_splogger = plogger;

   }

   void base_socket_handler::log(base_socket * psocket, const string & strUser, int iError,const string & strSystem, ::axis::log::e_level elevel)
   {

      if(m_splogger.is_null())
         return;

      m_splogger->log(this, psocket, strUser, iError, strSystem, elevel);

   }


} // namespace sockets




