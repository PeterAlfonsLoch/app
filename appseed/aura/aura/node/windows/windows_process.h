#pragma once


namespace windows
{


   class CLASS_DECL_AURA process :
      virtual public ::aura::process
   {
   public:


      PROCESS_INFORMATION     m_pi;
      STARTUPINFOW             m_si;


      process(sp(::aura::application) papp);
      virtual ~process();


      bool create_child_process(const char * pszCmdLine,bool bPiped,const char * pszDir = NULL,int32_t iPriorityClass = ::get_scheduling_priority_none());

      uint32_t wait_until_exit(int32_t iWaitMax = 0);
      bool has_exited(uint32_t * pdwExitCode = NULL);

      bool write(const char * psz);
      string read(bool bUntilExit = false);

   };


} // namespace windows
