#pragma once


namespace core
{


   class command_line;


} // namespace core


class db_server;


namespace simpledb
{


   class CLASS_DECL_CORE simpledb :
      virtual public ::base::departament,
      virtual public ::database::database
   {
   public:


      db_server   *  m_pserver;


      simpledb(::base::application * papp);
      virtual ~simpledb();

      virtual bool initialize2();
      virtual bool initialize();
      virtual bool finalize();

      virtual ::database::server * get_data_server();
      virtual db_server & db();

      virtual void on_set_locale(const char * lpcsz, ::action::context actioncontext);
      virtual void on_set_schema(const char * lpcsz, ::action::context actioncontext);


      virtual bool InitializeDataCentral();
      virtual bool FinalizeDataCentral();

      virtual bool set_keyboard_layout(const char * pszPath, ::action::context actioncontext);
      virtual void on_set_keyboard_layout(const char * pszPath, ::action::context actioncontext);

   };


} // namespace simpledb






