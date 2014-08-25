#pragma once


namespace windows
{


   class CLASS_DECL_AURA process :
      virtual public ::process::process
   {
   public:


      PROCESS_INFORMATION     m_pi;
      STARTUPINFOW             m_si;


      process(sp(::aura::application) papp);
      virtual ~process();


      virtual bool create_child_process(const char * pszCmdLine,bool bPiped,const char * pszDir = NULL,int32_t iPriorityClass = ::get_scheduling_priority_none());

      virtual bool has_exited(uint32_t * pdwExitCode = NULL);


   };


} // namespace windows
