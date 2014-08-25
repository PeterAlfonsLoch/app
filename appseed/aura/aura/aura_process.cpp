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
      return m_pipe.m_sppipeOut->read();
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

      return true;

   }


} // namespace core




