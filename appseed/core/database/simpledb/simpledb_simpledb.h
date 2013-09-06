#pragma once


namespace ca2
{


   class command_line;


} // namespace ca2


class db_server;


namespace simpledb
{


   class CLASS_DECL_ca2 simpledb :
      virtual public ::departament,
      virtual public ::database::database
   {
   public:


      db_server   *  m_pserver;


      simpledb(application * papp);
      virtual ~simpledb();

      virtual bool initialize2();
      virtual bool initialize();
      virtual bool finalize();

      virtual ::database::server * get_data_server();
      virtual db_server & db();

      virtual void on_set_locale(const char * lpcsz, bool bUser);
      virtual void on_set_schema(const char * lpcsz, bool bUser);


      virtual bool InitializeDataCentral();
      virtual bool FinalizeDataCentral();

      virtual bool set_keyboard_layout(const char * pszPath, bool bUser);
      virtual void on_set_keyboard_layout(const char * pszPath, bool bUser);

   };


} // namespace simpledb






