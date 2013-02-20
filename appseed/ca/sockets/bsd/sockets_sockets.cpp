#include "framework.h"


namespace sockets
{


   sockets::sockets() :
      m_mutexHttpPostBoundary(get_app()),
      m_mutexResolvCache(get_app())
   {

      m_pajpbasesocketinit    = NULL;

   }


   bool sockets::initialize1()
   {

      if(!::ca::section::initialize1())
         return false;

      
      if(Application.is_system())
      {

         ::sockets::SSLInitializer ssl_init(m_papp->m_psystem);

         System.factory().creatable_small < ::http::memory_file > ();
         System.factory().cloneable_small < ::sockets::ipv4_address > ();
         System.factory().cloneable_small < ::sockets::ipv6_address > ();

         m_pajpbasesocketinit = new AjpBaseSocket::Initializer;
      }

      m_countHttpPostBoundary = 0;

      return true;

   }

   bool sockets::finalize()
   {
    
      if(Application.is_system())
      {
         if(m_pajpbasesocketinit != NULL)
         {
            delete m_pajpbasesocketinit;
            m_pajpbasesocketinit = NULL;
         }
      }

      return true;

   }



} // namespace kar


