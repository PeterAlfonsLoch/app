#include "framework.h"


namespace process
{


   departament::departament(sp(::aura::application) papp):
      element(papp),
      ::aura::departament(papp)
   {

   }


   departament::~departament()
   {

   }


   var departament::get_output(const char * pszCmdLine,uint32_t dwTimeout,int32_t iShow, bool * pbPotentialTimeout)
   {

      string strRead;



      evReady.ResetEvent();

      bool

      process_thread * pthread = new process_thread(get_app(),&strRead,&evReady);

      pthread->m_pb = pbPotentialTimeout;

      pthread->m_bAutoDelete = true;

      if(!pthread->m_spprocess->create_child_process(pszCmdLine,true))
         return false;

      pthread->begin();

      evReady.wait();

      return strRead;

   }



   uint32_t departament::retry(const char * pszCmdLine,uint32_t dwTimeout,int32_t iShow, bool * pbPotentialTimeout)
   {

      manual_reset_event evReady(get_app());

      evReady.ResetEvent();

      process_thread * pthread = new process_thread(get_app(), NULL,&evReady);

      pthread->m_pb = pbPotentialTimeout;

      pthread->m_bAutoDelete = true;

      pthread->m_strCmdLine = pszCmdLine;

      pthread->begin();

      evReady.wait();

      return strRead;


   }


   uint32_t departament::synch(const char * pszCmdLine,int32_t iShow, const ::duration & dur, bool * p)
   {

      if(dur.is_pos_infinity())
      {

         return retry(pszCmdLine,0,iShow);

      }
      else
      {

         return retry(pszCmdLine,dur.get_total_milliseconds(),iShow);

      }

   }

   bool departament::launch(const char * pszCmdLine,int32_t iShow)
   {

      const char * pszEnd = NULL;

      string strBin = consume_param(pszCmdLine,&pszEnd);

#ifndef METROWIN

      int32_t iOk = call_async(strBin,pszEnd,NULL,iShow);

      return iOk != 0;

#else

      throw todo(get_app());

#endif

   }

   departament::process_thread::process_thread(sp(::aura::application) papp,string * pstrRead,manual_reset_event * pevReady, DWORD dwTimeOut):
      element(papp),
      thread(papp),
      simple_thread(papp),
      m_spprocess(allocer()),
      m_pstrRead(pstrRead),
      m_pevReady(pevReady)
   {

      m_bPotentialTimeout     = false;
      m_bInitFailure          = false;

   }


   int32_t departament::process_thread::run()
   {

      if(!m_spprocess->create_child_process(m_strCmdLine,true))
      {

         m_bInitFailure = true;

         if(m_pevReady != NULL)
         {

            m_pevReady->SetEvent();

         }

         return false;

      }

      m_dwStartTime = ::get_tick_count();

      string strRead;

      while(!m_spprocess->has_exited())
      {

         strRead = m_spprocess->m_pipe.m_sppipeOut->read();

         if(m_pstrRead != NULL)
         {

            *m_pstrRead += strRead;

         }

         if(!retry())
            break;

         Sleep(100);

      }

      while(get_run())
      {

         strRead = m_spprocess->m_pipe.m_sppipeOut->read();

         if(strRead.is_empty())
         {

            break;

         }
         else
         {

            if(m_pstrRead != NULL)
            {

               *m_pstrRead += strRead;

            }

         }

      }

      if(m_pevReady != NULL)
      {

         m_pevReady->SetEvent();

      }

      return 0;

   }


   bool departament::process_thread::retry()
   {

      if(m_dwTimeout > 0 && ::get_tick_count() - m_dwStartTime > m_dwTimeout)
      {

         if(m_pbPotentialTimeout != NULL)
         {

            *m_pbPotentialTimeout = true;

         }

         return false;

      }

      return true;

   }


   departament::process_processor::process_processor(sp(::aura::application) papp, const string & strCmdLine, DWORD dwTimeOut, string * pstrRead) :
      element(papp)
      m_evReady(papp)
   {

      m_pthread = new process

   }

   departament::process_processor::process_processor
   {
   }



} // namespace process




