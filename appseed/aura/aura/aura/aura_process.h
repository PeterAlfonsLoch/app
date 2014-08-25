#pragma once


namespace aura
{


   class CLASS_DECL_AURA process
   {
   public:


      cross_pipe              m_pipe;
      bool                    m_bPiped;


      process(sp(::aura::application) papp);
      virtual ~process();


      bool create_child_process(const char * pszCmdLine,bool bPiped,const char * pszDir = NULL,int32_t iPriorityClass = ::get_scheduling_priority_none());

      uint32_t wait_until_exit(int32_t iWaitMax = 0);
      bool has_exited(uint32_t * pdwExitCode = NULL);

      bool write(const char * psz);
      string read(bool bUntilExit = false);


   };


} // namespace aura


















