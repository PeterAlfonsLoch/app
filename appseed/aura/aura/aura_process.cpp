#include "framework.h"



namespace aura
{


   process::process():
      m_pipe(true)
   {

      m_bPiped = false;

   }


   process::~process()
   {


   }


   bool process::create_child_process(const char * pszCmdLine,bool bPiped,const char * pszDir,int32_t iCa2Priority)
   {

      if(bPiped)
      {
         if(!m_pipe.create(false))
            return false;
      }

      m_bPiped = bPiped;

      return true;

   }


   bool process::write(const char * psz)
   {
      return m_pipe.m_sppipeIn->write(psz);
   }

   string process::read(bool bUntilExit)
   {
      UNREFERENCED_PARAMETER(bUntilExit);
      return m_pipe.m_sppipeOut.read();
   }

   uint32_t process::wait_until_exit(int32_t iWaitMax)
   {
      uint32_t dwExitCode = 0;
      uint32_t dwStartTime = ::get_tick_count();
      int32_t i = 1;
      while(true)
      {
         if(has_exited(&dwExitCode))
            break;
         if(iWaitMax >= 0 && get_tick_count() > dwStartTime + iWaitMax)
            break;
         Sleep(100);
         i++;
      }
      return dwExitCode;
   }

   bool process::has_exited(uint32_t * puiExitCode)
   {


#ifdef WINDOWSEX

      DWORD dwExitCode;
      bool bExited;


      if(!GetExitCodeProcess(m_pi.hProcess,&dwExitCode))
      {

         bExited = true;

      }
      else
      {

         if(dwExitCode == STILL_ACTIVE)
         {

            bExited = false;

         }
         else
         {

            bExited = true;

         }

      }

      if(puiExitCode != NULL)
      {

         *puiExitCode = dwExitCode;
      }
      return bExited;

#elif defined(METROWIN)

      throw todo(get_thread_app());

#else
      int32_t iExitCode;
      //      bool bExited;

      int32_t wpid = waitpid(m_iPid,&iExitCode,
         0
#ifdef WNOHANG
         | WNOHANG
#endif
#ifdef WCONTINUED
         | WCONTINUED
#endif
         );

      if(wpid == -1)
         return true;

      if(WIFEXITED(iExitCode))
      {
         if(puiExitCode != NULL)
         {
            *puiExitCode = WEXITSTATUS(iExitCode);

         }
         return false;
      }
      else if(WIFSIGNALED(iExitCode))
      {
         if(puiExitCode != NULL)
         {
            *puiExitCode = WTERMSIG(iExitCode);
         }
         return false;
      }
      else if(WIFSTOPPED(iExitCode))
      {
         if(puiExitCode != NULL)
         {
            *puiExitCode = WSTOPSIG(iExitCode);
         }
         return false;
      }
#ifdef WIFCONTINUED
      else if(WIFCONTINUED(iExitCode))
      {
         return false;
      }
#endif

      return false;



#endif


   }


} // namespace core



#endif


