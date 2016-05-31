#pragma once


namespace ace
{

   class CLASS_DECL_ACE simple_app:
      virtual public ::ace::system
   {
   public:


      int32_t                       m_argc;
      TCHAR **						m_argv;

      MESSAGE                       m_msg;


      simple_app();
      virtual ~simple_app();

      virtual int32_t main();

      virtual void body();

      virtual int32_t simple_app_pre_run();

      virtual bool intro();
      virtual int32_t refrain();
      virtual bool end();


   };


} // namespace ace




