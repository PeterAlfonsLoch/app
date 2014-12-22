#include "framework.h"


namespace sockets
{


   sockets::sockets(::aura::application * papp) :
      element(papp),
      ::aura::departament(papp),
      m_mutexHttpPostBoundary(papp),
      m_mutexResolvCache(papp)
   {

      m_pajpbasesocketinit    = NULL;

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

      if(Application.is_system())
      {

/*            ::sockets::SSLInitializer ssl_init(m_psystem);*/

         //System.factory().creatable_small < ::http::memory_file > ();
         //System.factory().cloneable_large < ::sockets::winrt_address  >  (System.template type_info < ::net::address_base > ());
/*            System.factory().cloneable_small < ::sockets::ipv4_address > ();
         System.factory().cloneable_small < ::sockets::ipv6_address > ();*/

         m_pajpbasesocketinit = new AjpBaseSocket::Initializer;
      }

      m_countHttpPostBoundary = 0;

      return true;

   }

   bool sockets::finalize()
   {

      bool bOk = true;

      if(Application.is_system())
      {
         if(m_pajpbasesocketinit != NULL)
         {
            delete m_pajpbasesocketinit;
            m_pajpbasesocketinit = NULL;
         }
      }

      return bOk;

   }


   void sockets::http_config_proxy(const char * pszUrl, http_tunnel * psocket)
   {
      UNREFERENCED_PARAMETER(pszUrl);
      //UNREFERENCED_PARAMETER(psocket);
      //throw not_implemented(get_app());
      psocket->m_bDirect = true;
   }


   ::sockets::net & sockets::net()
   {
      return *m_spnet;
   }

} // namespace kar


