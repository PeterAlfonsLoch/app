#pragma once


#ifndef METROWIN


namespace ca2
{


   class CLASS_DECL_ca process :
      public ::gen::object
   {
   public:


      class process_thread : virtual public simple_thread
      {
      public:


         ::gen::process       m_process;
         string               m_strRead;
         manual_reset_event   m_evReady;


         process_thread(::ca::application * papp);
         int32_t run();


      };


      class on_retry
      {
      public:
         
         
         uint32_t    m_dwTimeout;
         uint32_t    m_dwStartTime;

      };


      process();
      virtual ~process();



      // run process and get output
      var get_output(const char * pszCmdLine);
      uint32_t retry(const char * pszCmdLine, uint32_t dwTimeOut, int32_t iShow = SW_HIDE);
      uint32_t synch(const char * pszCmdLine, int32_t iShow = SW_HIDE);
      bool launch(const char * pszCmdLine, int32_t iShow = SW_HIDE);


      static int32_t s_on_retry(int32_t iTry, uint_ptr dwParam);


   };


} // namespace ca2


#endif




#pragma once


#ifndef METROWIN

namespace gen
{

   class CLASS_DECL_ca process
   {
   public:


      cross_pipe              m_pipe;
      bool                    m_bPiped;

#ifdef WINDOWSEX

      PROCESS_INFORMATION     m_pi;
      STARTUPINFO             m_si;

#else

      int32_t                     m_iPid;

#endif


      process();
      virtual ~process();


      bool create_child_process(const char * pszCmdLine, bool bPiped, const char * pszDir = NULL);

      uint32_t wait_until_exit(int32_t iWaitMax = 0);
      bool has_exited(uint32_t * pdwExitCode = NULL);

      bool write(const char * psz);
      string read(bool bUntilExit = false);
   };

} // namespace gen



#endif


