#include "framework.h" // #include "axis/net/sockets/bsd/sockets.h"
#include "axis/net/net_sockets.h"


namespace sockets
{


   sockets::sockets(::aura::application * papp) :
     ::object(papp),
     ::aura::department(papp),
      m_mutexHttpPostBoundary(papp),
      m_mutexResolvCache(papp),
      m_clientcontextmap(papp),
      m_servercontextmap(papp)
   {

      m_iReturnCode = -1;

      m_psslinit = new ::sockets::SSLInitializer(get_app());

      m_pajpaxissocketinit    = NULL;

   }

   sockets::~sockets()
   {

      if(m_psslinit != NULL)
      {

         delete m_psslinit;

         m_psslinit = NULL;

      }


   }


   bool sockets::initialize1()
   {

      m_spnet = canew(::sockets::net(get_app()));
      //m_spnet.alloc(allocer());

      if(m_spnet.is_null())
      {

         m_iReturnCode = -1986;

         return false;

      }


      if(!m_spnet->initialize())
         return false;

      if(!::aura::department::initialize1())
         return false;


      m_spportforward = Application.alloc(System.type_info < ::net::port_forward > ());




      if(Application.is_system())
      {


         System.factory().creatable_small < ::file::memory_buffer > ();

         m_pajpaxissocketinit = new AjpBaseSocket::Initializer;

      }

      m_countHttpPostBoundary = 0;

      return true;

   }

   bool sockets::finalize()
   {


      bool bOk = true;


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

      try
      {
         m_spportforward.release();
      }
      catch(...)
      {
      }

      try
      {

         if(!m_spnet->finalize())
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

         m_spnet.release();

      }
      catch(...)
      {

         m_iReturnCode = -86;

      }


      if(Application.is_system())
      {
         if(m_pajpaxissocketinit != NULL)
         {
            delete m_pajpaxissocketinit;
            m_pajpaxissocketinit = NULL;
         }
      }

      return bOk;

   }

   ::sockets::net & sockets::net()
   {
      return *m_spnet;
   }



} // namespace karaoke



