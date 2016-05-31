#pragma once


namespace ace
{


   class CLASS_DECL_ACE assert_running_task:
      virtual public ::thread
   {
   public:


      string               m_strAppId;
      ::duration           m_durationCheckPeriod;


      assert_running_task(::ace::application * papp,const string & strAppId);
      virtual ~assert_running_task();


      virtual int32_t run();


   };


} // namespace ace



















