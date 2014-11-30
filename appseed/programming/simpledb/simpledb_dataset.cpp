#include "framework.h"

namespace simpledb
{

   int32_t callback(void * res_ptr,int32_t ncol, char** reslt,char** cols);

   set::set() :
      ::database::set()
   {
      //errmsg      = NULL;
      haveError   = false;
      db          = NULL;
   }


   set::set(base *newDb) :
      ::database::set(newDb)
   {
      //errmsg      = NULL;
      haveError = false;
      db = newDb;
   }

   set::~set()
   {
      //  if(errmsg != NULL)
      //  {
      //      sqlite_free_table(&errmsg);
      // }
   }

   bool set::exec(const char * pszSql)
   {
      database::result_set * r = (database::result_set *) &m_resultset;
      r->record_header.remove_all();
      r->records.remove_all();

      string strInstruction = sql_consume_keyword(pszSql);

      if(strInstruction == "select")
      {
         return sql_do_select(pszSql);
      }
      else if(strInstruction == "insert")
      {
         return sql_do_insert(pszSql);
      }

      return false;
   }
      /*if (!handle())
      {
         TRACE("vmssqlite::set::exec: No Database Connection");
         m_strQueryErrorMessage = "No Database Connection";
         m_strDatabaseErrorMessage = "No Database Connection";
         return false;
      }*/
/*      m_resultsetExec.record_header.remove_all();
      m_resultsetExec.records.remove_all();
   database::result_set* r = (database::result_set*)res_ptr;//dynamic_cast<result_set*>(res_ptr);
   int32_t sz = r->records.get_size();

   //if (reslt == NULL ) cout << "EMPTY!!!\n";
   if (r->record_header.get_size() <= 0)
   {
      r->record_header.set_size(ncol, 32);
      for (int32_t i=0; i < ncol; i++)
      {
         r->record_header[i].name = cols[i];
         if(cols[i + ncol] != NULL)
         {
            string str(cols[i + ncol]);
            str.make_lower();
            if(str == "integer")
            {
               r->record_header[i].type = database::DataTypeLong;
            }
            else if(str == "string")
            {
               r->record_header[i].type = database::DataTypeString;
            }
            else if(str == "numeric")
            {
               r->record_header[i].type = database::DataTypeDouble;
            }
         }
      }
   }


   database::SqlRecord rec;
   var v;

   if (reslt != NULL)
   {
      for (int32_t i=0; i<ncol; i++)
      {
         if (reslt[i] == NULL)
         {
            v = "";
            v.set_type(var::type_null);
         }
         else
         {
            //if(r->record_header[i].type == vmssqlite::DataTypeDouble)
            //{
              // v.SetDouble(strtod(reslt[i], NULL));
            //}
            //if(r->record_header[i].type == vmssqlite::DataTypeLong)
            //{
              // v.SetLong(atoi(reslt[i]));
            //}
            //else
            //{
              // string str;
               //::str::international::utf8_to_unicode(str, reslt[i]);
            v = reslt[i];
            //}
         }
         rec.set_at_grow(i, v);//(long)5;//reslt[i];
      }
      r->records.set_at_grow(sz, rec);
   }
   //cout <<"Fsz:"<<r->record_header.size()<<"\n";
   // cout << "Recs:"<<r->records.size() <<" m_value |" <<reslt<<"|"<<cols<<"|"<<"\n\n";
  return 0;
      //if ((strncmp("select",sql,6) == 0) || (strncmp("SELECT",sql,6) == 0))
      if(m_iLastResult = db->setErr(sqlite3_exec(handle(),sql,&callback,&m_resultsetExec,&errmsg)) == SQLITE_OK)
      {
         m_strQueryErrorMessage = "";
         m_strDatabaseErrorMessage = "";
         return true;
      }
      else
      {
         m_strQueryErrorMessage = errmsg;
         m_strDatabaseErrorMessage = db->getErrorMsg();
         TRACE("vmssqlite::set::exec: Error %s, %s", errmsg, db->getErrorMsg());
         return false;
      }
   }

   database::result_set* r = (database::result_set*)res_ptr;//dynamic_cast<result_set*>(res_ptr);
   int32_t sz = r->records.get_size();

   //if (reslt == NULL ) cout << "EMPTY!!!\n";
   if (r->record_header.get_size() <= 0)
   {
      r->record_header.set_size(ncol, 32);
      for (int32_t i=0; i < ncol; i++)
      {
         r->record_header[i].name = cols[i];
         if(cols[i + ncol] != NULL)
         {
            string str(cols[i + ncol]);
            str.make_lower();
            if(str == "integer")
            {
               r->record_header[i].type = database::DataTypeLong;
            }
            else if(str == "string")
            {
               r->record_header[i].type = database::DataTypeString;
            }
            else if(str == "numeric")
            {
               r->record_header[i].type = database::DataTypeDouble;
            }
         }
      }
   }


   database::SqlRecord rec;
   var v;

   if (reslt != NULL)
   {
      for (int32_t i=0; i<ncol; i++)
      {
         if (reslt[i] == NULL)
         {
            v = "";
            v.set_type(var::type_null);
         }
         else
         {
            //if(r->record_header[i].type == vmssqlite::DataTypeDouble)
            //{
              // v.SetDouble(strtod(reslt[i], NULL));
            //}
            //if(r->record_header[i].type == vmssqlite::DataTypeLong)
            //{
              // v.SetLong(atoi(reslt[i]));
            //}
            //else
            //{
              // string str;
               //::str::international::utf8_to_unicode(str, reslt[i]);
            v = reslt[i];
            //}
         }
         rec.set_at_grow(i, v);//(long)5;//reslt[i];
      }
      r->records.set_at_grow(sz, rec);
   }
   //cout <<"Fsz:"<<r->record_header.size()<<"\n";
   // cout << "Recs:"<<r->records.size() <<" m_value |" <<reslt<<"|"<<cols<<"|"<<"\n\n";
  return 0;  */


   bool set::sql_do_select(const char * & pszSql)
   {
      stringa straField;

      string str;


      ::str::consume_spaces(pszSql, 0);

      if(::str::begins_consume(pszSql, "*"))
      {
         ::str::consume_spaces(pszSql, 0);
      }
      else
      {
         for(;;)
         {
            str = sql_consume_field(pszSql);
            if(str.is_empty())
            {
               return false;
            }
            straField.add(str);
            try
            {
               ::str::consume(pszSql, ",");
            }
            catch(...)
            {
               break;
            }
         }
      }
      str = sql_consume_keyword(pszSql);
      if(str != "from")
         return false;

      stringa straTable;
      for(;;)
      {
         str = sql_consume_table(pszSql);
         if(str.is_empty())
         {
            return false;
         }
         straTable.add("table:" + str);
         try
         {
            ::str::consume(pszSql, ",");
         }
         catch(...)
         {
            try
            {

               str = sql_consume_keyword(pszSql);
               if(str == "inner")
               {
                  str = sql_consume_keyword(pszSql);
                  if(str != "join")
                     return false;
                  straTable.add("join:inner");
               }
               else if(str == "left")
               {
                  str = sql_consume_keyword(pszSql);
                  if(str != "outer")
                     return false;
                  str = sql_consume_keyword(pszSql);
                  if(str != "join")
                     return false;
                  straTable.add("join:left_outer");
                  return false;
               }
               else if(str == "right")
               {
                  str = sql_consume_keyword(pszSql);
                  if(str != "outer")
                     return false;
                  str = sql_consume_keyword(pszSql);
                  if(str != "join")
                     return false;
                  straTable.add("join:right_outer");
                  return false;
               }
               else if(str == "on")
               {
                  str = sql_consume_join_on(pszSql);
                  if(str.is_empty())
                     return false;
                  straTable.add("on:" + str);
               }
            }
            catch(...)
            {
               break;
            }
         }
      }

      if(straTable.get_count() == 1)
      {
         string strTable = straTable[0];
         if(::str::begins_eat_ci(strTable, "table:"))
         {
            ::simpledb::table table(dynamic_cast < ::simpledb::base * > (db), strTable);
            ::simpledb::record_row recrow;
            recrow.m_ptable = &table;
            file_position posEnd = (file_position) table.m_spfileFixed->get_length();
            table.m_spfileFixed->seek_to_begin();
            ::file::byte_stream stream((::file::stream_buffer *) table.m_spfileFixed.m_p);
            while(true)
            {
               if(table.m_spfileFixed->get_position() >= posEnd)
                  break;
               try
               {
                  recrow.read(stream);
               }
               catch(...)
               {
                  return false;
               }
               database::record rec;
               rec.::var_array::operator = (recrow.m_var.vara());
               m_resultset.records.add(rec);
               recrow.m_var.vara().remove_all();
            }
         }
      }

      return true;

   }

   bool set::sql_do_insert(const char * & pszSql)
   {

      try
      {
         string str = sql_consume_keyword(pszSql);
         if(str != "into")
            return false;

         string strTable;
         strTable = sql_consume_table(pszSql);
         if(strTable.is_empty())
         {
            return false;
         }

         str = sql_consume_keyword(pszSql);
         if(str != "values")
            return false;

         ::str::consume_spaces(pszSql, 0);

         if(!::str::begins_consume(pszSql, "("))
            return false;

         ::str::consume_spaces(pszSql, 0);

         stringa straValue;
         for(;;)
         {
            try
            {
               str = sql_consume_value(pszSql);
            }
            catch(...)
            {
               break;
            }
            straValue.add(str);
            ::str::consume_spaces(pszSql, 0);
            if(::str::begins_consume(pszSql, ")"))
               break;
            if(!::str::begins_consume(pszSql, ","))
               return false;

         }


         if(straValue.get_count() <= 0)
            return false;


         ::simpledb::table table(dynamic_cast < ::simpledb::base * > (db), strTable);
         ::simpledb::record_row rec;
         rec.m_ptable = &table;
         rec.m_var = straValue;
         table.m_spfileFixed->seek_to_end();
         ::file::byte_stream stream((::file::stream_buffer *) table.m_spfileFixed.m_p);
         rec.write(stream);

         {
            database::record rec;
            rec.add(string("one row inserted"));
            m_resultset.records.add(rec);
         }
         return true;
      }
      catch(...)
      {
         database::record rec;
         rec.add(string("could not add row"));
         m_resultset.records.add(rec);
         return false;
      }


   }

   string set::consume_quoted_value(const char * & pszXml)
   {
      const char * psz = pszXml;
      string qc = ::str::get_utf8_char(psz);
      if(qc != "\'")
      {
         throw "Quote character is required here";
      }
      string str;
      while(true)
      {
         psz = ::str::utf8_inc(psz);
         string qc2 = ::str::get_utf8_char(psz);
         //string str = ::str::international::utf8_to_unicode(qc2);
         if(qc2.is_empty())
         {
            throw "Quote character is required here, premature end";
         }
         if(qc2 == qc)
            break;
         str += qc2;
      }
      psz = ::str::utf8_inc(psz);
      pszXml = psz;
      return str;
   }

   string set::sql_consume_value(const char * & pszSql)
   {
      ::str::consume_spaces(pszSql, 0);
      string str = consume_quoted_value(pszSql);
      str.make_lower();
      return str;
   }

   string set::sql_consume_keyword(const char * & pszSql)
   {
      ::str::consume_spaces(pszSql, 0);
      string str = ::str::consume_nc_name(pszSql);
      str.make_lower();
      return str;
   }

   string set::sql_consume_field(const char * & pszSql)
   {
      ::str::consume_spaces(pszSql, 0);
      return ::str::consume_nc_name(pszSql);
   }

   string set::sql_consume_table(const char * & pszSql)
   {
      ::str::consume_spaces(pszSql, 0);
      return ::str::consume_nc_name(pszSql);
   }

   string set::sql_consume_join_on(const char * & pszSql)
   {
      UNREFERENCED_PARAMETER(pszSql);
      return "";
   }

   base * set::get_database()
   {
      return dynamic_cast < base * > (db);
   }

   void set::make_query(stringa &_sql)
   {
      string query;

      try
      {

         if(autocommit)
            db->start_transaction();

         if(db == NULL)
            throw database::DbErrors("No base Connection");

         //close();

         for (int32_t i = 0; i <_sql.get_size(); i++)
         {
            query = _sql.element_at(i);
//            char* err=NULL;
            set::parse_sql(query);
            //cout << "Executing: "<<query<<"\n\n";
/*            if (db->setErr(sqlite3_exec((::sqlite3::sqlite3 *) this->handle(),query,NULL,NULL,&err))!=SQLITE_OK)
            {
               fprintf(stderr,"Error: %s",err);
               throw database::DbErrors(db->getErrorMsg());
            }*/
         } // end of for


         if(db->in_transaction() && autocommit)
            db->commit_transaction();

         active = true;
         ds_state = database::dsSelect;
         refresh();

      } // end of try
      catch(...)
      {
         if (db->in_transaction()) db->rollback_transaction();
      }
   }


   void set::make_insert()
   {
      //make_query(insert_sql);
      last();
   }


   void set::make_edit()
   {
      //make_query(update_sql);
   }


   void set::make_deletion()
   {
      //make_query(delete_sql);
   }


   void set::fill_fields()
   {
      //cout <<"rr "<<m_resultset.records.size()<<"|" << frecno <<"\n";
      /*if ((db == NULL)
      || (m_resultset.record_header.get_size() == 0)
      || (m_resultset.records.get_size() < frecno))
         return;

      if (fields_object.get_size() == 0) // Filling columns name
      {
         fields_object.set_size(m_resultset.record_header.get_size());
         edit_object.set_size(m_resultset.record_header.get_size());
         for (int32_t i = 0; i < m_resultset.record_header.get_size(); i++)
         {
            fields_object[i].m_properties    = m_resultset.record_header[i];
            edit_object[i].m_properties      = m_resultset.record_header[i];
         }
      }

      //Filling m_resultset
      if (m_resultset.records.get_size() != 0)
      {
         for (int32_t i = 0; i < m_resultset.records[frecno].get_size(); i++)
         {
            fields_object[i].m_value   = m_resultset.records[frecno][i];
            edit_object[i].m_value     = m_resultset.records[frecno][i];
         }
      }
      else
         for (int32_t i = 0; i < m_resultset.record_header.get_size(); i++)
         {
            fields_object[i].m_value = "";
            edit_object[i].m_value = "";
         }
         */
   }



   bool set::exec()
   {
      return exec(sql);
   }

   const void * set::getExecRes()
   {
      return &m_resultsetExec;
   }


   bool set::query(const char *query)
   {
      UNREFERENCED_PARAMETER(query);
      if(db == NULL)
      {
         TRACE("set::query: base is not Defined");
         m_strQueryErrorMessage = "base is not defined";
         m_strDatabaseErrorMessage = "base is not defined";
         return false;
      }
      if(dynamic_cast<base*>(db) == NULL)
      {
         TRACE("set::query: base is not valid");
         m_strQueryErrorMessage = "base is not valid";
         m_strDatabaseErrorMessage = "base is not valid";
         return false;
      }
/*      if(dynamic_cast<base*>(db)->getHandle() == NULL)
      {
         TRACE("set::query: No base connection");
         m_strQueryErrorMessage = "No base Connection";
         m_strDatabaseErrorMessage = "No base Connection";
         return false;
      }
      if(strncmp("select",query,6) != 0)
      {
         TRACE("set::query: Must be select SQL");
         return false;
      }

      close();

      if(db->setErr(sqlite3_exec((::sqlite3::sqlite3 *) handle(),query,&callback,&m_resultset,&errmsg)) == SQLITE_OK)
      {
         m_strQueryErrorMessage = "";
         m_strDatabaseErrorMessage = "";
         active = true;
         ds_state = database::dsSelect;
         first();
         return true;
      }
      else
      {
         //m_strQueryErrorMessage = errmsg;
         //m_strDatabaseErrorMessage = db->getErrorMsg();
         //TRACE("set::query: Error: %s, %s", errmsg, db->getErrorMsg());
         //return false;
      }*/
      return false;
   }

   void set::open(const char * sql)
   {
      set_select_sql(sql);
      open();
   }

   void set::open()
   {
      if (!select_sql.is_empty())
      {
         //cout <<select_sql <<"  open\n\n";
         query(select_sql);
      }
      else
      {
         ds_state = database::dsInactive;
      }
   }


   void set::close()
   {
      ::database::set::close();
      m_resultset.record_header.remove_all();
      m_resultset.records.remove_all();
      edit_object.remove_all();
      fields_object.remove_all();
      ds_state = database::dsInactive;
      active = false;
   }


   void set::cancel()
   {
      if ((ds_state == database::dsInsert) || (ds_state==database::dsEdit))
      {
         if(m_resultset.record_header.get_size())
         {
            ds_state = database::dsSelect;
         }
         else
         {
            ds_state = database::dsInactive;
         }
      }
   }


   ::count set::num_rows()
   {
      return m_resultset.records.get_size();
   }


   bool set::eof()
   {
      return feof;
   }


   bool set::bof()
   {
      return fbof;
   }


   void set::first()
   {
      ::database::set::first();
      this->fill_fields();
      //cout << "In first "<< fields_object.size()<<"\n";
   }

   void set::last()
   {
      ::database::set::last();
      fill_fields();
   }

   void set::prev()
   {
      ::database::set::prev();
      fill_fields();
   }

   void set::next()
   {
      ::database::set::next();
      if (!eof())
         fill_fields();
   }


   bool set::seek(index pos)
   {
      if (ds_state == database::dsSelect)
      {
         set::seek(pos);
         fill_fields();
         return true;
      }
      return false;
   }



   long set::nextid(const char *seq_name)
   {
      UNREFERENCED_PARAMETER(seq_name);
/*      if(handle())
         return db->nextid(seq_name);
      else*/
         return DB_UNEXPECTED_RESULT;
   }

   bool set::remove_row()
   {
      if(feof || fbof)
      {
         return false;
      }

      m_resultset.records.remove_at(frecno);

      fbof = feof = (num_rows()==0)? true: false;

      return true;
   }

   bool set::SetFieldValue(const char *f_name, const var &value)
   {
      bool found = false;
      if(ds_state == database::dsSelect)
      {
         for (int32_t i=0; i < fields_object.get_size(); i++)
         {
            if(m_resultset.record_header[i].name == f_name)
            {
               m_resultset.records[frecno][i] = value;
               found = true;
            }
         }
         if (!found)
         {
            throw database::DbErrors("Field not found: %s",f_name);
         }
         return true;
      }
      else
      {
         return set::SetFieldValue(f_name, value);
      }
      throw database::DbErrors("Not in Insert or Edit or Select state");
      //  return false;
   }

   bool set::SetFieldValue(index iFieldIndex, const var &value)
   {
      if(ds_state == database::dsSelect)
      {
         if(iFieldIndex >= 0 && iFieldIndex < m_resultset.record_header.get_size())
         {
            m_resultset.records[frecno][iFieldIndex] = value;
            return true;
         }
         else
         {
            throw database::DbErrors("Field not found: %d",iFieldIndex);
         }
      }
      else
      {
         ASSERT(FALSE);
         //      return set::SetFieldValue(f_name, value);
      }
      throw database::DbErrors("Not in Insert or Edit or Select state");
      //  return false;
   }

   var & set::FieldValueAt(index iFieldIndex)
   {
      //if(ds_state == dsSelect)
      {
         if(iFieldIndex >= 0 && iFieldIndex < m_resultset.record_header.get_size())
         {
            return m_resultset.records[frecno][iFieldIndex];
         }
         else
         {
            throw database::DbErrors("Field not found: %d",iFieldIndex);
         }
      }
      //   else
      {
         ASSERT(FALSE);
         //return set::SetFieldValue(f_name, value);

      }
      throw database::DbErrors("Not in Insert or Edit or Select state");
      //  return false;
   }

   int32_t set::GetFieldIndex(const char *f_name)
   {
      for (int32_t i=0; i < fields_object.get_size(); i++)
      {
         if(m_resultset.record_header[i].name == f_name)
         {
            return i;

         }
      }
      return -1;
   }

   bool set::find_first(char * fieldname, var & value)
   {
      index iFound = -1;
      if(ds_state == database::dsSelect)
      {
         index i;
         for(i=0; i < fields_object.get_size(); i++)
            if(m_resultset.record_header[i].name == fieldname)
            {
               iFound = i;
               break;
            }
            if (iFound < 0) throw database::DbErrors("Field not found: %s",fieldname);
            ::count iNumRows = num_rows();
            for(i=0; i < iNumRows; i++)
               if(m_resultset.records[i][iFound] == value)
               {
                  seek(i);
                  return true;
               }

               return false;
      }
      throw database::DbErrors("not in Select state");
   }

   void set::query_items(stringa & stra, const char * pszSql)
   {
      if(query(pszSql))
      {
         first();
         while(!eof())
         {
            stra.add(FieldValueAt(0).get_string());
            next();
         }
      }
   }


   /**********************************************************************
   * Copyright (ca) 2002, Leo Seib, Hannover
   *
   * Project:CSQLiteDataset C++ Dynamic Library
   * Module: CSQLiteDataset class realisation file
   * Author: Leo Seib      E-Mail: lev@almaty.pointstrike.net
   * begin: 5/04/2002
   *
   * Permission is hereby granted, free of charge, to any person obtaining a copy
   * of this software and associated documentation files (the "Software"), to deal
   * in the Software without restriction, including without limitation the rights
   * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   * copies of the Software, and to permit persons to whom the Software is
   * furnished to do so, subject to the following conditions:
   *
   * The above copyright notice and this permission notice shall be included in
   * all copies or substantial portions of the Software.
   *
   * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
   * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   * THE SOFTWARE.
   *
   **********************************************************************/
   //************* Callback function ***************************

   int32_t callback(void * res_ptr,int32_t ncol, char** reslt,char** cols)
   {

      database::result_set* r = (database::result_set*)res_ptr;//dynamic_cast<result_set*>(res_ptr);
      ::count sz = r->records.get_size();

      //if (reslt == NULL ) cout << "EMPTY!!!\n";
      if (r->record_header.get_size() <= 0)
      {
         r->record_header.set_size(ncol, 32);
         for (index i=0; i < ncol; i++)
         {
            r->record_header[i].name = cols[i];
            if(cols[i + ncol] != NULL)
            {
               string str(cols[i + ncol]);
               str.make_lower();
               if(str == "integer")
               {
                  r->record_header[i].type = database::DataTypeLong;
               }
               else if(str == "string")
               {
                  r->record_header[i].type = database::DataTypeString;
               }
               else if(str == "numeric")
               {
                  r->record_header[i].type = database::DataTypeDouble;
               }
            }
         }
      }


      database::record rec;
      var v;

      if (reslt != NULL)
      {
         for (int32_t i=0; i<ncol; i++)
         {
            if (reslt[i] == NULL)
            {
               v = "";
               v.set_type(var::type_null);
            }
            else
            {
               //if(r->record_header[i].type == vmssqlite::DataTypeDouble)
               //{
               // v.SetDouble(strtod(reslt[i], NULL));
               //}
               //if(r->record_header[i].type == vmssqlite::DataTypeLong)
               //{
               // v.SetLong(atoi(reslt[i]));
               //}
               //else
               //{
               // string str;
               //::str::international::utf8_to_unicode(str, reslt[i]);
               v = reslt[i];
               //}
            }
            rec.set_at_grow(i, v);//(long)5;//reslt[i];
         }
         r->records.set_at_grow(sz, rec);
      }
      //cout <<"Fsz:"<<r->record_header.size()<<"\n";
      // cout << "Recs:"<<r->records.size() <<" m_value |" <<reslt<<"|"<<cols<<"|"<<"\n\n";
      return 0;
   }


} // namespace simpledb
