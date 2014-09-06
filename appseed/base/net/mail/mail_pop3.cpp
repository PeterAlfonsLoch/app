#include "base/net/net_sockets.h"


namespace mail
{


   pop3::pop3(sp(::aura::application) papp) :
      element(papp),
      m_handler(papp),
      m_evFinish(papp)
   {
      m_bRun = false;
      m_bSynch = false;
   }



   UINT pop3::pop3_thread_proc(LPVOID lpvoid)
   {
      pop3 * ppop3 = (pop3 *) lpvoid;
      ppop3->run();
      return 0;
   }

   UINT pop3::run()
   {
      m_psocket = new pop3_socket(m_handler);
      m_psocket->m_ppop3 = this;
      int32_t iPort = 995;
      if(iPort == 995)
      {
         m_psocket->m_bSsl = true;
         m_psocket->EnableSSL();
      }
      m_psocket->open(::net::address(get_host(), (port_t) iPort));
      m_handler.add(m_psocket);
      m_handler.select(1,0);
      while(m_bRun && m_psocket->m_estate != pop3_socket::state_finished)
      {
         m_handler.select(1,0);
      }
      m_bRun = false;
      m_evFinish.SetEvent();
      return 0;
   }

   void pop3::start()
   {
      if(m_bRun)
         return;
      m_bRun = true;
      if(m_bSynch)
      {
         run();
      }
      else
      {
         __begin_thread(get_app(), pop3_thread_proc, this);
      }
   }


   void pop3::filter_id()
   {
   }


   void pop3::store()
   {
   }


   void pop3::update_lists()
   {
   }


   string pop3::get_user()
   {
      return "";
   }

   string pop3::get_pass()
   {
      return "";
   }

   string pop3::get_host()
   {
      return "";
   }

   string pop3::get_transaction()
   {
      return "STAT";
   }

   void pop3::set_stat_count(int32_t iCount)
   {
      UNREFERENCED_PARAMETER(iCount);
   }

   void pop3::set_stat_size(int32_t iSize)
   {
      UNREFERENCED_PARAMETER(iSize);
   }

   void pop3::set_list_size(int32_t iSize)
   {
      UNREFERENCED_PARAMETER(iSize);
   }

   void pop3::on_finished_transaction()
   {
   }

} // namespace mail
