#include "framework.h"


namespace sockets
{


   sockets::sockets(::ca::application * papp) :
     ca(papp),
     ::ca::section(papp),
      m_mutexHttpPostBoundary(papp),
      m_mutexResolvCache(papp)
   {

      m_pajpbasesocketinit    = ::null();

   }

   sockets::~sockets()
   {
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
         if(m_pajpbasesocketinit != ::null())
         {
            delete m_pajpbasesocketinit;
            m_pajpbasesocketinit = ::null();
         }
      }

      return true;

   }



} // namespace karaoke


