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


   int32_t socket_thread::run()
   {

       

      while (get_run_thread())
      {
         
         try
         {
            
            m_psockethandler = create_socket_handler();

            m_psockethandler->EnablePool();

            ::sockets::listen_socket < socket > ll(*m_psockethandler);

            ll.m_strCat = m_strCat;

            ll.m_strCipherList = m_strCipherList;

            ll.m_bDetach = true;

            if (ll.m_strCat.has_char() &&
               (m_iSsl > 0 || (m_iSsl < 0 &&  (m_iPort == 443 || ::str::ends(::str::from(m_iPort), "443")))))
            {
               
               ll.EnableSSL();

            }

            while (true)
            {

               string strIp = m_strIp;

               int iPort = m_iPort;

               if (ll.Bind(strIp, (port_t)iPort))
               {

                  string strMessage;

                  strMessage.Format("could not bind to address %s %d", m_strIp, m_iPort);

                  TRACE(strMessage);

               }
               else
               {

                  m_psockethandler->add(&ll);

               }

               while (m_psockethandler->get_count() > 0 && get_run_thread())
               {

                  m_psockethandler->select(1, 0);

               }

               if (!get_run_thread())
                  break;

            }

         }
         catch (...)
         {

         }

      }

      return 0;

   }


} // namespace netnode



