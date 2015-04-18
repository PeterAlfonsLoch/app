#pragma once


namespace aura
{


   class CLASS_DECL_AURA simple_app_launcher:
      virtual public ::launcher
   {
   public:


      string m_strApp;


      simple_app_launcher(const string & strApp) { m_strApp = strApp; }


      virtual string get_executable_path();

      virtual string get_params();

   };




} // namespace aura





