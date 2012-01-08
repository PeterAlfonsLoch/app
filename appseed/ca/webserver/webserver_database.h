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

      template < class ARRAY1, class ARRAY2, class ARRAY3, class TYPE1, class TYPE2, class TYPE3 >
      ::count query_rows(const char * pszSql, ARRAY1 & array1, ARRAY2 & array2, ARRAY3 & array3, TYPE1 t1null, TYPE2 t2null, TYPE3 t3null)
      {
         dprint("webserver::database::query_rows");
         prof_enter("webserver::database::query_rows");
         ::count c = mysql::database::query_rows < ARRAY1, ARRAY2, ARRAY3, TYPE1, TYPE2, TYPE3 > (pszSql, array1, array2, array3, t1null, t2null, t3null);
         prof_leave("webserver::database::query_rows");
         return c;
      }


   	string and_instra(var field, var instra);
   	string and_instra_ltgt(var field, var instra);
   	string and_not_instra(var field, var instra);


   };


} // namespace webserver


