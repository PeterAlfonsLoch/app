#pragma once


namespace process
{


   class CLASS_DECL_AURA departament:
      public ::aura::departament
   {
   public:


      class process_thread: virtual public simple_thread
      {
      public:

         string                           m_strCmdLine;
         sp(process)                      m_spprocess;
         string *                         m_pstrRead;
         manual_reset_event *             m_pevReady;
         uint32_t                         m_dwTimeout;
         uint32_t                         m_dwStartTime;
         bool *                           m_pbInitFailure;
         bool *                           m_pbPotentialTimeout;



         process_thread(sp(::aura::application) papp);

         int32_t run();

         bool retry();

      };

      class process_processor :
         virtual public object
      {
      public:


         manual_reset_event               m_evReady;
         bool                             m_bInitFailure;
         bool                             m_bPotentialTimeout;
         process_thread *                 m_pthread;

         process_processor(sp(::aura::application) papp, const string & strCmdLine, DWORD dwTimeOut, string * pstrRead);
         virtual ~process_processor();

      };




      departament(sp(::aura::application) papp);
      virtual ~departament();



      // run process and get output
      virtual var get_output(const char * pszCmdLine,uint32_t dwTimeOut,int32_t iShow = SW_HIDE, bool * pbPotentialTimeout = NULL);
      virtual uint32_t retry(const char * pszCmdLine,uint32_t dwTimeOut,int32_t iShow = SW_HIDE, bool * pbPotentialTimeout = NULL);
      virtual uint32_t synch(const char * pszCmdLine,int32_t iShow = SW_HIDE, const ::duration & dur = ::duration::infinite(), bool * pbPotentialTimeout = NULL);
      virtual bool launch(const char * pszCmdLine,int32_t iShow = SW_HIDE);




   };


} // namespace process


