#include "StdAfx.h"
#include "mysql/mysql.h"


namespace mysql
{

   database::database(::ca::application * papp) :
      ca(papp)
   {
      m_pmysql = NULL;
   }

   database::~database()
   {
      if(m_pmysql != NULL)
      {
         close();
      }
   }
      
      
   bool database::connect(
      const char * pszHost, 
      const char * pszUser,
      const char * pszPassword, 
      const char * pszDatabase,
      int iPort,
      const char * pszSocketName,
      unsigned int uiFlags)
   {
      /* initialize connection handler */
      m_pmysql = mysql_init (NULL);
      if(m_pmysql == NULL)
      {
         trace_error1("mysql_init() failed (probably out of primitive::memory)\n");
       m_pmysql = NULL;
         return false;
      }
      if(mysql_real_connect(
         (MYSQL *) m_pmysql, 
         pszHost, 
         pszUser,
         pszPassword,
         pszDatabase, 
         iPort,
         pszSocketName, 
         uiFlags) == NULL)
      {
         trace_error1( "mysql_real_connect() failed\n");
         mysql_close((MYSQL *) m_pmysql);
         m_pmysql = NULL;
         return false;
      }
      mysql_query((MYSQL *) m_pmysql, "SET NAMES 'utf8' COLLATE 'utf8_unicode_ci'");
      mysql_query((MYSQL *) m_pmysql, "SET CHARACTER SET 'utf8'");
      return true;
   }

   bool database::close()
   {
      if(m_pmysql == NULL)
         return false;
      for(int i = 0; i < m_resultptra.get_count(); i++)
      {
         if(m_resultptra[i]->m_bAutoDelete)
         {
            delete m_resultptra[i];
         }
      }
      mysql_close((MYSQL *) m_pmysql);
      m_pmysql = NULL;
      return true;
   }

   string database::error1(const char * pszPrefix)
   {
      string strPrefix(pszPrefix);
      string strFormat;
      if(m_pmysql == NULL)
      {
         strFormat = "mysql error => NULL sql connection pointer";
      }
      else
      {
         strFormat.Format(
            "mysql error => %u (%s): %s\n",
            mysql_errno((MYSQL *) m_pmysql),
            mysql_sqlstate((MYSQL *) m_pmysql),
            mysql_error((MYSQL *) m_pmysql));
      }
      if(strPrefix.has_char())
         return strPrefix + ": " + strFormat;
      else
         return strPrefix + strFormat;
   }

   void database::trace_error1(const char * pszPrefix)
   {
      TRACE0(error1(pszPrefix));
   }

   result * database::query(const char * pszSql)
   {
      MYSQL_RES * pres;
     if(m_pmysql == NULL)
     {
       trace_error1("Could not execute statement (0)");
       return NULL;
     }
     try
     {
        if(mysql_query((MYSQL *) m_pmysql, pszSql) != 0) /* the statement failed */
        {
          trace_error1("Could not execute statement");
          return NULL;
        }
     }
     catch(...)
     {
       trace_error1("Could not execute statement (2)");
       return NULL;
     }
      /* the statement succeeded; determine whether it returned data */
      pres = mysql_store_result ((MYSQL *) m_pmysql);
      if(pres) /* a result set was returned */
      {
         m_iLastUsedTime = ::ca::profiler::micros();
         return new result(this, true, pres);
      }
      else /* no result set was returned */
      {
         /*
         * does the lack of a result set mean that the statement didn't
         * return one, or that it should have but an error occurred?
         */
         if (mysql_errno ((MYSQL *) m_pmysql) == 0)
         {
            /*
            * statement generated no result set (it was not a SELECT,
            * SHOW, DESCRIBE, etc.); just report rows-affected value.
            */
            m_iLastUsedTime = ::ca::profiler::micros();
            TRACE("Number of rows affected: %lu\n", (unsigned long) mysql_affected_rows ((MYSQL *) m_pmysql));
            return new result(this, true, NULL);
         }
         else /* an error occurred */
         {
            trace_error1 ("Could not retrieve result set");
            return NULL;
         }
      }
   }

   var database::query_item(const char * pszSql, var varDefault)
   {
      result * presult = query(pszSql);
      if(presult == NULL)
         return varDefault;
      MYSQL_ROW row = (MYSQL_ROW) presult->fetch_row();
      if(row == NULL)
         return varDefault;
      else if(row[0] == NULL)
         return gen::g_nullconst;
      else
         return var(row[0]);
   }
   var database::query_items(const char * pszSql)
   {
      result * presult = query(pszSql);
      if(presult == NULL)
         return gen::g_newconst;
      var a;
      MYSQL_ROW row;
      int i = 0;
      while((row = (MYSQL_ROW) presult->fetch_row()) != NULL)
      {
         if(row[0] == NULL)
            a.propset().add(gen::str::itoa(i), gen::g_nullconst);
         else
            a.propset().add(gen::str::itoa(i), var(row[0]));
         i++;
      }
      return a;
   }
   var database::query_row(const char * pszSql)
   {
      result * presult = query(pszSql);
      if(presult == NULL)
         return gen::g_newconst;
      MYSQL_ROW row = (MYSQL_ROW) presult->fetch_row();
      if(row == NULL)
         return gen::g_newconst;
      var a;
      int iNumFields = presult->num_fields();
      for(int j = 0; j < iNumFields; j++)
      {
         if(row[j] == NULL)
            a.propset().add(gen::str::itoa(j), gen::g_nullconst);
         else
            a.propset().add(gen::str::itoa(j), var(row[j]));
      }
      return a;
   }
   var database::query_rows(const char * pszSql)
   {
      result * presult = query(pszSql);
      if(presult == NULL)
         return gen::g_newconst;
      MYSQL_ROW row;
      var a;
      var a2;
      int i = 0;
      while((row = (MYSQL_ROW) presult->fetch_row()) != NULL)
      {
         int iNumFields = presult->num_fields();
         a2.propset().m_propertya.remove_all();
         for(int j = 0; j < iNumFields; j++)
         {
            if(row[j] == NULL)
               a2.propset().add(gen::str::itoa(j), gen::g_nullconst);
            else
               a2.propset().add(gen::str::itoa(j), var(row[j]));
         }
         a.propset().add(gen::str::itoa(i), a2);
         i++;
      }
      return a;
   }

   var database::query_table_item(const char * table, const char * item, const char *where, var notfound)
   {
      string strSql;
      strSql.Format("SELECT `$item` FROM `$table` WHERE $where", item, table, where);
      return query_item(strSql, notfound);
   }


   var database::get_agent(const char * pszTable, const char * psz, const char * pszUser)
   {
      string strSql;
      string strAgent(psz);
      string strTable(pszTable);
      strSql = "SELECT id FROM " + strTable + " WHERE value='" + strAgent + "'";
      string strId = query_item(strSql);

      if(strId.is_empty())
      {
         strId = query_item("SELECT MAX(id) FROM " + strTable + " ORDER BY id");
         if(strId.is_empty())
         {
            strId = string("0000000000000000") + string("0000000000000000") + string("0000000000000000") + string("0000000000000000")
                  + string("0000000000000000") + string("0000000000000000") + string("0000000000000000") + string("0000000000000000")
                  + string("0000000000000000") + string("0000000000000000") + string("0000000000000000") + string("0000000000000000")
                  + string("0000000000000000") + string("0000000000000000") + string("0000000000000000") + string("000000000000000");
         }
         else
         {
            gen::str::increment_digit_letter(strId);
         }
         strSql = "INSERT INTO " + strTable + "(`id`, `value`) VALUES('" + strId + "', '" + strAgent + "')";
         if(!query(strSql))
            return false;
      }
      if(pszUser != NULL)
      {
         if(!query("UPDATE " + strTable + " SET `user` = '" + string(pszUser) + "' WHERE `id` = '" + strId + "'"))
            return false;
      }
      return strId;
   }


   string database::real_escape_string(void * p, int iLen)
   {
      string str;
      char * psz = str.GetBufferSetLength(iLen * 2 + 1);
      if(psz == NULL)
         throw memory_exception();
      mysql_real_escape_string((MYSQL *) m_pmysql, psz, (const char *) p, iLen);
      str.ReleaseBuffer();
      return str;
   }
   string database::real_escape_string(const char * psz)
   {
      return real_escape_string((void *) psz, strlen(psz));
   }

   var database::get_insert_id()
   {
      string str;
      str.Format("%I64d", mysql_insert_id((MYSQL *) m_pmysql));
      return str;
   }

} //   namespace mysql