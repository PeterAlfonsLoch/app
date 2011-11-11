#pragma once

namespace ca2
{
   class CLASS_DECL_ca process :
      public ::radix::object
   {
   public:
      process();
      virtual ~process();

      class process_thread : virtual public simple_thread
      {
      public:
         process_thread(::ca::application * papp);
         ::gen::process m_process;
         string m_strRead;
         event m_evReady;
         int run();
      };

      // run process and get output
      var get_output(const char * pszCmdLine);
      DWORD retry(const char * pszCmdLine, DWORD dwTimeOut, int iShow = SW_HIDE);
      DWORD synch(const char * pszCmdLine, int iShow = SW_HIDE);
      bool launch(const char * pszCmdLine, int iShow = SW_HIDE);
   };

} // namespace ca2