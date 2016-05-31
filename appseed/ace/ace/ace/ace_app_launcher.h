#pragma once


namespace ace
{


   class CLASS_DECL_AURA app_launcher:
      virtual public ::launcher
   {
   public:


      string m_strApp;


      app_launcher(const string & strApp) { m_strApp = strApp;  }


      virtual string get_executable_path();

      virtual string get_params();

      virtual bool start();

   };




} // namespace ace




