#pragma once


namespace process
{


   class CLASS_DECL_AURA process
   {
   public:


      bidi_pipe               m_pipe;
      bool                    m_bPiped;


      process(sp(::aura::application) papp);
      virtual ~process();


      virtual bool create_child_process(const char * pszCmdLine,bool bPiped,const char * pszDir = NULL,int32_t iPriorityClass = ::get_scheduling_priority_none());

      virtual uint32_t wait_until_exit(int32_t iWaitMax = 0);
      virtual bool has_exited(uint32_t * pdwExitCode = NULL);

      virtual bool write(const char * psz);
      virtual string read(bool bUntilExit = false);


   };


} // namespace process






















