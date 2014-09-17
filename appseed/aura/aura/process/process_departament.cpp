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


   var departament::get_output(const char * pszCmdLine,const ::duration & dur,int32_t iShow, bool * pbPotentialTimeout)
   {

      string strRead;

      process_processor proc(get_app(), pszCmdLine, dur, pbPotentialTimeout, &strRead);

      return strRead;

   }



   uint32_t departament::retry(const char * pszCmdLine,const ::duration & dur,int32_t iShow, bool * pbPotentialTimeout)
   {

      process_processor proc(get_app(), pszCmdLine, dur, pbPotentialTimeout);

      return proc.m_uiRetCode;


   }


   uint32_t departament::synch(const char * pszCmdLine,int32_t iShow, const ::duration & dur, bool * pbPotentialTimeout)
   {

      process_processor proc(get_app(), pszCmdLine, dur, pbPotentialTimeout);

      return proc.m_uiRetCode;

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

   departament::process_thread::process_thread(sp(::aura::application) papp, const string & strCmdLine, const ::duration & dur, bool * pbPotentialTimeout, string * pstrRead):
      element(papp),
      thread(papp),
      simple_thread(papp),
      m_spprocess(allocer()),
      m_pstrRead(pstrRead),
      m_strCmdLine(strCmdLine)
   {

      if(dur.is_pos_infinity())
      {

         m_uiTimeout = 0;

      }
      else
      {

         m_uiTimeout = dur.get_total_milliseconds();

      }


      m_pbPotentialTimeout    = pbPotentialTimeout;
      m_pbInitFailure         = NULL;

   }


   int32_t departament::process_thread::run()
   {
   
   
      if(!m_spprocess->create_child_process(m_strCmdLine,true))
      {

         if(m_pbInitFailure != NULL)
         {

            *m_pbInitFailure = true;

         }

         if(m_pevReady != NULL)
         {

            m_pevReady->SetEvent();

         }

         return false;

      }

      m_uiStartTime = ::get_tick_count();

      string strRead;

      while(!m_spprocess->has_exited(m_puiRetCode))
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

      if(m_uiTimeout > 0 && ::get_tick_count() - m_uiStartTime > m_uiTimeout)
      {

         if(m_pbPotentialTimeout != NULL)
         {

            *m_pbPotentialTimeout = true;

         }

         return false;

      }

      return true;

   }


   departament::process_processor::process_processor(sp(::aura::application) papp, const string & strCmdLine, const duration & dur, bool * pbPotentialTimeout, string * pstrRead) :
      element(papp),
      m_evReady(papp)
   {
   
      m_uiRetCode = -1;

      m_bInitFailure = false;

      m_bPotentialTimeout = false;

      m_pbPotentialTimeout = pbPotentialTimeout;

      m_pthread = new process_thread(papp, strCmdLine, dur, &m_bPotentialTimeout, pstrRead);

      m_pthread->m_bAutoDelete = true;

      m_pthread->m_pbInitFailure = &m_bInitFailure;

      m_pthread->m_pbPotentialTimeout = &m_bPotentialTimeout;

      m_pthread->m_pevReady = &m_evReady;
      
      m_pthread->m_puiRetCode = &m_uiRetCode;

      m_evReady.ResetEvent();

      m_pthread->begin();

      m_evReady.wait();

   }

   departament::process_processor::~process_processor()
   {

      if(m_pbPotentialTimeout != NULL)
      {

         *m_pbPotentialTimeout = m_bPotentialTimeout;

      }

   }



} // namespace process




