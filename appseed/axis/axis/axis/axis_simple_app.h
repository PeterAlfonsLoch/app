#pragma once


namespace axis
{

   class CLASS_DECL_AXIS app:
      virtual public ::axis::system
   {
   public:


      int32_t                       m_argc;
      TCHAR **                      m_argv;

      MESSAGE                       m_msg;


      app();
      virtual ~app();

      virtual int32_t main();

      virtual void body();

      virtual int32_t simple_app_pre_run();

      virtual bool intro();
      virtual int32_t refrain();
      virtual bool end();


   };


} // namespace axis




