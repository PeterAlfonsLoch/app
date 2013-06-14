#pragma once


#ifndef METROWIN


namespace ca2
{


   class CLASS_DECL_ca2 process_section :
      public ::ca2::section
   {
   public:


      class process_thread : virtual public simple_thread
      {
      public:


         ::ca2::process           m_process;
         string                  m_strRead;
         manual_reset_event      m_evReady;


         process_thread(sp(::ca2::application) papp);
         int32_t run();


      };


      class on_retry
      {
      public:
         
         
         uint32_t    m_dwTimeout;
         uint32_t    m_dwStartTime;

      };


      process_section(::ca2::application * papp);
      virtual ~process_section();



      // run process and get output
      var get_output(const char * pszCmdLine);
      uint32_t retry(const char * pszCmdLine, uint32_t dwTimeOut, int32_t iShow = SW_HIDE);
      uint32_t synch(const char * pszCmdLine, int32_t iShow = SW_HIDE);
      bool launch(const char * pszCmdLine, int32_t iShow = SW_HIDE);


      static int32_t s_on_retry(int32_t iTry, uint_ptr dwParam);


   };


} // namespace ca2


#endif

