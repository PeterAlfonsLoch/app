#pragma once


namespace webserver
{


   class CLASS_DECL_ca database :
      virtual public mysql::database,
      virtual public dynamic_source::ptr
   {
   public:
      database(::ca::application * papp);


      virtual bool initialize() = 0;
      virtual mysql::result * query(const char * pszSql);
      virtual var query_item(const char * pszSql, var varDefault = gen::g_newconst);
      virtual var query_items(const char * pszSql);
      virtual var query_row(const char * pszSql);
      virtual var query_rows(const char * pszSql);

   	string and_instra(var field, var instra);
   	string and_instra_ltgt(var field, var instra);
   	string and_not_instra(var field, var instra);


   };


} // namespace webserver


