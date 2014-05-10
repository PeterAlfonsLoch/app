#include "framework.h"


namespace sockets
{


   sockets::sockets(::base::application * papp) :
     element(papp),
     ::base::departament(papp),
      m_mutexHttpPostBoundary(papp),
      m_mutexResolvCache(papp)
   {

      m_pajpbasesocketinit    = NULL;

   }

   sockets::~sockets()
   {
   }

   bool sockets::initialize1()
   {

      if(!::base::departament::initialize1())
         return false;

      
      if(Application.is_system())
      {

         ::sockets::SSLInitializer ssl_init(m_pbaseapp->m_pbasesystem);

         System.factory().creatable_small < ::file::memory_buffer > ();

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



} // namespace karaoke


