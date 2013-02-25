#pragma once

#pragma once


#ifndef METROWIN


namespace ca
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

} // namespace ca



#endif


