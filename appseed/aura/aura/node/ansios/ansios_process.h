#pragma once


namespace ansios
{


   class CLASS_DECL_CORE process :
      virtual ::aura::process
   {
   public:


      int32_t                     m_iPid;


      process();
      virtual ~process();


      bool create_child_process(const char * pszCmdLine,bool bPiped,const char * pszDir = NULL,int32_t iPriorityClass = ::get_scheduling_priority_none());

      uint32_t wait_until_exit(int32_t iWaitMax = 0);
      bool has_exited(uint32_t * pdwExitCode = NULL);


   };


} // namespace ansios



