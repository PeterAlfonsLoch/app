#pragma once


namespace ansios
{


   class CLASS_DECL_AURA process :
      virtual public ::process::process
   {
   public:


      int32_t                     m_iPid;


      process(::ace::application * papp);
      virtual ~process();


      virtual bool create_child_process(const char * pszCmdLine,bool bPiped,const char * pszDir = NULL,int32_t iPriorityClass = ::multithreading::priority_none);

      virtual bool has_exited(uint32_t * pdwExitCode = NULL);

      virtual int32_t synch_elevated(const char * pszCmdLine,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut);

   };


} // namespace ansios



