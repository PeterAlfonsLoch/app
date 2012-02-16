#pragma once


namespace gen
{


   class command_line;


} // namespace gen


class db_server;


namespace simpledb
{


   class CLASS_DECL_ca application :
      virtual public ::database::application
   {
   public:


      db_server   *  m_pserver;


      application();

      virtual bool initialize2();
      virtual bool initialize();
      virtual bool finalize();

      virtual ::database::server * get_data_server();
      virtual db_server & db();

      virtual void on_set_locale(const char * lpcsz, bool bUser);
      virtual void on_set_style(const char * lpcsz, bool bUser);


      virtual bool InitializeDataCentral();
      virtual bool FinalizeDataCentral();

      virtual bool set_keyboard_layout(const char * pszPath, bool bUser);
      virtual void on_set_keyboard_layout(const char * pszPath, bool bUser);

   };


} // namespace simpledb






