#include "framework.h"


namespace netserver
{


   socket_thread::socket_thread(::aura::application * papp) :
      ::object(papp),
      thread(papp)
   {

      m_iPort = 80;
      m_iSsl = -1;

   }


   socket_thread::~socket_thread()
   {

   }


   ::netserver::socket_handler * socket_thread::create_socket_handler()
   {

      return new netserver::socket_handler(get_app());


   }


   ::sockets::listen_socket_base * socket_thread::create_listen_socket()
   {

      return new ::sockets::listen_socket < socket > (*m_psockethandler);

   }

   bool socket_thread::initialize_listen_socket()
   {

      m_plistensocket->m_strCat = m_strCat;

      m_plistensocket->m_strCipherList = m_strCipherList;

      m_plistensocket->m_bDetach = true;

      if (m_plistensocket->m_strCat.has_char() &&
         (m_iSsl > 0 || (m_iSsl < 0 && (m_iPort == 443 || ::str::ends(::str::from(m_iPort), "443")))))
      {

         m_plistensocket->EnableSSL();

      }

      return true;

   }

   int32_t socket_thread::run()
   {

       

      while (get_run_thread())
      {
         
         try
         {
            
            m_psockethandler = create_socket_handler();

            m_psockethandler->EnablePool();

            m_plistensocket = create_listen_socket();

            initialize_listen_socket();

            while (true)
            {

               if (m_plistensocket->Bind(m_strIp, (port_t)m_iPort))
               {

                  string strMessage;

                  strMessage.Format("could not bind to address %s %d", m_strIp, m_iPort);

                  TRACE(strMessage);

               }
               else
               {

                  m_psockethandler->add(m_plistensocket);

               }

               while (m_psockethandler->get_count() > 0 && get_run_thread())
               {

                  m_psockethandler->select(1, 0);

               }

               if (!get_run_thread())
               {

                  break;

               }

            }

         }
         catch (...)
         {

         }

      }

      return 0;

   }


} // namespace netnode



