#pragma once


namespace gen
{

   class CLASS_DECL_ca process
   {
   public:


      cross_pipe              m_pipe;
      bool                    m_bPiped;

#ifdef WINDOWS

      PROCESS_INFORMATION     m_pi;
      STARTUPINFO             m_si;

#else

      int                     m_iPid;

#endif


      process();
      virtual ~process();


      bool create_child_process(const char * pszCmdLine, bool bPiped, const char * pszDir = NULL);

      DWORD wait_until_exit(int iWaitMax = 0);
      bool has_exited(DWORD * pdwExitCode = NULL);

      bool write(const char * psz);
      string read(bool bUntilExit = false);
   };

} // namespace gen
