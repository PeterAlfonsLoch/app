#pragma once

namespace gen
{
   class command_line;
}

class db_server;


namespace simpledb
{

   class CLASS_DECL_ca application :
      virtual public ::user::application
   {
   protected:


      db_server   * m_pserver;


   public:


      application();


      virtual bool initialize();
      virtual bool finalize();

      virtual ::database::server * get_data_server();
      virtual db_server & db();

      virtual void on_set_locale(const char * lpcsz, bool bUser);
      virtual void on_set_style(const char * lpcsz, bool bUser);
      virtual void on_set_keyboard_layout(const char * pszPath, bool bUser);

   protected:
      virtual bool InitializeDataCentral();
      virtual bool FinalizeDataCentral();
   };


   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

} // namespace simpledb
