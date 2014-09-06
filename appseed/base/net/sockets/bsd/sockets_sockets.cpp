#include "base/net/net_sockets.h"


namespace sockets
{


   sockets::sockets(::aura::application * papp) :
     element(papp),
     ::aura::departament(papp),
      m_mutexHttpPostBoundary(papp),
      m_mutexResolvCache(papp)
   {

      m_psslinit = new ::sockets::SSLInitializer(this);

      m_pajpbasesocketinit    = NULL;

   }

   sockets::~sockets()
   {
   }

   bool sockets::initialize1()
   {

      m_spnet = canew(::sockets::net(this));
      //m_spnet.alloc(allocer());

      if(m_spnet.is_null())
      {

         m_iReturnCode = -1986;

         return false;

      }


      if(!m_spnet->initialize())
         return false;

      if(!::aura::departament::initialize1())
         return false;

      
      if(Application.is_system())
      {


         System.factory().creatable_small < ::file::memory_buffer > ();

         m_pajpbasesocketinit = new AjpBaseSocket::Initializer;

      }

      m_countHttpPostBoundary = 0;

      return true;

   }

   bool sockets::finalize()
   {


      try
      {

         if(!m_spnet->gudo_set())
         {

            m_iReturnCode = -87;

         }

      }
      catch(...)
      {

         m_iReturnCode = -87;

      }
      try
      {

         if(m_spportforward.is_set())
         {

            m_spportforward.release();

         }

      }
      catch(...)
      {

         bOk = false;

      }


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

   ::sockets::net & sockets::net()
   {
      return *m_spnet;
   }



} // namespace karaoke


