#pragma once


#ifndef METROWIN


namespace core
{


   class CLASS_DECL_CORE process_departament :
      public ::base_departament
   {
   public:


      class process_thread : virtual public simple_thread
      {
      public:


         ::core::process           m_process;
         string                  m_strRead;
         manual_reset_event      m_evReady;


         process_thread(sp(base_application) papp);
         int32_t run();


      };


      class on_retry
      {
      public:


         uint32_t    m_dwTimeout;
         uint32_t    m_dwStartTime;

      };


      process_departament(application * papp);
      virtual ~process_departament();



      // run process and get output
      var get_output(const char * pszCmdLine);
      uint32_t retry(const char * pszCmdLine, uint32_t dwTimeOut, int32_t iShow = SW_HIDE);
      uint32_t synch(const char * pszCmdLine, int32_t iShow = SW_HIDE);
      bool launch(const char * pszCmdLine, int32_t iShow = SW_HIDE);


      static int32_t s_on_retry(int32_t iTry, uint_ptr dwParam);


   };


} // namespace core


#endif

