#include "StdAfx.h"

namespace netnode
{
   database::database(::ca::application * papp) :
      ca(papp),
      mysql::database(papp)
   {
   }

   mysql::result * database::query(const char * pszSql)
   {
      if(m_pmysql == NULL)
      {
         initialize();
      }
      dprint("<h4>netnode::database::query</h4>");
      dprint(pszSql);
      dprint("<br/>");
      dprint("<h5>query start</h5>");
      until_here();
      prof_enter("netnode::database::query");
      mysql::result * presult = mysql::database::query(pszSql);
      if(presult == NULL)
      {
         initialize();
         presult = mysql::database::query(pszSql);
      }
      prof_leave("netnode::database::query");
      until_here();
      dprint("<h5>query end</h5>");
      return presult;
   }

   var database::query_item(const char * pszSql, var varDefault)
   {
      dprint("netnode::database::query_item");
      prof_enter("netnode::database::query_item");
      var var = mysql::database::query_item(pszSql, varDefault);
      prof_leave("netnode::database::query_item");
      return var;
   }

   var database::query_items(const char * pszSql)
   {
      dprint("netnode::database::query_items");
      prof_enter("netnode::database::query_items");
      var var = mysql::database::query_items(pszSql);
      prof_leave("netnode::database::query_items");
      return var;
   }

   var database::query_row(const char * pszSql)
   {
      dprint("netnode::database::query_row");
      prof_enter("netnode::database::query_row");
      var var = mysql::database::query_row(pszSql);
      prof_leave("netnode::database::query_row");
      return var;
   }

   var database::query_rows(const char * pszSql)
   {
      dprint("netnode::database::query_rows");
      prof_enter("netnode::database::query_rows");
      var var = mysql::database::query_rows(pszSql);
      prof_leave("netnode::database::query_rows");
      return var;
   }

	string database::and_instra(var field, var instra)
	{
		var var(instra);
      var.stra().surround("INSTR(" + field + ", '", "') > 0");
		return gen::str::has_char(var.stra().implode(" AND "), "(" , ")");
	}

	string database::and_instra_ltgt(var field, var instra)
	{
		var var(instra);
      var.stra().surround("INSTR(" + field + ", '<", ">') > 0");
		return gen::str::has_char(var.stra().implode(" AND "), "(" , ")");
	}

	string database::and_not_instra(var field, var instra)
	{
		var var(instra);
      var.stra().surround("INSTR(" + field + ", '", "') = 0");
		return gen::str::has_char(var.stra().implode(" AND "), "(" , ")");
	}

} // namespace netnode