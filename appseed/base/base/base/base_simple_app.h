#pragma once


class CLASS_DECL_BASE simple_app :
   virtual public ::base::system
{
public:


   //HINSTANCE                   m_hinstance;
   int32_t                       __argc;
   TCHAR **                      __targv;

   MESSAGE                       m_msg;
   int32_t                       m_iError;


   simple_app();
   virtual ~simple_app();

   virtual int32_t main();

   virtual void body();

   virtual int32_t simple_app_pre_run();

   virtual bool intro();
   virtual int32_t refrain();
   virtual bool end();

   template < class APP >
   static int32_t s_main()
   {

      if(!os_initialize())
      {
         return -1;
      }


      if(!main_initialize())
      {
         return -1;
      }

      APP app;
      
      int32_t iRet = app.main();

      main_finalize();

      os_finalize();

      //finalize_primitive_heap(); 

      //_doexit();
      _term_args();

      return iRet;

   }

};


